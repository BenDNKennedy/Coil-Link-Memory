@echo off
cd /D F:\PROJECT\CoilLink-Memory\build\zephyr\kconfig || (set FAIL_LINE=2& goto :ABORT)
"C:\Program Files\CMake\bin\cmake.exe" -E env ZEPHYR_BASE=F:/PROJECT/CoilLink-Memory/zephyr PYTHON_EXECUTABLE=C:/Users/benke/AppData/Local/Programs/Python/Python310/python.exe srctree=F:/PROJECT/CoilLink-Memory/zephyr KERNELVERSION=0x3016300 KCONFIG_CONFIG=F:/PROJECT/CoilLink-Memory/build/zephyr/.config ARCH=arm ARCH_DIR=F:/PROJECT/CoilLink-Memory/zephyr/arch BOARD_DIR=F:/PROJECT/CoilLink-Memory/zephyr/boards/arm/nucleo_l496zg BOARD_REVISION= KCONFIG_BINARY_DIR=F:/PROJECT/CoilLink-Memory/build/Kconfig ZEPHYR_TOOLCHAIN_VARIANT=zephyr TOOLCHAIN_KCONFIG_DIR=F:/PROJECT/zephyr-sdk-0.14.2/cmake/zephyr TOOLCHAIN_HAS_NEWLIB=y EDT_PICKLE=F:/PROJECT/CoilLink-Memory/build/zephyr/edt.pickle ZEPHYR_CANOPENNODE_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/canopennode ZEPHYR_CANOPENNODE_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/canopennode/Kconfig ZEPHYR_CHRE_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/chre ZEPHYR_CMSIS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/cmsis ZEPHYR_FATFS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/fs/fatfs ZEPHYR_ALTERA_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/altera ZEPHYR_ATMEL_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/atmel ZEPHYR_ESPRESSIF_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/espressif ZEPHYR_HAL_GIGADEVICE_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/gigadevice ZEPHYR_HAL_GIGADEVICE_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/hal_gigadevice/Kconfig ZEPHYR_HAL_INFINEON_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/infineon ZEPHYR_HAL_INFINEON_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/hal_infineon/Kconfig ZEPHYR_MICROCHIP_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/microchip ZEPHYR_HAL_NORDIC_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/nordic ZEPHYR_HAL_NORDIC_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/hal_nordic/Kconfig ZEPHYR_NUVOTON_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/nuvoton ZEPHYR_HAL_NXP_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/nxp ZEPHYR_HAL_NXP_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/hal_nxp/Kconfig ZEPHYR_OPENISA_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/openisa ZEPHYR_QUICKLOGIC_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/quicklogic ZEPHYR_HAL_RPI_PICO_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/rpi_pico ZEPHYR_HAL_RPI_PICO_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/hal_rpi_pico/Kconfig ZEPHYR_SILABS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/silabs ZEPHYR_ST_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/st ZEPHYR_STM32_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/stm32 ZEPHYR_HAL_TELINK_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/telink ZEPHYR_TI_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/ti ZEPHYR_XTENSA_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/xtensa ZEPHYR_LIBMETAL_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/hal/libmetal ZEPHYR_LIBLC3CODEC_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/liblc3codec ZEPHYR_LIBLC3CODEC_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/liblc3codec/Kconfig ZEPHYR_LITTLEFS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/fs/littlefs ZEPHYR_LITTLEFS_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/littlefs/Kconfig ZEPHYR_LORAMAC_NODE_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/loramac-node ZEPHYR_LORAMAC_NODE_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/loramac-node/Kconfig ZEPHYR_LVGL_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/gui/lvgl ZEPHYR_LZ4_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/lz4 ZEPHYR_LZ4_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/lz4/Kconfig ZEPHYR_MBEDTLS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/crypto/mbedtls ZEPHYR_MBEDTLS_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/mbedtls/Kconfig ZEPHYR_MCUBOOT_MODULE_DIR=F:/PROJECT/CoilLink-Memory/bootloader/mcuboot ZEPHYR_MIPI_SYS_T_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/debug/mipi-sys-t ZEPHYR_NANOPB_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/nanopb ZEPHYR_NANOPB_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/nanopb/Kconfig ZEPHYR_NRF_HW_MODELS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/bsim_hw_models/nrf_hw_models ZEPHYR_OPEN_AMP_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/open-amp ZEPHYR_OPENTHREAD_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/openthread ZEPHYR_PICOLIBC_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/picolibc ZEPHYR_SEGGER_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/debug/segger ZEPHYR_SOF_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/audio/sof ZEPHYR_TFLITE_MICRO_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/tflite-micro ZEPHYR_TFLITE_MICRO_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/tflite-micro/Kconfig ZEPHYR_TINYCBOR_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/tinycbor ZEPHYR_TINYCRYPT_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/crypto/tinycrypt ZEPHYR_TRACERECORDER_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/debug/TraceRecorder ZEPHYR_TRACERECORDER_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/TraceRecorder/Kconfig ZEPHYR_TRUSTED_FIRMWARE_M_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/tee/tf-m/trusted-firmware-m ZEPHYR_TRUSTED_FIRMWARE_M_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/trusted-firmware-m/Kconfig ZEPHYR_TF_M_TESTS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/tee/tf-m/tf-m-tests ZEPHYR_PSA_ARCH_TESTS_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/tee/tf-m/psa-arch-tests ZEPHYR_ZCBOR_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/zcbor ZEPHYR_ZCBOR_KCONFIG=F:/PROJECT/CoilLink-Memory/zephyr/modules/zcbor/Kconfig ZEPHYR_ZSCILIB_MODULE_DIR=F:/PROJECT/CoilLink-Memory/modules/lib/zscilib SHIELD_AS_LIST= DTS_POST_CPP=F:/PROJECT/CoilLink-Memory/build/zephyr/zephyr.dts.pre DTS_ROOT_BINDINGS=F:/PROJECT/CoilLink-Memory/zephyr/dts/bindings C:/Users/benke/AppData/Local/Programs/Python/Python310/python.exe F:/PROJECT/CoilLink-Memory/zephyr/scripts/kconfig/guiconfig.py F:/PROJECT/CoilLink-Memory/zephyr/Kconfig || (set FAIL_LINE=3& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%