zephyr_library()

zephyr_library_sources_ifdef(CONFIG_ADC_ADS1X1X adc_ads1x1x.c)
zephyr_library_sources_ifdef(CONFIG_ADC_ADS1X4S0X adc_ads1x4s0x.c)