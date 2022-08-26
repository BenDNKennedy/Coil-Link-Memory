# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(BOARD nucleo_l496zg)

find_package(Zephyr)
project(app)

target_sources(app PRIVATE src/main.c)