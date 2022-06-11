
#include "Std_types.h"
#include "Bit_utils.h"
#include "GPIO.h"
#include "diag/Trace.h"
/* REGISTER DEFINATION */
typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDT;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOReg_t;

/* REGISTER BASE */
#define GPIO_A_BASE 0x40020000
#define GPIO_B_BASE 0x40020400
#define GPIO_C_BASE 0x40020800
#define GPIO_D_BASE 0x40020C00
#define GPIO_E_BASE 0x40021000
#define GPIO_H_BASE 0x40021C00

/* MASKS */
#define GET_MODE_MASK 	0b11000
#define GET_TYPE_MASK 	0b00100
#define GET_PUPDR_MASK 	0b00011

#define GET_FIRST_BIT  1
#define MAX_PIN_CONFG 65536

#define GPIO_MODE_OUTPUT 1
#define GPIO_MODE_INPUT  0

/* REGISTER BASE */
static GPIOReg_t* const GPIOA = (GPIOReg_t* const) GPIO_A_BASE;
static GPIOReg_t* const GPIOB = (GPIOReg_t* const) GPIO_B_BASE;
static GPIOReg_t* const GPIOC = (GPIOReg_t* const) GPIO_C_BASE;
static GPIOReg_t* const GPIOD = (GPIOReg_t* const) GPIO_D_BASE;
static GPIOReg_t* const GPIOE = (GPIOReg_t* const) GPIO_E_BASE;
static GPIOReg_t* const GPIOH = (GPIOReg_t* const) GPIO_H_BASE;


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
enuGpioErrorStatus Gpio_enuInit(GPIOPortConfg_t* Add_strPortConfg){

  enuGpioErrorStatus enuReturnError = Gpio_enuOK;
	u32 Loc_u32RegisterMode = 0;
	u32 Loc_u32RegisterType = 0;
	u32 Loc_u32RegisterPUP = 0;
	u16 Loc_u16CurrentPin = 0;
	u8 Loc_u8LoopIterator = 0;


	/* ERROR : WRONG PIN */
	if((Add_strPortConfg -> GPIOPin) > MAX_PIN_CONFG){
		enuReturnError = Gpio_enuPinError;
	}

	/* ERROR : WRONG PORT */
	else if((Add_strPortConfg -> GPIOPort) > GPIO_PORTH){
		enuReturnError = Gpio_enuPortError;
	}

	/* ERROR : WRONG SPEED */
	else if((Add_strPortConfg -> GPIOSpeed) > GPIO_OUTPUT_SPEED_VERYHIGH){
		enuReturnError = Gpio_enuSpeedError;
	}

	else{

		/* ITERATE THROUGH ALL THE PINS TO GET THE HIGH ONE */
		for(Loc_u8LoopIterator=0;Loc_u8LoopIterator<GPIO_PIN_NUM;Loc_u8LoopIterator++){
			/* MASKING THE PIN */
			Loc_u16CurrentPin = ((Add_strPortConfg -> GPIOPin)>>Loc_u8LoopIterator) & GET_FIRST_BIT;

			/* SELETED PIN TO BE CONFIGURED */
			if(Loc_u16CurrentPin == GPIO_TRUE){

				/* GET THE PORT */
				switch (Add_strPortConfg -> GPIOPort){

		        	/* SELECTED : PORT A */
                	case GPIO_PORTA:

                		/* SET MODE REGISTER */
                		Loc_u32RegisterMode = ((((Add_strPortConfg -> GPIOMode) & GET_MODE_MASK)>>3));
                		GPIOA -> MODER |= (Loc_u32RegisterMode<<(Loc_u8LoopIterator*2));

                		/* SET TYPE REGISTER */
                		Loc_u32RegisterType = ((((Add_strPortConfg -> GPIOMode) & GET_TYPE_MASK)>>2));
                		GPIOA -> OTYPER = (Loc_u32RegisterType<<(Loc_u8LoopIterator));

                		/* SET PUP RESITER  */
                		Loc_u32RegisterPUP = ((Add_strPortConfg -> GPIOMode) & GET_PUPDR_MASK);
                		GPIOA -> PUPDR = (Loc_u32RegisterPUP<<(Loc_u8LoopIterator*2));;

                		/* SET SPEED */
                		GPIOA -> OSPEEDT = ((Add_strPortConfg -> GPIOSpeed)<<(Loc_u8LoopIterator*2));
                	break;

                	/* SELECTED : PORT B */
                	case GPIO_PORTB:

                		/* SET MODE REGISTER */
                		Loc_u32RegisterMode = ((((Add_strPortConfg -> GPIOMode) & GET_MODE_MASK)>>3));
                		GPIOB -> MODER |= (Loc_u32RegisterMode<<(Loc_u8LoopIterator*2));

                		/* SET TYPE REGISTER */
                		Loc_u32RegisterType = ((((Add_strPortConfg -> GPIOMode) & GET_TYPE_MASK)>>2));
                		GPIOB -> OTYPER = (Loc_u32RegisterType<<(Loc_u8LoopIterator));

                		/* SET PUP RESITER  */
                		Loc_u32RegisterPUP = ((Add_strPortConfg -> GPIOMode) & GET_PUPDR_MASK);
                		GPIOB -> PUPDR = (Loc_u32RegisterPUP<<(Loc_u8LoopIterator*2));;

                		/* SET SPEED */
                		GPIOB -> OSPEEDT = ((Add_strPortConfg -> GPIOSpeed)<<(Loc_u8LoopIterator*2));

                	break;

                	/* SELECTED : PORT C */
                    case GPIO_PORTC:

                    	/* SET MODE REGISTER */
                    	Loc_u32RegisterMode = ((((Add_strPortConfg -> GPIOMode) & GET_MODE_MASK)>>3));
                    	GPIOC -> MODER |= (Loc_u32RegisterMode<<(Loc_u8LoopIterator*2));

                    	/* SET TYPE REGISTER */
                    	Loc_u32RegisterType = ((((Add_strPortConfg -> GPIOMode) & GET_TYPE_MASK)>>2));
                    	GPIOC -> OTYPER = (Loc_u32RegisterType<<(Loc_u8LoopIterator));

                    	/* SET PUP RESITER  */
                    	Loc_u32RegisterPUP = ((Add_strPortConfg -> GPIOMode) & GET_PUPDR_MASK);
                    	GPIOC -> PUPDR = (Loc_u32RegisterPUP<<(Loc_u8LoopIterator*2));;

                    	/* SET SPEED */
                    	GPIOC -> OSPEEDT = ((Add_strPortConfg -> GPIOSpeed)<<(Loc_u8LoopIterator*2));

                    break;

                    /* SELECTED : PORT D */
                    case GPIO_PORTD:

                    	/* SET MODE REGISTER */
                    	Loc_u32RegisterMode = ((((Add_strPortConfg -> GPIOMode) & GET_MODE_MASK)>>3));
                    	GPIOD -> MODER |= (Loc_u32RegisterMode<<(Loc_u8LoopIterator*2));

                    	/* SET TYPE REGISTER */
                    	Loc_u32RegisterType = ((((Add_strPortConfg -> GPIOMode) & GET_TYPE_MASK)>>2));
                    	GPIOD -> OTYPER = (Loc_u32RegisterType<<(Loc_u8LoopIterator));

                    	/* SET PUP RESITER  */
                    	Loc_u32RegisterPUP = ((Add_strPortConfg -> GPIOMode) & GET_PUPDR_MASK);
                    	GPIOD -> PUPDR = (Loc_u32RegisterPUP<<(Loc_u8LoopIterator*2));;

                        /* SET SPEED */
                        GPIOD -> OSPEEDT = ((Add_strPortConfg -> GPIOSpeed)<<(Loc_u8LoopIterator*2));

                    break;

                    /* SELECTED : PORT E */
                    case GPIO_PORTE:

                    	/* SET MODE REGISTER */
                    	Loc_u32RegisterMode = ((((Add_strPortConfg -> GPIOMode) & GET_MODE_MASK)>>3));
                    	GPIOE -> MODER |= (Loc_u32RegisterMode<<(Loc_u8LoopIterator*2));

                    	/* SET TYPE REGISTER */
                    	Loc_u32RegisterType = ((((Add_strPortConfg -> GPIOMode) & GET_TYPE_MASK)>>2));
                    	GPIOE -> OTYPER = (Loc_u32RegisterType<<(Loc_u8LoopIterator));

                    	/* SET PUP RESITER  */
                    	Loc_u32RegisterPUP = ((Add_strPortConfg -> GPIOMode) & GET_PUPDR_MASK);
                    	GPIOE -> PUPDR = (Loc_u32RegisterPUP<<(Loc_u8LoopIterator*2));;

                    	/* SET SPEED */
                    	GPIOE -> OSPEEDT = ((Add_strPortConfg -> GPIOSpeed)<<(Loc_u8LoopIterator*2));

                    break;

                    /* SELECTED : PORT H */
                    case GPIO_PORTH:

                    	/* SET MODE REGISTER */
                    	Loc_u32RegisterMode = ((((Add_strPortConfg -> GPIOMode) & GET_MODE_MASK)>>3));
                    	GPIOH -> MODER |= (Loc_u32RegisterMode<<(Loc_u8LoopIterator*2));

                    	/* SET TYPE REGISTER */
                    	Loc_u32RegisterType = ((((Add_strPortConfg -> GPIOMode) & GET_TYPE_MASK)>>2));
                    	GPIOH -> OTYPER = (Loc_u32RegisterType<<(Loc_u8LoopIterator));

                    	/* SET PUP RESITER  */
                    	Loc_u32RegisterPUP = ((Add_strPortConfg -> GPIOMode) & GET_PUPDR_MASK);
                    	GPIOH -> PUPDR = (Loc_u32RegisterPUP<<(Loc_u8LoopIterator*2));;

                    	/* SET SPEED */
                    	GPIOH -> OSPEEDT = ((Add_strPortConfg -> GPIOSpeed)<<(Loc_u8LoopIterator*2));

                    break;
				} //switch
			} //if
		} //for
	} // else
	return	enuReturnError;
}

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
enuGpioErrorStatus Gpio_enuSetBit(u8 Copy_u8Port, u16 Copy_u16Pin, u8 Copy_u8Value){
	enuGpioErrorStatus enuReturnError = Gpio_enuOK;
	u32 Loc_u32RegisterMode = 0;
	u16 Loc_u16CurrentPin = 0;
	u8 Loc_u8LoopIterator = 0;

	/* ERROR : WRONG PIN */
	if(Copy_u16Pin > MAX_PIN_CONFG){
		enuReturnError = Gpio_enuPinError;
	}

	/* ERROR : WRONG PORT */
	else if(Copy_u8Port > GPIO_PORTH){
		enuReturnError = Gpio_enuPortError;
	}

	/* ERROR : WRONG VALUE */
	else if((Copy_u8Value != GPIO_VALUE_SET) && (Copy_u8Value != GPIO_VALUE_RESET)){
		enuReturnError = Gpio_enuValueError;
	}

	/* GET THE RIGHT PORT */
	else{
		/* ITERATE THROUGH ALL THE PINS TO GET THE HIGH ONE */
		for(Loc_u8LoopIterator=0;Loc_u8LoopIterator<GPIO_PIN_NUM;Loc_u8LoopIterator++){

			/* MASKING THE PIN */
			Loc_u16CurrentPin = (Copy_u16Pin>>Loc_u8LoopIterator) & GET_FIRST_BIT;

			/* SELETED PIN TO BE CONFIGURED */
			if(Loc_u16CurrentPin == GPIO_TRUE){

				/* GET THE PORT */
				switch (Copy_u8Port){

					/* SELECTED : PORT A */
					case GPIO_PORTA:

						/* RESET VALUE */
						if(Copy_u8Value == GPIO_VALUE_RESET){

							/* RESET BSRR REGISTER TO SET A VALUE */
							GPIOA -> BSRR |= (1<<(Loc_u8LoopIterator+16));
						}

						/* SET VALUE */
						else{

							/* SET BSRR REGISTER TO SET A VALUE */
							GPIOA -> BSRR |= (1<<Loc_u8LoopIterator);
						}

					break;

					/* SELECTED : PORT B */
					case GPIO_PORTB:

						/* RESET VALUE */
						if(Copy_u8Value == GPIO_VALUE_RESET){

							/* RESET BSRR REGISTER TO SET A VALUE */
							GPIOB -> BSRR |= (1<<(Loc_u8LoopIterator+16));
						}

						/* SET VALUE */
						else{

							/* SET BSRR REGISTER TO SET A VALUE */
							GPIOB -> BSRR |= (1<<Loc_u8LoopIterator);
						}

					break;

					/* SELECTED : PORT C */
					case GPIO_PORTC:

						/* RESET VALUE */
						if(Copy_u8Value == GPIO_VALUE_RESET){

							/* RESET BSRR REGISTER TO SET A VALUE */
							GPIOC -> BSRR |= (1<<(Loc_u8LoopIterator+16));
						}

						/* SET VALUE */
						else{

							/* SET BSRR REGISTER TO SET A VALUE */
							GPIOC -> BSRR |= (1<<Loc_u8LoopIterator);
						}

					break;

					/* SELECTED : PORT D */
					case GPIO_PORTD:

						/* RESET VALUE */
						if(Copy_u8Value == GPIO_VALUE_RESET){

							/* RESET BSRR REGISTER TO SET A VALUE */
							GPIOD -> BSRR |= (1<<(Loc_u8LoopIterator+16));
						}

						/* SET VALUE */
						else{

							/* SET BSRR REGISTER TO SET A VALUE */
							GPIOD -> BSRR |= (1<<Loc_u8LoopIterator);
						}

					break;

					/* SELECTED : PORT E */
					case GPIO_PORTE:

						/* RESET VALUE */
						if(Copy_u8Value == GPIO_VALUE_RESET){

							/* RESET BSRR REGISTER TO SET A VALUE */
							GPIOE -> BSRR |= (1<<(Loc_u8LoopIterator+16));
						}

						/* SET VALUE */
						else{

							/* SET BSRR REGISTER TO SET A VALUE */
							GPIOE -> BSRR |= (1<<Loc_u8LoopIterator);
						}
					break;

					/* SELECTED : PORT H */
					case GPIO_PORTH:

						/* RESET VALUE */
						if(Copy_u8Value == GPIO_VALUE_RESET){

							/* RESET BSRR REGISTER TO SET A VALUE */
							GPIOH -> BSRR |= (1<<(Loc_u8LoopIterator+16));
						}

						/* SET VALUE */
						else{

							/* SET BSRR REGISTER TO SET A VALUE */
							GPIOH -> BSRR |= (1<<Loc_u8LoopIterator);
						}

					break;
				}//switch
			}//if
		}//for
	}//else

	return enuReturnError;
}


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
enuGpioErrorStatus Gpio_enuGetBit(u8 Copy_u8Port, u16 Copy_u16Pin, u8* Add_p8Value){
	enuGpioErrorStatus enuReturnError = Gpio_enuOK;
	u32 Loc_u32RegisterMode = 0;
	u16 Loc_u16CurrentPin = 0;
	u8 Loc_u8LoopIterator = 0;

	/* ERROR : WRONG PIN */
	if(Copy_u16Pin > MAX_PIN_CONFG){
		enuReturnError = Gpio_enuPinError;
	}

	/* ERROR : WRONG PORT */
	else if(Copy_u8Port > GPIO_PORTH){
		enuReturnError = Gpio_enuPortError;
	}

	/* GET THE RIGHT PORT */
	else{

		/* GET THE PIN */
		for(Loc_u8LoopIterator=0;Loc_u8LoopIterator<GPIO_PIN_NUM;Loc_u8LoopIterator++){

			/* MASKING THE PIN */
			Loc_u16CurrentPin = (Copy_u16Pin>>Loc_u8LoopIterator) & GET_FIRST_BIT;

			/* SELETED PIN TO BE CONFIGURED */
			if(Loc_u16CurrentPin == GPIO_TRUE){
				break;
			}
		}

		/* GET THE PORT */
		switch (Copy_u8Port){

			/* SELECTED : PORT A */
			case GPIO_PORTA:

				/* GET MODE REGISTER */
				Loc_u32RegisterMode = ((GPIOA -> MODER)>>(Loc_u8LoopIterator*2));

				/* GET THE VALUE OF IDR REGISTER */
				*Add_p8Value = (GPIOA->IDR>>Loc_u8LoopIterator) & GET_FIRST_BIT;

			break;

			/* SELECTED : PORT B */
			case GPIO_PORTB:

				/* GET MODE REGISTER */
				Loc_u32RegisterMode = ((GPIOB -> MODER)>>(Loc_u8LoopIterator*2));

				/* GET THE VALUE OF IDR REGISTER */
				*Add_p8Value = (GPIOB->IDR>>Loc_u8LoopIterator) & GET_FIRST_BIT;

			break;

			/* SELECTED : PORT C */
			case GPIO_PORTC:

				/* GET MODE REGISTER */
				Loc_u32RegisterMode = ((GPIOC -> MODER)>>(Loc_u8LoopIterator*2));

				/* GET THE VALUE OF IDR REGISTER */
				*Add_p8Value = (GPIOC->IDR>>Loc_u8LoopIterator) & GET_FIRST_BIT;
			break;

			/* SELECTED : PORT D */
			case GPIO_PORTD:

				/* GET MODE REGISTER */
				Loc_u32RegisterMode = ((GPIOD -> MODER)>>(Loc_u8LoopIterator*2));

				/* GET THE VALUE OF IDR REGISTER */
				*Add_p8Value = (GPIOD->IDR>>Loc_u8LoopIterator) & GET_FIRST_BIT;
			break;

			/* SELECTED : PORT E */
			case GPIO_PORTE:

				/* GET MODE REGISTER */
				Loc_u32RegisterMode = ((GPIOE -> MODER)>>(Loc_u8LoopIterator*2));

				/* GET THE VALUE OF IDR REGISTER */
				*Add_p8Value = (GPIOE->IDR>>Loc_u8LoopIterator) & GET_FIRST_BIT;
			break;


			/* SELECTED : PORT H */
			case GPIO_PORTH:

				/* GET MODE REGISTER */
				Loc_u32RegisterMode = ((GPIOH -> MODER)>>(Loc_u8LoopIterator*2));

				/* GET THE VALUE OF IDR REGISTER */
				*Add_p8Value = (GPIOH->IDR>>Loc_u8LoopIterator) & GET_FIRST_BIT;
			break;
		}
	}
	return enuReturnError;
}

