#ifndef _REG_H_
#define _REG_H_

#include "stdint.h"

typedef struct 
{
    union 
    {
        uint32_t Reg;
        struct 
        {
            uint32_t MODE0  : 2;
            uint32_t CNF0   : 2;
            uint32_t MODE1  : 2;
            uint32_t CNF1   : 2;
            uint32_t MODE2  : 2;
            uint32_t CNF2   : 2;
            uint32_t MODE3  : 2;
            uint32_t CNF3   : 2;
            uint32_t MODE4  : 2;
            uint32_t CNF4   : 2;
            uint32_t MODE5  : 2;
            uint32_t CNF5   : 2;
            uint32_t MODE6  : 2;
            uint32_t CNF6   : 2;
            uint32_t MODE7  : 2;
            uint32_t CNF7   : 2;
        }Bits;          
    }CRL;

    union 
    {
        uint32_t Reg;
        struct 
        {
            uint32_t MODE8  : 2;
            uint32_t CNF8   : 2;
            uint32_t MODE9  : 2;
            uint32_t CNF9   : 2;
            uint32_t MODE10 : 2;
            uint32_t CNF10  : 2;
            uint32_t MODE11 : 2;
            uint32_t CNF11  : 2;
            uint32_t MODE12 : 2;
            uint32_t CNF12  : 2;
            uint32_t MODE13 : 2;
            uint32_t CNF13  : 2;
            uint32_t MODE14 : 2;
            uint32_t CNF14  : 2;
            uint32_t MODE15 : 2;
            uint32_t CNF15  : 2;
        }Bits;          
    }CRH;
    
    union 
    {
        uint32_t Reg;
        struct 
        {
            uint32_t bit0 : 1;
            uint32_t bit1 : 1;
            uint32_t bit2 : 1;
            uint32_t bit3 : 1;
            uint32_t bit4 : 1;
            uint32_t bit5 : 1;
            uint32_t bit6 : 1;
            uint32_t bit7 : 1;
            uint32_t bit8 : 1;
            uint32_t bit9 : 1;
            uint32_t bit10 : 1;
            uint32_t bit11 : 1;
            uint32_t bit12 : 1;
            uint32_t bit13 : 1;
            uint32_t bit14 : 1;
            uint32_t bit15 : 1;
            uint32_t _reserved : 16;
        }Bits;
    }IDR;

    union 
    {
        uint32_t Reg;
        struct 
        {
            uint32_t bit0 : 1;
            uint32_t bit1 : 1;
            uint32_t bit2 : 1;
            uint32_t bit3 : 1;
            uint32_t bit4 : 1;
            uint32_t bit5 : 1;
            uint32_t bit6 : 1;
            uint32_t bit7 : 1;
            uint32_t bit8 : 1;
            uint32_t bit9 : 1;
            uint32_t bit10 : 1;
            uint32_t bit11 : 1;
            uint32_t bit12 : 1;
            uint32_t bit13 : 1;
            uint32_t bit14 : 1;
            uint32_t bit15 : 1;
            uint32_t _reserved : 16;
        }Bits;
    }ODR;

    union 
    {
        uint32_t Reg;
        union 
        {
            struct 
            {
                uint16_t bit0 : 1;
                uint16_t bit1 : 1;
                uint16_t bit2 : 1;
                uint16_t bit3 : 1;
                uint16_t bit4 : 1;
                uint16_t bit5 : 1;
                uint16_t bit6 : 1;
                uint16_t bit7 : 1;
                uint16_t bit8 : 1;
                uint16_t bit9 : 1;
                uint16_t bit10 : 1;
                uint16_t bit11 : 1;
                uint16_t bit12 : 1;
                uint16_t bit13 : 1;
                uint16_t bit14 : 1;
                uint16_t bit15 : 1;
            }Bits;
        }BSR;

        union 
        {
            struct 
            {
                uint16_t bit0 : 1;
                uint16_t bit1 : 1;
                uint16_t bit2 : 1;
                uint16_t bit3 : 1;
                uint16_t bit4 : 1;
                uint16_t bit5 : 1;
                uint16_t bit6 : 1;
                uint16_t bit7 : 1;
                uint16_t bit8 : 1;
                uint16_t bit9 : 1;
                uint16_t bit10 : 1;
                uint16_t bit11 : 1;
                uint16_t bit12 : 1;
                uint16_t bit13 : 1;
                uint16_t bit14 : 1;
                uint16_t bit15 : 1;
            }Bits;
        }BR;
        
    }BSRR;
    union 
    {   
        uint32_t Reg;
        struct 
        {
            uint32_t bit0 : 1;
            uint32_t bit1 : 1;
            uint32_t bit2 : 1;
            uint32_t bit3 : 1;
            uint32_t bit4 : 1;
            uint32_t bit5 : 1;
            uint32_t bit6 : 1;
            uint32_t bit7 : 1;
            uint32_t bit8 : 1;
            uint32_t bit9 : 1;
            uint32_t bit10 : 1;
            uint32_t bit11 : 1;
            uint32_t bit12 : 1;
            uint32_t bit13 : 1;
            uint32_t bit14 : 1;
            uint32_t bit15 : 1;        
            uint32_t _reserved : 16;
        }Bits;

    }BRR;
    
    union 
    {
        uint32_t Reg;
        struct 
        {
            uint32_t bit0 : 1;
            uint32_t bit1 : 1;
            uint32_t bit2 : 1;
            uint32_t bit3 : 1;
            uint32_t bit4 : 1;
            uint32_t bit5 : 1;
            uint32_t bit6 : 1;
            uint32_t bit7 : 1;
            uint32_t bit8 : 1;
            uint32_t bit9 : 1;
            uint32_t bit10 : 1;
            uint32_t bit11 : 1;
            uint32_t bit12 : 1;
            uint32_t bit13 : 1;
            uint32_t bit14 : 1;
            uint32_t bit15 : 1; 
            uint32_t LOCK : 1;       
            uint32_t _reserved : 15;
        }Bits;
    }LCKR;
    
}GPIO_TypeDef;

typedef struct 
{

}RCC_TypeDef;



#endif