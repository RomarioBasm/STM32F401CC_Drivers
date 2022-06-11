#ifndef _LCD_H_
#define _LCD_H_
typedef enum{
    LCD_enuReqIdle,
    LCD_enuReqWrite,
}LCD_enuRequest_t;

typedef enum{
    LCD_enuInitStart,
    LCD_enuInitFunctionSet,
    LCD_enuInitClearDisplay,
    LCD_enuInitReturnHome,
    LCD_enuInitDisplayOn,
    LCD_enuInitStartAddress,
    LCD_enuInitDone
}LCD_enuInit_t;

typedef enum{
    LCD_enuWriteStart,
    LCD_enuWriteSetPosition,
    LCD_enuWriteCharacter, 
    LCD_enuWriteDone
}LCD_enuWrite_t;

typedef enum{
    LCD_enuOK,
    LCD_enuErrorNULLPointer,
    LCD_enuErrorNOBuffer,
    LCD_enuErrorRowNumber,
    LCD_enuErrorColumnNumber
}LCD_enuErrorStatus_t;

typedef struct{
    u8  LCD_stringData[32];
    u8  LCD_enuPosX;
    u8  LCD_enuPosY;
    u8  LCD_enuSize;
    u8  LCD_enuCurrPos;
    u8  LCD_enuBuffered;
}LCD_strUserData_t;


#define LCD_BUFFERED    1
#define LCD_NOTBUFFERED 0

void LCD_vidInit();
void LCD_TASK();
LCD_enuErrorStatus_t LCD_enuWriteString(u8* Add_pu8String, u8 Copy_u8Size,u8 Copy_u8PosX, u8 Copy_u8PosY);
#endif
