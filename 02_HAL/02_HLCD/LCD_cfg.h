#ifndef _LCD_CFG_H_
#define _LCD_CFG_H_

typedef struct{
    u8 LCD_u8Port;
    u16 LCD_u16Pin;
}LCD_cfg_t; 

#define LCD_PIN_NUMS          11


#define LCD_BUFFERSIZE        4

#define LCD_ROWS_NUM          2
#define LCD_COLUMNS_NUM       16

/* options :

       LCD_DATA_LENGTH_8
       LCD_DATA_LENGTH_4

*/

#define LCD_DATA_LENGTH LCD_DATA_LENGTH_8

/* options :

       LCD_NU_OF_LINES_1
       LCD_NU_OF_LINES_2

*/
#define LCD_NU_OF_LINES LCD_NU_OF_LINES_2


/* options :

       LCD_FONT_TYPE_5X8
       LCD_FONT_TYPE_5X11

*/
#define LCD_FONT_TYPE LCD_FONT_TYPE_5X8

/* options :

       LCD_DISPLAY_ON
       LCD_DISPLAY_OFF

*/
#define LCD_DISPLAY LCD_DISPLAY_ON

/* options :

       LCD_CURSOR_ON
       LCD_CURSOR_OFF

*/
#define LCD_CURSOR LCD_CURSOR_OFF

/* options :

       LCD_BLINKING_CURSOR_ON
       LCD_BLINKING_CURSOR_OFF

*/
#define LCD_BLINKING_CURSOR LCD_BLINKING_CURSOR_OFF

#endif
