#include "Std_types.h"
#include "GPIO.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

const LCD_cfg_t LCD_PINS[LCD_PIN_NUMS] = {

    [LCD_RW_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN0
    },
    
    [LCD_RS_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN1
    },

	[LCD_ENABLE_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN2
    },
    
    [LCD_D0_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN3
    },
    
    [LCD_D1_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN4
    },
    
    [LCD_D2_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN5
    },
    
    [LCD_D3_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN6
    },
    
    [LCD_D4_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN7
    },
    
    [LCD_D5_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN8
    },
    
    [LCD_D6_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN9
    },
    
    [LCD_D7_PIN] = {
        .LCD_u8Port = GPIO_PORTA,
        .LCD_u16Pin = GPIO_PIN10
    }
    
};


