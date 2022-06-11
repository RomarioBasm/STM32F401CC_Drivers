#ifndef _LED_H_
#define _LED_H_

typedef struct {
	u8 Port;
	u8 Pin;
	u8 active_state;
	u8 otype;
	u8 Speed;
}ledcfg_t;

typedef enum{
	Res_PortError,
	Res_PinError,
	Res_StateError,
	Res_LedNumberError,
	Res_Ok,
	Res_NotOk
}Res_t;


typedef void (*ledcbf_t) (void);

/* LET STATE */
#define LED_STATE_ON 0
#define LED_STATE_OFF 1

/* LED MODE */
#define ACTIVE_STATE_HIGH 0
#define ACTIVE_STATE_LOW 1

/* LED TYPE */
#define OTYPE_PP 0
#define OTYPE_OD 1

/* LED SPEED */
#define LED_SPEED_LOW  0
#define LED_SPEED_MEDIUM  1
#define LED_SPEED_HIGH  2
#define LED_SPEED_VERYHIGH  3


/* FUNCTIONS */
extern Res_t led_init(void);
extern Res_t led_setLedState(u16 led, u8 ledstate);
extern Res_t LED_enuRegisterCallback(ledcbf_t Copy_callBackFunction);


#endif
