#include "Std_types.h"
#include "Systick.h"
#include "Systick_cfg.h"
#include "Systick_priv.h"

/* POINTER : systickcbf_t type */
static systickcbf_t APPCallBackFunction;

void SYSTICK_vidInit(){

	/* SET CLOCK SOURCE */
	STK_CTRL |= SYSTICK_CLK_SOURCE;

	/* SET INTURRUPT MODE */
	STK_CTRL |= SYSTICK_TICK_INT;
}


SYSTICK_enuErrorStatus SYSTICK_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock){

	SYSTICK_enuErrorStatus Ret_enuErrorStatus = Systick_enuNOK;
	u32 Loc_u32LoadValue = 0;

	/* CLOCK SOURCE -> SYSTICK_CLK_SOURCE_AHB */
	if( STK_CTRL & SYSTICK_CLK_SOURCE_AHB ){

		/* CALCULATE THE LOAD VALUE */
		Loc_u32LoadValue = (((u64)Copy_u16TickTime) * (u64)Copy_u32Clock)/1000;
		Ret_enuErrorStatus = Systick_enuOK;
	}

	/* CLOCK SOURCE -> SYSTICK_CLK_SOURCE_AHB_DIV_BY_8 */
	else{

		/* CALCULATE THE LOAD VALUE */
		Loc_u32LoadValue = (((u64)Copy_u16TickTime * (u64)Copy_u32Clock)/(u64) 8000);
		Ret_enuErrorStatus = Systick_enuOK;
	}

	/* SET THE VALUE ON THE REGISTER */
	STK_LOAD = Loc_u32LoadValue;

	return Ret_enuErrorStatus;
}

SYSTICK_enuErrorStatus SYSTICK_enuStart(){
	SYSTICK_enuErrorStatus Ret_enuErrorStatus = Systick_enuOK;

	/* CLEAR VAL REGISTER */
	STK_VAL = 0;

	/* ENABLE SYSTICK */
	STK_CTRL |= STK_ENABLE_MASK;

	return Ret_enuErrorStatus;
}


SYSTICK_enuErrorStatus SYSTICK_enuRegisterCallback(systickcbf_t Copy_callBackFunction){

	SYSTICK_enuErrorStatus Ret_enuErrorStatus = Systick_enuNOK;

	/* ASSIGN THE FUNCTION TO THE POINTER */
	if(Copy_callBackFunction){

		APPCallBackFunction = Copy_callBackFunction;

		Ret_enuErrorStatus = Systick_enuOK;
	}

	else{
		Ret_enuErrorStatus = Systick_enuNOK;
	}

	return Ret_enuErrorStatus;
}

void SysTick_Handler (void){

	/* CHECKING IF THE USER SET THE VALUE */
	if(APPCallBackFunction){

		/* CALL THE FUNCTION */
		APPCallBackFunction();
	}

}
