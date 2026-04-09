#ifndef __MY_PID_H_
#define __MY_PID_H_

#include "stm32f4xx.h"
#include "SysConfig.h"


void get_hight_data(void);

#define Safe_div(numerator, denominator, zero) ((denominator == 0) ? (zero) : ((numerator) / (denominator)))//分母不为0
#define Limit( x,min,max ) ( ((x) <= (min)) ? (min) : ( ((x) > (max))? (max) : (x) ) ) //限幅

typedef struct
{
  float Kp;   //比例系数
  float Ki;   //积分系数
  float Kd_expect;//微分系数
  float Kd_feedback;//微分先行
  float K_ff; //前馈
  
  float err;
  float expect_old;    
  float feedback_old; 
  
  float expect_d;      //目标微分
  float feedback_d;    //实际微分
    
  float err_i;   //积分
  float out;     //PID输出  
}PID_DATA;
void PID_Calculate(float expect,float feedback,float feedforward,float dT,PID_DATA *PID,float ierr_Limit,float i_Limit);

void my_PID_Init(void);
extern PID_DATA centre_xy[4];
extern s32 hight_ture;
extern s32 x_ture;
extern s32 y_ture;
#endif
