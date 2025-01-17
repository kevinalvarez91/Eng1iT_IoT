
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

	/* Initialize User Button */

	result = Ms_Button_Init();
	if (result < 0){
		printf("Initialization Error %i\n", result);
	}

	int32_t i, k;

	float ground_truth[2];

	float error, net_error;

	int32_t number_weights;
	float dedw[81];
	float bias[15];
	unsigned int network_topology[3] = { 3, 9, 6 };

	float output[6];
	float x[3];
	float y[6];
	float weights_initial[81];

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
	printf("Embedded ML XOR-AND Press User Button to Start\n");


	number_weights = network_topology[0]*network_topology[1] + network_topology[1]*network_topology[2];



	/*
	 * XOR-AND Input Values corresponding to output Ground Truth values
	 * The neural network includes 3 input neurons
	 *
	 */

	float x0[3] = { 0.0, 0.0, 0.0 };  // Corresponds to output 0 0
	float x1[3] = { 0.0, 0.0, 1.0 };  // Corresponds to output 0 0
	float x2[3] = { 0.0, 1.0, 0.0 };  // Corresponds to output 1 0
	float x3[3] = { 0.0, 1.0, 1.0 };  // Corresponds to output 1 1
	float x4[3] = { 1.0, 0.0, 0.0 };  // Corresponds to output 1 0
	float x5[3] = { 1.0, 0.0, 1.0 };  // Corresponds to output 1 0
	float x6[3] = { 1.0, 1.0, 0.0 };  // Corresponds to output 0 0
	float x7[3] = { 1.0, 1.0, 1.0 };  // Corresponds to output 0 1


	User_Button_Wait();


	/* Initialize random values for weights */

	srand(1);

	for (i = 0; i < number_weights; i++){
		weights_initial[i] = (float)rand()/RAND_MAX;
	}


	for (i = 0; i < 15; i++){
		bias[i] = 0.5;
	}
	for (i = 0; i < 6; i++){
		output[i] = 0.0;
	}
	for (i = 0; i < 81; i++){
		dedw[i] = 0.0;
	}

	ANN net;
	net.weights = weights_initial;
	net.dedw = dedw;
	net.bias = bias;
	net.topology = network_topology;
	net.n_layers = 3;
	net.n_weights = number_weights;
	net.n_bias = 15;
	net.output = output;


	net.eta = 0.2;     						//Learning Rate
	net.beta = 0.005;    					//Bias Learning Rate
	net.alpha = 0.25;   					//Momentum Coefficient
	net.output_activation_function = &relu;
	net.hidden_activation_function = &relu;


	while(1){

		/*
		 * Initialize neural network data structure
		 */

		init_ann(&net);

		/*
		 * Initiate train and test cycles
		 */

		i = 0;
		k = 0;
		while (i < N_EPOCH_XOR_AND && UserButtonPressed == 0) {

			/*
			 * Compute input and output ground truth
			 */

			/*
			 * Generate uniformly distributed selection of XOR-AND inputs and
			 * ground truth outputs
			 */

			k = k + 1;
			if (k > 7){
				k = 0;
			}

			generate_xorand(x, y, k);

			/*
			 * Train network on input and ground truth
			 */

			train_ann(&net, x, y);

			/*
			 * After completion of a number of epochs, N_REPORT
			 * perform neural network test execution, display
			 * resulting outputs and output error
			 */

			if (i % N_REPORT_XOR_AND == 0 || i == 0 || ((i < 500) && (i % 100 == 0)) ) {
				printf("\n\n        Epoch: %i\n", i);
				printf("    Ground         Network\n");
				printf("    Truth          Outputs\n");
				printf("   1	  2       1      2\n");
				printf("_____________________________\n");
				net_error = 0;

				/*
				 * Execute trained network and compute Output Error
				 * with Ground Truth supplied in ground_truth array
				 */

				run_ann(&net, x0);
				ground_truth[0] = 0.0;
				ground_truth[1] = 0.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x1);
				ground_truth[0] = 0.0;
				ground_truth[1] = 1.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x2);
				ground_truth[0] = 1.0;
				ground_truth[1] = 1.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x3);
				ground_truth[0] = 1.0;
				ground_truth[1] = 0.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x4);
				ground_truth[0] = 1.0;
				ground_truth[1] = 0.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x5);
				ground_truth[0] = 1.0;
				ground_truth[1] = 1.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x6);
				ground_truth[0] = 0.0;
				ground_truth[1] = 1.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				run_ann(&net, x7);
				ground_truth[0] = 0.0;
				ground_truth[1] = 0.0;
				Output_Error(2, &net, ground_truth, &error);
				net_error = net_error + error;

				printf("\nTotal Mean Squared Error: %0.3f", net_error);
			}

			/* Exit train and test cycles if test error is less than 1 percent */
			if (net_error < 0.01){
				break;
			}

			i++;
		}

		printf("\n\n\nTrain and Test Complete at Epoch: %i with Total Error: %0.3f\n", i, net_error);
		printf("\n\nPress User Button to Repeat\n");
		User_Button_Wait();

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



