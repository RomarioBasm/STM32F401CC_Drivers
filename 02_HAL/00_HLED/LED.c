
#include "Std_types.h"
#include "Bit_utils.h"
#include "GPIO.h"

#include "LED.h"
#include "LED_cfg.h"
#include "diag/Trace.h"
/* POINTER : ledcbf_t type */
static ledcbf_t APPCallBackFunction;
extern const ledcfg_t leds[LEDS_NUM];

Res_t led_init(void){

	u8 Loc_u8LedIndex = 0;

	Res_t returnErrorState = Res_Ok;
	GPIOPortConfg_t cfg;

	/* ITERATE THROUGH ALL THE LEDS */
	for(Loc_u8LedIndex=0;Loc_u8LedIndex<LEDS_NUM;Loc_u8LedIndex++){

		/* SET THE CONFIGURATION OF THE PORTS */

		/* CHECKING THE MODE */
		if(leds[Loc_u8LedIndex].otype == GPIO_MODE_OUTPUT_PP){

			/* 1 : PUSHPULL MODE */
			cfg.GPIOMode = GPIO_MODE_OUTPUT_PP;
		}
		else{

			/* 2 : OPENDRAIN MODE */
			cfg.GPIOMode = GPIO_MODE_OUTPUT_OPENDRAIN;
		}

		cfg.GPIOPort = leds[Loc_u8LedIndex].Port;
		cfg.GPIOPin = leds[Loc_u8LedIndex].Pin;
		cfg.GPIOSpeed = leds[Loc_u8LedIndex].Speed;

		/* INITIALIZE GPIO PORTS */
		Gpio_enuInit(&cfg);
	}

	return returnErrorState;
}


Res_t led_setLedState(u16 Copy_u8Led, u8 Copy_u8LedState){

	Res_t returnErrorState = Res_NotOk;

	/* VALIDATION : CHECK THE NUMBER OF LEDS */
	if(Copy_u8Led > LEDS_NUM){
		returnErrorState = Res_LedNumberError;
	}

	/* VALIDATION : CHECK THE STATES */
	else if(Copy_u8LedState != LED_STATE_ON && Copy_u8LedState != LED_STATE_OFF){
		returnErrorState = Res_StateError;
	}

	else{

		returnErrorState = Res_Ok;
		trace_printf("%d \n", Copy_u8LedState ^ leds[Copy_u8Led].active_state);
		/* SET THE STATE OF THE LED */
		Gpio_enuSetBit(leds[Copy_u8Led].Port,leds[Copy_u8Led].Pin, Copy_u8LedState ^ leds[Copy_u8Led].active_state);
	}

	return returnErrorState;

}

Res_t LED_enuRegisterCallback(ledcbf_t Copy_callBackFunction){

	Res_t Ret_enuErrorStatus = Res_Ok;

	/* ASSIGN THE FUNCTION TO THE POINTER */
	if(Copy_callBackFunction){

		APPCallBackFunction = Copy_callBackFunction;

		Ret_enuErrorStatus = Res_Ok;
	}

	else{
		Ret_enuErrorStatus = Res_NotOk;
	}

	return Ret_enuErrorStatus;
}
