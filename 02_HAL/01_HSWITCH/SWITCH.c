
#include "Std_types.h"
#include "GPIO.h"

#include "SWITCH.h"
#include "SWITCH_cfg.h"

/* POINTER : switchcbf_t type */
static switchcbf_t APPCallBackFunction;

extern switchcfg_t SWITCHS [SWITCH_NUM];

static SWITCH_enuState SWITCH_status[SWITCH_NUM];

void SWITCH_vidInit(void){

	u8 Loc_u8SwitchIndex = 0;

	GPIOPortConfg_t cfg;

	/* ITERATE THROUGH ALL THE LEDS */
	for(Loc_u8SwitchIndex=0;Loc_u8SwitchIndex<SWITCH_NUM;Loc_u8SwitchIndex++){

		/* SET THE CONFIGURATION OF THE PORTS */

		/* CHECKING THE MODE */
		if(SWITCHS[Loc_u8SwitchIndex].mode == SWITCH_MODE_PU){

			/* 1 : INPUT PULL UP MODE */
			cfg.GPIOMode = GPIO_MODE_INPUT_PU;
		}
		else if(SWITCHS[Loc_u8SwitchIndex].mode == SWITCH_MODE_PD){

			/* 2 : INPUT PULL DOWN MODE */
			cfg.GPIOMode = GPIO_MODE_INPUT_PD;
		}

		else if(SWITCHS[Loc_u8SwitchIndex].mode == SWITCH_MODE_FLOATING){

			/* 3 : INPUT FLOATING MODE */
			cfg.GPIOMode = GPIO_MODE_INPUT_FLOATING;
		}


		cfg.GPIOPort = SWITCHS[Loc_u8SwitchIndex].Port;
		cfg.GPIOPin = SWITCHS[Loc_u8SwitchIndex].Pin;

		/* INITIALIZE GPIO PORTS */
		Gpio_enuInit(&cfg);
	}
}

SWITCH_enuErrorStatus SWITCH_enuGetStatus(u8 Copy_u8SwitchNumber, SWITCH_enuState* Add_SwitchStatus){

	SWITCH_enuErrorStatus Ret_enuErrorStatus = SWITCH_enuOk;

	/* VALIDATION : CHECK THE SWITCH NUMBER */
	if(Copy_u8SwitchNumber > SWITCH_NUM){
		Ret_enuErrorStatus = SWITCH_enuSwitchNumberError;
	}

	/* VALIDATION : CHECK THE SWITCH STATUS POINTER */
	else if(Add_SwitchStatus == NULL){
		Ret_enuErrorStatus = SWITCH_enuNULLPointer;
	}

	else{

		/* SET THE STATUS */
        *Add_SwitchStatus = SWITCH_status[Copy_u8SwitchNumber];
	}

    return Ret_enuErrorStatus;
}

void SWITCH_task(void){

	/* STATIC : COUNT NUMBER OF SIMILAR STATUS */
	static u8 SWITCH_u8Counter[SWITCH_NUM];

	/* STATIC : SAVE THE PREVIOUS STATUS */
	static SWITCH_enuState SWITCH_enuPreviousValue[SWITCH_NUM];

	/* LOCAL : TO GET THE CURRENT STATUS */
	SWITCH_enuState Loc_enuCurrentValue[SWITCH_NUM];

	u16 Loc_u16SwitchIndex = 0;

	/* ITERATE THROUGH ALL THE SWITCHES */
	for(Loc_u16SwitchIndex=0;Loc_u16SwitchIndex<SWITCH_NUM;Loc_u16SwitchIndex++){

		 /* GET THE VALUE OF THE SWITCH */
		 Gpio_enuGetBit(SWITCHS[Loc_u16SwitchIndex].Port, SWITCHS[Loc_u16SwitchIndex].Pin, &Loc_enuCurrentValue[Loc_u16SwitchIndex]);

		 /* 1: CURRENT VALUE IS EQUAL THE PREVIOUS ONE */
		 if(Loc_enuCurrentValue[Loc_u16SwitchIndex] == SWITCH_enuPreviousValue[Loc_u16SwitchIndex]){

			 /* INCREAMENT THE COUNTER */
			 SWITCH_u8Counter[Loc_u16SwitchIndex]++;
		 }

		 /* 2:  CURRENT VALUE NOT EQUAL THE PREVIOUS ONE */
		 else{

			 /* SET THE COUNTER BY ZERO */
			 SWITCH_u8Counter[Loc_u16SwitchIndex] = 0;
		 }

		 /* IF THE COUNTER EQUAL 5 STAMPS */
		 if(SWITCH_u8Counter[Loc_u16SwitchIndex] == 5){

			 /* SET THE STATUS OF THE SWITCH AS A CURRENT VALUE */
			 SWITCH_status[Loc_u16SwitchIndex] = Loc_enuCurrentValue[Loc_u16SwitchIndex];

			 /* SET THE COUNTER BY ZERO */
			 SWITCH_u8Counter[Loc_u16SwitchIndex] = 0;
		 }

		 /* SET THE PREVIOUS VALUE AS A CURRENT TO GET A NEW ONE */
		 SWITCH_enuPreviousValue[Loc_u16SwitchIndex] = Loc_enuCurrentValue[Loc_u16SwitchIndex];
	}

}

SWITCH_enuErrorStatus SWITCH_enuRegisterCallback(switchcbf_t Copy_callBackFunction){

	SWITCH_enuErrorStatus Ret_enuErrorStatus = SWITCH_enuOk;

	/* ASSIGN THE FUNCTION TO THE POINTER */
	if(Copy_callBackFunction){

		APPCallBackFunction = Copy_callBackFunction;

		Ret_enuErrorStatus = SWITCH_enuOk;
	}

	else{
		Ret_enuErrorStatus = SWITCH_enuNULLPointer;
	}

	return Ret_enuErrorStatus;
}
