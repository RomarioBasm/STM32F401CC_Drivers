#include "Std_types.h"
#include "GPIO.h"
#include "LED.h"
#include "LED_cfg.h"

const ledcfg_t leds[LEDS_NUM] = {

		[LED_START] = {
				.Port = GPIO_PORTA,
				.Pin =  GPIO_PIN0,
				.active_state = ACTIVE_STATE_HIGH,
				.otype = GPIO_MODE_OUTPUT_PP,
				.Speed = GPIO_OUTPUT_SPEED_HIGH,
		      }
};
