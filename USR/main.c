#include "main.h"
#include "stdio.h"
#include <math.h>
#define Gravity 9.8
#define PI 3.1415926
extern int32_t Temp,P;
extern int16_t Acc[3], GYO[3],Mag[3];
float Factor = 1000/32768.0;
void Sensor_Read()
{
	Single_Read_Temp();//2ms
	ReadPressure_Pre();
	MPU6050_Read();
	HMC5983_Read_Mag();
	Mahony_update(GYO[0] * Factor,GYO[1] * Factor,GYO[2] * Factor,
								Acc[0],Acc[1],Acc[2],
								Mag[0],Mag[1],Mag[2]);
	Mahony_computeAngles();
	ReadPressure();
	Caculate();
}
int main(void)
{
	InitSystem();
	Mahony_Init(50);
  while (1)
  {
		char T[10] = {0};
		Sensor_Read();
		#define Float
		#ifdef Float
		sprintf(T,"%.4f",getRoll());
		#else
		sprintf(T,"%d",P);
		#endif
		LCD_E_Str(0,0,T);
		#ifdef Float
		sprintf(T,"%.4f",getPitch());
		#else
		sprintf(T,"%d",Mag[0]);
		#endif
		LCD_E_Str(0,1,T);
		#ifdef Float
		sprintf(T,"%.4f",getYaw());
		#else
		sprintf(T,"%d",Acc[0]);
		#endif
		LCD_E_Str(0,2,T);
		//LCD_clear();
  }
}
