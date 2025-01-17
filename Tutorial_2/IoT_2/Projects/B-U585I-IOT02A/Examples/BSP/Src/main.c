
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
	BSP_MOTION_SENSOR_Axes_t axes;

	int32_t j;
	uint32_t msTick, msTickPrev = 0;

	int32_t rotation_rate_mag_threshold, acceleration_mag_threshold;
	int32_t accel_mag, gyro_mag;
	int32_t X_Offset, Y_Offset, Z_Offset;
	int32_t fullScale;

	initialise_monitor_handles();	/*rtt*/

	/* STM32U5xx HAL library initialization:
       - Configure the Flash prefetch
       - Configurethe Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 3
       - Low Level Initialization
	 */
	HAL_Init();
	/* Enable the Instruction Cache */
	CACHE_Enable();

	/* Configure the System clock to have a frequency of 160 MHz */
	SystemClock_Config();

	/* Initialize User Button */

	result = Ms_Button_Init();
	if (result < 0){
		printf("Initialization Error %i\n", result);
	}

	while (1)
	{

		printf("\n\nAccelerometer Event Detection Test: Start and Stop with User Button Click\n");
		User_Button_Wait();

		result = Ms_Accel_Init();
		if (result < 0){
			printf("Initialization Error %i\n", result);
		}

		/* GetFullScale and SetFullScale functions */
		if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 16) != BSP_ERROR_NONE) result--;
		if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
		if (fullScale != 16) result--;
		if (result < 0){
			printf("Sensor Full Scale Error %i\n", result);
		}

		if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 2) != BSP_ERROR_NONE) result--;
		if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
		if (fullScale != 2) result--;
		if (result < 0){
			printf("Sensor Full Scale Error %i\n", result);
		}

		/*
		 *  Adjust acceleration magnitude event detection threshold
		 */

		acceleration_mag_threshold = 500;

		printf("Acceleration Magnitude Event Detection Threshold: %i (milli-g) \n",
				acceleration_mag_threshold);

		while (UserButtonPressed == 0)
		{
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n", result);
			}
			msTick = HAL_GetTick();

			accel_mag = axes.xval*axes.xval + axes.yval*axes.yval + (((axes.zval - 1000) - 1000))*((axes.zval - 1000));
			accel_mag = sqrt(accel_mag);

			if (accel_mag > acceleration_mag_threshold ){
				printf("Event Time %i, X = %i, Y = %i, , Z = %i, |Acc| = %i\n", msTick, axes.xval,
						axes.yval, (axes.zval - 1000), accel_mag);
			}
		}


		printf("\n\nGyroscope Event Detection Test: Start and Stop with User Button Click\n");

		result = Ms_Gyro_Init();
		if (result < 0){
			printf("Initialization Error %i\n", result);
		}

		rotation_rate_mag_threshold = 300;
		printf("Rotation Rate Magnitude Event Detection Threshold: %i (milli-degree/s) \n",
				rotation_rate_mag_threshold);


		User_Button_Wait();

		while (UserButtonPressed == 0)
		{
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n", result);
			}
			msTick = HAL_GetTick();
			gyro_mag = axes.xval*axes.xval + axes.yval*axes.yval + (axes.zval - 1000)*(axes.zval - 1000);
			gyro_mag = sqrt(gyro_mag);

			if (gyro_mag > rotation_rate_mag_threshold){
				printf("Angular Velocity (mdeg/sec): Time %i, X = %i, Y = %i, , Z = %i, "
						"|Ang Velocity| = %i\n", msTick, axes.xval, axes.yval, (axes.zval - 1000), gyro_mag);
			}

		}

		printf("\n\nGyroscope Event Detection Test Using Offset Correction: Start and Stop with User Button Click\n");
		User_Button_Wait();

		HAL_Delay(1000);

		printf("Place IoT Node at Rest on Table and Maintain Motionless\n");

		HAL_Delay(3000);

		printf("5 Second Zero Offset Measurement Starting\n");

		msTickPrev = HAL_GetTick();

		X_Offset = 0;
		Y_Offset = 0;
		Z_Offset = 0;

		j = 0;

		while ((HAL_GetTick() - msTickPrev) < 5000){
			HAL_Delay(100);
			j = j + 1;
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n", result);
			}
			X_Offset = X_Offset + axes.xval;
			Y_Offset = Y_Offset + axes.yval;
			Z_Offset = Z_Offset + (axes.zval - 1000);
		}
		X_Offset = X_Offset/j;
		Y_Offset = Y_Offset/j;
		Z_Offset = Z_Offset/j;

		printf("Rotation Rate Offsets (milli-deg/s): X_Offset %i, Y_Offset %i, Z_Offset %i\n", X_Offset, Y_Offset, Z_Offset);

		UserButtonPressed = RESET;

		rotation_rate_mag_threshold = 500;
		printf("Rotation Rate Magnitude Event Detection Threshold: %i (milli-degree/s) \n", rotation_rate_mag_threshold);


		printf("\nGyroscope Event Detection Test: Start and Stop with User Button Click\n");
		User_Button_Wait();

		while (UserButtonPressed == 0)
		{
			HAL_Delay(100);
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n", result);
			}
			axes.xval = axes.xval - X_Offset;
			axes.yval = axes.yval - Y_Offset;
			axes.zval = axes.zval - 1000 - Z_Offset;

			msTick = HAL_GetTick();
			gyro_mag = axes.xval*axes.xval + axes.yval*axes.yval + (axes.zval - 1000)*(axes.zval - 1000);
			gyro_mag = sqrt(gyro_mag);

			if (gyro_mag > rotation_rate_mag_threshold){
				printf("Event - Angular Velocity (mdeg/sec): Time %i, X = %i, Y = %i, , Z = %i, |Ang Velocity| = %i\n", msTick, axes.xval, axes.yval, (axes.zval - 1000), gyro_mag);
			}

		}
		UserButtonPressed = RESET;


		printf("\n\nGyroscope Event Detection Test with Reduced Threshold: Start and Stop with User Button Click\n");
		rotation_rate_mag_threshold = 500;
		printf("\nRotation Rate Magnitude Event Detection Threshold: %i (milli-degree/s) \n", rotation_rate_mag_threshold);

		User_Button_Wait();



		while (UserButtonPressed == 0)
		{
			HAL_Delay(100);
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n", result);
			}

			axes.xval = axes.xval - X_Offset;
			axes.yval = axes.yval - Y_Offset;
			(axes.zval) = axes.zval - 1000 - Z_Offset;

			msTick = HAL_GetTick();
			gyro_mag = axes.xval*axes.xval + axes.yval*axes.yval + (axes.zval - 1000)*(axes.zval - 1000);
			gyro_mag = sqrt(gyro_mag);

			if (gyro_mag > rotation_rate_mag_threshold){
				printf("Event - Angular Velocity (mdeg/sec): Time %i, X = %i, Y = %i, , Z = %i, |Ang Velocity| = %i\n", msTick, axes.xval, axes.yval, (axes.zval - 1000), gyro_mag);
			}

		}

		UserButtonPressed = RESET;
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



