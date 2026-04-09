#include "My_PID.h"
#include "ANO_LX.h"
#include "stm32f4xx.h"
#include "LX_FC_EXT_Sensor.h"
#include "Drv_AnoOf.h"
#include "Drv_Uart.h"
#include  "User_Task.h"
#include "Drv_AnoOf.h"


s32 hight_ture; 
s32 x_ture;
s32 y_ture;

void get_hight_data(void)
{
	hight_ture = hight.st_data.alt_add;
	x_ture=POS.st_data.POS_X;
	y_ture=POS.st_data.POS_Y;
}

PID_DATA centre_xy[4];
  void my_PID_Init(void)
 {
  centre_xy[0].Kp = 1.0f;
  centre_xy[0].Ki = 0.001f;
  centre_xy[0].Kd_expect = 0;
  centre_xy[0].Kd_feedback = 0;
  centre_xy[0].K_ff = 0;
  centre_xy[1] = centre_xy[0];

  centre_xy[2].Kp = 1.0f;
  centre_xy[2].Ki = 0.001f;
  centre_xy[2].Kd_expect = 0;
  centre_xy[2].Kd_feedback = 0;
  centre_xy[2].K_ff = 0;
 }
void PID_Calculate(float expect,float feedback,float feedforward,float dT,PID_DATA *PID,float ierr_Limit,float i_Limit)
{
  static float hz,derros;
  hz = Safe_div(1.0f,dT,0);
  PID->feedback_old = feedback;
  PID->expect_old   = expect;
  
  PID->err = expect - feedback; //误差
  
  PID->expect_d = PID->Kd_expect *(expect - PID->expect_old) *hz; //期望值微分
  
  PID->feedback_d = PID->Kd_feedback *(feedback - PID->feedback_old) *hz;//实际值微分
  
  derros = PID->expect_d - PID->feedback_d; //微分KD*
  
  PID->err_i += PID->Ki * Limit(PID->err,-ierr_Limit,ierr_Limit) *dT;
  PID->err_i = Limit(PID->err_i,-i_Limit,i_Limit);
              /*P                    I               D          前馈 */
  PID->out = PID->Kp * PID->err + PID->err_i + derros + PID->K_ff *feedforward;
	
}  
