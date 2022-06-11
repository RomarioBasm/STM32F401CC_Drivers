#ifndef _GPIO_H_
#define _GPIO_H_
/* PORT CONFIGURATION */

typedef struct{
	u8 GPIOMode;
	u8 GPIOSpeed;
	u8 GPIOPort;
	u16 GPIOPin;
}GPIOPortConfg_t;


/* ERROR STATUS */
typedef enum{
	Gpio_enuOK,
	Gpio_enuPortError,
	Gpio_enuPinError,
	Gpio_enuSpeedError,
	Gpio_enuValueError,
	Gpio_enuWrongConfig
}enuGpioErrorStatus ;


#define	GPIO_PORTA		    0
#define	GPIO_PORTB		    1
#define	GPIO_PORTC		    2
#define	GPIO_PORTD          3
#define	GPIO_PORTE		    4
#define	GPIO_PORTH          5

#define GPIO_PIN0			((u16)0x0001)
#define GPIO_PIN1			((u16)0x0002)
#define GPIO_PIN2			((u16)0x0004)
#define GPIO_PIN3			((u16)0x0008)
#define GPIO_PIN4			((u16)0x0010)
#define GPIO_PIN5			((u16)0x0020)
#define GPIO_PIN6			((u16)0x0040)
#define GPIO_PIN7			((u16)0x0080)
#define GPIO_PIN8			((u16)0x0100)
#define GPIO_PIN9			((u16)0x0200)
#define GPIO_PIN10			((u16)0x0400)
#define GPIO_PIN11			((u16)0x0800)
#define GPIO_PIN12			((u16)0x1000)
#define GPIO_PIN13			((u16)0x2000)
#define GPIO_PIN14			((u16)0x4000)
#define GPIO_PIN15			((u16)0x8000)


#define GPIO_PORTS_COUNT 5
#define GPIO_PINS_COUNT 15

/* MODE CONFIGURATION */
#define GPIO_MODE_INPUT_FLOATING 			0b00000
#define GPIO_MODE_INPUT_PU					0b00001
#define GPIO_MODE_INPUT_PD                	0b00010

#define GPIO_MODE_OUTPUT_PP					0b01000
#define GPIO_MODE_OUTPUT_PP_PU        		0b01001
#define GPIO_MODE_OUTPUT_PP_PD      		0b01010

#define GPIO_MODE_OUTPUT_OPENDRAIN			0b01100
#define GPIO_MODE_OUTPUT_OPENDRAIN_PU       0b01101
#define GPIO_MODE_OUTPUT_OPENDRAIN_PD     	0b01110

#define GPIO_MODE_AF_PP						0b10000
#define GPIO_MODE_AF_PP_PU            		0b10001
#define GPIO_MODE_AF_PP_PD          		0b10010
#define GPIO_MODE_AF_OPENDRAIN				0b10100
#define GPIO_MODE_AF_OPENDRAIN_PU           0b10101
#define GPIO_MODE_AF_OPENDRAIN_PD         	0b10110

#define GPIO_MODE_ANALOG					0b11000


/* SPEED CONFIGURATION */
#define GPIO_OUTPUT_SPEED_LOW			    0b00
#define GPIO_OUTPUT_SPEED_MEDIUM		    0b01
#define GPIO_OUTPUT_SPEED_HIGH			    0b10
#define GPIO_OUTPUT_SPEED_VERYHIGH          0b11

#define GPIO_PIN_NUM 15

#define GPIO_FALSE 0
#define GPIO_TRUE  1

#define GPIO_VALUE_RESET 0
#define GPIO_VALUE_SET 1


/****************************** Gpio_enuInit *******************************************
* @description  :  Initialize the ports of the GPIO peripheral ------------------------*
* @param        :        Add_strPortConfg (GPIOPortConfg_t) : structure	               *
* 	                            GPIOMode :  GPIO_MODE_INPUT_FLOATING                   *
*                                       GPIO_MODE_INPUT_PU                             *
*                                       GPIO_MODE_INPUT_PD                             *
*                                       GPIO_MODE_OUTPUT_PP                            *
*                                       GPIO_MODE_OUTPUT_PP_PU                         *
*                                       GPIO_MODE_OUTPUT_PP_PD                         *
*                                       GPIO_MODE_OUTPUT_OPENDRAIN                     *
*                                       GPIO_MODE_OUTPUT_OPENDRAIN_PU                  *
*                                       GPIO_MODE_OUTPUT_OPENDRAIN_PD                  *
*                                       GPIO_MODE_AF_PP	                               *
*                                       GPIO_MODE_AF_PP_PU                             *
*                                       GPIO_MODE_AF_PP_PD                             *
*                                       GPIO_MODE_AF_OPENDRAIN                         *
*                                       GPIO_MODE_AF_OPENDRAIN_PU                      *
*                                       GPIO_MODE_AF_OPENDRAIN_PD                      *
*                                                                                      *
*                              GPIOSpeed : GPIO_OUTPUT_SPEED_LOW                       *
*                                       GPIO_OUTPUT_SPEED_MEDIUM                       *
*                                       GPIO_OUTPUT_SPEED_HIGH                         *
*                                       GPIO_OUTPUT_SPEED_VERYHIGH                     *
*                                                                                      *
*                               GPIOPort  : GPIO_PORTA, GPIO_PORTB, GPIO_PORTC         *
*                                       GPIO_PORTD, GPIO_PORTE, GPIO_PORTH             *
*                                                                                      *
*                               GPIOPin   : GPIO_PIN0 : GPIO_PIN15                     *
*                                                                                      *
*                   #support to configure many pins in the same port at once           *
* @return      :  error, choosing a wrong pin, port or speed   ------------------------*
****************************************************************************************/
enuGpioErrorStatus Gpio_enuInit(GPIOPortConfg_t* Add_strPortConfg);

/****************************** Gpio_enuSetBit *****************************************
* @description  :  Set the pin in the register by a value (HIGH, LOW) ---------------- *
*                                                                                      *
* @param        :       Copy_u8Port  (u8) : GPIO_PORTA, GPIO_PORTB, GPIO_PORTC         *
*                                           GPIO_PORTD, GPIO_PORTE, GPIO_PORTH         *
*                                                                                      *
*                       Copy_u8Value (u8) : GPIO_VALUE_SET, GPIO_VALUE_RESET           *
*                                                                                      *
*                       Copy_u16Pin  (u8) : GPIO_PIN0 : GPIO_PIN15                     *
*                   #support to configure many pins in the same port at once.          *
* @return       :  error, choosing a wrong pin, port or value   -----------------------*
****************************************************************************************/
enuGpioErrorStatus Gpio_enuSetBit(u8 Copy_u8Port, u16 Copy_u32Pin, u8 Copy_u8Value);

/****************************** Gpio_enuGetBit *****************************************
* @description  :  get the pin in the register by a value (HIGH, LOW) ---------------- *
*                                                                                      *
* @param        :       Copy_u8Port  (u8) : GPIO_PORTA, GPIO_PORTB, GPIO_PORTC         *
*                                           GPIO_PORTD, GPIO_PORTE, GPIO_PORTH         *
*                                                                                      *
*                       Add_p8Value (u8*) : GPIO_VALUE_SET, GPIO_VALUE_RESET           *
*                                       -> to return the value                         *
*                       Copy_u16Pin  (u8) : GPIO_PIN0 : GPIO_PIN15                     *
*                   #support to configure many pins in the same port at once.          *
* @return       :  error, choosing a wrong pin, port or value   -----------------------*
****************************************************************************************/
enuGpioErrorStatus Gpio_enuGetBit(u8 Copy_u8Port, u16 Copy_u32Pin, u8* Add_p8Value);


#endif
