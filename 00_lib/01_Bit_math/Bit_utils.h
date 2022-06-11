/******************************************************/
/* Author   : Romario Basem                           */
/* Date     : 1 FEB 2022                             */
/* Version  : V01                                     */
/******************************************************/


#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#define SET_BIT(Reg,Bit)        (Reg)|=(1<<Bit)
#define CLR_BIT(Reg,Bit)        (Reg)&=(~(1<<Bit))
#define GET_BIT(Reg,Bit)        (Reg>>Bit)&(1)
#define RSHFT_REG(Reg,No)       (Reg)=(Reg>>No)
#define LSHFT_REG(Reg,No)       (Reg)=(Reg<<No)

#define CRSHFT_REG(Reg,No) Reg=((Reg>>No)|(Reg<<(8-No)))
#define CLSHFT_REG(Reg,No) Reg=((Reg<<No)|(Reg>>(8-No)))

#define ASSIGN_REG(Reg,Value)   (Reg) = Value
#define SET_REG(Reg)            (Reg)=0xFF
#define CLR_REG(Reg)            (Reg)=0x00
#define TGL_BIT(Reg,Bit)        (Reg)^=(Bit<<1)
#define TGL_REG(Reg)            (Reg)^=(0xFF)
#define SET_H_NIB(Reg)          (Reg)|=0xF0
#define SET_L_NIB(Reg)          (Reg)|=0x0F
#define CLR_H_NIB(Reg)          (Reg)&=0x0F
#define CLR_L_NIB(Reg)          (Reg)&=0xF0
#define GET_H_NIB(Reg)          ((0xF0&Reg)>>4)
#define GET_L_NIB(Reg)          (0x0F&Reg)
#define ASSIGN_H_NIB(Reg,Value) (Reg)=(Reg&0x0F)|(Value<<4) 
#define ASSIGN_L_NIB(Reg,Value) (Reg)=(Reg&0xF0)|Value
#define TGL_H_NIB(Reg)          (Reg)^=0xF0
#define TGL_L_NIB(Reg)          (Reg)^=0x0F
#define SWAP_NIB(Reg)           (Reg)=((Reg&0x0F)<<4)|((Reg&0xF0)>>4)


#endif
