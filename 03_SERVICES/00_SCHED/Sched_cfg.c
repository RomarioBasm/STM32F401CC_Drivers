/*
 * Sched_cfg.c
 *
 *  Created on: Apr 3, 2022
 *      Author: Romario
 */

#include "Std_types.h"
#include "GPIO.h"
#include "Sched.h"
#include "App.h"
#include "Sched_cfg.h"


const enuRunnable_t runnableList[SCHED_RUNNABLE_COUNT] = {


		[0] = {
				.callBackFuction = APP_Task,
				.Sched_enuCyclicTimeMs = 1000,
		}
};

