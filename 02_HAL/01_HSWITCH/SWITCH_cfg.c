
#include "Std_types.h"
#include "GPIO.h"

#include "SWITCH.h"
#include "SWITCH_cfg.h"

const switchcfg_t SWITCHS [SWITCH_NUM] = {

		[SWITCH_START] = {
				.Port = GPIO_PORTA,
				.Pin  = GPIO_PIN1,
				.mode = GPIO_MODE_INPUT_PD
		}
};
