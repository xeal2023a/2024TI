#ifndef __USART_H_
#define __USART_H_

#include "stm32f4xx.h"


void getdimianzhan(u8 data);
void get265(u8 data);

extern float t265Data_x;
extern float t265Data_y;
extern float t265Data_z;
extern short t265Data_dx;
extern short t265Data_dy;
extern short t265Data_dz;
extern u8 t265kale;
extern float t265Data_check;
extern u8 t265Data[4];
extern u8 state;
extern u8 cnt;
extern u8 dimianzhan_state; 
extern u8 jieshouwanle;

extern u8 MVData;
extern u8 num_data;
extern u8 dis_data;

#endif
