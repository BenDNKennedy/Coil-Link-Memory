# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_GPIO_ADS1X4S0X gpio_ads1x4s0x.c)