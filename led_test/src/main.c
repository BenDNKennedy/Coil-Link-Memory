//Test committ
//Test committ

//Standard includes
#include <stdio.h>
#include <math.h>

//Necessary drivers to blink LEDs
#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>

//Define constants
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define sleep_time 500

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
//static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
//static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

void main(void)	
{
	int ret;

	if (!device_is_ready(led0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	//ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	//ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&led0);
		//ret = gpio_pin_toggle_dt(&led1);
		//ret = gpio_pin_toggle_dt(&led2);

		printk("Test Text %s\n", CONFIG_BOARD);

		if (ret < 0) {
			return;
		}
		k_msleep(sleep_time);
	}
}
