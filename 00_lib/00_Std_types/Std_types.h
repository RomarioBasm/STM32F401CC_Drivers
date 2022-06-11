/******************************************************/
/* Author   : Romario Basem                           */
/* Date     : 23 JAN 2022                             */
/* Version  : V01                                     */
/******************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char       u8;
typedef signed char         s8;
typedef unsigned int        u16;
typedef signed int          s16;
typedef unsigned long       u32;
typedef signed long         s32;
typedef unsigned long long  u64;
typedef signed long long    s64;

typedef float               f32;
typedef double              f64;
typedef long double         f128;


/*************************** Constants ***********************************/
typedef const u8  ku8; 
typedef const u16 ku16;
typedef const u32 ku32;
typedef const u64 ku64;

typedef const s8  ks8;
typedef const s16 ks16;
typedef const s32 ks32;
typedef const s64 ks64;

typedef const f32 kf32;
typedef const f64 kf64;
typedef const f128 kf128;

/*************************** Pointers ***********************************/
typedef unsigned char*       pu8;
typedef signed char*         ps8;
typedef unsigned int*        pu16;
typedef signed int*          ps16;
typedef unsigned long*       pu32;
typedef signed long*         ps32;
typedef unsigned long long*  pu64;
typedef signed long long*    ps64;

typedef float*               pf32;
typedef double*              pf64;
typedef long double*         pf128;


#define NULL ((void*)0)


#endif
