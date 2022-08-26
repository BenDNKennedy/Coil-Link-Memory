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
	//Creates pointer to ads1x4s0x_data struct. Sets pointer (*data) to config member from dev struct.
	const struct ads1x4s0x_config *config = dev->config; 
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

	

	}
};
