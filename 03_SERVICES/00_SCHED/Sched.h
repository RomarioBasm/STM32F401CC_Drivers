/*
 * Sched.h
 *
 *  Created on: Apr 3, 2022
 *      Author: Romario
 */

#ifndef SCHED_H_
#define SCHED_H_

typedef struct {
	void (*callBackFuction)(void);
	u32 Sched_enuCyclicTimeMs;
}enuRunnable_t;

typedef enum {
  SCHED_enuOK,
  SCHED_enuErrorPriority
}SCHED_enuErrorStatus;

void Sched_vidInit();
void Sched_vidStart();
SCHED_enuErrorStatus Sched_vidRegisterRunnable(enuRunnable_t * Add_prunnable, u32 Copy_u32Priority);
void sched(void);
#endif /* SCHED_H_ */
