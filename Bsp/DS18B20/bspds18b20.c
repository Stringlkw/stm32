/***************************************************************
 * 模块名称 : DS18B20驱动模块
 * 文件名	  : BSPDS18B20.C
 * 说明  	  : 驱动DS18B20温度传感器
 * 版本号	  : v1.0
 * 修改记录 :
 * 	版本号	        日期	                  作者
 *  v1.0     2020-7-10      李康伟
 ***************************************************************/

/***************************************************************
 模块移植性说明
 ****************************************************************/
//TODO
/***************************************************************
 INCLUDES
 ****************************************************************/
#include "bspds18b20.h"

/***************************************************************
 DS18B20硬件接口定义
 ****************************************************************/
#define DS18B20_PORT              GPIOD
#define DS18B20_PIN               GPIO_PIN_6
#define DS18B20_CLK_ENABLE()	__HAL_RCC_GPIOD_CLK_ENABLE()

/***************************************************************
 DS18B20函数宏定义
 ****************************************************************/
#define DS18B20_DQ_RESET() HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET)
#define DS18B20_DQ_SET() HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET)
#define DS18B20_DQ_IN() HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)
#define DS18B20_DELAY_US(us)  CPU_TS_Tmr_Delay_US(us)
#define DS18B20_DELAY_MS(ms)  CPU_TS_Tmr_Delay_MS(ms)

/***************************************************************
 本模块提供给内部调用的函数
 ***************************************************************/
static void DS18B20_Init(); //DS18B20 GPIO初始化函数
static void DS18B20_Mode_IPU(); //DS18B20-DATA引脚输入模式
static void DS18B20_Mode_Out_PP(); //DS18B20-DATA引脚输出模式
static void DS18B20_Rst(); //复位
static uint8_t DS18B20_Presence(); //检测DS18B20是否连接，成功返回0，失败返回1
static uint8_t DS18B20_ReadBit(); //DS18B20读取一个bit
static uint8_t DS18B20_ReadByte(); //DS18B20读一个字节
static void DS18B20_WriteByte(uint8_t dat); //写一个字节到DS18B20
static void DS18B20_SkipRom();//跳过匹配 DS18B20 ROM

/**
 * @brief  DS18B20 初始化配置函数
 * @param  无
 * @retval DS18B20_Presence()
 */
uint8_t BSP_DS18B20_Config()
{
	DS18B20_Init();

	DS18B20_DQ_SET();

	DS18B20_Rst();

	return DS18B20_Presence();

}

/*
 * 函数名：DS18B20_GPIO_Init
 * 描述  ：配置DS18B20用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
static void DS18B20_Init()
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };

	/*开启DS18B20_DQ_GPIO_PORT的外设时钟*/
	DS18B20_CLK_ENABLE();

	/*选择要控制的DS18B20_DQ_GPIO_PORT引脚*/
	GPIO_InitStruct.Pin = DS18B20_PIN;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

	/*设置引脚速率为50MHz */
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/*调用库函数，初始化DS18B20_DQ_GPIO_PORT*/
	HAL_GPIO_Init( DS18B20_PORT, &GPIO_InitStruct);

}

/*
 * 函数名：DS18B20_Mode_IPU
 * 描述  ：使DS18B20-DATA引脚变为输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DS18B20_Mode_IPU()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*选择要控制的DS18B20_DQ_GPIO_PORT引脚*/
	GPIO_InitStruct.Pin = DS18B20_PIN;

	/*设置引脚模式为浮空输入模式*/
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

	/*调用库函数，初始化DS18B20_DQ_GPIO_PORT*/
	HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

/*
 * 函数名：DS18B20_Mode_Out_PP
 * 描述  ：使DS18B20-DATA引脚变为输出模式
 * 输入  ：无
 * 输出  ：无
 */
static void DS18B20_Mode_Out_PP()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*选择要控制的DS18B20_DQ_GPIO_PORT引脚*/
	GPIO_InitStruct.Pin = DS18B20_PIN;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

	/*设置引脚速率为50MHz */
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/*调用库函数，初始化DS18B20_DQ_GPIO_PORT*/
	HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

/*
 *主机给从机发送复位脉冲
 */
static void DS18B20_Rst()
{
	/* 主机设置为推挽输出 */
	DS18B20_Mode_Out_PP();

	DS18B20_DQ_RESET();
	/* 主机至少产生480us的低电平复位信号 */
	DS18B20_DELAY_US(750);

	/* 主机在产生复位信号后，需将总线拉高 */
	DS18B20_DQ_SET();

	/*从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲*/
	DS18B20_DELAY_US(15);
}

/*
 * 检测从机给主机返回的存在脉冲
 * 0：成功
 * 1：失败
 */
static uint8_t DS18B20_Presence()
{
	uint8_t pulse_time = 0;

	/* 主机设置为上拉输入 */
	DS18B20_Mode_IPU();

	/* 等待存在脉冲的到来，存在脉冲为一个60~240us的低电平信号
	 * 如果存在脉冲没有来则做超时处理，从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲
	 */
	while ( DS18B20_DQ_IN() && pulse_time < 100)
	{
		pulse_time++;
		DS18B20_DELAY_US(1);
	}
	/* 经过100us后，存在脉冲都还没有到来*/
	if (pulse_time >= 100)
		return 1;
	else
		pulse_time = 0;

	/* 存在脉冲到来，且存在的时间不能超过240us */
	while (!DS18B20_DQ_IN() && pulse_time < 240)
	{
		pulse_time++;
		DS18B20_DELAY_US(1);
	}
	if (pulse_time >= 240)
		return 1;
	else
		return 0;
}

/*
 * 从DS18B20读取一个bit
 */
static uint8_t DS18B20_ReadBit()
{
	uint8_t dat;

	/* 读0和读1的时间至少要大于60us */
	DS18B20_Mode_Out_PP();
	/* 读时间的起始：必须由主机产生 >1us <15us 的低电平信号 */
	DS18B20_DQ_RESET();
	DS18B20_DELAY_US(10);

	/* 设置成输入，释放总线，由外部上拉电阻将总线拉高 */
	DS18B20_Mode_IPU();
	//DS18B20_DELAY_US(2);

	if ( DS18B20_DQ_IN() == GPIO_PIN_SET)
		dat = 1;
	else
		dat = 0;

	/* 这个延时参数请参考时序图 */
	DS18B20_DELAY_US(45);

	return dat;
}

/*
 * 从DS18B20读一个字节，低位先行
 */
static uint8_t DS18B20_ReadByte()
{
	uint8_t i, j, dat = 0;

	for (i = 0; i < 8; i++)
	{
		j = DS18B20_ReadBit();
		dat = (dat) | (j << i);
	}

	return dat;
}

/*
 * 写一个字节到DS18B20，低位先行
 */
static void DS18B20_WriteByte(uint8_t dat)
{
	uint8_t i, testb;
	DS18B20_Mode_Out_PP();

	for (i = 0; i < 8; i++)
	{
		testb = dat & 0x01;
		dat = dat >> 1;
		/* 写0和写1的时间至少要大于60us */
		if (testb)
		{
			DS18B20_DQ_RESET();
			/* 1us < 这个延时 < 15us */
			DS18B20_DELAY_US(8);

			DS18B20_DQ_SET();
			DS18B20_DELAY_US(58);
		}
		else
		{
			DS18B20_DQ_RESET();
			/* 60us < Tx 0 < 120us */
			DS18B20_DELAY_US(70);

			DS18B20_DQ_SET();
			/* 1us < Trec(恢复时间) < 无穷大*/
			DS18B20_DELAY_US(2);
		}
	}
}

/**
 * @brief  跳过匹配 DS18B20 ROM
 * @param  无
 * @retval 无
 */
static void DS18B20_SkipRom()
{
	DS18B20_Rst();

	DS18B20_Presence();

	DS18B20_WriteByte(0XCC); /* 跳过 ROM */

}

/*
 * 存储的温度是16 位的带符号扩展的二进制补码形式
 * 当工作在12位分辨率时，其中5个符号位，7个整数位，4个小数位
 *
 *         |---------整数----------|-----小数 分辨率 1/(2^4)=0.0625----|
 * 低字节  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |
 *
 *
 *         |-----符号位：0->正  1->负-------|-----------整数-----------|
 * 高字节  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
 *
 *
 * 温度 = 符号位 + 整数 + 小数*0.0625
 */
/**
 * @brief  在跳过匹配 ROM 情况下获取 DS18B20 温度值
 * @param  无
 * @retval 温度值
 */
float BSP_DS18B20_GetTemp()
{
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;

	DS18B20_SkipRom();
	DS18B20_WriteByte(0X44); /* 开始转换 */

	DS18B20_SkipRom();
	DS18B20_WriteByte(0XBE); /* 读温度值 */

	tplsb = DS18B20_ReadByte();
	tpmsb = DS18B20_ReadByte();

	s_tem = tpmsb << 8;
	s_tem = s_tem | tplsb;

	if (s_tem < 0) /* 负温度 */
		f_tem = (~s_tem + 1) * 0.0625;
	else
		f_tem = s_tem * 0.0625;

	return f_tem;

}
/*************************************END OF FILE******************************/

