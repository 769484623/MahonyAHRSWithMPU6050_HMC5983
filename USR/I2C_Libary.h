#ifndef I2C_Lib
#define I2C_Lib
#include "stm32f0xx.h"
enum LMSB {MSB,LSB};
void I2C_WriteByte(I2C_TypeDef * I2Cx ,uint8_t Slave_Addr, uint8_t Data);
void I2C_WriteRegBytes(I2C_TypeDef * I2Cx , uint8_t Slave_Addr,uint8_t Reg,uint8_t* Data,uint8_t Length);
void I2C_WriteRegBytes_1(I2C_TypeDef * I2Cx , uint8_t Slave_Addr,uint8_t Reg,uint8_t* Data,uint8_t Length);
void I2C_ReadBytes(I2C_TypeDef * I2Cx ,uint8_t Slave_Addr,uint8_t Register,uint8_t Length,uint8_t* Array,enum LMSB Word);
#endif
