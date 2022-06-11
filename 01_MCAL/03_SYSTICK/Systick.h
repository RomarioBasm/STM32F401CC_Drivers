#ifndef _SYSTICK_H_
#define _SYSTICK_H_

typedef void (*systickcbf_t) (void);


#define SYSTICK_TICK_INT_OFF               0x00000000
#define SYSTICK_TICK_INT_ON                0x00000002

#define SYSTICK_CLK_SOURCE_AHB_DIV_BY_8    0x00000000
#define SYSTICK_CLK_SOURCE_AHB             0x00000004

typedef enum{
	Systick_enuOK,
	Systick_enuNOK
}SYSTICK_enuErrorStatus;


void SYSTICK_vidInit();
SYSTICK_enuErrorStatus SYSTICK_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock);
SYSTICK_enuErrorStatus SYSTICK_enuStart();
SYSTICK_enuErrorStatus SYSTICK_enuRegisterCallback(systickcbf_t cbf);
void SYSTICK_Handler (void);


#endif
