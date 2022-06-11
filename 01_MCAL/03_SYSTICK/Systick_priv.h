
#ifndef _SYSTICK_PRIV_H_
#define _SYSTICK_PRIV_H_

#define STK_CTRL	*((volatile u32*)0xE000E010)
#define STK_LOAD	*((volatile u32*)0xE000E014)
#define STK_VAL		*((volatile u32*)0xE000E018)

#define STK_ENABLE_MASK     0x00000001

#endif
