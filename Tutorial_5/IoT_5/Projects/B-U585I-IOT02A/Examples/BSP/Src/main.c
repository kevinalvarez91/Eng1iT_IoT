
/**
 ******************************************************************************
 * @file    Examples/BSP/Src/main.c
 * @author  MCD Application Team
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <math.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#define RCC_SYS_CLOCK_FREQ 160000000 // should equal HAL_RCC_GetSysClockFreq()
#define RCC_HCLK_FREQ 160000000 // should equal HAL_RCC_GetHCLKFreq()

/** @addtogroup STM32U5xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */
/* Private variables --------------------------------------------------------*/
__IO FlagStatus UserButtonPressed = RESET;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
extern void initialise_monitor_handles(void);
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
BSP_DemoTypedef  BSP_examples[]=
{
		{Led_demo,    "LED"},
		{Button_demo, "BUTTON"},
		{Rs_demo,     "RangingSensor"},
		{Camera_demo, "CAMERA"},
		{Ms_demo,     "MotionSensor"},
		{Es_demo,     "EnvSensor"},
		{Ls_demo,     "LightSensor"},
		{OSPI_NOR_demo, "OSPI NOR"},
		{OSPI_RAM_demo, "OSPI RAM"},
		{AudioRecord_demo, "Audio"},
		{EEPROM_demo, "EEPROM"}
};
__IO uint8_t DemoIndex = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void CACHE_Enable(void);


/* Private functions ---------------------------------------------------------*/



/**
 * @brief  Main program
 * @param  None
 * @retval None
 */

int main(void)
{

	int32_t  result = 0;
	int32_t i;
	int32_t msTick, msTickPrev;
	int32_t fullScale;
	float outputDataRate, sensitivity;

	float weights_initial_ss[81];
	int32_t number_weights_ss;
	float dedw_ss[81];
	float bias_ss[15];
	unsigned int network_topology_ss[3] = { 3, 9, 6 };
	float output_ss[6];

	int32_t hasTrained;

	initialise_monitor_handles();	/*rtt*/
	/* STM32U5xx HAL library initialization:
       - Configure the Flash prefetch
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 3
       - Low Level Initialization
	 */
	HAL_Init();
	/* Enable the Instruction Cache */
	CACHE_Enable();
	/* Configure the System clock to have a frequency of 160 MHz */
	SystemClock_Config();

	/* STM32U5xx HAL library initialization:
	       - Configure the Flash prefetch
	       - Configure the Systick to generate an interrupt each 1 msec
	       - Set NVIC Group Priority to 3
	       - Low Level Initialization
	 */
	initialise_monitor_handles();	/*rtt*/

	HAL_Init();

	/* Enable the Instruction Cache */
	CACHE_Enable();

	/* Configure the System clock to have a frequency of 160 MHz */
	SystemClock_Config();

	/*
	 * Initialize User Button
	 */

	result = Ms_Button_Init();
	if (result < 0){
		printf("Initialization Error %i\n", result);
	}

	printf("\n");
	printf("\n\nEmbeddedML Single State Orientation Classification Press User Button to Start\n\n");
	User_Button_Wait();



	Ms_Init();

	result = 0;
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 2) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 2) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	result = 0;
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 3333.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 3333.0f) result--;

	result = 0;
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 833.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 833.0f) result--;

	result = 0;
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_ACCELERO, &sensitivity) != BSP_ERROR_NONE) result--;
	if (result < 0){
		printf("Sensitivity Error %i\n", result);
	}
	printf("Accelerometer Full Scale Range = %i (milli-g)\n", fullScale*1000);
	printf("Accelerometer Data Rate %0.1f (Hz), Sensitivity (milli-g) %0.1f\n\n", outputDataRate, sensitivity);
	result = 0;

	/* Initialize the Red LED */
	if (BSP_LED_Init(LED6) != BSP_ERROR_NONE) result--;
	/* Initialize the Green LED */
	if (BSP_LED_Init(LED7) != BSP_ERROR_NONE) result--;


	/* Initialize random values for weights */

	number_weights_ss = network_topology_ss[0]*network_topology_ss[1] +
			network_topology_ss[1]*network_topology_ss[2];


	srand(1);

	for (i = 0; i < number_weights_ss; i++){
		weights_initial_ss[i] = (float)rand()/RAND_MAX;
	}


	for (i = 0; i < 15; i++){
		bias_ss[i] = 0.5;
	}
	for (i = 0; i < 6; i++){
		output_ss[i] = 0.0;
	}
	for (i = 0; i < 81; i++){
		dedw_ss[i] = 0.0;
	}

	ANN net_ss;
	net_ss.weights = weights_initial_ss;

	net_ss.dedw = dedw_ss;
	net_ss.bias = bias_ss;
	net_ss.topology = network_topology_ss;
	net_ss.n_layers = 3;
	net_ss.n_weights = 81;
	net_ss.n_bias = 15;
	net_ss.output = output_ss;

	net_ss.eta = 0.13;     //Learning Rate
	net_ss.beta = 0.01;    //Bias Learning Rate
	net_ss.alpha = 0.25;   //Momentum Coefficient
	net_ss.output_activation_function = &relu2;
	net_ss.hidden_activation_function = &relu2;


	init_ann(&net_ss);


	hasTrained = 0;

	int loc = -1;
	while (1) {
		/* Get sysTick value and check if it's time to execute the task */
		msTick = HAL_GetTick();
		if (msTick % DATA_PERIOD_MS == 0 && msTickPrev != msTick) {
			msTickPrev = msTick;
			if (hasTrained){
				loc = Test_ANN(&net_ss, loc);
			}
		}

		if (!hasTrained) {
			printf("Press User Button to Start Training\n");
			User_Button_Wait();
			TrainOrientation(&net_ss);
			hasTrained = 1;
		}
	}
}




/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follows :
 *            System Clock source            = PLL (MSI)
 *            SYSCLK(Hz)                     = 160000000
 *            HCLK(Hz)                       = 160000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            APB2 Prescaler                 = 1
 *            APB3 Prescaler                 = 1
 *            MSI Frequency(Hz)              = 4000000
 *            PLL_MBOOST                     = 1
 *            PLL_M                          = 1
 *            PLL_N                          = 80
 *            PLL_Q                          = 2
 *            PLL_R                          = 2
 *            PLL_P                          = 2
 *            Flash Latency(WS)              = 4
 * @param  None
 * @retval None
 */


void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	/* Enable voltage range 1 for frequency above 100 Mhz */
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Switch to SMPS regulator instead of LDO */
	HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY);

	__HAL_RCC_PWR_CLK_DISABLE();

	/* MSI Oscillator enabled at reset (4Mhz), activate PLL with MSI as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 80;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLFRACN= 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}

	/* Select PLL as system clock source and configure bus clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | \
			RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_PCLK3);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}
}

/**
 * @brief  Enable ICACHE with 1-way set-associative configuration.
 * @param  None
 * @retval None
 */
static void CACHE_Enable(void)
{
	/* Configure ICACHE associativity mode */
	HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY);

	/* Enable ICACHE */
	HAL_ICACHE_Enable();
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void)
{
	printf("You have an ERROR!\n");
	while(1)
	{
		BSP_LED_Toggle(LED_RED);
		HAL_Delay(500);
	}
}

/**
 * @brief  Ask user for result.
 * @param  None
 * @retval None
 */
uint32_t CheckResult(void)
{
	printf("Next step loading..\n\n");

	return 0;
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %i\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_FULL_ASSERT */

/**
 * @brief  BSP Push Button callback
 * @param  Button Specifies the pin connected EXTI line
 * @retval None.
 */
void BSP_PB_Callback(Button_TypeDef Button)
{
	if (Button == BUTTON_USER)
	{
		UserButtonPressed = SET;
	}
}



