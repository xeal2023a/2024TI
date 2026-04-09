#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "stm32f4xx_usart.h"
#include "My_PID.h"
#include "usart.h"
#include "Ano_math.h"

float t265_ox = 0;
float t265_oy = 0;
u8 t265_ox_flag = 0;

u8 jinqu[3][2]; 
u8 path[100][2];
int zuobiao[100][2];
u8 guihuawanle = 0;
u8 path_cnt = 0;
u8 current_x = 0;
u8 current_y = 0;
u8 left_flag = 0;
u8 heng_flag = 0;
u8 edge_flag = 0;
u8 shangjixiaou_flag = 2;
u8 path_mode = 0;
u8 jinqu_minx = 10;
u8 jinqu_miny = 10;
u8 pidgui0 = 0;
int bushu = 0;
int next_step = 1;
u8 timuzuobiao = 0x91;
u8 timuzuobiaox = 0;
u8 timuzuobiaoy = 0;

#define MY_ABS(x) ((x) > 0 ? (x) : -(x)) //绝对值
#define MY_MAX(a, b) ((a) > (b) ? (a) : (b))

#define speed_error_x 1/1.35f
#define speed_error_y 1/1.35f

void pid_init(PID *pid, float kp, float ki, float kd, float setpoint) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->setpoint = setpoint;
    pid->integral = 0.0;
    pid->last_error = 0.0;
}

float pid_compute(PID *pid, float measured_value, float dt) {
    // 计算误差
    float error = pid->setpoint - measured_value;

    // 计算积分项
    pid->integral += error * dt;

    // 计算微分项
    float derivative = (error - pid->last_error) / dt;

    // 计算PID输出
    float output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;

    // 更新上一次的误差
    pid->last_error = error;

    return output;
}

PID t265pidx;
PID t265pidy;

void UserTask_OneKeyCmd(void)
{
   //////////////////////////////////////////////////////////////////////
    //一键起飞/降落例程
    //////////////////////////////////////////////////////////////////////
    //用静态变量记录一键起飞/降落指令已经执行。
    static u8 one_key_takeoff_f = 1, one_key_land_f = 1, one_key_mission_f = 0;
    static u8 mission_step ;
	
	if(guihuawanle == 0 && jieshouwanle == 1)
	{
		
		guihuawanle = 1;
	if(jinqu[0][0] == jinqu[1][0])
	{
		heng_flag = 0;
	}
	else
	{
		heng_flag = 1;
	}
	
	if(jinqu[0][1] == 0 || jinqu[1][1] == 0 || jinqu[2][1] == 0 || jinqu[0][1] == 6 || jinqu[1][1] == 6 || jinqu[2][1] == 6)
	{
		edge_flag = 1;
	}
	else
	{
		edge_flag = 0;
	}
			
	if(jinqu[0][0] > 5 || jinqu[1][0] > 5 || jinqu[2][0] > 5)
	{
		left_flag = 0;
	}
	else
	{
		left_flag = 1;
	}
	
	if(heng_flag == 1)
	{
		for(int i = 0;i<3;i++)
		{
			if(jinqu_minx > jinqu[i][0])
			{
				jinqu_minx = jinqu[i][0];
				jinqu_miny = jinqu[i][1];
			}
		}
	}
	else
	{
		for(int i = 0;i<3;i++)
		{
			if(jinqu_miny > jinqu[i][1])
			{
				jinqu_miny = jinqu[i][1];
				jinqu_minx = jinqu[i][0];
			}
		}
	}
	
	if(jinqu_miny == 0)
	{
		shangjixiaou_flag = 1;
	}
	else if(jinqu_miny == 6)
	{
		shangjixiaou_flag = 0;
	}
	
	if(edge_flag == 0)
	{
		if(heng_flag == 1)
		{
			path_mode = 0;
		}
		else
		{
			path_mode = 1;
		}
	}
	else
	{
		if(heng_flag == 1)
		{
			if(shangjixiaou_flag == 1)
			{
				path_mode = 2;
			}
			else
			{
				path_mode = 3;
			}
		}
		else
		{
			if(shangjixiaou_flag == 1)
			{
				path_mode = 4;
			}
			else
			{
				path_mode = 5;
			}
		}
	}
	
	switch(path_mode)
	{
		case 0: //中间 横
		{
	for(;current_x < 9; current_x++)
	{
		for(;current_y < 7; current_y++)
		{
			if(current_x == jinqu_minx && current_y == jinqu_miny-1)
			{
				if(left_flag == 0)
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+2;
				}
				else
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+2;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+3;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+3;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x+3;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					path[path_cnt][0] = current_x+2;
					path[path_cnt][1] = current_y+2;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+2;
				}
			}
			else if(current_x == jinqu_minx+1 && current_y == 6-jinqu_miny-1)
			{
				if(left_flag == 0)
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-2;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-2;
					path[path_cnt][1] = current_y+1;
					path_cnt++;
					path[path_cnt][0] = current_x-2;
					path[path_cnt][1] = current_y+2;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+2;
				}
				else
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+2;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+2;
					path[path_cnt][1] = current_y+1;
					path_cnt++;
					path[path_cnt][0] = current_x+2;
					path[path_cnt][1] = current_y+2;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+2;
				}
			}
			else if(current_x == jinqu_minx+2 && current_y == jinqu_miny-1)
			{
				if(left_flag == 0)
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-2;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-3;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-3;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x-3;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					path[path_cnt][0] = current_x-2;
					path[path_cnt][1] = current_y+2;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+2;
				}
				else
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+2;
				}
			}
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
		}
		current_y = 0;
	}
		}
		break;
		case 1: //中间 竖
		{
			for(;current_x < 9; current_x++)
	{
		for(;current_y < 7; current_y++)
		{
			if(current_x == jinqu_minx && current_y == jinqu_miny-1)
			{
				if(left_flag == 0)
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-3;
					path_cnt++;
					path[path_cnt][0] = current_x-1;
					path[path_cnt][1] = 6-current_y-4;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+4;
				}
				else
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-3;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-4;
					path_cnt++;
					current_x = current_x;
					current_y = current_y+4;
				}
			}
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
		}
		current_y = 0;
	}
		}
		break;
		case 2: //边缘 横上奇下偶
		{
			for(;current_x < 9; current_x++)
	{
		for(;current_y < 7; current_y++)
		{
			if(current_x == jinqu_minx-1 && current_y == 6-jinqu_miny)
			{
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y-1;
				path_cnt++;
				current_x = current_x+1;
				current_y = 6-current_y+1;
			}
			else if(current_x == jinqu_minx+1 && current_y == 6-jinqu_miny-1)
			{
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
				current_x = current_x+1;
				current_y = 6-current_y;
			}
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
		}
		current_y = 0;
	}
		}
		break;
		case 3: //边缘 横上偶下奇
		{
			for(;current_x < 9; current_x++)
	{
		for(;current_y < 7; current_y++)
		{
			if(current_x == jinqu_minx && current_y == jinqu_miny-1)
			{
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
				current_x = current_x+1;
				current_y = 6-current_y;
			}
			else if(current_x == jinqu_minx+2 && current_y == jinqu_miny-1)
			{
				if(jinqu_minx+2 == 8)
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					current_y++;
					goto flag;
				}
				else
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					current_x = current_x+1;
					current_y = 6-current_y-1;
				}	
			}
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
			flag:;
		}
		current_y = 0;
	}
		}
		break;
		case 4: //边缘 竖上奇下偶
		{
			for(;current_x < 9; current_x++)
	{
		for(;current_y < 7; current_y++)
		{
			if(current_x == jinqu_minx-1 && current_y == 6-jinqu_miny)
			{
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y-1;
				path_cnt++;
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y-2;
				path_cnt++;
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y-3;
				path_cnt++;
				current_x = current_x+1;
				current_y = 6-current_y+3;
			}
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
		}
		current_y = 0;
	}
		}
		break;
		case 5: //边缘 竖上偶下奇
		{
			for(;current_x < 9; current_x++)
	{
		for(;current_y < 7; current_y++)
		{
			if(current_x == jinqu_minx && current_y == jinqu_miny-1)
			{
				if(jinqu_minx == 8)
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					current_y+=3;
					goto flag1;
				}
				else
				{
					path[path_cnt][0] = current_x;
					path[path_cnt][1] = current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-1;
					path_cnt++;
					path[path_cnt][0] = current_x+1;
					path[path_cnt][1] = 6-current_y-2;
					path_cnt++;
					current_x = current_x+1;
					current_y = 6-current_y-3;
				}	
			}
				path[path_cnt][0] = current_x;
				path[path_cnt][1] = current_y;
				path_cnt++;
			flag1:;
		}
		current_y = 0;
	}
		}
		break;
	}
	for(int i = 0; (!(path[i][0]==0&&path[i][1]==0)) || i == 0; i++)
	{
		zuobiao[i][1] = path[i][0]*50;
		if(path[i][0] % 2 == 0)
		{
			zuobiao[i][0] = path[i][1]*50;
		}
		else
		{
			zuobiao[i][0] = (6-path[i][1])*50;
		}
	}
}
	
    //判断有遥控信号才执行
    if (rc_in.fail_safe == 0)
    {
				
//        //判断第6通道拨杆位置 1300<CH_6<1700
//        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1300 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1700)
//        {
//            //还没有执行z
//            if (one_key_takeoff_f == 0)
//            {
//                //标记已经执行
//                one_key_takeoff_f =
//                    //执行一键起飞
//                    OneKey_Takeoff(100); ////参数单位：厘米； 0：默认上位机设置的高度。
//            }
//        }
//        else
//        {
//            //复位标记，以便再次执行
//            one_key_takeoff_f = 0;
//        }
//        //
       //判断第6通道拨杆位置 800<CH_6<1200
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //还没有执行
            if (one_key_land_f == 0)
            {
                //标记已经执行
                one_key_land_f =
                    //ִ执行一键降落
                    OneKey_Land();
            }
        }
        else
        {
            //复位标记，以便再次执行
            one_key_land_f = 0;
        }


				 //判断第6通道拨杆位置 1700<CH_6<2200 
         if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1700 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 2200)
         {

             if(one_key_mission_f == 0)
            {
                  //标记已经执行
                one_key_mission_f = 1;
                //开始流程
                mission_step = 1;

            }
         }
         else
         {
           //复位标记，以便再次执行
            one_key_mission_f = 0;
		        	mission_step = 0;
         }
         //
         if (one_key_mission_f == 1)
         {
            static u16 time_dly_cnt_ms;
					
            rt_tar.st_data.vel_x = rt_tar.st_data.vel_y = rt_tar.st_data.vel_z = 0;
			  switch(mission_step)                     
			 {    
				 case 0:
				{
					time_dly_cnt_ms=0;
				}
				break ;
				case 1 :                                 ////正式流程
				{   
						
				if(guihuawanle == 1 && t265kale == 0)
			{
					if(time_dly_cnt_ms <= 2000)
					{
						time_dly_cnt_ms += 20;
					}
					else if((2000 < time_dly_cnt_ms)&&(time_dly_cnt_ms <= 5000))         ////////��ʽ�������·�ע�Ͳ��֣��˲���Ϊ���߶Ȼ���д
					{ 
						FC_Unlock();  
							  	
						time_dly_cnt_ms += 20;  								
					}
					else 
					{
						time_dly_cnt_ms =0;  
						mission_step = 2;
						 			
					}
				}
				}  
				break;    
				case 2:
				{ 
					t265_ox = t265Data_x;
					t265_oy = t265Data_y;
					mission_step+=OneKey_Takeoff(112);	
			}				
				break ;
				
		case 3:
				{	
					if(time_dly_cnt_ms<5000)
					{  
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;//进入下一个case
					}	
					
				} 
				break;
				
				case 4:////////////////////直接改这个地方就可以平动
        {
			if(pidgui0 == 0 && next_step == 1)
			{
				if(bushu > 0)
				{
				timuzuobiaox = 8-path[bushu-1][0]+1;
		if(path[bushu-1][0] % 2 == 0)
		{
			timuzuobiaoy = path[bushu-1][1]+1;
		}
		else
		{
			timuzuobiaoy = 6-path[bushu-1][1]+1;
		}
				timuzuobiao = timuzuobiaox<<4 | timuzuobiaoy;
				}
				t265pidx.integral = 0;
				t265pidx.last_error = 0;
				t265pidy.integral = 0;
				t265pidy.last_error = 0;
				pidgui0 = 1;
				next_step = 0;
			
		}
			pid_init(&t265pidx, 0.7,0.1,0.05, t265_ox+zuobiao[bushu][0]);
			rt_tar.st_data.vel_x = Limit(pid_compute(&t265pidx, t265Data_x, 0.1),-30,30);
			pid_init(&t265pidy, 0.8,0.1,0.05, t265_oy+zuobiao[bushu][1]);
			rt_tar.st_data.vel_y = Limit(pid_compute(&t265pidy, t265Data_y, 0.1),-30,30);
			if(t265kale==1)
			{
				rt_tar.st_data.vel_x = 0;
				rt_tar.st_data.vel_y = 0;
			}
			if(time_dly_cnt_ms<3000)
			{  
				time_dly_cnt_ms+=20;//ms
			}
			else
			{
				next_step = 1;
				pidgui0 = 0;
				time_dly_cnt_ms = 0;
				bushu++;
			}
			if(zuobiao[bushu][0] == 0 && zuobiao[bushu][1] == 0 && (bushu != 0))
			{
				mission_step += 1;
				time_dly_cnt_ms = 0;
				rt_tar.st_data.vel_x = 0;
				rt_tar.st_data.vel_y = 0;
			}
			
        }
        break;
			
		
		case 5:
				{ 
					timuzuobiaox = 8-path[bushu-1][0]+1;
		if(path[bushu-1][0] % 2 == 0)
		{
			timuzuobiaoy = path[bushu-1][1]+1;
		}
		else
		{
			timuzuobiaoy = 6-path[bushu-1][1]+1;
		}
				timuzuobiao = timuzuobiaox<<4 | timuzuobiaoy;		


			mission_step+=1;
				}

				break ;
				
				
				case 6:
				{ 
					mission_step+=OneKey_Land();					
				}
				break ;
				
				
				
				  	default:
				{
						
				}
			  break;
				


			}
		}
	
	}
    ////////////////////////////////////////////////////////////////////////
//      else{
//			
//			       FC_Lock();
//			
//			}

}
