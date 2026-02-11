#ifndef __GPIO_H
#define __GPIO_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
重定义关键词
**********************************/
#define LEDS_GPIO_CLK                 RCC_APB2Periph_GPIOC        //最小系统LED
#define LEDS_GPIO_PORT                GPIOC
#define LEDS_GPIO_PIN                 GPIO_Pin_13
#define LED_SYS                       PCout(13)

#define BEEP_GPIO_CLK                 RCC_APB2Periph_GPIOB				//蜂鸣器引脚
#define BEEP_PORT                     GPIOB
#define BEEP_PIN                      GPIO_Pin_1
#define BEEP 									    		PBout(1)

#define LED_GPIO_CLK                  RCC_APB2Periph_GPIOB				//LED灯引脚
#define LED_PORT                      GPIOB
#define LED_PIN                       GPIO_Pin_0
#define LED 									    		PBout(0)

#define RELAY_FS_GPIO_CLK             RCC_APB2Periph_GPIOB				//风扇继电器引脚
#define RELAY_FS_PORT                 GPIOB
#define RELAY_FS_PIN                  GPIO_Pin_10
#define RELAY_FS 											PBout(10)

#define RELAY_JH_GPIO_CLK             RCC_APB2Periph_GPIOB				//净化继电器引脚
#define RELAY_JH_PORT                 GPIOB
#define RELAY_JH_PIN                  GPIO_Pin_11
#define RELAY_JH 											PBout(11)

#define CHECK_S_GPIO_CLK              RCC_APB2Periph_GPIOB				//烟雾检测引脚
#define CHECK_S_PORT                  GPIOB
#define CHECK_S_PIN                   GPIO_Pin_12
#define CHECK_S 											PBin(12)

#define CHECK_T_GPIO_CLK              RCC_APB2Periph_GPIOB				//天然气检测引脚
#define CHECK_T_PORT                  GPIOB
#define CHECK_T_PIN                   GPIO_Pin_13
#define CHECK_T 											PBin(13)

#define CHECK_H_GPIO_CLK              RCC_APB2Periph_GPIOA				//有害气体检测引脚
#define CHECK_H_PORT                  GPIOB
#define CHECK_H_PIN                   GPIO_Pin_14
#define CHECK_H 											PBin(14)

#define CHECK_JQ_GPIO_CLK             RCC_APB2Periph_GPIOA				//甲醛气体检测引脚
#define CHECK_JQ_PORT                 GPIOB
#define CHECK_JQ_PIN                  GPIO_Pin_15
#define CHECK_JQ 											PBin(15)


/**********************************
函数声明
**********************************/
void Gpio_Init(void);													//GPIO初始化


#endif
