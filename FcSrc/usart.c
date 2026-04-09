#include "usart.h"
#include "My_Data.h"
#include "ANO_LX.h"
#include "stm32f4xx.h"
#include "LX_FC_EXT_Sensor.h"
#include "Drv_AnoOf.h"
#include "Drv_Uart.h"
#include  "User_Task.h"
#include "Drv_AnoOf.h"
#include "My_PID.h"

float t265Data_x = 0;
float t265Data_y = 0;
float t265Data_z = 0;
short t265Data_dx = 0;
short t265Data_dy = 0;
short t265Data_dz = 0;
u8 t265kale = 1;
float t265Data_check = 0;
u8 t265Data[4];
u8 state = 0;
u8 cnt = 0;
u8 jieshouwanle = 0;

u8 dimianzhan_state = 0;


u8 MVData=0;
u8 num_data=0;
u8 dis_data=0;

void getdimianzhan(u8 data)              ///串口三接受t265数据
{
	if(dimianzhan_state == 0 && data == 0xAA)
	{
		dimianzhan_state++;
	}
	else if(dimianzhan_state == 1)
	{
		jinqu[0][0] = data;
		dimianzhan_state++;
	}
	else if(dimianzhan_state == 2)
	{
		jinqu[0][1] = data;
		dimianzhan_state++;
	}
	else if(dimianzhan_state == 3)
	{
		jinqu[1][0] = data;
		dimianzhan_state++;
	}
	else if(dimianzhan_state == 4)
	{
		jinqu[1][1] = data;
		dimianzhan_state++;
	}
	else if(dimianzhan_state == 5)
	{
		jinqu[2][0] = data;
		dimianzhan_state++;
	}
	else if(dimianzhan_state == 6)
	{
		jinqu[2][1] = data;
		dimianzhan_state++;
		jieshouwanle = 1;
	}
}
	
void get265(u8 data)
{
	if(state == 0 && data == 0xAA)
	{
		state++;
	}	
	else if(state == 1 && data == 0xBB)
	{
		state++;
	}
	else if(state == 2)
	{
		t265Data[cnt++] = data;
		if(cnt > 3)
		{
			state++;
			cnt = 0;
			if((*(float*)t265Data) == t265Data_check)
			{
				t265kale = 1;
			}
			else
			{
				t265kale = 0;
			}
			t265Data_check = *(float*)t265Data;
			t265Data_x = (*(float*)t265Data)*100;
		}
	}
	else if(state == 3)
	{
		t265Data[cnt++] = data;
		if(cnt > 3)
		{
			state++;
			cnt = 0;
			t265Data_y = (*(float*)t265Data)*100;
		}
	}
	else if(state == 4)
	{
		t265Data[cnt++] = data;
		if(cnt > 3)
		{
			state++;
			cnt = 0;
			t265Data_z = (*(float*)t265Data)*100;
		}
	}
	else if(state == 5)
	{
		t265Data[cnt++] = data;
		if(cnt > 3)
		{
			state++;
			cnt = 0;
			t265Data_dx = (short)((*(float*)t265Data)*100);
		}
	}
	else if(state == 6)
	{
		t265Data[cnt++] = data;
		if(cnt > 3)
		{
			state++;
			cnt = 0;
			t265Data_dy = (short)((*(float*)t265Data)*100);
		}
	}
	else if(state == 7)
	{
		t265Data[cnt++] = data;
		if(cnt > 3)
		{
			state++;
			cnt = 0;
			t265Data_dz = (short)((*(float*)t265Data)*100);
		}
	}
	else if(state == 8 && data == 0xFF)
	{
		state = 0;
	}
	else
	{
		state = 0;
		cnt = 0;
	}
		
}










