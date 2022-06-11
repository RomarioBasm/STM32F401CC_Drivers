#ifndef _NVIC_PRIV_H_
#define _NVIC_PRIV_H_

#define SCB_AIRCR    *((volatile u32 *)0xE000ED00+0x0C)

#define NVIC_ISER_BASE ((volatile u32 *) 0xE000E100)
#define NVIC_ICER_BASE ((volatile u32 *) 0xE000E180)
#define NVIC_ISPR_BASE ((volatile u32 *) 0xE000E200)
#define NVIC_ICPR_BASE ((volatile u32 *) 0xE000E280)
#define NVIC_IAB_BASE  ((volatile u32 *) 0xE000E300)
#define NVIC_IPR_BASE  ((volatile u32 *) 0xE000E400)
#define NVIC_STIR      ((volatile u32 *) 0xE000EF00)


#define SCB_PRI_GROUP_0 	0x05FA0000
#define SCB_PRI_GROUP_1     0x05FA0100
#define SCB_PRI_GROUP_2     0x05FA0200
#define SCB_PRI_GROUP_3     0x05FA0300
#define SCB_PRI_GROUP_4     0x05FA0400
#define SCB_PRI_GROUP_5     0x05FA0500
#define SCB_PRI_GROUP_6     0x05FA0600
#define SCB_PRI_GROUP_7     0x05FA0700





#endif
