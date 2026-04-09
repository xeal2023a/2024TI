/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"



uint8_t yizhifa = 0;

float t265_ox = 0;
float t265_oy = 0;
uint8_t t265_ox_flag = 0;
uint8_t path[100][2];
int zuobiao[100][2];
uint8_t guihuawanle = 0;
uint8_t path_cnt = 0;
uint8_t current_x = 0;
uint8_t current_y = 0;
uint8_t left_flag = 0;
uint8_t heng_flag = 0;
uint8_t edge_flag = 0;
uint8_t shangjixiaou_flag = 2;
uint8_t path_mode = 0;
uint8_t jinqu_minx = 10;
uint8_t jinqu_miny = 10;
uint8_t pidgui0 = 0;
int bushu = 0;
int next_step = 1;

uint8_t zhentou = 0xAA;
uint8_t zhenwei = 0xFF;

uint8_t dimianzhan_data;
uint8_t jinqu_buf[3];
uint8_t jinqu_shuliang = 0;
uint8_t jinqu[3][2];
uint8_t dimianzhan_state = 0;
uint8_t jinqusuanwanle = 0;
uint8_t keyifale = 0;
uint8_t fageidimianzhanle = 0;
uint8_t kongjianid[100];

uint8_t maxicam_data;
uint8_t maxicam_state;

uint8_t bianlv[7] ={0x32, 0x30, 0x32, 0x34, 0xff, 0xff, 0xff};
uint8_t bianhui[8] = {0x35, 0x30, 0x37, 0x31, 0x32, 0xFF, 0xFF, 0xFF};
uint8_t lingcha62 = 0x62;
uint8_t lingcha2E[5] = {0x2E, 0x62, 0x63, 0x6F, 0x3D};
uint8_t lingcha74[8] = {0x74, 0x30, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22};
int xianzaidebushu = 0;

uint8_t zuobiao_data = 0;
uint8_t zuobiao_datax = 0;
uint8_t zuobiao_datay = 0;
uint8_t lingcha30 = 0x30;
uint8_t lingcha41 = 0x41;
uint8_t lingcha42 = 0x42;
uint8_t lingcha0f = 0x0f;
uint8_t lingcha22[] = {0x22, 0xff, 0xff, 0xff};
uint8_t lastzuobiao_data = 0;

uint8_t dongwuzhonglei = 0;
uint8_t dongwumingcheng[3][8] ={
0x74, 0x31, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
0x74, 0x32, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
0x74, 0x33, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22
};
uint8_t daxiangmingcheng[4] ={0xB4, 0xF3, 0xCF, 0xF3};
uint8_t laohumingcheng[4] ={0xC0, 0xCF, 0xBB, 0xA2};
uint8_t langmingcheng[2] ={0xC0, 0xC7};
uint8_t houzimingcheng[4] ={0xBA, 0xEF, 0xD7, 0xD3};
uint8_t kongquemingcheng[4] ={0xBF, 0xD7, 0xC8, 0xB8};
uint8_t dongwumingchengff[4] = {0x22, 0xff, 0xff, 0xff};
uint8_t daxiangshuliang = 0;
uint8_t laohushuliang = 0;
uint8_t langshuliang = 0;
uint8_t houzishuliang = 0;
uint8_t kongqueshuliang = 0;
uint8_t keyifadongwuxinxi = 0;
uint8_t lingcha3A = 0x3A;
uint8_t dongwu1[9] = {0xB6, 0xAF, 0xCE, 0xEF, 0x31, 0x22, 0xff, 0xff, 0xff};
uint8_t dongwu2[9] = {0xB6, 0xAF, 0xCE, 0xEF, 0x32, 0x22, 0xff, 0xff, 0xff};
uint8_t dongwu3[9] = {0xB6, 0xAF, 0xCE, 0xEF, 0x33, 0x22, 0xff, 0xff, 0xff};

uint8_t daxiangzongshuliang = 0x30;
uint8_t laohuzongshuliang = 0x30;
uint8_t langzongshuliang = 0x30;
uint8_t houzizongshuliang = 0x30;
uint8_t kongquezongshuliang = 0x30;

uint8_t daxiangshuliang_now = 0x30;
uint8_t laohushuliang_now = 0x30;
uint8_t langshuliang_now = 0x30;
uint8_t houzishuliang_now = 0x30;
uint8_t kongqueshuliang_now = 0x30;

uint8_t daxiangshuliangtxt[15] = {0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22};
uint8_t laohushuliangtxt[15] = {0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x36, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22};
uint8_t langshuliangtxt[16] = {0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x31, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22};
uint8_t houzishuliangtxt[16] = {0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x36, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22};
uint8_t kongqueshuliangtxt[16] = {0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x32, 0x31, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22};

uint8_t daxiangzuobiaotxt[3][15] = {
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x32, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x33, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x34, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22
};
uint8_t laohuzuobiaotxt[3][15] = {
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x37, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x38, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x39, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22
}; 
uint8_t langzuobiaotxt[3][16] = {
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x32, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x33, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x34, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22
}; 
uint8_t houzizuobiaotxt[3][16] = {
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x37, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x38, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x31, 0x39, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22
}; 
uint8_t kongquezuobiaotxt[3][16] = {
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x32, 0x32, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x32, 0x33, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22,
	0x61, 0x6E, 0x69, 0x6D, 0x61, 0x6C, 0x2E, 0x74, 0x32, 0x34, 0x2E, 0x74, 0x78, 0x74, 0x3D, 0x22
}; 



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if(huart->Instance == USART1) {
        // 处理rx_buf中的数据帧
        if(dimianzhan_state == 0 && dimianzhan_data == 0x65 && jinqu_shuliang < 3)
		{
			dimianzhan_state++;
		}
		else if(dimianzhan_state == 1 && dimianzhan_data == 0x00)
		{
			dimianzhan_state++;
		}
		else if(dimianzhan_state == 2)
		{
			jinqu_buf[jinqu_shuliang] = dimianzhan_data;
			jinqu_shuliang++;
			dimianzhan_state = 0;
		}
		
		
        // 重新启动接收
        HAL_UART_Receive_IT(&huart1, &dimianzhan_data, sizeof(dimianzhan_data));
    }
	else if(huart->Instance == USART2) {
        // 处理rx_buf中的数据帧
		if((zuobiao_data != lastzuobiao_data) && (zuobiao_data != 0))
		{
		keyifadongwuxinxi = 1;
		lastzuobiao_data = zuobiao_data;
		zuobiao_datax = zuobiao_data>>4 | lingcha30;
		zuobiao_datay = zuobiao_data & lingcha0f;
		zuobiao_datay = zuobiao_datay | lingcha30;
        
		}
		
		HAL_UART_Receive_IT(&huart2, &zuobiao_data, sizeof(zuobiao_data));
        // 重新启动接收
    }
	else if(huart->Instance == USART3) {
        // 处理rx_buf中的数据帧
        if(maxicam_state == 0 && maxicam_data == 0xAA)
		{
			maxicam_state++;
		}
		else if(maxicam_state == 1)
		{
			daxiangshuliang = maxicam_data | lingcha30;
			maxicam_state++;
		}
		else if(maxicam_state == 2)
		{
			laohushuliang = maxicam_data | lingcha30;
			maxicam_state++;
		}
		else if(maxicam_state == 3)
		{
			langshuliang = maxicam_data | lingcha30;
			maxicam_state++;
		}
		else if(maxicam_state == 4)
		{
			houzishuliang = maxicam_data | lingcha30;
			maxicam_state++;
		}
		else if(maxicam_state == 5)
		{
			kongqueshuliang = maxicam_data | lingcha30;
			maxicam_state = 0;
		}
		
        // 重新启动接收
        HAL_UART_Receive_IT(&huart3, &maxicam_data, sizeof(maxicam_data));
    }
	
	
}
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
  /* USER CODE END 2 */
HAL_UART_Receive_IT(&huart1, &dimianzhan_data, sizeof(dimianzhan_data));
HAL_UART_Receive_IT(&huart2, &dimianzhan_data, sizeof(zuobiao_data));
HAL_UART_Receive_IT(&huart3, &dimianzhan_data, sizeof(maxicam_data));
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(jinqu_shuliang > 2 && jinqusuanwanle == 0) //解算禁区
	  {
		  jinqusuanwanle = 1;
		  for(int i = 0; i < 3; i++)
		  {
			  jinqu[i][0] = 8 - ((jinqu_buf[i] - 1)/ 7);
			  if(jinqu[i][0] % 2 == 0)
			  {
				  jinqu[i][1] = 6 - ((jinqu_buf[i]-1)%7);
			  }
			  else
			  {
				  jinqu[i][1] = (jinqu_buf[i]-1)%7;
			  }
		  }
		  keyifale = 1;
	  }
	  
	  
	  if(keyifale == 1 && guihuawanle == 0) //路径规划
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
	  
	
	  
	
if(keyifale == 1)
{
	for(int i = 0; i < path_cnt; i++)
		  {
			
			HAL_UART_Transmit(&huart2,&zhentou,1,0xFFFF); //发给凌霄禁区
			HAL_UART_Transmit(&huart2,(uint8_t*)jinqu,6,0xFFFF);
			HAL_UART_Transmit(&huart2,&zhenwei,1,0xFFFF);
			  
			if(keyifadongwuxinxi == 1)
			{
				HAL_UART_Transmit(&huart1,lingcha74,8,0xFFFF); //发给串口屏当前坐标
				HAL_UART_Transmit(&huart1,&lingcha41,1,0xFFFF);
				HAL_UART_Transmit(&huart1,&zuobiao_datax,1,0xFFFF);
				HAL_UART_Transmit(&huart1,&lingcha42,1,0xFFFF);
				HAL_UART_Transmit(&huart1,&zuobiao_datay,1,0xFFFF);
				HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
				
				HAL_UART_Transmit(&huart1,&dongwumingcheng[0][0],8,0xFFFF); //清空动物名称
				HAL_UART_Transmit(&huart1,dongwu1,9,0xFFFF);
				HAL_UART_Transmit(&huart1,&dongwumingcheng[1][0],8,0xFFFF);
				HAL_UART_Transmit(&huart1,dongwu2,9,0xFFFF);
				HAL_UART_Transmit(&huart1,&dongwumingcheng[2][0],8,0xFFFF);
				HAL_UART_Transmit(&huart1,dongwu3,9,0xFFFF);
				
				
				if(daxiangshuliang > 0x30)
				{
					daxiangshuliang_now = daxiangshuliang;
					HAL_UART_Transmit(&huart1,&dongwumingcheng[dongwuzhonglei][0],8,0xFFFF); //更改第一页动物
					HAL_UART_Transmit(&huart1,daxiangmingcheng,4,0xFFFF);
					HAL_UART_Transmit(&huart1,&lingcha3A,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&daxiangshuliang_now,1,0xFFFF);
					HAL_UART_Transmit(&huart1,dongwumingchengff,4,0xFFFF);
					dongwuzhonglei++;
					
					
					daxiangzongshuliang += daxiangshuliang_now-0x30; //更改第二页动物数量
					HAL_UART_Transmit(&huart1,daxiangshuliangtxt,15,0xFFFF);
					HAL_UART_Transmit(&huart1,&daxiangzongshuliang,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					
					for( int i = daxiangzongshuliang-daxiangshuliang_now; i < daxiangzongshuliang-0x30; i++) //更改第二页动物坐标
					{
						HAL_UART_Transmit(&huart1,&daxiangzuobiaotxt[i][0],15,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha41,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datax,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha42,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datay,1,0xFFFF);
						HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					}
					
				}
				if(laohushuliang > 0x30)
				{
					laohushuliang_now = laohushuliang;
					HAL_UART_Transmit(&huart1,&dongwumingcheng[dongwuzhonglei][0],8,0xFFFF);
					HAL_UART_Transmit(&huart1,laohumingcheng,4,0xFFFF);
					HAL_UART_Transmit(&huart1,&lingcha3A,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&laohushuliang_now,1,0xFFFF);
					HAL_UART_Transmit(&huart1,dongwumingchengff,4,0xFFFF);
					dongwuzhonglei++;
					
					laohuzongshuliang += laohushuliang_now-0x30; //更改第二页动物数量
					HAL_UART_Transmit(&huart1,laohushuliangtxt,15,0xFFFF);
					HAL_UART_Transmit(&huart1,&laohuzongshuliang,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					
					for( int i = laohuzongshuliang-laohushuliang_now; i < laohuzongshuliang-0x30; i++) //更改第二页动物坐标
					{
						HAL_UART_Transmit(&huart1,&laohuzuobiaotxt[i][0],15,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha41,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datax,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha42,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datay,1,0xFFFF);
						HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					}
				}
				if(langshuliang > 0x30)
				{
					langshuliang_now  = langshuliang;
					HAL_UART_Transmit(&huart1,&dongwumingcheng[dongwuzhonglei][0],8,0xFFFF);
					HAL_UART_Transmit(&huart1,langmingcheng,2,0xFFFF);
					HAL_UART_Transmit(&huart1,&lingcha3A,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&langshuliang_now,1,0xFFFF);
					HAL_UART_Transmit(&huart1,dongwumingchengff,4,0xFFFF);
					dongwuzhonglei++;
					
					langzongshuliang += langshuliang_now-0x30; //更改第二页动物数量
					HAL_UART_Transmit(&huart1,langshuliangtxt,16,0xFFFF);
					HAL_UART_Transmit(&huart1,&langzongshuliang,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					
					for( int i = langzongshuliang-langshuliang_now; i < langzongshuliang-0x30; i++) //更改第二页动物坐标
					{
						HAL_UART_Transmit(&huart1,&langzuobiaotxt[i][0],16,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha41,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datax,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha42,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datay,1,0xFFFF);
						HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					}
				}
				if(houzishuliang > 0x30)
				{
					houzishuliang_now = houzishuliang;
					HAL_UART_Transmit(&huart1,&dongwumingcheng[dongwuzhonglei][0],8,0xFFFF);
					HAL_UART_Transmit(&huart1,houzimingcheng,4,0xFFFF);
					HAL_UART_Transmit(&huart1,&lingcha3A,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&houzishuliang_now,1,0xFFFF);
					HAL_UART_Transmit(&huart1,dongwumingchengff,4,0xFFFF);
					dongwuzhonglei++;
					
					houzizongshuliang += houzishuliang_now-0x30; //更改第二页动物数量
					HAL_UART_Transmit(&huart1,houzishuliangtxt,16,0xFFFF);
					HAL_UART_Transmit(&huart1,&houzizongshuliang,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					
					for( int i = houzizongshuliang-houzishuliang_now; i < houzizongshuliang-0x30; i++) //更改第二页动物坐标
					{
						HAL_UART_Transmit(&huart1,&houzizuobiaotxt[i][0],16,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha41,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datax,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha42,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datay,1,0xFFFF);
						HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					}
				}
				if(kongqueshuliang > 0x30)
				{
					kongqueshuliang_now = kongqueshuliang;
					HAL_UART_Transmit(&huart1,&dongwumingcheng[dongwuzhonglei][0],8,0xFFFF);
					HAL_UART_Transmit(&huart1,kongquemingcheng,4,0xFFFF);
					HAL_UART_Transmit(&huart1,&lingcha3A,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongqueshuliang_now,1,0xFFFF);
					HAL_UART_Transmit(&huart1,dongwumingchengff,4,0xFFFF);
					dongwuzhonglei++;
					
					kongquezongshuliang += kongqueshuliang_now-0x30; //更改第二页动物数量
					HAL_UART_Transmit(&huart1,kongqueshuliangtxt,16,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongquezongshuliang,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					
					for( int i = kongquezongshuliang-kongqueshuliang_now; i < kongquezongshuliang-0x30; i++) //更改第二页动物坐标
					{
						HAL_UART_Transmit(&huart1,&kongquezuobiaotxt[i][0],16,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha41,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datax,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&lingcha42,1,0xFFFF);
						HAL_UART_Transmit(&huart1,&zuobiao_datay,1,0xFFFF);
						HAL_UART_Transmit(&huart1,lingcha22,4,0xFFFF);
					}
				}
				dongwuzhonglei = 0;
				keyifadongwuxinxi = 0;
			}
			  
			  
			  
			  if(path[i][0] % 2 == 0)
			  {
				  kongjianid[i] = (6-path[i][1])+(8-path[i][0])*7;
			  }
			  else
			  {
				  kongjianid[i] = path[i][1]+(8-path[i][0])*7;
			  }
			  switch(kongjianid[i])
			  {
				  case 0:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x30;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 1:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x31;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 2:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x32;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 3:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x33;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 4:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x34;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 5:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x35;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 6:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x36;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 7:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x37;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 8:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x38;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 9:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi = 0x39;
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,&kongjianidjiasanshi,1,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 10:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x30};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 11:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x31};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 12:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x32};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 13:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x33};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 14:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x34};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 15:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x35};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 16:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x36};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 17:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x37};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 18:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x38};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 19:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x31, 0x39};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 20:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x30};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 21:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x31};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 22:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x32};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 23:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x33};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 24:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x34};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 25:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x35};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 26:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x36};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 27:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x37};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 28:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x38};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 29:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x32, 0x39};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 30:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x30};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 31:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x31};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 32:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x32};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 33:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x33};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 34:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x34};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 35:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x35};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 36:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x36};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 37:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x37};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 38:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x38};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 39:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x33, 0x39};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 40:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x30};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 41:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x31};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 42:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x32};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 43:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x33};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 44:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x34};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 45:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x35};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 46:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x36};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 47:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x37};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 48:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x38};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 49:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x34, 0x39};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 50:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x30};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 51:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x31};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 52:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x32};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 53:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x33};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 54:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x34};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 55:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x35};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 56:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x36};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 57:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x37};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 58:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x38};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 59:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x35, 0x39};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 60:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x36, 0x30};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 61:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x36, 0x31};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
				  case 62:
				  {
					HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					uint8_t kongjianidjiasanshi[2] = {0x36, 0x32};
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianlv,7,0xFFFF);
					  
					  HAL_Delay(100);
					  
					 HAL_UART_Transmit(&huart1,&lingcha62,1,0xFFFF);
					HAL_UART_Transmit(&huart1,kongjianidjiasanshi,2,0xFFFF);
					HAL_UART_Transmit(&huart1,lingcha2E,5,0xFFFF);
					HAL_UART_Transmit(&huart1,bianhui,8,0xFFFF);
				  }
					  break;
				  
			  }
			  
		  }

}




  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
