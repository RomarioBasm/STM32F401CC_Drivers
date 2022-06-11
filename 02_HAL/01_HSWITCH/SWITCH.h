#ifndef _SWITCH_H_
#define _SWITCH_H_

typedef struct {
	u8 Port;
	u8 Pin;
	u8 mode;
}switchcfg_t;

typedef enum{
	SWITCH_enuPortError,
	SWITCH_enuPinError,
	SWITCH_enuNULLPointer,
	SWITCH_enuSwitchNumberError,
	SWITCH_enuSwitchModeError,
	SWITCH_enuOk
}SWITCH_enuErrorStatus;


typedef enum{
	SWITCH_enuReleased,
	SWITCH_enuPressed
}SWITCH_enuState;

typedef void (*switchcbf_t) (void);

/* SWITCH STATE */
#define SWITCH_STATE_ON 0
#define SWITCH_STATE_OFF 1


/* SWITCH MODE */
#define SWITCH_MODE_PU 0
#define SWITCH_MODE_PD 1
#define SWITCH_MODE_FLOATING 2


/* FUNCTIONS */
extern void SWITCH_vidInit(void);
SWITCH_enuErrorStatus SWITCH_enuGetStatus(u8 Copy_u8SwitchNumber, SWITCH_enuState* Add_SwitchStatus);
void SWITCH_task(void);

#endif
