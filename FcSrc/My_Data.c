#include "My_Data.h"
#include "ANO_LX.h"
#include "stm32f4xx.h"
#include "LX_FC_EXT_Sensor.h"
#include "Drv_AnoOf.h"
#include "Drv_Uart.h"
#include  "User_Task.h"
#include "Drv_AnoOf.h"
#include "My_PID.h"



//void get_hight_data(void)
//{
//	hight = hight.st_data.alt_add;
//}


//void get_of_data(void)
//{
//	of_data_x=ano_of.of2_dx_fix;
//	of_data_y=ano_of.of2_dy_fix;
//}

//void SET_ZERO(void)     ///***这个函数的作用是执行手动清零，阶段性手动清零重新积分
//{
//	dis_x = 0;
//	dis_y = 0;
//}


//void DISTANCE_X(void)         ///**此函数积分得到X轴位移    2024/3/25 参数未调,随机给的
//{
//	if(of_data_x < 50 && of_data_x > -50)    //**判断光流速度是否有效
//	{
//		vel_x_intital += of_data_x;
//		dis_x = vel_x_intital*1.6/1000;         //**注意这里因为是除以1000所以此函数必须放在1ms的调度函数内，采用近似相等的方法积分。
//	}
//}



//void DISTANCE_Y(void)          ///***注释同上
//{
//	if(of_data_y < 100 && of_data_y > -100)
//	{
//			vel_y_intital += of_data_y;
//		  dis_y = vel_y_intital*1.6/1000;
//	}
//}

//                        ////////*****但是需要说明的是这个系列的速度环只能单纯地走X，Y两个方向的直线
//void DISTANCE_CHECK(void)       //////****封装一下，用标志位来进行积分控制和自动清零(此函数必须放在1ms调度函数内!!!!!!!!!!!!)
//{
//	if(my_dis_x_flag == 1)
//	{
//		DISTANCE_X();
//	}
//	else if(my_dis_y_flag == 1)
//	{
//		DISTANCE_Y();
//	}
//	else if(my_dis_y_flag == 0 || my_dis_x_flag == 0)
//	{
//		SET_ZERO();
//	}
//}

//////////////////////////////////////////////////////
