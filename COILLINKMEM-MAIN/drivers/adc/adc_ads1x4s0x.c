/*
 * Copyright (c) 2021 Rubus Technologies Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ADC driver for the ADS1x4S0x ADC.
 */

#include <drivers/adc.h>
#include <drivers/adc/ads1x4s0x.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <kernel.h>
#include <sys/byteorder.h>
#include <sys/crc.h>
#include <zephyr.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(ADS1X4S0X, CONFIG_SENSOR_LOG_LEVEL);

#define ADC_CONTEXT_USES_KERNEL_TIMER
#include "adc_context.h"

#include "adc_ads1x4s0x.h"

static int ads1x4s0x_init(const struct device *dev)
{
	//Creates pointer to ads1x4s0x_config struct. Sets pointer (*config) to config member from dev struct.
	const struct ads1x4s0x_config *config = dev->config; 

	//Creates pointer to ads1x4s0x_data struct. Sets pointer (*data) to config member from dev struct.
	struct ads1x4s0x_data *data = dev->config;			 

	//8 bit integer for device id
	uint8_t dev_id; 

	//Integer for error code
	int err;

	//Gets member dev that struct data points to. Set to dev.
	data->dev = dev;

	//Initializes two semaphore objects, then configures them as
	//binary semaphores by setting their count to 0 and their limit to 1
	k_sem_init(&data->acq_sem, 0, 1);
	k_sem_init(&data->drdy_gpio_sem, 0, 1);

#ifdef CONFIG_ADC_ADS1X4S0X_GPIO

	//Initializes a mutex object with gpio_lock address
	k_mutex_init(&data->gpio_lock);

#endif /* CONFIG_ADC_ADS1X4S0X_GPIO */
	
	//Validates that ads1x4s0x bus is ready. If it isn't,
	//return error number 19 ENODEV (No such device)
	if (!spi_is_ready(&config->bus)) {
		LOG_ERR("SPI bus %s not ready", config->bus.bus->name);
		return -ENODEV;
	}

	//If data ready IRQ is in use (Reset GPIO pin isn't NULL)...
	if (ADS1X4S0X_HAS_RESET(config)) {
		//Configure a single pin (RESET) from gpio_dt_spec in ads1x4s0x_config struct
		err = gpio_pin_configure_dt(&config->reset_gpio, GPIO_OUTPUT);
		//If pin configuration fails, return error number 22 EINVAL (Invalid argument)
		if (err) {
			LOG_ERR("failed to configure RESET GPIO pin (err %d)", err);
			return -EINVAL;
		}

	//Attempts to reset the device, returns error if it fails
	err = ads1x4s0x_reset(dev);
	if(err){
		LOG_ERR("failed to request reset (err %d)", err);
		return err;
	}

	//Attemps to read from the ADS1x4S0x using the reg id (), returns error if it fails
	err = ads1x4s0x_read_reg(dev, ADS1X4S0X_REG_ID, &dev_id);
	if(err){
		return err
	}	

	/*
	Configures channels and bit resolution based on the device id
	ADS114S06 -> 6 channels   16 bits
	ADS114S08 -> 12 channels  16 bits
	ADS124S06 -> 6 channels   24 bits
	ADS124S08 -> 12 channels  24 bits
	*/
	switch (dev_id) {
		case ADS1X4S0X_REG_ID_DEV_ID_ADS124S08:
			data->resolution = 24;
			data->channels = 12;
			break;
		case ADS1X4S0X_REG_ID_DEV_ID_ADS124S06:
			data->resolution = 24;
			data->channels = 6;
			break;
		case ADS1X4S0X_REG_ID_DEV_ID_ADS114S08:
			data->resolution = 16;
			data->channels = 12;
			break;
		case ADS1X4S0X_REG_ID_DEV_ID_ADS114S06:
			data->resolution = 16;
			data->channels = 6;
			break;
		default:
			LOG_ERR("Unsupported device ID: %04X", dev_id);
			return err;
	}

	//Attemps to read multiple registers from the ADS1x4S0x, returns error if it fails
	err = ads1x4s0x_read_reg_multiple(dev, ADS1X4S0X_REG_INPMUX, &data->shadow, sizeof(data->shadow));
	if (err) {
		return err;
	}	

	//If Cyclic Redundancy Check (address 09h, bit 1)
	if (IS_ENABLED(CONFIG_ADC_ADS1X4S0X_CRC)) {
		modify_reg(&data->shadow.sys, ADS1X4S0X_SYS_CRC_MSK, ADS1X4S0X_SYS_CRC_MODE(1));
	}	

	//If ADS1X4S0X has DRDY pin (D10 on NucleoL496ZG)
	if (ADS1X4S0X_HAS_DRDY(config)) {
		//Print and return an error if the DRDY pin wasn't configured properly
		err = gpio_pin_configure_dt(&config->drdy_gpio, GPIO_INPUT);
		if (err) {
			LOG_ERR("failed to configure DRDY GPIO pin (err %d)",
				err);
			return -EINVAL;
		}

		//Helps initialize a struct gpio_callback 
		gpio_init_callback(&data->drdy_gpio_cb,				//Valid app's callback structure pointer
							ads1x4s0x_drdy_gpio_callback, 	//Valid handler function pointer
							BIT(config->drdy_gpio.pin));	//Bit mask of relevent handler pins (drdy gpio)

		//Add application callback using the drdy pin as the port (pointer to the device structure for the driver instance),
		//and as a valid application's callback structure pointer
		err = gpio_add_callback(config->drdy_gpio.port, &data->drdy_gpio_cb);
		//Return -EINVAL (Invalid argument) if it fails
		if (err) {
			LOG_ERR("failed to add DRDY callback (err %d)", err);
			return -EINVAL;
		}

		//Configures pin interrupts from "gpio_dt_spec" 
		err = gpio_pin_interrupt_configure_dt(&config->drdy_gpio, 		 //GPIO specification from devicetree
											   GPIO_INT_EDGE_TO_ACTIVE); //interrupt configuration flags
		if (err) {
			LOG_ERR("failed to configure DRDY interrupt (err %d)",
				err);
			return -EINVAL;
		}
	}

	//Initializes thread tid, then schedules it for execution.
	const k_tid_t tid = k_thread_create(&data->thread, 										//Pointer to uninitialized struct k_thread
										data->stack,										//Pointer to the stack space
			      						CONFIG_ADC_ADS1X4S0X_ACQUISITION_THREAD_STACK_SIZE,	//Stack size in bytes
			      						(k_thread_entry_t)ads1x4s0x_acquisition_thread,		//Thread entry function
			      						data, 												//1st entry point parameter (Using)
										NULL, NULL,											//2nd and 3rd entry point parameters (Not using) 
			      						CONFIG_ADC_ADS1X4S0X_ACQUISITION_THREAD_PRIO,		//Thread priority
			      						0, 													//Thread options
										K_NO_WAIT);											//Scheduling delay (K_NO_WAIT = No delay)
	//Sets name of thread tid to "adc_ads1x4s0x"
	k_thread_name_set(tid, "adc_ads1x4s0x");

	//Puts device in power-down until ready to make a measurement
	err = ads1x4s0x_write_cmd(dev, ADS1X4S0X_CMD_POWERDOWN);
	if (err) {
		LOG_ERR("failed to request power down mode (err %d)", err);
		return err;
	}

	adc_context_unlock_unconditionally(&data->ctx);

	return 0;
};


