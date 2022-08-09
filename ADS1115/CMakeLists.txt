# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(BOARD nucleo_l496zg)

find_package(Zephyr)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.c)

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_ADC_ADS1x1x		src/main.c)
