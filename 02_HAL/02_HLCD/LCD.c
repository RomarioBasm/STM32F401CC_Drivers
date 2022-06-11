#include "Std_types.h"
#include "Bit_utils.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

typedef enum{
    LCD_enuEnableOff,
    LCD_enuEnableOn
}LCD_enuEnableState;

static LCD_enuInit_t       LCD_enuInitState      = LCD_enuInitStart;
static LCD_enuWrite_t      LCD_enuWriteState     = LCD_enuWriteStart;
static LCD_enuEnableState  LCD_enuEnable         = LCD_enuEnableOff;
static LCD_enuRequest_t    LCD_enuCurrRequest    = LCD_enuReqIdle;
                                                 
static u8                  LCD_u8BusyFlag        = LCD_BUSYFLAG_OFF;
static u8                  LCD_u8CurrentBuffer   = 0;
static u8                  LCD_u8CurrentPosition = 0;
static u8                  LCD_u8BufferIndex     = 0;

static LCD_strUserData_t   LCD_strUserData[LCD_BUFFERSIZE];
extern LCD_cfg_t           LCD_PINS[LCD_PIN_NUMS];

/* PRIVATE FUNCTIONS PROTOTYPES */
static void LCD_vidSendCommand(u8 Copy_u8Command, u8 Copy_u8RWValue, u8 Copy_u8RSValue);
static void LCD_vidSetEnable(u8 Copy_u8Value);
static void LCD_vidInitProcess();
static void LCD_vidWriteProcess();

/* *********************** LCD_vidInit ************************

   @Description  : Function to initialize the LCD.
   @param        : void
   @return       : void

****************************************************************/
void LCD_vidInit(){
    
	/* INDEXING PINS TO CONFIGURE */
    u8 Loc_u8PinIndex = 0;
    /* STRUCTURE OF GPIO CONFIGURATION */
    GPIOPortConfg_t cfg;
    
    /* ITERATE THROUGH ALL THE PINS */
	for(Loc_u8PinIndex=0;Loc_u8PinIndex<LCD_PIN_NUMS;Loc_u8PinIndex++){

		cfg.GPIOPort  = LCD_PINS[Loc_u8PinIndex].LCD_u8Port;
		cfg.GPIOPin   = LCD_PINS[Loc_u8PinIndex].LCD_u16Pin;
        cfg.GPIOMode  = GPIO_MODE_OUTPUT_PP;
        cfg.GPIOSpeed = GPIO_OUTPUT_SPEED_HIGH;

		/* INITIALIZE GPIO PORTS */
		Gpio_enuInit(&cfg);
	}

	/* SET THE BUSY FLAG */
    LCD_u8BusyFlag = LCD_BUSYFLAG_ON;
}


/* ******************** LCD_enuWriteString ********************

   @Description  : Function to write a string on the LCD.
   @param        : Add_pu8String (u8 *)
                   Copy_u8Size   (u8  )
                   Copy_u8PosX   (u8  )
                   Copy_u8PosY   (u8  )
   @return       : LCD_enuErrorStatus_t (Error)

****************************************************************/
LCD_enuErrorStatus_t LCD_enuWriteString(u8* Add_pu8String, u8 Copy_u8Size,u8 Copy_u8PosX, u8 Copy_u8PosY){  
    
    LCD_enuErrorStatus_t Ret_enuErrorStatus = LCD_enuOK;
    u8                   Loc_u8BufferIndex  = 0;
    u8                   Loc_u8CharBuffer   = 0;
    
    /* VALIDATION : CHECK THE STRING */
    if(Add_pu8String == NULL){
        Ret_enuErrorStatus = LCD_enuErrorNULLPointer;
    }
    
    /* VALIDATION : CHECKING Y POSITION */
    else if(Copy_u8PosY > LCD_ROWS_NUM){
        Ret_enuErrorStatus = LCD_enuErrorRowNumber;
    }
    
    /* VALIDATION : CHECKING X POSITION */
    else if(Copy_u8PosX > LCD_COLUMNS_NUM){
        Ret_enuErrorStatus = LCD_enuErrorColumnNumber;
    }
    
    else{
        
    	/* ITERATE THROUGH BUFFER SIZE */
        for(Loc_u8BufferIndex=0;Loc_u8BufferIndex<LCD_BUFFERSIZE;Loc_u8BufferIndex++){

        	/* FINDING AN EMPTY BUFFER */
            if(LCD_strUserData[Loc_u8BufferIndex].LCD_enuBuffered == LCD_NOTBUFFERED){
                
                /* BUFFERING THE DATA */

            	/* BUFFER THE STRING */
            	for(Loc_u8CharBuffer=0;Loc_u8CharBuffer<Copy_u8Size;Loc_u8CharBuffer++){
					LCD_strUserData[Loc_u8BufferIndex].LCD_stringData[Loc_u8CharBuffer]  = Add_pu8String[Loc_u8CharBuffer];
            	}

                LCD_strUserData[Loc_u8BufferIndex].LCD_enuPosX     = Copy_u8PosX;
                LCD_strUserData[Loc_u8BufferIndex].LCD_enuPosY     = Copy_u8PosY;
                LCD_strUserData[Loc_u8BufferIndex].LCD_enuSize     = Copy_u8Size;
                LCD_strUserData[Loc_u8BufferIndex].LCD_enuCurrPos  = 0;
                LCD_strUserData[Loc_u8BufferIndex].LCD_enuBuffered = LCD_BUFFERED;
                
                /* CHANGE CURRENT REQUEST */
                if(LCD_enuCurrRequest == LCD_enuReqIdle){
					LCD_enuCurrRequest = LCD_enuReqWrite;
					LCD_enuWriteState  = LCD_enuWriteStart;
                }

                break;
            }
        }
        
        /* NO VALED BUFFER */
        if(Loc_u8BufferIndex == LCD_BUFFERSIZE){
            Ret_enuErrorStatus = LCD_enuErrorNOBuffer;
        }
    } 
    
    return Ret_enuErrorStatus;
}    

/************************** LCD TASK *************************/
void LCD_TASK(){
    
	/* CHECKING IF THE INITIALIZE IS DONE */
    if(LCD_enuInitState != LCD_enuInitDone){
        LCD_vidInitProcess();
    }

    /* INITIALIZE IS DONE */
    else{
        
    	/* CHECKING THE CURRENT REQUEST */
        switch(LCD_enuCurrRequest){
            
            /* WRITE REQUEST */
            case LCD_enuReqWrite:
                LCD_vidWriteProcess();
            break;
            
            default:
            break;
        }
    }  
}

/************************** INIT PROCESS *************************/
static void LCD_vidInitProcess(){

    switch(LCD_enuInitState){

        case LCD_enuInitStart:
            LCD_enuInitState = LCD_enuInitFunctionSet;
			LCD_vidSetEnable(LCD_enuEnableOff);

        break;

        case LCD_enuInitFunctionSet:
            if(LCD_enuEnable == LCD_enuEnableOff){
                LCD_vidSendCommand(LCD_FUNCTIONSET_COMMAND|LCD_DATA_LENGTH|LCD_NU_OF_LINES|LCD_FONT_TYPE, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_vidSetEnable(LCD_enuEnableOn);
            }
            else{
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_vidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitClearDisplay;
            }
        break;

        case LCD_enuInitClearDisplay:
            if(LCD_enuEnable == LCD_enuEnableOff){
                LCD_vidSendCommand(LCD_CLEARDISPLAY_COMMAND, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_vidSetEnable(LCD_enuEnableOn);
            }
            else{
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_vidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitReturnHome;
            }
        break;

        case LCD_enuInitReturnHome:
            if(LCD_enuEnable == LCD_enuEnableOff){
                LCD_vidSendCommand(LCD_RETURNHOME_COMMAND, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_vidSetEnable(LCD_enuEnableOn);
            }
            else{
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_vidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitDisplayOn;
            }
        break;

        case LCD_enuInitDisplayOn:
            if(LCD_enuEnable == LCD_enuEnableOff){
                LCD_vidSendCommand(LCD_DISPLAYON_COMMAND|LCD_DISPLAY|LCD_CURSOR|LCD_BLINKING_CURSOR, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_vidSetEnable(LCD_enuEnableOn);
            }
            else{
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_vidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitStartAddress;
            }
        break;

        case LCD_enuInitStartAddress:
            if(LCD_enuEnable == LCD_enuEnableOff){
                LCD_vidSendCommand(LCD_STARTADDRESS_COMMAND, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                LCD_enuEnable = LCD_enuEnableOn;
                LCD_vidSetEnable(LCD_enuEnableOn);
            }
            else{
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_vidSetEnable(LCD_enuEnableOff);
                LCD_enuInitState = LCD_enuInitDone;
            }
        break;

        case LCD_enuInitDone:
            LCD_u8BusyFlag = LCD_BUSYFLAG_OFF;
        break;
    }
}


/************************** WRITE PROCESS *************************/
static void LCD_vidWriteProcess(){
    

    switch(LCD_enuWriteState){
        
        case LCD_enuWriteStart:

            LCD_enuWriteState = LCD_enuWriteSetPosition;
        break;
        
        case LCD_enuWriteSetPosition:
            
            LCD_u8BusyFlag = LCD_BUSYFLAG_ON;
            
            if(LCD_enuEnable == LCD_enuEnableOff){
                switch(LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuPosY){

                    case LCD_LINE_ONE:
                        LCD_vidSendCommand(LCD_LINE_ONE_BASE + LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuPosX, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                    break;
                    
                    case LCD_LINE_TWO:
                        LCD_vidSendCommand(LCD_LINE_TWO_BASE + LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuPosX, GPIO_VALUE_RESET, GPIO_VALUE_RESET);
                    break;
                }

                LCD_vidSetEnable(LCD_enuEnableOn);
                LCD_enuEnable = LCD_enuEnableOn;
            }
            else{
                LCD_enuEnable = LCD_enuEnableOff;
                LCD_vidSetEnable(LCD_enuEnableOff);
                LCD_enuWriteState = LCD_enuWriteCharacter;
            }
        break;

        
        case LCD_enuWriteCharacter:
        
            if(LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuCurrPos < LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuSize){
                if(LCD_enuEnable == LCD_enuEnableOff){
                    LCD_u8CurrentPosition = LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuCurrPos;
                    LCD_vidSendCommand(LCD_strUserData[LCD_u8CurrentBuffer].LCD_stringData[LCD_u8CurrentPosition], GPIO_VALUE_RESET, GPIO_VALUE_SET);
                    LCD_vidSetEnable(LCD_enuEnableOn);
                    LCD_enuEnable = LCD_enuEnableOn;
                }
                else{
                    LCD_enuEnable = LCD_enuEnableOff;
                    LCD_vidSetEnable(LCD_enuEnableOff);
                    LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuCurrPos++;
                }
            }
            else{
                LCD_enuWriteState = LCD_enuWriteDone;    
            }
        break;
        
        case LCD_enuWriteDone:
            
            LCD_strUserData[LCD_u8CurrentBuffer].LCD_enuBuffered = LCD_NOTBUFFERED;

            /* CHECKING IF THERE IS A BUFFERED ONE */
            for(LCD_u8BufferIndex=0;LCD_u8BufferIndex<LCD_BUFFERSIZE;LCD_u8BufferIndex++){

                if(LCD_strUserData[LCD_u8BufferIndex].LCD_enuBuffered == LCD_BUFFERED){
                    break;
                }
            }
            
            /* ALL BUFFERS ARE EMPTY */
            if(LCD_u8BufferIndex == LCD_BUFFERSIZE){
                LCD_enuCurrRequest = LCD_enuReqIdle;
                LCD_u8CurrentBuffer = 0;
				LCD_u8BusyFlag = LCD_BUSYFLAG_OFF;
            }
            else{
            	LCD_enuWriteState     = LCD_enuWriteStart;
				//LCD_u8CurrentBuffer += 1;
				LCD_u8CurrentBuffer = LCD_u8BufferIndex;

				if(LCD_u8CurrentBuffer == LCD_BUFFERSIZE){
					LCD_u8CurrentBuffer = 0;
				}
            }
        break;
        
    }
    
}

static void LCD_vidSetEnable(u8 Copy_u8Value){
    Gpio_enuSetBit(LCD_PINS[LCD_ENABLE_PIN].LCD_u8Port, LCD_PINS[LCD_ENABLE_PIN].LCD_u16Pin, Copy_u8Value);
}


static void LCD_vidSendCommand(u8 Copy_u8Command, u8 Copy_u8RWValue, u8 Copy_u8RSValue){
    
    Gpio_enuSetBit(LCD_PINS[LCD_RW_PIN].LCD_u8Port, LCD_PINS[LCD_RW_PIN].LCD_u16Pin, Copy_u8RWValue);
    Gpio_enuSetBit(LCD_PINS[LCD_RS_PIN].LCD_u8Port, LCD_PINS[LCD_RS_PIN].LCD_u16Pin, Copy_u8RSValue);
    
    Gpio_enuSetBit(LCD_PINS[LCD_D0_PIN].LCD_u8Port, LCD_PINS[LCD_D0_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,0));
    Gpio_enuSetBit(LCD_PINS[LCD_D1_PIN].LCD_u8Port, LCD_PINS[LCD_D1_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,1));
    Gpio_enuSetBit(LCD_PINS[LCD_D2_PIN].LCD_u8Port, LCD_PINS[LCD_D2_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,2));
    Gpio_enuSetBit(LCD_PINS[LCD_D3_PIN].LCD_u8Port, LCD_PINS[LCD_D3_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,3));
    Gpio_enuSetBit(LCD_PINS[LCD_D4_PIN].LCD_u8Port, LCD_PINS[LCD_D4_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,4));
    Gpio_enuSetBit(LCD_PINS[LCD_D5_PIN].LCD_u8Port, LCD_PINS[LCD_D5_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,5));
    Gpio_enuSetBit(LCD_PINS[LCD_D6_PIN].LCD_u8Port, LCD_PINS[LCD_D6_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,6));
    Gpio_enuSetBit(LCD_PINS[LCD_D7_PIN].LCD_u8Port, LCD_PINS[LCD_D7_PIN].LCD_u16Pin, GET_BIT(Copy_u8Command,7));
}
