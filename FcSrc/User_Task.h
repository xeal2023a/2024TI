#ifndef __USER_TASK_H
#define __USER_TASK_H

#include "SysConfig.h"

typedef struct {
    float kp;       // 比例系数
    float ki;       // 积分系数
    float kd;       // 微分系数
    float setpoint; // 设定值
    float integral; // 积分项
    float last_error; // 上一次的误差
} PID;
void pid_init(PID *pid, float kp, float ki, float kd, float setpoint);
float pid_compute(PID *pid, float measured_value, float dt);
void target(float x,float y);

void UserTask_OneKeyCmd(void);
extern float t265_ox;
extern u8 t265_ox_flag;

extern u8 jinqu[3][2];
extern u8 path[100][2];
extern int zuobiao[100][2];
extern u8 guihuawanle;
extern u8 path_cnt;
extern u8 current_x;
extern u8 current_y;
extern u8 left_flag;
extern u8 heng_flag;
extern u8 edge_flag;
extern u8 shangjixiaou_flag;
extern u8 path_mode;
extern u8 jinqu_minx;
extern u8 jinqu_miny;
extern u8 pidgui0;
extern PID t265pid;
extern int bushu;
extern int next_step;
extern u8 timuzuobiao;
#endif
