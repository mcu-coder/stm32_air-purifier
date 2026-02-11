#include "gpio.h"


/****
*******	LED IO初始化
*****/    
void Gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RELAY_FS_GPIO_CLK|LEDS_GPIO_CLK|BEEP_GPIO_CLK,ENABLE);			    //使能端口时钟

	GPIO_InitStructure.GPIO_Pin  = LEDS_GPIO_PIN;  						//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
 	GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_SetBits(LEDS_GPIO_PORT,LEDS_GPIO_PIN);  							//IO口输出高

	GPIO_InitStructure.GPIO_Pin  = LED_PIN; 									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
 	GPIO_Init(LED_PORT, &GPIO_InitStructure);									//根据设定参数初始化
	GPIO_SetBits(LED_PORT,LED_PIN); 				 									//IO口输出高

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
	GPIO_InitStructure.GPIO_Pin  = BEEP_PIN; 									//引脚配置
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);								//根据设定参数初始化
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN); 				 							//IO口输出低

	GPIO_InitStructure.GPIO_Pin  = RELAY_FS_PIN|RELAY_JH_PIN; //引脚配置
 	GPIO_Init(RELAY_FS_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_ResetBits(RELAY_FS_PORT,RELAY_FS_PIN|RELAY_JH_PIN);  //IO口输出低
	
	GPIO_InitStructure.GPIO_Pin = CHECK_S_PIN|CHECK_H_PIN|CHECK_T_PIN|CHECK_JQ_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(CHECK_S_PORT,&GPIO_InitStructure);
}

