/*
 * Copyright (c) 2018 Analog Devices Inc.
 * Copyright (C) 2021 Timberstone Tools Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_ADC_ADS1X4S0X_H_
#define ZEPHYR_DRIVERS_ADC_ADS1X4S0X_H_

#define CONFIG_ADC_ADS1X4S0X_GPIO


#include <zephyr/types.h>
#include <device.h>
#include <kernel.h>
#include <drivers/adc.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <sys/byteorder.h>
#include <sys/util.h>
#include <sys/util_macro.h>

#include "adc_context.h"

/* ADS1x4S0x register addresses */
#define ADS1X4S0X_REG_ID				0x00U
#define ADS1X4S0X_REG_STATUS			0x01U
#define ADS1X4S0X_REG_INPMUX			0x02U
#define ADS1X4S0X_REG_PGA				0x03U
#define ADS1X4S0X_REG_DATARATE			0x04U
#define ADS1X4S0X_REG_REF				0x05U
#define ADS1X4S0X_REG_IDACMAG			0x06U
#define ADS1X4S0X_REG_IDACMUX			0x07U
#define ADS1X4S0X_REG_VBIAS				0x08U
#define ADS1X4S0X_REG_SYS				0x09U
#define ADS1X4S0X_REG_OFCAL0			0x0AU
#define ADS1X4S0X_REG_OFCAL1			0x0BU
#define ADS1X4S0X_REG_OFCAL2			0x0CU
#define ADS1X4S0X_REG_FSCAL0			0x0DU
#define ADS1X4S0X_REG_FSCAL1			0x0EU
#define ADS1X4S0X_REG_FSCAL2			0x0FU
#define ADS1X4S0X_REG_GPIODAT			0x10U
#define ADS1X4S0X_REG_GPIOCON			0x11U

/* ADS1x4S0x commands */
#define ADS1X4S0X_CMD_NOP				0x00U
#define ADS1X4S0X_CMD_WAKEUP			0x02U
#define ADS1X4S0X_CMD_POWERDOWN			0x04U
#define ADS1X4S0X_CMD_RESET				0x06U
#define ADS1X4S0X_CMD_START				0x08U
#define ADS1X4S0X_CMD_STOP				0x0AU
#define ADS1X4S0X_CMD_SYOCAL			0x16U
#define ADS1X4S0X_CMD_SYGCAL			0x17U
#define ADS1X4S0X_CMD_SFOCAL			0x19U
#define ADS1X4S0X_CMD_RDATA				0x12U
#define ADS1X4S0X_CMD_RREG(x)			(0x20U | (x & GENMASK(5, 0)))
#define ADS1X4S0X_CMD_WREG(x)			(0x40U | (x & GENMASK(5, 0)))
#define ADS1X4S0X_CMD_LEN(x)			((x - 1U) & GENMASK(4, 0))

/* ADS1X4S0X_ID */
#define ADS1X4S0X_REG_ID_DEV_ID_ADS124S08	0x00U
#define ADS1X4S0X_REG_ID_DEV_ID_ADS124S06	0x01U
#define ADS1X4S0X_REG_ID_DEV_ID_ADS114S08	0x04U
#define ADS1X4S0X_REG_ID_DEV_ID_ADS114S06	0x05U

/* ADS1X4S0X_STATUS */
#define ADS1X4S0X_STATUS_FL_POR_MSK			BIT(7)
#define ADS1X4S0X_STATUS_FL_POR_MODE(x)		(((x) & BIT(0)) << 7)
#define ADS1X4S0X_STATUS_FL_POR(x)			(((x) >> 7) & BIT(0))
#define ADS1X4S0X_STATUS_RDY(x)				(((x) >> 6) & BIT(0))
#define ADS1X4S0X_STATUS_FL_P_RAILP(x)		(((x) >> 5) & BIT(0))
#define ADS1X4S0X_STATUS_FL_P_RAILN(x)		(((x) >> 4) & BIT(0))
#define ADS1X4S0X_STATUS_FL_N_RAILP(x)		(((x) >> 3) & BIT(0))
#define ADS1X4S0X_STATUS_FL_N_RAILN(x)		(((x) >> 2) & BIT(0))
#define ADS1X4S0X_STATUS_FL_REF_L1(x)		(((x) >> 1) & BIT(0))
#define ADS1X4S0X_STATUS_FL_REF_L0(x)		(((x) >> 0) & BIT(0))

/* ADS1X4S0X_INPMUX */
#define ADS1X4S0X_INPMUX_MUXP_MSK			GENMASK(7, 4)
#define ADS1X4S0X_INPMUX_MUXP_MODE(x)		(((x) & BIT_MASK(4)) << 4)
#define ADS1X4S0X_INPMUX_MUXN_MSK			GENMASK(3, 0)
#define ADS1X4S0X_INPMUX_MUXN_MODE(x)		(((x) & BIT_MASK(4)) << 0)

/* ADS1X4S0X_PGA */
#define ADS1X4S0X_PGA_DELAY_MSK				GENMASK(7,5)
#define ADS1X4S0X_PGA_DELAY_MODE(x)			(((x) & BIT_MASK(3)) << 5)
#define ADS1X4S0X_PGA_PGA_EN_MSK			GENMASK(4,3)
#define ADS1X4S0X_PGA_PGA_EN_MODE(x)		(((x) & BIT_MASK(2)) << 3)
#define ADS1X4S0X_PGA_GAIN_MSK				GENMASK(2,0)
#define ADS1X4S0X_PGA_GAIN_MODE(x)			(((x) & BIT_MASK(3)) << 0)

/* ADS1X4S0X_DATARATE */
#define ADS1X4S0X_DATARATE_G_CHOP_MSK		BIT(7)
#define ADS1X4S0X_DATARATE_G_CHOP_MODE(x)	(((x) & BIT(0)) << 7)
#define ADS1X4S0X_DATARATE_CLK_MSK			BIT(6)
#define ADS1X4S0X_DATARATE_CLK_MODE(x)		(((x) & BIT(0)) << 6)
#define ADS1X4S0X_DATARATE_MODE_MSK			BIT(5)
#define ADS1X4S0X_DATARATE_MODE_MODE(x)		(((x) & BIT(0)) << 5)
#define ADS1X4S0X_DATARATE_FILTER_MSK		BIT(4)
#define ADS1X4S0X_DATARATE_FILTER_MODE(x)	(((x) & BIT(0)) << 4)
#define ADS1X4S0X_DATARATE_DR_MSK			GENMASK(3,0)
#define ADS1X4S0X_DATARATE_DR_MODE(x)		(((x) & BIT_MASK(4)) << 0)

/* ADS1X4S0X_REF */
#define ADS1X4S0X_REF_FL_REF_EN_MSK			GENMASK(7,6)
#define ADS1X4S0X_REF_FL_REF_EN_MODE(x)		(((x) & BIT_MASK(2)) << 6)
#define ADS1X4S0X_REF_REFP_BUF_MSK			BIT(5)
#define ADS1X4S0X_REF_REFP_BUF_MODE(x)		(((x) & BIT(0)) << 5)
#define ADS1X4S0X_REF_REFN_BUF_MSK			BIT(4)
#define ADS1X4S0X_REF_REFN_BUF_MODE(x)		(((x) & BIT(0)) << 4)
#define ADS1X4S0X_REF_REFSEL_MSK			GENMASK(3,2)
#define ADS1X4S0X_REF_REFSEL_MODE(x)		(((x) & BIT_MASK(2)) << 2)
#define ADS1X4S0X_REF_REFSEL_REF0			0x00U
#define ADS1X4S0X_REF_REFSEL_REF1			0x01U
#define ADS1X4S0X_REF_REFSEL_INTERNAL		0x02U
#define ADS1X4S0X_REF_REFCON_MSK			GENMASK(1,0)
#define ADS1X4S0X_REF_REFCON_MODE(x)		(((x) & BIT_MASK(2)) << 0)

/* ADS1X4S0X_IDACMAG */
#define ADS1X4S0X_IDACMAG_FL_RAIL_EN_MSK	BIT(7)
#define ADS1X4S0X_IDACMAG_FL_RAIL_EN_MODE(x)(((x) & BIT(0)) << 7)
#define ADS1X4S0X_IDACMAG_PSW_EN_MSK		BIT(6)
#define ADS1X4S0X_IDACMAG_PSW_MODE(x)		(((x) & BIT(0)) << 6)
#define ADS1X4S0X_IDACMAG_IMAG_MSK			GENMASK(3,0)
#define ADS1X4S0X_IDACMAG_IMAG_MODE(x)		(((x) & BIT_MASK(4)) << 0)

/* ADS1X4S0X_IDACMUX */
#define ADS1X4S0X_IDACMUX_I2MUX_MSK			GENMASK(7, 4)
#define ADS1X4S0X_IDACMUX_I2MUX_MODE(x)		(((x) & BIT_MASK(4)) << 4)
#define ADS1X4S0X_IDACMUX_I1MUX_MSK			GENMASK(3, 0)
#define ADS1X4S0X_IDACMUX_I1MUX_MODE(x)		(((x) & BIT_MASK(4)) << 0)

/* ADS1X4S0X_VBIAS */
#define ADS1X4S0X_VBIAS_VB_LEVEL_MSK		BIT(7)
#define ADS1X4S0X_VBIAS_VB_LEVEL_MODE(x)	(((x) & BIT(0)) << 7)
#define ADS1X4S0X_VBIAS_VB_AINC_MSK			BIT(6)
#define ADS1X4S0X_VBIAS_VB_AINC_MODE(x)		(((x) & BIT(0)) << 6)
#define ADS1X4S0X_VBIAS_VB_AIN5_MSK			BIT(5)
#define ADS1X4S0X_VBIAS_VB_AIN5_MODE(x)		(((x) & BIT(0)) << 5)
#define ADS1X4S0X_VBIAS_VB_AIN4_MSK			BIT(4)
#define ADS1X4S0X_VBIAS_VB_AIN4_MODE(x)		(((x) & BIT(0)) << 4)
#define ADS1X4S0X_VBIAS_VB_AIN3_MSK			BIT(3)
#define ADS1X4S0X_VBIAS_VB_AIN3_MODE(x)		(((x) & BIT(0)) << 3)
#define ADS1X4S0X_VBIAS_VB_AIN2_MSK			BIT(2)
#define ADS1X4S0X_VBIAS_VB_AIN2_MODE(x)		(((x) & BIT(0)) << 2)
#define ADS1X4S0X_VBIAS_VB_AIN1_MSK			BIT(1)
#define ADS1X4S0X_VBIAS_VB_AIN1_MODE(x)		(((x) & BIT(0)) << 1)
#define ADS1X4S0X_VBIAS_VB_AIN0_MSK			BIT(0)
#define ADS1X4S0X_VBIAS_VB_AIN0_MODE(x)		(((x) & BIT(0)) << 0)

/* ADS1X4S0X_SYS */
#define ADS1X4S0X_SYS_SYS_MON_MSK			GENMASK(7, 5)
#define ADS1X4S0X_SYS_SYS_MON_MODE(x)		(((x) & BIT_MASK(3)) << 5)
#define ADS1X4S0X_SYS_CAL_SAMP_MSK			GENMASK(4, 3)
#define ADS1X4S0X_SYS_CAL_SAMPMODE(x)		(((x) & BIT_MASK(2)) << 3)
#define ADS1X4S0X_SYS_TIMEOUT_MSK			BIT(2)
#define ADS1X4S0X_SYS_TIMEOUT_MODE(x)		(((x) & BIT(0)) << 2)
#define ADS1X4S0X_SYS_CRC_MSK				BIT(1)
#define ADS1X4S0X_SYS_CRC_MODE(x)			(((x) & BIT(0)) << 1)
#define ADS1X4S0X_SYS_SENDSTAT_MSK			BIT(0)
#define ADS1X4S0X_SYS_SENDSTAT_MODE(x)		(((x) & BIT(0)) << 0)

/* ADS1X4S0X_GPIODAT */
#define ADS1X4S0X_GPIODAT_DIR_MSK			GENMASK(7, 4)
#define ADS1X4S0X_GPIODAT_DIR_MODE(x)		(((x) & BIT_MASK(4)) << 4)
#define ADS1X4S0X_GPIODAT_DIR(x)			(((x) & ADS1X4S0X_GPIODAT_DIR_MSK) >> 4)
#define ADS1X4S0X_GPIODAT_DAT_MSK			GENMASK(3, 0)
#define ADS1X4S0X_GPIODAT_DAT_MODE(x)		(((x) & BIT_MASK(4)) << 0)
#define ADS1X4S0X_GPIODAT_DAT(x)			(((x) & ADS1X4S0X_GPIODAT_DIR_MSK) >> 0)

/* ADS1X4S0X_GPIOCON */
#define ADS1X4S0X_GPIOCON_CON_MSK			GENMASK(3, 0)
#define ADS1X4S0X_GPIOCON_CON_MODE(x)		(((x) & BIT_MASK(4)) << 0)

/* Macro for checking if Data Ready IRQ is in use */
#define ADS1X4S0X_HAS_DRDY(config) (config->drdy_gpio.port != NULL)
#define ADS1X4S0X_HAS_RESET(config) (config->reset_gpio.port != NULL)

/* Maximum number of ADC channels */
#define ADS1X4S0X_MAX_CHANNELS 12

/* Maximum number of ADC inputs */
#define ADS1X4S0X_MAX_INPUTS 8

//NOTE FOR SELF:
//	- All of the following are seperate registers (ads1115 only had config/conversion)
struct ads1x4s0x_regs {
	uint8_t inpmux;
	uint8_t pga;
	uint8_t datarate;
	uint8_t ref;
	uint8_t idacmag;
	uint8_t idacmux;
	uint8_t vbias;
	uint8_t sys;
	uint8_t ofcal[3];
	uint8_t fscal[3];
#ifdef CONFIG_ADC_ADS1X4S0X_GPIO
	uint8_t gpiodat;
	uint8_t gpiocon;
#endif /* CONFIG_ADC_ADS1X4S0X_GPIO */
};

struct ads1x4s0x_config {
	struct spi_dt_spec bus;
	struct gpio_dt_spec drdy_gpio;
	struct gpio_dt_spec reset_gpio;
};

struct ads1x4s0x_data {
	struct adc_context ctx;
	const struct device *dev;
	struct gpio_callback drdy_gpio_cb;
	int32_t *buffer;
	int32_t *repeat_buffer;
	uint8_t resolution;
	uint32_t channels;
	bool calibrate;
	uint8_t channel_odr[ADS1X4S0X_MAX_CHANNELS];
	struct ads1x4s0x_regs shadow;
#ifdef CONFIG_ADC_ADS1X4S0X_GPIO
	struct k_mutex gpio_lock;
#endif /* CONFIG_ADC_ADS1X4S0X_GPIO */
	struct k_thread thread;
	struct k_sem acq_sem;
	struct k_sem drdy_gpio_sem;

	K_KERNEL_STACK_MEMBER(stack,
			CONFIG_ADC_ADS1X4S0X_ACQUISITION_THREAD_STACK_SIZE);
};

#endif /* ZEPHYR_DRIVERS_ADC_ADS1X4S0X_H_ */