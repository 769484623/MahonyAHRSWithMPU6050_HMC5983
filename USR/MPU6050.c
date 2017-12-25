#include "MPU6050.h"
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0xEB	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ
int16_t Acc[3] = {0}, GYO[3] = {0};
int32_t Gyo_Offset[3] = {0};
void MPU6050_Read()
{
	I2C_ReadBytes(I2C1,SlaveAddress,ACCEL_XOUT_H,2,(uint8_t*)Acc,MSB);
	I2C_ReadBytes(I2C1,SlaveAddress,ACCEL_YOUT_H,2,(uint8_t*)(Acc + 1),MSB);
	I2C_ReadBytes(I2C1,SlaveAddress,ACCEL_ZOUT_H,2,(uint8_t*)(Acc + 2),MSB);
	I2C_ReadBytes(I2C1,SlaveAddress,GYRO_XOUT_H,2,(uint8_t*)GYO,MSB);
	GYO[0] -= Gyo_Offset[0];
	I2C_ReadBytes(I2C1,SlaveAddress,GYRO_YOUT_H,2,(uint8_t*)(GYO + 1),MSB);
	GYO[1] -= Gyo_Offset[1];
	I2C_ReadBytes(I2C1,SlaveAddress,GYRO_ZOUT_H,2,(uint8_t*)(GYO + 2),MSB);
	GYO[2] -= Gyo_Offset[2];
}
void MPU6050_GYO_Calibration()
{
	uint8_t i , k;
	for(k = 0;k < 10;k++)
	{
		uint8_t i = 0;
		I2C_ReadBytes(I2C1,SlaveAddress,GYRO_XOUT_H,2,(uint8_t*)GYO,MSB);
		I2C_ReadBytes(I2C1,SlaveAddress,GYRO_YOUT_H,2,(uint8_t*)(GYO + 1),MSB);
		I2C_ReadBytes(I2C1,SlaveAddress,GYRO_ZOUT_H,2,(uint8_t*)(GYO + 2),MSB);
		for(i = 0;i<3;i++)
		{
			Gyo_Offset[i] += GYO[i];
		}
	}
	for(i = 0;i<3;i++)
	{
		Gyo_Offset[i] /= 10;
	}
}
void MPU6050_Config()
{
	uint8_t Value = 0;
	Value = 0x00;
	I2C_WriteRegBytes(I2C1,SlaveAddress,PWR_MGMT_1,&Value,1);
	Value = 0x07;
	I2C_WriteRegBytes(I2C1,SlaveAddress,SMPLRT_DIV,&Value,1);
	Value = 0x04;
	I2C_WriteRegBytes(I2C1,SlaveAddress,CONFIG,&Value,1);
	Value = 0x10;//1000 degree
	I2C_WriteRegBytes(I2C1,SlaveAddress,GYRO_CONFIG,&Value,1);
	Value = 0x09;//4g
	I2C_WriteRegBytes(I2C1,SlaveAddress,ACCEL_CONFIG,&Value,1);
	MPU6050_GYO_Calibration();
}
