/*
 * Sched.c
 *
 *  Created on: Apr 3, 2022
 *      Author: Romario
 */

#include "Std_types.h"
#include "Systick.h"
#include "Sched.h"
#include "Sched_cfg.h"

#include "diag/Trace.h"
extern enuRunnable_t runnableList[SCHED_RUNNABLE_COUNT];

void Sched_vidInit(){

	/* INITALIZE SYSTICK TIMER */
	SYSTICK_vidInit();

    /* CONFIGURE TICK TIME */
	SYSTICK_enuSetTickTimeMS(SCHED_TICK_MS,16000000);

	/* SET CALLBACK FUNCTION */
	SYSTICK_enuRegisterCallback(sched);
}

void Sched_vidStart(){

	/* START SYSTICK TIMER */
	SYSTICK_enuStart();

	/* POLLING TILL NEW TICK */
	while(1);
}


void sched(void){

	/* STATIC VARIABLE : TO INCREAMENT SCHEDULER TIME */
	static u32 Loc_u32TimeMs;

	/* LOCAL VARIABLE : TO ITERATE THROUGH THE LIST OF THE RUNNABLE */
	u8 Loc_u8RunnableIndex=0;

	/* INTERATE THROUGHT ALL THE RUNNABLE, BY PRIORITY */
	for(Loc_u8RunnableIndex=0;Loc_u8RunnableIndex<SCHED_RUNNABLE_COUNT;Loc_u8RunnableIndex++){

		/* CHECKING IF TASK WOULD RUN */
		if((Loc_u32TimeMs % runnableList[Loc_u8RunnableIndex].Sched_enuCyclicTimeMs) == 0){
			/* CALL THE FUNCTION OF THE TASK */
			(runnableList[Loc_u8RunnableIndex].callBackFuction)();
		}
	}

    /* INCREAMENT BY THE SCHEDULER TICK TIME */
	Loc_u32TimeMs += SCHED_TICK_MS;
}




