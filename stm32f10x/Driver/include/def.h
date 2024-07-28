#ifndef _DEF_H_
#define _DEF_H_

#define __IO volatile

typedef enum
{
    FUNCTION_OK = 0x00,
    FUNCTION_ERROR,
    FUNCTION_BUSY,
    FUNCTION_TIMEOUT
}Funct_StatusTypeDef;

typedef enum
{
    LOCK = 0,
    UNLOCK = !(LOCK)
}Lock_TypeDef;

typedef enum
{
    LOW = 0,
    HIGH = !(LOW)
}Pin_Status_TypeDef;




#endif
