#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "delay.h"
#include "gpio.h"
#include "key.h"
#include "oled.h"
#include "usart.h"
#include "adc.h"
#include "dht11.h"
#include "pm25.h"
/**********************************
变量定义
**********************************/
uint8_t key_num = 0;									//按键扫描标志位	
uint8_t flag_display = 0;							//显示界面标志位
uint32_t time_num = 0;								//10ms计时
char display_buf[32];									//显示缓存区

_Bool flag_mode = 0;									//当前模式标志位
extern uint8_t usart1_buf[256];				//串口1接收数组

u16 smog_value = 0;                   //烟雾值
u16 smog_max = 80;                   	//烟雾最大值
u16 trq_value = 0;                    //天然气值
u16 trq_max = 80;                    	//天然气最大值
u16 har_value = 0;                    //有害气体值
u16 har_max = 80;                    	//有害气体最大值
u16 jq_value = 0;											//甲醛气体值
u16 jq_max = 80;											//甲醛气体最大值
u16 temp_value = 0;                   //温度值
u16 temp_max = 35;                   	//温度最大值
_Bool flag_yy_temp = 0;								//语音标志位
u16 humi_value = 0;                   //湿度值
u16 humi_max = 70;                   	//湿度最大值
_Bool flag_yy_humi = 0;								//语音标志位
u16 pm_value = 0;											//PM2.5值
u16 pm_max = 300;											//PM2.5最大值

/**********************************
函数声明
**********************************/
void Key_function(void);							//按键函数
void Monitor_function(void);					//监测函数
void Display_function(void);					//显示函数
void Manage_function(void);						//处理函数


/****
*******	主函数 
*****/
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置中断优先分组
	Delay_Init();	    	 								//延时初始化	  
	Gpio_Init();		  									//IO初始化
	Key_Init();		  										//按键初始化
	Oled_Init();		  									//OLED初始化
	 
	while(1)
	{
		Key_function();										//按键函数
		Monitor_function();								//监测函数
		Display_function();								//显示函数
		Manage_function();								//处理函数

		time_num++;												//计时变量+1
		Delay_ms(10);
		if(time_num %10 == 0)
			LED_SYS = ~LED_SYS;
		if(time_num >= 5000)
		{
			time_num = 0;
		}
	}
}

/****
*******按键函数
*****/
void Key_function(void)
{
	key_num = Chiclet_Keyboard_Scan(0);		//按键扫描
	if(key_num != 0)											//有按键按下
	{
		switch(key_num)
		{
			case 1:								            //按键1，切换设置界面
				flag_display++;
				if(flag_display >= 8)
					flag_display = 0;
				
				Oled_Clear_All();					      //清屏
			break;
 

			default:
				
			break;
		}
	}
}

/****
*******监测函数
*****/
void Monitor_function(void)
{
	if(flag_display == 0)									//测量界面
	{
		if(time_num % 2 == 0)							//获取数据
		{
			if(CHECK_S == 0)																			//如果烟雾触发检测烟雾值
				smog_value = 90*(Get_Adc_Average(0,3)*3.3/4096.0);
			else
				smog_value = 0;
			
			if(CHECK_T == 0)																			//如果天然气触发检测天然气值
				trq_value = 90*(Get_Adc_Average(1,3)*3.3/4096.0);
			else
				trq_value = 0;
			
			if(CHECK_H == 0)																			//如果有害气体触发检测有害气体值
				har_value = 90*(Get_Adc_Average(4,3)*3.3/4096.0);
			else
				har_value = 0;
			
			if(CHECK_JQ == 0)																			//如果甲醛气体触发检测甲醛气体的数值
				jq_value = 90*(Get_Adc_Average(5,3)*3.3/4096.0);
			else
				jq_value = 0;
			
			pm_value=Pm25_Get_Value(3);
			if(pm_value<200)pm_value=0;
			Dht11_Get_Temp_Humi_Value(&temp_value,&humi_value);
			
		}
		 
	}
}

/****
*******显示函数
*****/
void Display_function(void)
{
	switch(flag_display)									//根据不同的显示模式标志位，显示不同的界面
	{
		case 0:									      			//界面0：
			
		Oled_ShowCHinese(1,0,"温度");
		sprintf(display_buf,":%d",temp_value/10);				//显示温度的值
		Oled_ShowString(1, 4, display_buf);
		
		
		Oled_ShowCHinese(1,4,"湿度");
		sprintf(display_buf,":%d%%",humi_value/10);				//显示湿度的值
	  Oled_ShowString(1, 12, display_buf);

			
		
		
			Oled_ShowCHinese(2,0,"烟雾");
		 
		break;
		
		case 1:															//界面1：
			Oled_ShowCHinese(1,0,"设置烟雾最大值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d  ",smog_max);
				Oled_ShowString(2, 7, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "    ");
			}
			
		break;
		 
			
		
		default:
			
		break;
	}
}

/****
*******处理函数
*****/
void Manage_function(void)
{
	if(flag_display == 0)                  //测量界面
	{	
		if(flag_mode == 0)
		{
			if(smog_value > smog_max ||  pm_value > pm_max)//有值大于设置的最大值,通风、净化，触发报警
			{
				RELAY_FS = 1;
				RELAY_JH = 1;
				if(time_num % 2 == 0)
				{
					LED = ~LED;
					BEEP = ~BEEP;
				}
			} 
		}
		else
		{
			LED = 1;
      BEEP = 0;
		}
	}
	else													         //设置界面
	{
		RELAY_FS = 0;
    RELAY_JH = 0;
		LED = 1;
		BEEP = 0;
	}
}

