
/**
 ******************************************************************************
 * @file    motion_sensor.c
 * @author  MCD Application Team
 * @brief   This example code shows how to use the motion sensor feature in the
 *          b_u585i_iot02_motion_sensors  driver
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

/** @addtogroup STM32U5xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Ms_Disable(void)
{
	int32_t  result  = 0;
	/* Disable function */
	if (BSP_MOTION_SENSOR_Disable(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	/* De-initialize function */
	if (BSP_MOTION_SENSOR_DeInit(0) != BSP_ERROR_NONE) result--;
}

int32_t  Ms_Accel_Init(void)
{
	int32_t  result  = 0;
	MOTION_SENSOR_Capabilities_t Capabilities;
	uint8_t chipId;
	float sensitivity, outputDataRate;
	int32_t fullScale;

	/* Initialize function for Microaccelerometer */

	/* Initialize function */
	if (BSP_MOTION_SENSOR_Init(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	if (BSP_MOTION_SENSOR_GetCapabilities(0, &Capabilities) != BSP_ERROR_NONE) result--;

	/* Read id function */
	if (BSP_MOTION_SENSOR_ReadID(0, &chipId) != BSP_ERROR_NONE) result--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	/* GetFullScale and SetFullScale functions */
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 16) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 16) result--;

	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 2) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 2) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 3333.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 3333.0f) result--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 208.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 208.0f) result--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_ACCELERO, &sensitivity) != BSP_ERROR_NONE) result--;

	return result;

}

int32_t Ms_Gyro_Init(void)
{
	int32_t  result  = 0;
	MOTION_SENSOR_Capabilities_t Capabilities;
	uint8_t chipId;
	float sensitivity, outputDataRate;
	int32_t fullScale;

	/* Initialize function for Microgyro */

	/* Initialize function */

	if (BSP_MOTION_SENSOR_Init(0, MOTION_GYRO) != BSP_ERROR_NONE) result--;

	if (BSP_MOTION_SENSOR_GetCapabilities(0, &Capabilities) != BSP_ERROR_NONE) result--;

	/* Read id function */
	if (BSP_MOTION_SENSOR_ReadID(0, &chipId) != BSP_ERROR_NONE) result--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(0, MOTION_GYRO) != BSP_ERROR_NONE) result--;

	/* GetFullScale and SetFullScale functions */
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_GYRO, 2000) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_GYRO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 2000) result--;

	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_GYRO, 500) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_GYRO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 500) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_GYRO, 3333.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_GYRO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 3333.0f) result--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_GYRO, 208.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_GYRO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 208.0f) result--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_GYRO, &sensitivity) != BSP_ERROR_NONE) result--;

	return result;

}

int32_t Ms_Button_Init(void)
{
	int32_t  result  = 0;
	/* Initialize user button */
	if (BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI) != BSP_ERROR_NONE) result--;
	return result;
}

void User_Button_Wait_Stop()
{
	printf("\n");
	printf("Click User Button to Stop\n");
	UserButtonPressed = RESET;
	while (UserButtonPressed == 0)
	{
		HAL_Delay(10);
	}
	UserButtonPressed = RESET;
	printf("\n");
}

void User_Button_Wait()
{
	printf("\n");
	UserButtonPressed = RESET;
	while (UserButtonPressed == 0)
	{
		HAL_Delay(10);
	}
	UserButtonPressed = RESET;
	printf("\n");
}

int32_t Mg_Init(void)
{
		int32_t result = 0;
		MOTION_SENSOR_Capabilities_t Capabilities;
		uint8_t chipId;
		float sensitivity, outputDataRate;
		int32_t fullScale;

		/* Initialize function */
		if (BSP_MOTION_SENSOR_Init(1, MOTION_MAGNETO) != BSP_ERROR_NONE) result--;

		if (BSP_MOTION_SENSOR_GetCapabilities(1, &Capabilities) != BSP_ERROR_NONE) result--;

		/* Read id function */
		if (BSP_MOTION_SENSOR_ReadID(1, &chipId) != BSP_ERROR_NONE) result--;

		/* Enable function */
		if (BSP_MOTION_SENSOR_Enable(1, MOTION_MAGNETO) != BSP_ERROR_NONE) result--;

		/* GetFullScale functions */
		if (BSP_MOTION_SENSOR_GetFullScale(1, MOTION_MAGNETO, &fullScale) != BSP_ERROR_NONE) result--;
		if (fullScale != 50) result--;

		/* GetOutputDataRate and SetOutputDataRate functions */
		if (BSP_MOTION_SENSOR_SetOutputDataRate(1, MOTION_MAGNETO, 80.0f) != BSP_ERROR_NONE) result--;
		if (BSP_MOTION_SENSOR_GetOutputDataRate(1, MOTION_MAGNETO, &outputDataRate) != BSP_ERROR_NONE) result--;
		if (outputDataRate != 100.0f) result--;

		if (BSP_MOTION_SENSOR_SetOutputDataRate(1, MOTION_MAGNETO, 20.0f) != BSP_ERROR_NONE) result--;
		if (BSP_MOTION_SENSOR_GetOutputDataRate(1, MOTION_MAGNETO, &outputDataRate) != BSP_ERROR_NONE) result--;
		if (outputDataRate != 20.0f) result--;

		/* GetSensitivity function */
		if (BSP_MOTION_SENSOR_GetSensitivity(1, MOTION_MAGNETO, &sensitivity) != BSP_ERROR_NONE) result--;
		return result;
}

int32_t Ms_Init(void)
{
	int32_t  result  = 0;
	MOTION_SENSOR_Capabilities_t Capabilities;
	uint8_t chipId;
	float sensitivity, outputDataRate;
	int32_t fullScale;

	/* Initialize function for Microaccelerometer */

	/* Initialize user button */
	if (BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI) != BSP_ERROR_NONE) result--;

	/* Initialize function */
	if (BSP_MOTION_SENSOR_Init(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	if (BSP_MOTION_SENSOR_GetCapabilities(0, &Capabilities) != BSP_ERROR_NONE) result--;

	/* Read id function */
	if (BSP_MOTION_SENSOR_ReadID(0, &chipId) != BSP_ERROR_NONE) result--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	/* GetFullScale and SetFullScale functions */
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 16) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 16) result--;

	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 2) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 2) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 3333.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 3333.0f) result--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 208.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 208.0f) result--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_ACCELERO, &sensitivity) != BSP_ERROR_NONE) result--;

	/* Initialize function for Microgyro */

	/* Initialize function */
	if (BSP_MOTION_SENSOR_Init(0, MOTION_GYRO) != BSP_ERROR_NONE) result--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(0, MOTION_GYRO) != BSP_ERROR_NONE) result--;

	/* GetFullScale and SetFullScale functions */
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_GYRO, 2000) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_GYRO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 2000) result--;

	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_GYRO, 500) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_GYRO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 500) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_GYRO, 3333.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_GYRO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 3333.0f) result--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_GYRO, 208.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_GYRO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 208.0f) result--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_GYRO, &sensitivity) != BSP_ERROR_NONE) result--;
	return result;
}

/**
 * @brief  Motion sensor demo
 * @param  None
 * @retval 0 if ok, else value < 0.
 */
int32_t Ms_demo(void)
{
	int32_t  result  = 0;
	MOTION_SENSOR_Capabilities_t Capabilities;
	BSP_MOTION_SENSOR_Axes_t         axes;
	uint8_t chipId;
	float sensitivity, outputDataRate;
	int32_t fullScale;
	int32_t  gresult  = 0;
	MOTION_SENSOR_Capabilities_t gCapabilities;
	uint8_t gchipId;
	float gsensitivity, goutputDataRate;
	int32_t gfullScale;

	printf("\n******MOTION SENSORS EXAMPLE******\n");
	printf("Press user button for next step\n");

	/* Initialize user button */
	if (BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI) != BSP_ERROR_NONE) result--;

	/* --------------- */
	/* TEST of IIS2MDC */
	/* --------------- */

	/*************************/
	/* Test of Accelerometer */
	/*************************/
	printf("TEST OF IIS2MDC ACCLEROMETER\n");

	/* Initialize function */
	if (BSP_MOTION_SENSOR_Init(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	if (BSP_MOTION_SENSOR_GetCapabilities(0, &Capabilities) != BSP_ERROR_NONE) result--;

	/* Read id function */
	if (BSP_MOTION_SENSOR_ReadID(0, &chipId) != BSP_ERROR_NONE) result--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	/* GetFullScale and SetFullScale functions */
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 16) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 16) result--;

	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_ACCELERO, 2) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_ACCELERO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 2) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 3333.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 3333.0f) result--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_ACCELERO, 208.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_ACCELERO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 208.0f) result--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_ACCELERO, &sensitivity) != BSP_ERROR_NONE) result--;

	/* GetAxes function */
	printf("Accelerometer axes:\n");
	while (UserButtonPressed == 0)
	{
		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
		printf("X = %d, Y = %d, , Z = %d\n", axes.xval, axes.yval, axes.zval);
		HAL_Delay(500);
	}
	HAL_Delay(1000);
	UserButtonPressed = RESET;


	/* Disable function */
	if (BSP_MOTION_SENSOR_Disable(0, MOTION_ACCELERO) != BSP_ERROR_NONE) result--;

	/* De-initialize function */
	if (BSP_MOTION_SENSOR_DeInit(0) != BSP_ERROR_NONE) result--;

	/*********************/
	/* Test of Gyroscope */
	/*********************/
	printf("TEST OF IIS2MDC GYROSCOPE\n");

	if (BSP_MOTION_SENSOR_GetCapabilities(0, &gCapabilities) != BSP_ERROR_NONE) gresult--;

	/* Read id function */

	if (BSP_MOTION_SENSOR_ReadID(0, &gchipId) != BSP_ERROR_NONE) gresult--;

	/* Initialize function */
	if (BSP_MOTION_SENSOR_Init(0, MOTION_GYRO) != BSP_ERROR_NONE) gresult--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(0, MOTION_GYRO) != BSP_ERROR_NONE) gresult--;

	/* GetFullScale and SetFullScale functions */
	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_GYRO, 2000) != BSP_ERROR_NONE) gresult--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_GYRO, &gfullScale) != BSP_ERROR_NONE) gresult--;
	if (gfullScale != 2000) gresult--;

	if (BSP_MOTION_SENSOR_SetFullScale(0, MOTION_GYRO, 500) != BSP_ERROR_NONE) gresult--;
	if (BSP_MOTION_SENSOR_GetFullScale(0, MOTION_GYRO, &gfullScale) != BSP_ERROR_NONE) gresult--;
	if (gfullScale != 500) gresult--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_GYRO, 3333.0f) != BSP_ERROR_NONE) gresult--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_GYRO, &goutputDataRate) != BSP_ERROR_NONE) gresult--;
	if (goutputDataRate != 3333.0f) gresult--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(0, MOTION_GYRO, 208.0f) != BSP_ERROR_NONE) gresult--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(0, MOTION_GYRO, &goutputDataRate) != BSP_ERROR_NONE) gresult--;
	if (goutputDataRate != 208.0f) gresult--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(0, MOTION_GYRO, &gsensitivity) != BSP_ERROR_NONE) gresult--;

	/* GetAxes function */
	printf("Gyroscope and Accelerometer axes:\n");
	while (UserButtonPressed == 0)
	{
		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
		printf("Accel X = %d, Y = %d, , Z = %d\n", axes.xval, axes.yval, axes.zval);
		HAL_Delay(500);
	}
	HAL_Delay(1000);
	UserButtonPressed = RESET;


	/* Disable function */
	if (BSP_MOTION_SENSOR_Disable(0, MOTION_GYRO) != BSP_ERROR_NONE) result--;

	/* De-initialize function */
	if (BSP_MOTION_SENSOR_DeInit(0) != BSP_ERROR_NONE) result--;

	/* --------------- */
	/* TEST of ISM330DHCX */
	/* --------------- */

	/************************/
	/* Test of Magnetometer */
	/************************/
	printf("TEST OF ISM330DHCX MAGNETOMETER\n");

	/* Initialize function */
	if (BSP_MOTION_SENSOR_Init(1, MOTION_MAGNETO) != BSP_ERROR_NONE) result--;

	if (BSP_MOTION_SENSOR_GetCapabilities(1, &Capabilities) != BSP_ERROR_NONE) result--;

	/* Read id function */
	if (BSP_MOTION_SENSOR_ReadID(1, &chipId) != BSP_ERROR_NONE) result--;

	/* Enable function */
	if (BSP_MOTION_SENSOR_Enable(1, MOTION_MAGNETO) != BSP_ERROR_NONE) result--;

	/* GetFullScale functions */
	if (BSP_MOTION_SENSOR_GetFullScale(1, MOTION_MAGNETO, &fullScale) != BSP_ERROR_NONE) result--;
	if (fullScale != 50) result--;

	/* GetOutputDataRate and SetOutputDataRate functions */
	if (BSP_MOTION_SENSOR_SetOutputDataRate(1, MOTION_MAGNETO, 80.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(1, MOTION_MAGNETO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 100.0f) result--;

	if (BSP_MOTION_SENSOR_SetOutputDataRate(1, MOTION_MAGNETO, 20.0f) != BSP_ERROR_NONE) result--;
	if (BSP_MOTION_SENSOR_GetOutputDataRate(1, MOTION_MAGNETO, &outputDataRate) != BSP_ERROR_NONE) result--;
	if (outputDataRate != 20.0f) result--;

	/* GetSensitivity function */
	if (BSP_MOTION_SENSOR_GetSensitivity(1, MOTION_MAGNETO, &sensitivity) != BSP_ERROR_NONE) result--;

	/* GetAxes function */
	printf("Magnetometer axes:\n");
	while (UserButtonPressed == 0)
	{
		if (BSP_MOTION_SENSOR_GetAxes(1, MOTION_MAGNETO, &axes) != BSP_ERROR_NONE) result--;
		printf("X = %d, Y = %d, , Z = %d\n", axes.xval, axes.yval, axes.zval);
		HAL_Delay(500);
	}
	HAL_Delay(1000);
	UserButtonPressed = RESET;


	/* Disable function */
	if (BSP_MOTION_SENSOR_Disable(1, MOTION_MAGNETO) != BSP_ERROR_NONE) result--;

	/* De-initialize function */
	if (BSP_MOTION_SENSOR_DeInit(1) != BSP_ERROR_NONE) result--;

	/***************/
	/* End of example */
	/***************/

	/* De-Initialize User Button */
	if (BSP_PB_DeInit(BUTTON_USER) != BSP_ERROR_NONE) result--;

	printf("Motion Sensors Example Ended\n");
	return result;
}



void generate_xorand(float *x, float *y, int i) {
	int k;

	k = rand() % 8;

	switch (k) {
	case 0:
		x[0] = 0.0;
		x[1] = 0.0;
		x[2] = 1.0;
		y[0] = 0.0;
		y[1] = 0.0;
		break;
	case 1:
		x[0] = 0.0;
		x[1] = 1.0;
		x[2] = 1.0;
		y[0] = 1.0;
		y[1] = 1.0;
		break;
	case 2:
		x[0] = 1.0;
		x[1] = 0.0;
		x[2] = 1.0;
		y[0] = 1.0;
		y[1] = 0.0;
		break;
	case 3:
		x[0] = 1.0;
		x[1] = 1.0;
		x[2] = 1.0;
		y[0] = 0.0;
		y[1] = 1.0;
		break;
	case 4:
		x[0] = 0.0;
		x[1] = 0.0;
		x[2] = 0.0;
		y[0] = 0.0;
		y[1] = 0.0;
		break;
	case 5:
		x[0] = 0.0;
		x[1] = 1.0;
		x[2] = 0.0;
		y[0] = 1.0;
		y[1] = 0.0;
		break;
	case 6:
		x[0] = 1.0;
		x[1] = 0.0;
		x[2] = 0.0;
		y[0] = 1.0;
		y[1] = 0.0;
		break;
	case 7:
		x[0] = 1.0;
		x[1] = 1.0;
		x[2] = 0.0;
		y[0] = 0.0;
		y[1] = 0.0;
		break;
	default:
		x[0] = 0.0;
		x[1] = 0.0;
		x[2] = 1.0;
		y[0] = 0.0;
		y[1] = 0.0;
		break;
	}

	/*
	 * The XOR-AND system supplies three input values and
	 * two Ground Truth output values.
	 *
	 * Since 6 input neurons form the neural network, the
	 * remaining four Ground Truth values are set to zero.
	 *
	 */

	y[2] = 0.0;
	y[3] = 0.0;
	y[4] = 0.0;
	y[5] = 0.0;
}

void Output_Error(int size, ANN *net, float * ground_truth, float *error) {

	int i;

	/*
	 * Compute error as mean squared difference between
	 * output and Ground Truth
	 */

	*error = 0;
	for (i = 0; i < size; i++) {
		*error = *error
				+ (net->output[i] - ground_truth[i]) * (net->output[i] - ground_truth[i]);
	}
	*error = *error / size;

	printf("%0.3f\t%0.3f\t", ground_truth[0], ground_truth[1]);
	printf("%0.3f\t%0.3f\n", net->output[0], net->output[1]);
}

void BP_ANN(ANN *net, float *input, float *output, float *weights, float *velocity, float *bias, float *delta, int depth){
	unsigned int i,j;
	unsigned int DIM[2] = {net->topology[net->n_layers - depth], net->topology[net->n_layers - depth - 1]};

	if(depth == 1){
		for(i = 0; i < DIM[0]; i++){
			net->output[i] = 0.0;
			for(j = 0; j < DIM[1]; j++){
				net->output[i] += weights[(DIM[1]*i)+j]*input[j];
			}
			net->output[i] = net->output[i] + bias[i];
			delta[i] = (output[i]-net->output_activation_function(net->output[i])) * net->output_activation_derivative(net->output[i]);
			net->output[i] = net->output_activation_function(net->output[i]);
			bias[i] = bias[i] + delta[i]*net->beta;
		}

		float dEdW[DIM[0]*DIM[1]];
		for(i = 0; i < DIM[0]; i++){
			for(j = 0; j < DIM[1]; j++){
				dEdW[(DIM[1]*i)+j] = delta[i]*input[j];
			}
		}
		for(i = 0; i < DIM[0]*DIM[1]; i++){
			velocity[i] = dEdW[i]*net->eta - velocity[i]*net->alpha;
			weights[i] = weights[i] + velocity[i];
		}
		return;
	}
	else{
		float a[DIM[0]];
		float d[DIM[0]];

		for(i = 0; i < DIM[0]; i++){
			a[i] = 0.0;
			for(j = 0; j < DIM[1]; j++){
				a[i] += weights[(DIM[1]*i)+j]*input[j];
			}
			a[i] += bias[i];
			d[i] = net->hidden_activation_derivative(a[i]);
			a[i] = net->hidden_activation_function(a[i]);
		}

		unsigned int DIM1 = net->topology[net->n_layers - depth + 1];

		float prev_delta[DIM1];
		unsigned int weight_iter = DIM[0] * DIM[1];

		float next_weights_T[DIM[0]*DIM1];
		unsigned int iter = 0;
		for(i = 0; i < DIM[0]; i++){
			for(j = 0; j < DIM1; j++){
				next_weights_T[iter] = weights[(DIM[0]*j)+i+weight_iter];
				iter++;
			}
		}

		BP_ANN(net, a, output, &weights[weight_iter], &velocity[weight_iter], &bias[DIM[0]], prev_delta, depth-1);

		for(i = 0; i < DIM[0]; i++){
			delta[i] = 0;
			for(j = 0; j < DIM1; j++){
				delta[i] += next_weights_T[(DIM1*i)+j]*prev_delta[j];
			}
			delta[i] = delta[i]*d[i];
			bias[i] = bias[i] + delta[i]*net->beta;
		}
		float dEdW[DIM[0]*DIM[1]];
		for(i = 0; i < DIM[0]; i++){
			for(j = 0; j < DIM[1]; j++){
				dEdW[(DIM[1]*i)+j] = delta[i]*input[j];
			}
		}
		for(i = 0; i < DIM[0]*DIM[1]; i++){
			velocity[i] = dEdW[i]*net->eta - velocity[i]*net->alpha;
			weights[i] = weights[i] + velocity[i];
		}
		return;
	}
}

//-----ANN-----


void train_ann(ANN *net, float *input, float *output){
	float delta[net->topology[1]];
	BP_ANN(net, input, output, net->weights, net->dedw, net->bias, delta, net->n_layers-1);
}

void FP_ANN(ANN *net, float *input, unsigned int depth, float *weights){
	unsigned int DIM[2] = {net->topology[net->n_layers - depth], net->topology[net->n_layers - depth - 1]};
	unsigned int i,k;

	if(depth == 1){
		for(i = 0; i < DIM[0]; i++){
			net->output[i] = 0.0;
			for(k = 0; k < DIM[1]; k++){
				net->output[i] += weights[(DIM[1]*i)+k]*input[k];
			}
			net->output[i] = net->output_activation_function(net->output[i] + net->bias[i]);
		}
		return;
	}
	else{
		float a[DIM[0]];
		for(i = 0; i < DIM[0]; i++){
			a[i] = 0.0;
			for(k = 0; k < DIM[1]; k++){
				a[i] += weights[(DIM[1]*i)+k]*input[k];
			}
			a[i] = net->hidden_activation_function(a[i] + net->bias[i]);
			//if(depth == 2) printf("%f,", a[i]);
		}
		//if(depth == 2) printf("0\n");
		FP_ANN(net, a, depth-1, &weights[DIM[0]*DIM[1]]);
	}
	return;
}

void run_ann(ANN *net, float *input){
	FP_ANN(net, input, net->n_layers-1, net->weights);
}

void init_ann(ANN *net){
	fill_number(net->bias, net->n_bias, 0.1);
	fill_zeros(net->dedw, net->n_weights);

	if(net->output_activation_function == &relu) net->output_activation_derivative = &relu_derivative;
	else if(net->output_activation_function == &relu2) net->output_activation_derivative = &relu2_derivative;

	if(net->hidden_activation_function == &relu) net->hidden_activation_derivative = &relu_derivative;
	else if(net->hidden_activation_function == &relu2) net->hidden_activation_derivative = &relu2_derivative;
}

void init_pretrained_ann(ANN *net){
	fill_zeros(net->dedw, net->n_weights);

	if(net->output_activation_function == &relu) net->output_activation_derivative = &relu_derivative;
	else if(net->output_activation_function == &relu2) net->output_activation_derivative = &relu2_derivative;

	if(net->hidden_activation_function == &relu) net->hidden_activation_derivative = &relu_derivative;
	else if(net->hidden_activation_function == &relu2) net->hidden_activation_derivative = &relu2_derivative;
}

//-----Utility-----
void fill_zeros(float *v, unsigned int size){
	int i;
	for(i = 0; i < size; i++){ v[i] = 0.0; }
}
void fill_number(float *v, unsigned int size, float number){
	int i;
	for(i = 0; i < size; i++){ v[i] = number; }
}

//-----Activation Functions-----
float relu(float x){
	if(x < 0.0) return 0.0;
	else if(x > 1.0) return 0.1*x+0.93;
	return x;
}

//Similar to Tanh
float relu2(float x){
	if(x < -1.0)     return 0.1*x-0.93;
	else if(x > 1.0) return 0.1*x+0.93;
	return x;
}

//-----Derivative Functions-----
float relu_derivative(float x){
	if(x < 0.0) return 0.0;
	else if(x > 1.0) return 0.1;
	return 1.0;
}
float relu2_derivative(float x){
	if(x < -1.0) return 0.1;
	else if(x > 1.0) return 0.1;
	return 1.0;
}

//----Wrapper Functions-----

void set_model_memory(ANN *model, float *weights, float *dedw, float *bias, float *output){
	model->weights = weights;
	model->dedw = dedw;
	model->bias = bias;
	model->output = output;
}

void set_model_parameters(ANN *model, unsigned int *topology, unsigned int nlayers, char activation_function){
	model->topology = topology;
	model->n_layers = nlayers;

	int i;
	int nweights = 0, nbias = 0;
	for(i = 1; i < nlayers; i++){
		nweights += topology[i]*topology[i-1];
		nbias += topology[i-1];
	}

	model->n_weights = nweights;
	model->n_bias = nbias;

	switch(activation_function){
	case 'r':
		model->output_activation_function = &relu;
		model->hidden_activation_function = &relu;
		break;
	case 'R':
		model->output_activation_function = &relu2;
		model->hidden_activation_function = &relu2;
		break;
	default:
		model->output_activation_function = &relu;
		model->hidden_activation_function = &relu;
		break;
	}
}

void set_model_hyperparameters(ANN *model, float learning_rate, float bias_learning_rate, float momentum_factor){
	model->eta = learning_rate;
	model->beta = bias_learning_rate;
	model->alpha = momentum_factor;
}

void set_learning_rate(ANN *model, float eta){
	model->eta = eta;
}

void set_bias_learning_rate(ANN *model, float beta){
	model->beta = beta;
}

void set_momentum_factor(ANN *model, float alpha){
	model->alpha = alpha;
}

void set_output_actfunc(ANN *model, char func){
	switch(func){
	case 'r':
		model->output_activation_function = &relu;
		model->output_activation_derivative = &relu_derivative;
		break;
	case 'R':
		model->output_activation_function = &relu2;
		model->output_activation_derivative = &relu2_derivative;
		break;
	default:
		model->output_activation_function = &relu;
		model->output_activation_derivative = &relu_derivative;
		break;
	}
}

void set_hidden_actfunc(ANN *model, char func){
	switch(func){
	case 'r':
		model->hidden_activation_function = &relu;
		model->hidden_activation_derivative = &relu_derivative;
		break;
	case 'R':
		model->hidden_activation_function = &relu2;
		model->hidden_activation_derivative = &relu2_derivative;
		break;
	default:
		model->hidden_activation_function = &relu;
		model->hidden_activation_derivative = &relu_derivative;
		break;
	}
}


void Feature_Extraction_State_0(float * feature_1, float * feature_2, float * feature_3, float * sig_mag_scale) {

	BSP_MOTION_SENSOR_Axes_t	ttt;
	BSP_MOTION_SENSOR_Axes_t    ttt_diff;
	float accel_mag;
	int32_t result;


	/*
	 * Acquire acceleration values prior to motion
	 */
	printf("\nMove to Initial Start Position While Red LED On");
	LED_Notification_Blink_Red(5);
	BSP_LED_On(LED6);
	HAL_Delay(3000);

	result = 0;
	if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt_diff) != BSP_ERROR_NONE) result--;
	if (result < 0){
		printf("Sampling Error %i\n\r", result);
	}

	BSP_LED_Off(LED6);
	printf("\nStart Motion to new Orientation and hold while Green LED On");

	LED_Notification_Blink_Green(5);
	BSP_LED_On(LED7);

	HAL_Delay(3000);

	/*
	 * Acquire final state acceleration values after motion
	 * Notify user of motion complete
	 */
	result = 0;
	if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt) != BSP_ERROR_NONE) result--;
	if (result < 0){
		printf("Sampling Error %i\n\r", result);
	}

	printf("\nMotion Complete\n");
	BSP_LED_Off(LED7);


	/*
	 * Compute acceleration magnitude including only X and Y axes
	 */

	accel_mag = pow((ttt.xval - ttt_diff.xval), 2);
	accel_mag = accel_mag + pow((ttt.yval - ttt_diff.yval), 2);
	//accel_mag = accel_mag + pow((ttt.zval - ttt_diff.zval), 2);

	accel_mag = sqrt(accel_mag);

	/*
	 * Compute feature values including only X and Y axes and
	 * setting Z-axis feature to zero
	 */

	*feature_1 = ttt.xval - ttt_diff.xval;
	*feature_2 = ttt.yval - ttt_diff.yval;
	*feature_3 = 0;
	*sig_mag_scale = accel_mag;

	return;
}

void Feature_Extraction_State_Machine_Translation(float * feature_1, float * feature_2, float * sig_mag_scale) {

	float acc_x, acc_y;
	float acc_x_prev, acc_y_prev;
	float acc_x_filter_lp, acc_y_filter_lp;
	float acc_x_filter_hp;
	float acc_y_filter_hp;
	float acc_x_filter_hp_prev, acc_y_filter_hp_prev;
	float acc_x_filter_lp_prev, acc_y_filter_lp_prev;
	float vel_x = 0;
	float vel_x_prev = 0;
	float vel_y = 0;
	float vel_y_prev = 0;
	float vel_mag;
	float sample_period;
	float W_HP, I_HP, iir_HP_0, iir_HP_1, iir_HP_2;
	float W_LP, I_LP, iir_LP_0, iir_LP_1, iir_LP_2;
	float integration_interval;
	int32_t motion_state;

	BSP_MOTION_SENSOR_Axes_t axes;
	int32_t result;

	/*
	 * Define sample period
	 */
	sample_period = INTEGRATION_INTERVAL_DISP;

	/*
	 * Compute high pass filter coefficients
	 */

	W_HP = 2 * 3.1416 * HIGH_PASS_FILTER_FREQUENCY_DISP;
	I_HP = 2/(W_HP * sample_period);
	if (HP_FILTER_ENABLE_DISP == 1){
		iir_HP_0 = 1 - (1/(1 + I_HP));
		iir_HP_1 = -iir_HP_0;
		iir_HP_2 = (1/(1 + I_HP))*(1 - I_HP);
	}
	if (HP_FILTER_ENABLE_DISP == 0){
		iir_HP_0 = 1;
		iir_HP_1 = 0;
		iir_HP_2 = 0;
	}

	/*
	 * Compute low pass filter coefficients
	 */

	W_LP = 2 * 3.1416 * LOW_PASS_FILTER_FREQUENCY_DISP;
	I_LP = 2/(W_LP * sample_period);
	if (LP_FILTER_ENABLE_DISP == 1){
		iir_LP_0 = 1/(1 + I_LP);
		iir_LP_1 = iir_LP_0;
		iir_LP_2 = (1/(1 + I_LP))*(1 - I_LP);
	}
	if (LP_FILTER_ENABLE_DISP == 0){
		iir_LP_0 = 1;
		iir_LP_1 = 0;
		iir_LP_2 = 0;
	}

	printf("Start Motion Segment with Green LED Blink\n");

	BSP_LED_Off(LED6);
	LED_Notification_Blink_Green(5);
	BSP_LED_On(LED7);

	motion_state = 0;
	acc_x = 0;
	acc_y = 0;
	acc_x_prev = 0;
	acc_y_prev = 0;
	acc_x_filter_lp_prev = 0;
	acc_y_filter_lp_prev = 0;
	acc_x_filter_hp_prev = 0;
	acc_y_filter_hp_prev = 0;

	vel_x = 0;
	vel_x_prev = 0;
	vel_y = 0;
	vel_y_prev = 0;

	while (1) {

		/*
		 * Introduce delay establishing integration interval
		 * This is summed with sensor data access delay to
		 * yield loop delay of 4 msec
		 */

			HAL_Delay(2);

            result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n", result);
			}



			/* Setting for integration interval */

				integration_interval = INTEGRATION_INTERVAL_DISP;

			/* Convert acceleration to millimeter/sec/sec using 1 milli-g = (9.81 m/s/s)/1000 */

			acc_x = 9.81*(float)(axes.xval);
			acc_y = 9.81*(float)(axes.yval);


			/* Apply Low Pass filter to acceleration */
			acc_x_filter_lp  = iir_LP_0 * acc_x + iir_LP_1 * acc_x_prev - iir_LP_2 * acc_x_filter_lp_prev;
			acc_y_filter_lp  = iir_LP_0 * acc_y + iir_LP_1 * acc_y_prev - iir_LP_2 * acc_y_filter_lp_prev;

			/* Apply High Pass filter to signal of Low Pass filter to acceleration */
			acc_x_filter_hp = iir_HP_0 * acc_x_filter_lp  + iir_HP_1 * acc_x_filter_lp_prev - iir_HP_2 * acc_x_filter_hp_prev;
			acc_y_filter_hp = iir_HP_0 * acc_y_filter_lp  + iir_HP_1 * acc_y_filter_lp_prev - iir_HP_2 * acc_y_filter_hp_prev;

			acc_x_prev = acc_x;
			acc_y_prev = acc_y;

			/*
			 * Compute velocity by integration
			 */

			vel_x = vel_x + (acc_x_filter_hp + acc_x_filter_hp_prev) * integration_interval/2;
			vel_y = vel_y + (acc_y_filter_hp + acc_y_filter_hp_prev) * integration_interval/2;

			acc_x_filter_lp_prev = acc_x_filter_lp;
			acc_y_filter_lp_prev = acc_y_filter_lp;

			acc_x_filter_hp_prev = acc_x_filter_hp;
			acc_y_filter_hp_prev = acc_y_filter_hp;

			/*
			 * Detect motion and assign velocities to features
			 */

			if (motion_state == 0 && (abs(vel_x_prev - vel_x) > 0.2 || abs(vel_y_prev - vel_y) > 0.2)){
				motion_state = 1;
				BSP_LED_Off(LED7);
					vel_mag = sqrt((vel_x_prev - vel_x)*(vel_x_prev - vel_x) + (vel_y_prev - vel_y)*(vel_y_prev - vel_y));
					//printf("Int %0.5f\tVdiff: X: %0.1f\tY: %0.1f\tMag: %0.1f\n", integration_interval, vel_x_prev - vel_x, vel_y_prev - vel_y, vel_mag);
					*feature_1 = vel_x_prev - vel_x;
					*feature_2 = vel_y_prev - vel_y;
					vel_mag = sqrt((vel_x_prev - vel_x)*(vel_x_prev - vel_x) + (vel_y_prev - vel_y)*(vel_y_prev - vel_y));
					*sig_mag_scale = vel_mag;
			}

			/*
			 * Detect cessation of motion
			 */

			if (motion_state == 1 && (abs(vel_x_prev - vel_x) < 0.01 || abs(vel_y_prev - vel_y) < 0.01)){
				LED_Notification_Blink_Red(10);
				break;
			}

			vel_x_prev = vel_x;
			vel_y_prev = vel_y;
	}
	return;
}


void Feature_Extraction_State_Machine(float * feature_1, float * feature_2, float * feature_3, float * sig_mag_scale) {

	BSP_MOTION_SENSOR_Axes_t	axes;
	BSP_MOTION_SENSOR_Axes_t	ttt;
	BSP_MOTION_SENSOR_Axes_t    ttt_diff;
	float accel_mag;
	int32_t accel_x_avg, accel_y_avg, accel_z_avg;
	int32_t accel_x_diff_avg, accel_y_diff_avg, accel_z_diff_avg;
	int32_t accel_x_prev, accel_y_prev, accel_z_prev;
	int32_t accel_x_diff, accel_y_diff, accel_z_diff;
	int32_t motion_indicator;
	int32_t Motion_State = 0;
	int32_t Motion_State_Prev, Motion_State_Diff;
	int32_t Motion_State_Change_Time, Motion_State_Dwell_Time, GestureMotion_State;
	int32_t Motion_Cycles;
	int32_t avg_count;
	int32_t result;

	BSP_LED_Off(LED7);
	printf("\nMove to Start Position and Hold While Red LED On");
	LED_Notification_Blink_Red(5);
	BSP_LED_On(LED6);

	Motion_Cycles = 0;

	/*************************************************************/
	/* State Definitions:
	 * Motion_State 0 : No detected motion along X, Y, or Z axes
	 * Motion_State 1 : Motion detected along any of X, Y, or Z axes
	 * Motion_State 2 : No motion detected along any of X, Y, or Z axes and
	 *                  node level and oriented upright with upwards Z-axis.
	 * Motion_State 3 : No motion detected along any of X, Y, or Z axes and
	 *                  node level and oriented downward with downwards Z-axis.
	 *
	 * GestureMotion_State -1 : Gesture motion state not yet discovered or
	 *                           Gesture motion completed
	 * GestureMotion_State 0  : Gesture motion not started and with system level
	 *                           and upright
	 * GestureMotion_State 1 :  Gesture motion underway to initial orientation
	 *                           Green LED blink and Green LED On
	 * GestureMotion_State 2 :  Gesture motion arrival at initial orientation
	 *                           User notified with Red LED blink, Green LED
	 *                           blink and Green LED On
	 * GestureMotion_State 3 :  Gesture motion underway to final orientation
	 *                           User notified with Green LED On
	 * GestureMotion_State 4 :  Gesture motion completed. User notified with
	 *                           Green LED set off


	 */
	while (1){


		/* Initialize Motion and Gesture State Variables */
		if (Motion_Cycles == 0){
			Motion_State_Prev = Motion_State;
			GestureMotion_State = -1;
			Motion_State_Change_Time = HAL_GetTick();
			Motion_State_Diff = 0;
		}

		avg_count = 0;
		accel_x_diff_avg = 0;
		accel_y_diff_avg = 0;
		accel_z_diff_avg = 0;
		accel_x_avg = 0;
		accel_y_avg = 0;
		accel_z_avg = 0;
		result = 0;
		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
		if (result < 0){
			printf("Sampling Error %i\n\r", result);
		}
		accel_x_prev = axes.xval;
		accel_y_prev = axes.yval;
		accel_z_prev = axes.zval;
		while (avg_count < 100){
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			accel_x_avg = accel_x_avg + axes.xval;
			accel_y_avg = accel_y_avg + axes.yval;
			accel_z_avg = accel_z_avg + axes.zval;
			accel_x_diff = abs(axes.xval - accel_x_prev);
			accel_y_diff = abs(axes.yval - accel_y_prev);
			accel_z_diff = abs(axes.zval - accel_z_prev);
			accel_x_prev = axes.xval;
			accel_y_prev = axes.yval;
			accel_z_prev = axes.zval;
			accel_x_diff_avg = accel_x_diff_avg + accel_x_diff;
			accel_y_diff_avg = accel_y_diff_avg + accel_y_diff;
			accel_z_diff_avg = accel_z_diff_avg + accel_z_diff;
			HAL_Delay(2);
			avg_count++;
		}
		accel_x_avg = accel_x_avg/avg_count;
		accel_y_avg = accel_y_avg/avg_count;
		accel_z_avg = accel_z_avg/avg_count;
		accel_x_diff_avg = accel_x_diff_avg/avg_count;
		accel_y_diff_avg = accel_y_diff_avg/avg_count;
		accel_z_diff_avg = accel_z_diff_avg/avg_count;
		motion_indicator = accel_x_diff_avg + accel_y_diff_avg + accel_z_diff_avg;
		if (motion_indicator < 20){
			Motion_State = 0;
			/* Detect Level and Upright (Z accel positive)*/
			if (abs(accel_x_avg) < 200 && abs(accel_y_avg) < 200 && accel_z_avg > 0){
				Motion_State = 2;
			}
			/*Detect Level and Downward (Z accel negative) */
			if (abs(accel_x_avg) < 200 && abs(accel_y_avg) < 200 && accel_z_avg < 0){
				Motion_State = 3;
			}

		} else {
			Motion_State = 1;
		}

		Motion_State_Diff = Motion_State - Motion_State_Prev;
		Motion_State_Prev = Motion_State;
		//printf("State %i\tDiff %i\t%i\t%i\t%i\n", Motion_State, Motion_State_Diff, accel_x_diff_avg, accel_y_diff_avg, accel_z_diff_avg);


		if (Motion_State_Diff != 0){
			Motion_State_Change_Time = HAL_GetTick();
		}
		if (Motion_State_Diff == 0 && (Motion_State == 0 || Motion_State == 2)){

			Motion_State_Dwell_Time = HAL_GetTick() - Motion_State_Change_Time;
			if (Motion_State_Dwell_Time/1000 > 0.2){
				//printf("Node Stationary\n");
				if (Motion_State == 2){
					printf("Node Stationary Level Upright Starting\n");
					/* Indicate Gesture Motion Underway to First Waypoint */
					BSP_LED_Off(LED6);
					LED_Notification_Blink_Green(5);
					BSP_LED_On(LED7);
					GestureMotion_State = 0;
				}
			}
		}

		/* Detect departure from diff level state */
		if (GestureMotion_State == 0 && Motion_State != 2  ){
			GestureMotion_State = 1; /* Gesture motion underway to diff state */
		}
		if (GestureMotion_State == 1 && Motion_State == 0 ){
			GestureMotion_State = 2; /* Gesture motion diff state reached */
			/* Record diff state */
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt_diff) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			printf("\nGesture Motion Initial State\n");
			BSP_LED_Off(LED7);
			LED_Notification_Blink_Red(10);
			LED_Notification_Blink_Green(5);
			BSP_LED_On(LED7);
		}
		/* Detect departure from diff level state */
		if (GestureMotion_State == 2 && Motion_State == 1  ){
			GestureMotion_State = 3; /* Gesture motion to final state underway */
		}
		if (GestureMotion_State == 3 && ( Motion_State == 0 || Motion_State == 3) ){
			GestureMotion_State = 4; /* Gesture motion final state reached */
			/* Record final state */
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			printf("\nGesture Motion Intermediate State Reached\n");
			BSP_LED_Off(LED7);
			break;
		}

		//printf("\nGesture Motion State %i\n", GestureMotion_State);
		Motion_Cycles++;
	}

	BSP_LED_Off(LED7);


	accel_mag = pow((ttt.xval - ttt_diff.xval), 2);
	accel_mag = accel_mag + pow((ttt.yval - ttt_diff.yval), 2);
	accel_mag = accel_mag + pow((ttt.zval - ttt_diff.zval), 2);

	accel_mag = sqrt(accel_mag);

	/*
	 * Compute feature values including only X and Y axes and
	 * setting Z-axis feature to zero
	 */

	*feature_1 = ttt.xval - ttt_diff.xval;
	*feature_2 = ttt.yval - ttt_diff.yval;
	*feature_3 = ttt.zval - ttt_diff.zval;
	*sig_mag_scale = accel_mag;

	return;
}

void Feature_Extraction_State_Machine_Six_Feature(float * feature_1, float * feature_2, float * feature_3, float * feature_4, float * feature_5, float * feature_6, float * sig_mag_scale) {

	BSP_MOTION_SENSOR_Axes_t	axes;
	BSP_MOTION_SENSOR_Axes_t	ttt, ttt_final;
	BSP_MOTION_SENSOR_Axes_t    ttt_diff;
	float accel_mag;
	int32_t accel_x_avg, accel_y_avg, accel_z_avg;
	int32_t accel_x_diff_avg, accel_y_diff_avg, accel_z_diff_avg;
	int32_t accel_x_prev, accel_y_prev, accel_z_prev;
	int32_t accel_x_diff, accel_y_diff, accel_z_diff;
	int32_t motion_indicator, motion_indicator_angle;
	int32_t Motion_State = 0;
	int32_t Motion_State_Prev, Motion_State_Diff;
	int32_t Motion_State_Change_Time, Motion_State_Dwell_Time, GestureMotion_State;
	int32_t Motion_Cycles;
	int32_t avg_count;
	int32_t result;




	BSP_MOTION_SENSOR_Axes_t	rate_axes;
	int32_t gyro_accel;
	float diff_time, diff_time_prev;
	int32_t rate_x, rate_y, rate_z, rate_x_prev, rate_y_prev, rate_z_prev;
	int32_t 	angle_x_initial, angle_y_initial, angle_z_initial;
	int32_t 	angle_x_diff, angle_y_diff, angle_z_diff;
	float angle_x, angle_y, angle_z;
	float angle_x_intermediate, angle_y_intermediate, angle_z_intermediate;
	float angle_mag;
	float angle_arr[3], ttt_arr[3];
	/* Configure for rate gyro data source */

	gyro_accel = 1;


	printf("\nMove to Level Start Position and Hold While Red LED On");
	LED_Notification_Blink_Red(5);
	BSP_LED_On(LED6);


	Motion_Cycles = 0;

	/*************************************************************/
	/* State Definitions:
	 *
	 * Gestures that may be recognized include three motions each terminated
	 * by a motionless period.
	 *
	 * Each Gesture training and recognition begins with a return to IoT node
	 * level condition.  Then, the IoT node is moved to its first orientation,
	 * then second orientation, then third orientation.
	 *
	 * Motion_State 0 : No detected motion along X, Y, or Z axes
	 * Motion_State 1 : Motion detected along any of X, Y, or Z axes
	 * Motion_State 2 : No motion detected along any of X, Y, or Z axes and
	 *                  node level and oriented upright with upwards Z-axis.
	 * Motion_State 3 : No motion detected along any of X, Y, or Z axes and
	 *                  node level and oriented downward with downwards Z-axis.
	 *
	 * GestureMotion_State -1 : Gesture motion state not yet discovered or
	 *                           Gesture motion completed
	 * GestureMotion_State 0  : Gesture motion not started and with system level
	 *                           and upright, User notified with Red LED On
	 * GestureMotion_State 1 :  Gesture motion underway to initial orientation
	 *                           Green LED blink and Green LED On
	 * GestureMotion_State 2 :  Gesture motion arrival at initial orientation
	 *                           User notified with Red LED blink, Green LED
	 *                           blink and Green LED On
	 * GestureMotion_State 3 :  Gesture motion underway to intermediate orientation
	 *                           User notified with Green LED On
	 * GestureMotion_State 4 :  Gesture motion reached intermediate orientation.
	 *                           User notified with Red LED blink, Green LED
	 *                           blink and Green LED On
	 * GestureMotion_State 5 :  Gesture motion underway to final orientation. User notified with
	 *                           Green LED On
	 * GestureMotion_State 6 :  Gesture motion reached final orientation. User notified with
	 *                           Green LED Off
	 */



	/* Calibrate loop execution time to permit computation of differential time value */

	avg_count = 0;
	accel_x_diff_avg = 0;
	accel_y_diff_avg = 0;
	accel_z_diff_avg = 0;
	accel_x_avg = 0;
	accel_y_avg = 0;
	accel_z_avg = 0;
	result = 0;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	rate_x_prev = 0;
	rate_y_prev = 0;
	rate_z_prev = 0;

	if (Motion_Cycles == 0){
		diff_time_prev = HAL_GetTick();
		while (avg_count < STATE_MACHINE_AVG_COUNT){
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			accel_x_avg = accel_x_avg + axes.xval;
			accel_y_avg = accel_y_avg + axes.yval;
			accel_z_avg = accel_z_avg + axes.zval;
			accel_x_diff = abs(axes.xval - accel_x_prev);
			accel_y_diff = abs(axes.yval - accel_y_prev);
			accel_z_diff = abs(axes.zval - accel_z_prev);
			accel_x_prev = axes.xval;
			accel_y_prev = axes.yval;
			accel_z_prev = axes.zval;
			accel_x_diff_avg = accel_x_diff_avg + accel_x_diff;
			accel_y_diff_avg = accel_y_diff_avg + accel_y_diff;
			accel_z_diff_avg = accel_z_diff_avg + accel_z_diff;
			HAL_Delay(1);
			avg_count++;


			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}

			rate_x = rate_axes.xval;
			rate_y = rate_axes.yval;
			rate_z = rate_axes.zval;

			/* Apply estimated differential time for computation of loop execution time */

			diff_time = 0.005;

			angle_x = angle_x + (float)((rate_x + rate_x_prev) * diff_time/2);
			angle_y = angle_y + (float)((rate_y + rate_y_prev) * diff_time/2);
			angle_z = angle_z + (float)((rate_z + rate_z_prev) * diff_time/2);


			rate_x_prev = rate_x;
			rate_y_prev = rate_y;
			rate_z_prev = rate_z;

		}

		/* Compute differential time from loop execution time */

		diff_time = (HAL_GetTick() - diff_time_prev)/(1000.0 * (float)STATE_MACHINE_AVG_COUNT);

	}

	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	rate_x_prev = 0;
	rate_y_prev = 0;
	rate_z_prev = 0;

	while (1){


		/* Initialize Motion and Gesture State Variables */
		if (Motion_Cycles == 0){
			Motion_State_Prev = Motion_State;
			GestureMotion_State = -1;
			Motion_State_Change_Time = HAL_GetTick();
			Motion_State_Diff = 0;
		}

		avg_count = 0;
		accel_x_diff_avg = 0;
		accel_y_diff_avg = 0;
		accel_z_diff_avg = 0;
		accel_x_avg = 0;
		accel_y_avg = 0;
		accel_z_avg = 0;

		angle_x_initial = angle_x;
		angle_y_initial = angle_y;
		angle_z_initial = angle_z;

		result = 0;

		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
		if (result < 0){
			printf("Sampling Error %i\n\r", result);
		}
		accel_x_prev = axes.xval;
		accel_y_prev = axes.yval;
		accel_z_prev = axes.zval;

		while (avg_count < STATE_MACHINE_AVG_COUNT){
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			accel_x_avg = accel_x_avg + axes.xval;
			accel_y_avg = accel_y_avg + axes.yval;
			accel_z_avg = accel_z_avg + axes.zval;
			accel_x_diff = abs(axes.xval - accel_x_prev);
			accel_y_diff = abs(axes.yval - accel_y_prev);
			accel_z_diff = abs(axes.zval - accel_z_prev);
			accel_x_prev = axes.xval;
			accel_y_prev = axes.yval;
			accel_z_prev = axes.zval;
			accel_x_diff_avg = accel_x_diff_avg + accel_x_diff;
			accel_y_diff_avg = accel_y_diff_avg + accel_y_diff;
			accel_z_diff_avg = accel_z_diff_avg + accel_z_diff;
			HAL_Delay(1);
			avg_count++;


			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}

			rate_x = rate_axes.xval;
			rate_y = rate_axes.yval;
			rate_z = rate_axes.zval;

			angle_x = angle_x + (float)((rate_x + rate_x_prev) * diff_time/2);
			angle_y = angle_y + (float)((rate_y + rate_y_prev) * diff_time/2);
			angle_z = angle_z + (float)((rate_z + rate_z_prev) * diff_time/2);


			rate_x_prev = rate_x;
			rate_y_prev = rate_y;
			rate_z_prev = rate_z;
		}

		accel_x_avg = accel_x_avg/avg_count;
		accel_y_avg = accel_y_avg/avg_count;
		accel_z_avg = accel_z_avg/avg_count;
		accel_x_diff_avg = accel_x_diff_avg/avg_count;
		accel_y_diff_avg = accel_y_diff_avg/avg_count;
		accel_z_diff_avg = accel_z_diff_avg/avg_count;
		angle_x_diff = abs(angle_x - angle_x_initial);
		angle_y_diff = abs(angle_y - angle_y_initial);
		angle_z_diff = abs(angle_z - angle_z_initial);
		motion_indicator = accel_x_diff_avg + accel_y_diff_avg + accel_z_diff_avg;
		motion_indicator_angle = (int)(angle_x_diff + angle_y_diff + angle_z_diff)/1000;


		if (gyro_accel == 0){
			if (motion_indicator < 20){
				Motion_State = 0;
				/* Detect Level and Upright (Z accel positive)*/
				if (abs(accel_x_avg) < 200 && abs(accel_y_avg) < 200 && accel_z_avg > 0){
					Motion_State = 2;
				}
				/*Detect Level and Downward (Z accel negative) */
				if (abs(accel_x_avg) < 200 && abs(accel_y_avg) < 200 && accel_z_avg < 0){
					Motion_State = 3;
				}

			} else {
				Motion_State = 1;
			}
		}

		if (gyro_accel == 1){
			if (motion_indicator_angle < 2){
				Motion_State = 0;
				/* Detect Level and Upright (Z accel positive)*/
				if (abs(accel_x_avg) < 200 && abs(accel_y_avg) < 200 && accel_z_avg > 0){
					Motion_State = 2;
				}
				/*Detect Level and Downward (Z accel negative) */
				if (abs(accel_x_avg) < 200 && abs(accel_y_avg) < 200 && accel_z_avg < 0){
					Motion_State = 3;
				}

			} else {
				Motion_State = 1;
			}
		}

		Motion_State_Diff = Motion_State - Motion_State_Prev;
		Motion_State_Prev = Motion_State;

		if (Motion_State_Diff != 0){
			Motion_State_Change_Time = HAL_GetTick();
		}
		if (Motion_State_Diff == 0 && (Motion_State == 0 || Motion_State == 2)){

			Motion_State_Dwell_Time = HAL_GetTick() - Motion_State_Change_Time;
			if (Motion_State_Dwell_Time/1000 > 0.2){
				//printf("Node Stationary\n");
				/* Select level state as diff state */
				if (Motion_State == 2){
					//printf("Node Stationary Level Upright Starting\n");

					/* Indicate Gesture Motion Underway to First Waypoint */
					BSP_LED_Off(LED6);
					LED_Notification_Blink_Green(5);
					BSP_LED_On(LED7);
					GestureMotion_State = 0;
				}
			}
		}

		/* Detect departure from diff level state */
		if (GestureMotion_State == 0 && Motion_State != 2  ){
			GestureMotion_State = 1; /* Gesture motion underway to diff state */
		}

		if (GestureMotion_State == 1 && Motion_State == 0 ){
			GestureMotion_State = 2; /* Gesture motion diff state reached */
			/* Record diff state */
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt_diff) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			//printf("\nGesture Motion Initial State Reached\n");
			//printf("X %0.1f\tY %0.1f\tZ %0.1f\tDiff Time %0.4f\n", angle_x/1e3, angle_y/1e3, angle_z/1e3, diff_time);
			BSP_LED_Off(LED7);
			LED_Notification_Blink_Red(10);
			LED_Notification_Blink_Green(5);
			BSP_LED_On(LED7);

		}

		/* Detect departure from diff level state */
		if (GestureMotion_State == 2 && Motion_State == 1  ){
			GestureMotion_State = 3; /* Gesture motion to intermediate state underway */
		}
		if (GestureMotion_State == 3 && ( Motion_State == 0 || Motion_State == 3) ){
			GestureMotion_State = 4; /* Gesture motion intermediate state reached */
			/* Record intermediate state */
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			printf("\nGesture Motion Intermediate State Reached\n");
			if (gyro_accel == 1){
				angle_x_intermediate = angle_x;
				angle_y_intermediate = angle_y;
				angle_z_intermediate = angle_z;
			}
			angle_mag = 0;
			BSP_LED_Off(LED7);
			LED_Notification_Blink_Red(10);
			LED_Notification_Blink_Green(5);
			BSP_LED_On(LED7);

		}
		if (GestureMotion_State == 4 && Motion_State == 1  ){
			GestureMotion_State = 5; /* Gesture motion to final state underway */
		}
		if (gyro_accel == 0 && GestureMotion_State == 5 && ( Motion_State == 0 || Motion_State == 3) ){
			GestureMotion_State = 6; /* Gesture motion final state reached */
			/* Record final state */
			result = 0;
			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_ACCELERO, &ttt_final) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}
			printf("\nGesture Motion Final State Reached\n");
			BSP_LED_Off(LED7);
			break;
		}

		angle_mag = angle_mag + pow((angle_x_intermediate - angle_x),2);
		angle_mag = angle_mag + pow((angle_y_intermediate - angle_y),2);
		angle_mag = angle_mag + pow((angle_z_intermediate - angle_z),2);

		if (gyro_accel == 1 && GestureMotion_State == 5 && angle_mag/1000 > 30 ){
			GestureMotion_State = 6; /* Gesture motion final state reached */
			/* Record final state */
			printf("\nGesture Motion Final State Reached\n");
			BSP_LED_Off(LED7);
			break;
		}
		//printf("\nGesture Motion State %i\n", GestureMotion_State);
		Motion_Cycles++;
	}

	BSP_LED_Off(LED7);


	accel_mag = pow((ttt.xval - ttt_diff.xval), 2);
	accel_mag = accel_mag + pow((ttt.yval - ttt_diff.yval), 2);
	accel_mag = accel_mag + pow((ttt.zval - ttt_diff.zval), 2);
	accel_mag = accel_mag + pow((ttt.xval - ttt_final.xval), 2);
	accel_mag = accel_mag + pow((ttt.yval - ttt_final.yval), 2);
	accel_mag = accel_mag + pow((ttt.zval - ttt_final.zval), 2);

	accel_mag = sqrt(accel_mag);

	/*
	 * Compute feature values including only X and Y axes and
	 * setting Z-axis feature to zero
	 */

	if (gyro_accel == 0){
		*feature_1 = ttt.xval - ttt_diff.xval;
		*feature_2 = ttt.yval - ttt_diff.yval;
		*feature_3 = ttt.zval - ttt_diff.zval;


		*feature_4 = ttt_final.xval - ttt.xval;
		*feature_5 = ttt_final.yval - ttt.yval;
		*feature_6 = ttt_final.zval - ttt.zval;
	}


	if (gyro_accel == 1){
		/* Normalize each sensing mode */

		angle_arr[0] = ttt.xval - ttt_diff.xval;
		angle_arr[1] = ttt.yval - ttt_diff.yval;
		angle_arr[2] = ttt.zval - ttt_diff.zval;
		motion_softmax(3, angle_arr, ttt_arr);
		*feature_1 = ttt_arr[0];
		*feature_2 = ttt_arr[1];
		*feature_3 = ttt_arr[2];


		angle_arr[0] = (angle_x_intermediate - angle_x);
		angle_arr[1] = (angle_y_intermediate - angle_y);
		angle_arr[2] = (angle_z_intermediate - angle_z);
		motion_softmax(3, angle_arr, ttt_arr);
		*feature_4 = ttt_arr[0];
		*feature_5 = ttt_arr[1];
		*feature_6 = ttt_arr[2];
	}

	*sig_mag_scale = accel_mag;

	return;
}


void Feature_Extraction_State_Machine_Gyro_Backup(float * feature_1, float * feature_2, float * feature_3, float * sig_mag_scale) {


	int32_t motion_indicator_angle;
	int32_t Motion_State = 0;
	int32_t Motion_State_Prev, Motion_State_Diff;
	int32_t Motion_State_Change_Time, Motion_State_Dwell_Time, GestureMotion_State;
	int32_t Motion_Cycles;
	int32_t avg_count;
	int32_t result;


	BSP_MOTION_SENSOR_Axes_t	rate_axes;
	float diff_time, diff_time_prev;
	int32_t rate_x, rate_y, rate_z, rate_x_prev, rate_y_prev, rate_z_prev;
	int32_t 	angle_x_initial, angle_y_initial, angle_z_initial;
	int32_t 	angle_x_diff, angle_y_diff, angle_z_diff;
	float angle_x, angle_y, angle_z;
	float angle_x_intermediate, angle_y_intermediate, angle_z_intermediate;
	float angle_mag;


	printf("\nMove to Level Start Position and Hold While Red LED On Start in 3 Seconds After Blink");
	LED_Notification_Blink_Red(50);
	BSP_LED_On(LED6);


	Motion_Cycles = 0;

	/*************************************************************/
	/* State Definitions:
	 *
	 * Gestures that may be recognized include three motions each terminated
	 * by a motionless period.
	 *
	 * Each Gesture training and recognition begins with a return to IoT node
	 * level condition.  Then, the IoT node is moved to its first orientation,
	 * then second orientation, then third orientation.
	 *
	 * Motion_State 0 : No detected motion along X, Y, or Z axes
	 * Motion_State 1 : Motion detected along any of X, Y, or Z axes
	 * Motion_State 2 : No motion detected along any of X, Y, or Z axes and
	 *                  node level and oriented upright with upwards Z-axis.
	 * Motion_State 3 : No motion detected along any of X, Y, or Z axes and
	 *                  node level and oriented downward with downwards Z-axis.
	 *
	 * GestureMotion_State -1 : Gesture motion state not yet discovered or
	 *                           Gesture motion completed
	 * GestureMotion_State 0  : Gesture motion not started and with system level
	 *                           and upright, User notified with Red LED On
	 * GestureMotion_State 1 :  Gesture motion underway to initial orientation
	 *                           Green LED blink and Green LED On
	 * GestureMotion_State 2 :  Gesture motion arrival at initial orientation
	 *                           User notified with Red LED blink, Green LED
	 *                           blink and Green LED On
	 * GestureMotion_State 3 :  Gesture motion underway to intermediate orientation
	 *                           User notified with Green LED On
	 * GestureMotion_State 4 :  Gesture motion reached intermediate orientation.
	 *                           User notified with Red LED blink, Green LED
	 *                           blink and Green LED On
	 * GestureMotion_State 5 :  Gesture motion reached final orientation. User notified with
	 *                           Green LED Off
	 */



	/* Calibrate loop execution time to permit computation of differential time value */

	avg_count = 0;
	result = 0;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	rate_x_prev = 0;
	rate_y_prev = 0;
	rate_z_prev = 0;

	if (Motion_Cycles == 0){
		diff_time_prev = HAL_GetTick();
		while (avg_count < STATE_MACHINE_AVG_COUNT){
			result = 0;
			HAL_Delay(3);
			avg_count++;


			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}

			rate_x = rate_axes.xval;
			rate_y = rate_axes.yval;
			rate_z = rate_axes.zval;

			/* Apply estimated differential time for computation of loop execution time */

			diff_time = 0.005;

			angle_x = angle_x + (float)((rate_x + rate_x_prev) * diff_time/2);
			angle_y = angle_y + (float)((rate_y + rate_y_prev) * diff_time/2);
			angle_z = angle_z + (float)((rate_z + rate_z_prev) * diff_time/2);


			rate_x_prev = rate_x;
			rate_y_prev = rate_y;
			rate_z_prev = rate_z;

		}

		/* Compute differential time from loop execution time */

		diff_time = (HAL_GetTick() - diff_time_prev)/(1000.0 * (float)STATE_MACHINE_AVG_COUNT);

	}

	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	angle_x_initial = angle_x;
	angle_y_initial = angle_y;
	angle_z_initial = angle_z;
	rate_x_prev = 0;
	rate_y_prev = 0;
	rate_z_prev = 0;
	angle_mag = 0;

	while (1){


		/* Initialize Motion and Gesture State Variables */
		if (Motion_Cycles == 0){
			Motion_State_Prev = Motion_State;
			GestureMotion_State = -1;
			Motion_State_Change_Time = HAL_GetTick();
			Motion_State_Diff = 0;
		}

		avg_count = 0;


		while (avg_count < STATE_MACHINE_AVG_COUNT){

			HAL_Delay(3);
			avg_count++;


			if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
			if (result < 0){
				printf("Sampling Error %i\n\r", result);
			}

			rate_x = rate_axes.xval;
			rate_y = rate_axes.yval;
			rate_z = rate_axes.zval;

			angle_x = angle_x + (float)((rate_x + rate_x_prev) * diff_time/2);
			angle_y = angle_y + (float)((rate_y + rate_y_prev) * diff_time/2);
			angle_z = angle_z + (float)((rate_z + rate_z_prev) * diff_time/2);


			rate_x_prev = rate_x;
			rate_y_prev = rate_y;
			rate_z_prev = rate_z;
		}

		angle_x_diff = abs(angle_x - angle_x_initial);
		angle_y_diff = abs(angle_y - angle_y_initial);
		angle_z_diff = abs(angle_z - angle_z_initial);
		motion_indicator_angle = abs((int)(angle_x_diff + angle_y_diff + angle_z_diff)/1000);

		if (motion_indicator_angle < 2){
			Motion_State = 0;
		} else {
			Motion_State = 1;
		}

		Motion_State_Diff = Motion_State - Motion_State_Prev;
		Motion_State_Prev = Motion_State;

		if (Motion_State_Diff != 0){
			Motion_State_Change_Time = HAL_GetTick();
		}
		if (Motion_State_Diff == 0 && Motion_State == 0){

			Motion_State_Dwell_Time = HAL_GetTick() - Motion_State_Change_Time;
			if (Motion_State_Dwell_Time/1000 > 0.2){

				printf("Node Stationary Start State\n");

				/* Indicate Gesture Motion Underway to First Waypoint */
				BSP_LED_Off(LED6);
				LED_Notification_Blink_Green(5);
				BSP_LED_On(LED7);
				GestureMotion_State = 0;
				angle_mag = 0;
				angle_x = 0;
				angle_y = 0;
				angle_z = 0;
				angle_x_intermediate = angle_x;
				angle_y_intermediate = angle_y;
				angle_z_intermediate = angle_z;

			}
		}


		/* Detect departure from diff level state */
		if (GestureMotion_State == 0 && Motion_State == 1  ){
			GestureMotion_State = 1; /* Gesture motion underway to diff state */
		}

		angle_mag = angle_mag + pow((angle_x_intermediate - angle_x),2);
		angle_mag = angle_mag + pow((angle_y_intermediate - angle_y),2);
		angle_mag = angle_mag + pow((angle_z_intermediate - angle_z),2);
		angle_mag = sqrt(angle_mag);

		if (GestureMotion_State == 1 && angle_mag/1000 > 30 ){
			GestureMotion_State = 2; /* Gesture motion final state reached */
			/* Record final state */
			printf("\nGesture Motion Final State Reached\n");
			printf("\nX %0.1f Y %0.1f Z %0.1f Mag %0.1f\n", angle_x, angle_y, angle_z, angle_mag/1000);
			BSP_LED_Off(LED7);
			break;
		}
		//printf("\nGesture Motion State %i\n", GestureMotion_State);
		Motion_Cycles++;
	}

	BSP_LED_Off(LED7);


	/*
	 * Compute feature values
	 */

	/*
	if (gyro_accel == 1){

		angle_arr[0] = (angle_x_intermediate - angle_x);
		angle_arr[1] = (angle_y_intermediate - angle_y);
		angle_arr[2] = (angle_z_intermediate - angle_z);
		motion_softmax(3, angle_arr, ttt_arr);
	 *feature_1 = ttt_arr[0];
	 *feature_2 = ttt_arr[1];
	 *feature_3 = ttt_arr[2];
	}

	 */
	*feature_1 = (angle_x_intermediate - angle_x);
	*feature_2 = (angle_y_intermediate - angle_y);
	*feature_3 = (angle_z_intermediate - angle_z);

	*sig_mag_scale = angle_mag;

	return;
}

void Feature_Extraction_State_Machine_Gyro(float * feature_1, float * feature_2, float * feature_3, float * sig_mag_scale) {


	int ttt[3], ttt_initial[3];
	int axis_index, sample_index;
	int32_t start_tick;
	int32_t result;

	BSP_MOTION_SENSOR_Axes_t	rate_axes;


	float rotate_angle[3];
	float angle_mag, angle_mag_max_threshold;
	float Tsample;

	angle_mag_max_threshold = 30;

	/*
	 * Estimate differential time as 1 msec greater than loop delay due
	 * to msec sampling delay
	 */
	Tsample = 0.004;

	/* Calibrate differential time */

	start_tick = HAL_GetTick();

	for (sample_index = 0; sample_index < 100; sample_index++) {

		for (axis_index = 0; axis_index < 3; axis_index++) {
			ttt_initial[axis_index] = ttt[axis_index];
		}

		/* Introduce integration time period delay */

		HAL_Delay(3);

		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
		if (result < 0){
			printf("Sampling Error %i\n\r", result);
		}

		ttt[0] = rate_axes.xval;
		ttt[1] = rate_axes.yval;
		ttt[2] = rate_axes.zval;

		for (axis_index = 0; axis_index < 3; axis_index++) {
			rotate_angle[axis_index] = rotate_angle[axis_index]
													+ (float)((ttt_initial[axis_index] + ttt[axis_index]) * Tsample / 2);
		}
		angle_mag = 0;
		for (axis_index = 0; axis_index < 3; axis_index++) {
			angle_mag = angle_mag + pow((rotate_angle[axis_index]), 2);
		}
		angle_mag = sqrt(angle_mag)/1000;
	}


	Tsample = (float)((HAL_GetTick() - start_tick)/(100.0 * 1000.0));

	printf("\nMove to New Position While Red LED On Start in 3 Seconds After Blink");
	LED_Notification_Blink_Red(50);
	HAL_Delay(10);
	BSP_LED_On(LED7);

	if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
	if (result < 0){
		printf("Sampling Error %i\n\r", result);
	}

	ttt_initial[0] = rate_axes.xval;
	ttt_initial[1] = rate_axes.yval;
	ttt_initial[2] = rate_axes.zval;

	for (axis_index = 0; axis_index < 3; axis_index++) {
		rotate_angle[axis_index] = 0;
	}


	for (sample_index = 0; sample_index < 10000; sample_index++) {


		for (axis_index = 0; axis_index < 3; axis_index++) {
			ttt_initial[axis_index] = ttt[axis_index];
		}

		/* Introduce integration time period delay */

		HAL_Delay(3);

		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
		if (result < 0){
			printf("Sampling Error %i\n\r", result);
		}

		ttt[0] = rate_axes.xval;
		ttt[1] = rate_axes.yval;
		ttt[2] = rate_axes.zval;

		for (axis_index = 0; axis_index < 3; axis_index++) {
			rotate_angle[axis_index] = rotate_angle[axis_index]
													+ (float)((ttt_initial[axis_index] + ttt[axis_index]) * Tsample / 2);
		}

		angle_mag = 0;
		for (axis_index = 0; axis_index < 3; axis_index++) {
			angle_mag = angle_mag + pow((rotate_angle[axis_index]), 2);
		}


		angle_mag = sqrt(angle_mag)/1000;

		if (angle_mag >= angle_mag_max_threshold) {
			BSP_LED_Off(LED7);
			break;
		}
	}

	*feature_1 = (float)rotate_angle[0];
	*feature_2 = (float)rotate_angle[1];
	*feature_3 = (float)rotate_angle[2];

	*sig_mag_scale = angle_mag;
	return;
}



void motion_softmax(int size, float *x, float *y) {
	float norm;

	norm = sqrt((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]));
	y[0] = x[0] / norm;
	y[1] = x[1] / norm;
	y[2] = x[2] / norm;
}

void motion_softmax_six_feature(int size, float *x, float *y) {
	float norm;

	norm = sqrt((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2] + (x[3] * x[3]) + (x[4] * x[4]) + (x[5] * x[5])));
	y[0] = x[0] / norm;
	y[1] = x[1] / norm;
	y[2] = x[2] / norm;
	y[3] = x[3] / norm;
	y[4] = x[4] / norm;
	y[5] = x[5] / norm;

}

void motion_softmax_n_feature(int n, float *x, float *y) {
	float norm;
	int32_t i;

	norm = 0;
	for (i = 0; i < n; i++){
		norm = norm + x[i] * x[i];
	}
	norm = sqrt(norm);
	for (i = 0; i < n; i++){
		y[i] = x[i]/norm;
	}
}

void LED_Code_Blink_Red(int count) {

	int i;

	/*
	 * Alert signal of rapid blinks indicating code to be shown
	 */
	for (i = 0; i < 7; i++) {
		BSP_LED_On(LED6);

		HAL_Delay(20);
		BSP_LED_Off(LED6);

		HAL_Delay(50);
	}

	/*
	 * Code indicated by number of slow blinks
	 */

	if (count != 0) {
		HAL_Delay(1000);
		for (i = 0; i < count; i++) {
			BSP_LED_On(LED6);

			HAL_Delay(500);
			BSP_LED_Off(LED6);

			HAL_Delay(500);
		}
	}

	/*
	 * Alert signal of rapid blinks indicating end of code
	 */
	for (i = 0; i < 7; i++) {
		BSP_LED_On(LED6);

		HAL_Delay(20);
		BSP_LED_Off(LED6);

		HAL_Delay(30);
	}

}

void LED_Code_Blink_Green(int count) {

	int i;

	/*
	 * Alert signal of rapid blinks indicating code to be shown
	 */
	for (i = 0; i < 7; i++) {

		BSP_LED_On(LED7);
		HAL_Delay(20);

		BSP_LED_Off(LED7);
		HAL_Delay(50);
	}

	/*
	 * Code indicated by number of slow blinks
	 */

	if (count != 0) {
		HAL_Delay(1000);
		for (i = 0; i < count; i++) {

			BSP_LED_On(LED7);
			HAL_Delay(500);

			BSP_LED_Off(LED7);
			HAL_Delay(500);
		}
	}

	/*
	 * Alert signal of rapid blinks indicating end of code
	 */
	for (i = 0; i < 7; i++) {

		BSP_LED_On(LED7);
		HAL_Delay(20);

		BSP_LED_Off(LED7);
		HAL_Delay(30);
	}

}

void LED_Notification_Blink_Green(int count) {

	int i;

	/*
	 * Rapid blink notification
	 */

	for (i = 0; i < count; i++) {

		BSP_LED_On(LED7);
		HAL_Delay(20);

		BSP_LED_Off(LED7);
		HAL_Delay(50);
	}
}

void LED_Notification_Blink_Red(int count) {

	int i;

	/*
	 * Rapid blink notification
	 */

	for (i = 0; i < count; i++) {
		BSP_LED_On(LED6);

		HAL_Delay(20);
		BSP_LED_Off(LED6);

		HAL_Delay(50);
	}
}


void print_Z_Score_ANN(ANN *net, int input_state, int * error) {

	int i, loc, count;
	float point = 0.0;
	float rms_output, mean_output, mean_output_rem, next_max;
	float classification_metric;

	/*
	 * Initialize error state
	 */

	*error = 0;

	count = 0;
	mean_output = 0;
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		mean_output = mean_output + (net->output[i]);
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
		count++;
	}

	next_max = 0;
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (i == loc) {
			continue;
		}
		if (net->output[i] > next_max && net->output[i] > 0.1) {
			next_max = net->output[i];
		}
	}

	mean_output = (mean_output) / (count);

	count = 0;
	mean_output_rem = 0;
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		mean_output_rem = mean_output_rem + (net->output[i]);
		if (i == loc) {
			continue;
		}
		count++;
	}

	mean_output_rem = (mean_output_rem) / (count);

	rms_output = 0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		rms_output = rms_output + pow((net->output[i] - mean_output), 2);
	}

	rms_output = sqrt(rms_output / count);
	if (rms_output != 0) {
		classification_metric = (point - mean_output) / rms_output;
	} else {
		classification_metric = 0;
	}

	if (loc != input_state) {
		rms_output = 0;
		classification_metric = 0;
		point = 0;
		mean_output = 0;
		mean_output_rem = 0;
	}

	printf("\nZ-score %0.1f\n", classification_metric);

	if (loc != input_state) {
		*error = 1;
		printf("\n\t Classification Error\n");
	}

	if ((loc == input_state)
			&& ((classification_metric < CLASSIFICATION_ACC_THRESHOLD)
					|| ((point / next_max) < CLASSIFICATION_DISC_THRESHOLD))) {
		*error = 1;
		printf("\n\t Classification Accuracy Limit\n");
	}
}

void printOutput_ANN(ANN *net, int input_state, int * error) {

	int i, loc, count;
	float point = 0.0;
	float rms_output, mean_output, mean_output_rem, next_max;
	float classification_metric;

	/*
	 * Initialize error state
	 */

	*error = 0;
	loc = -1;
	count = 0;
	mean_output = 0;
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		mean_output = mean_output + (net->output[i]);
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
		count++;
	}

	next_max = 0;
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (i == loc) {
			continue;
		}
		if (net->output[i] > next_max && net->output[i] > 0.1) {
			next_max = net->output[i];
		}
	}

	mean_output = (mean_output) / (count);

	count = 0;
	mean_output_rem = 0;
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		mean_output_rem = mean_output_rem + (net->output[i]);
		if (i == loc) {
			continue;
		}
		count++;
	}

	mean_output_rem = (mean_output_rem) / (count);

	rms_output = 0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		rms_output = rms_output + pow((net->output[i] - mean_output), 2);
	}

	rms_output = sqrt(rms_output / count);
	if (rms_output != 0) {
		classification_metric = (point - mean_output) / rms_output;
	} else {
		classification_metric = 0;
	}

	if (loc != input_state) {
		rms_output = 0;
		classification_metric = 0;
		point = 0;
		mean_output = 0;
		mean_output_rem = 0;
	}
	if (loc > -1){
		printf("State: %i",loc);
	}
	if (loc == -1){
		printf("State:  ");
	}

	if (mean_output >= 0){
		printf(" Max: %0.1f Mean:  %0.1f Z: %0.1f ", loc, point, mean_output, classification_metric);
	}
	if (mean_output < 0){
		printf(" Max: %0.1f Mean: %0.1f Z: %0.1f ", loc, point, mean_output, classification_metric);
	}

	printf("Outputs: ");
	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] >= 0){
			printf("  %0.1f", net->output[i]);
		}
		if (net->output[i] < 0){
			printf(" %0.1f", net->output[i]);
		}
	}

	if (loc != input_state) {
		*error = 1;
		printf("\t Classification Error");
	}

	if ((loc == input_state)
			&& ((classification_metric < CLASSIFICATION_ACC_THRESHOLD)
					|| ((point / next_max) < CLASSIFICATION_DISC_THRESHOLD))) {
		*error = 1;
		printf("\t Classification Accuracy Limit");
	}
	printf("\n");
}

int Test_ANN_SM(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[3];
	float sig_xyz[3];
	float feature_1, feature_2, feature_3, sig_mag_scale;
	int i, j, loc;
	int error;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	printf("\nMove to Start Level Position While Red - Wait for Green LED On");

	Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
			&sig_mag_scale);

	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;

	motion_softmax(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 3; j++) {
		printf("%i0.3f\t", sig_xyz[j]);
	}
	printf("\n Softmax Output: \t");
	for (j = 0; j < 3; j++) {
		printf("%0.3f\t", sig_xyz_norm[j]);
	}
	printf("\r\n");

	run_ann(net, sig_xyz_norm);

	point = 0.0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
	}

	if (error == 1){
		loc = -1;
	}

	switch (loc) {
	case 0:
		printf("\n\rNeural Network Classification - Motion 1");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6");
		break;
	case -1:
		printf("\n\rNeural Network Classification - ERROR");
		break;
	default:
		printf("\n\rNeural Network Classification - NULL");
		break;
	}

	printf("\n");

	print_Z_Score_ANN(net, loc, &error);

	if (loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(loc + 1);
	}

	return prev_loc;
}

int Test_ANN_SM_Six_Feature(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[6];
	float sig_xyz[6];
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, sig_mag_scale;
	int i, j, loc;
	int error;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	printf("\nMove to Start Level Position While Red - Wait for Green LED On");

	Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
			&sig_mag_scale);

	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;
	sig_xyz[3] = feature_4;
	sig_xyz[4] = feature_5;
	sig_xyz[5] = feature_6;

	motion_softmax_six_feature(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 6; j++) {
		printf("%0.3f\t", sig_xyz[j]);
	}
	printf("\n Softmax Output: \t");
	for (j = 0; j < 6; j++) {
		printf("%0.3f\t", sig_xyz_norm[j]);
	}
	printf("\r\n");

	run_ann(net, sig_xyz_norm);

	point = 0.0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
	}



	if (error == 1){
		loc = -1;
	}

	switch (loc) {
	case 0:
		printf("\n\rNeural Network Classification - Motion 1");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6");
		break;
	case -1:
		printf("\n\rNeural Network Classification - ERROR");
		break;
	default:
		printf("\n\rNeural Network Classification - NULL");
		break;
	}

	printf("\n");

	print_Z_Score_ANN(net, loc, &error);

	if (loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(loc + 1);
	}

	return prev_loc;
}

int Test_ANN_SM_Six_Feature_Gyro(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[6];
	float sig_xyz[6];
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, sig_mag_scale;
	int i, j, loc;
	int error;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	printf("\nMove to Start Level Position While Red - Wait for Green LED On");

	Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
	Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);

	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;
	sig_xyz[3] = feature_4;
	sig_xyz[4] = feature_5;
	sig_xyz[5] = feature_6;

	motion_softmax_six_feature(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 6; j++) {
		printf("%0.3f\t", sig_xyz[j]);
	}
	printf("\n Softmax Output: \t");
	for (j = 0; j < 6; j++) {
		printf("%0.3f\t", sig_xyz_norm[j]);
	}
	printf("\r\n");

	run_ann(net, sig_xyz_norm);


	point = 0.0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
	}

	printOutput_ANN(net, loc, &error);


	if (error == 1){
		loc = -1;
	}

	switch (loc) {
	case 0:
		printf("\n\rNeural Network Classification - Motion 1");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6");
		break;
	case -1:
		printf("\n\rNeural Network Classification - ERROR");
		break;
	default:
		printf("\n\rNeural Network Classification - NULL");
		break;
	}

	printf("\n");

	print_Z_Score_ANN(net, loc, &error);

	if (loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(loc + 1);
	}

	return prev_loc;
}

int Test_ANN_SM_Nine_Feature_Gyro(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[9];
	float sig_xyz[9];
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, feature_7, feature_8, feature_9, sig_mag_scale;
	int i, j, loc;
	int error;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	printf("\nMove to Start Level Position While Red - Wait for Green LED On");

	Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
	Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
	Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);

	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;
	sig_xyz[3] = feature_4;
	sig_xyz[4] = feature_5;
	sig_xyz[5] = feature_6;
	sig_xyz[6] = feature_7;
	sig_xyz[7] = feature_8;
	sig_xyz[8] = feature_9;

	motion_softmax_n_feature(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 9; j++) {
		printf("%0.3f\t", sig_xyz[j]);
	}
	printf("\n Softmax Output: \t");
	for (j = 0; j < 9; j++) {
		printf("%0.3f\t", sig_xyz_norm[j]);
	}
	printf("\r\n");

	run_ann(net, sig_xyz_norm);


	point = 0.0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
	}

	printOutput_ANN(net, loc, &error);


	if (error == 1){
		loc = -1;
	}

	switch (loc) {
	case 0:
		printf("\n\rNeural Network Classification - Motion 1");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6");
		break;
	case -1:
		printf("\n\rNeural Network Classification - ERROR");
		break;
	default:
		printf("\n\rNeural Network Classification - NULL");
		break;
	}

	printf("\n");

	print_Z_Score_ANN(net, loc, &error);

	if (loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(loc + 1);
	}

	return prev_loc;
}

int Test_ANN_SM_Translation(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[8];
	float sig_xyz[8];
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, feature_7, feature_8, sig_mag_scale;
	int i, j, loc;
	int error;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
	Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
	Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
	Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);

	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;
	sig_xyz[3] = feature_4;
	sig_xyz[4] = feature_5;
	sig_xyz[5] = feature_6;
	sig_xyz[6] = feature_7;
	sig_xyz[7] = feature_8;

	motion_softmax_n_feature(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 8; j++) {
		printf("%0.3f\t", sig_xyz[j]);
	}
	printf("\n Softmax Output: \t");
	for (j = 0; j < 8; j++) {
		printf("%0.3f\t", sig_xyz_norm[j]);
	}
	printf("\r\n");

	run_ann(net, sig_xyz_norm);


	point = 0.0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
	}

	printOutput_ANN(net, loc, &error);


	if (error == 1){
		loc = -1;
	}

	switch (loc) {
	case 0:
		printf("\n\rNeural Network Classification - Motion 1");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6");
		break;
	case -1:
		printf("\n\rNeural Network Classification - ERROR");
		break;
	default:
		printf("\n\rNeural Network Classification - NULL");
		break;
	}

	printf("\n");

	print_Z_Score_ANN(net, loc, &error);

	if (loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(loc + 1);
	}

	return prev_loc;
}


int Test_ANN(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[3];
	float sig_xyz[3];
	float feature_1, feature_2, feature_3, sig_mag_scale;
	int i, j, loc;
	int error;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	printf("\nMove to Start Position - Wait for LED On");

	Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
			&sig_mag_scale);

	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;

	motion_softmax(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 3; j++) {
		printf("%i0.3f\t", sig_xyz[j]);
	}
	printf("\n Softmax Output: \t");
	for (j = 0; j < 3; j++) {
		printf("%0.3f\t", sig_xyz_norm[j]);
	}
	printf("\r\n");

	run_ann(net, sig_xyz_norm);

	point = 0.0;

	for (i = 0; i < net->topology[net->n_layers - 1]; i++) {
		if (net->output[i] > point && net->output[i] > 0.1) {
			point = net->output[i];
			loc = i;
		}
	}

	print_Z_Score_ANN(net, loc, &error);
	printf("\n");

	if (error == 1){
		loc = -1;
	}

	if (loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(loc + 1);
	}

	switch (loc) {
	case 0:
		printf("\n\rNeural Network Classification - Motion 1");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6");
		break;
	case -1:
		printf("\n\rNeural Network Classification - ERROR");
		break;
	default:
		printf("\n\rNeural Network Classification - NULL");
		break;
	}
	return prev_loc;
}



void TrainOrientation(ANN *net) {
	float training_dataset[6][8][3];
	float sig_xyz[3];
	float sig_xyz_norm[3];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, sig_mag_scale;


	printf("\n\n\nTraining Start in 2 seconds ..");
	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);
	HAL_Delay(2000);

	/*
	 * Maximum of 8 cycles
	 */
	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {


			//HAL_Delay(START_POSITION_INTERVAL);

			switch (i) {

			case 0:
				BSP_LED_On(LED6);
				printf("\n\nTrain Orientation 1");
				Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 1:

				printf("\n\nTrain Orientation 2");
				Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 2:
				printf("\n\nTrain Orientation 3");
				Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 3:
				printf("\n\nTrain Orientation 4");
				Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 4:
				printf("\n\nTrain Orientation 5");
				Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 5:
				printf("\n\nTrain Orientation 6");
				Feature_Extraction_State_0(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;
			}

			printf("Feature 1: %0.3f\t Feature 2: %0.3f\t Feature 3: %0.3f\n", feature_1, feature_2, feature_3);


			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;

			motion_softmax(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];

			printf("\n Softmax Input \t");

			for (r = 0; r < 3; r++) {
				printf("\t%0.3f", sig_xyz[r]);
			}
			printf("\n Softmax Output\t");

			for (r = 0; r < 3; r++) {
				printf("\t%0.3f", sig_xyz_norm[r]);

			}
			printf("\n\n");

		}
	}

	/*
	 * Enter NN training
	 */

	float Motion_1[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_2[6] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_3[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
	float Motion_4[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	float Motion_5[6] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	float Motion_6[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

	printf("\n\nNeural Network Training Start\n");

	training_cycles = TRAINING_CYCLES;

	for (k = 0; k < num_train_data_cycles; k++) {

		i = 0;
		while (i < training_cycles) {
			for (j = 0; j < 6; j++) {

				if ((i % 20 == 0 && i < 100) || i % 100 == 0) {
					printf("\n\nTraining Epochs: %d\n", i);

					LED_Code_Blink_Green(0);

					net_error = 0;
					for (m = 0; m < 6; m++) {
						run_ann(net, training_dataset[m][k]);
						printOutput_ANN(net, m, &error);
						if (error == 1) {
							net_error = 1;
						}
					}
					printf("\nError State: %i\n", net_error);

					if (net_error == 0) {
						return;
					}

				}

				switch (j) {

				case 0:
					train_ann(net, training_dataset[j][k], Motion_1);
					break;
				case 1:
					train_ann(net, training_dataset[j][k], Motion_2);
					break;
				case 2:
					train_ann(net, training_dataset[j][k], Motion_3);
					break;
				case 3:
					train_ann(net, training_dataset[j][k], Motion_4);
					break;
				case 4:
					train_ann(net, training_dataset[j][k], Motion_5);
					break;
				case 5:
					train_ann(net, training_dataset[j][k], Motion_6);
					break;
				default:
					break;
				}
				i++;
				HAL_Delay(5);
			}

		}

	}


	if (net_error == 0){
		LED_Code_Blink_Green(0);
		LED_Code_Blink_Green(0);
	} else {
		LED_Code_Blink_Red(1);
		LED_Code_Blink_Red(1);
	}

	printf("\n\nNeural Network Training Complete, Now Start Test Motions\n");
	return;
}

void TrainOrientation_SM(ANN *net) {
	float training_dataset[6][8][3];
	float sig_xyz[3];
	float sig_xyz_norm[3];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, sig_mag_scale;


	printf("\n\n\nTraining Start in 2 seconds ..");
	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);
	HAL_Delay(2000);

	/*
	 * Maximum of 8 cycles
	 */
	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {


			//HAL_Delay(START_POSITION_INTERVAL);

			switch (i) {

			case 0:
				BSP_LED_On(LED6);
				printf("\n\nTrain Orientation 1");
				Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 1:

				printf("\n\nTrain Orientation 2");
				Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 2:
				printf("\n\nTrain Orientation 3");
				Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 3:
				printf("\n\nTrain Orientation 4");
				Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 4:
				printf("\n\nTrain Orientation 5");
				Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;

			case 5:
				printf("\n\nTrain Orientation 6");
				Feature_Extraction_State_Machine(&feature_1, &feature_2, &feature_3,
						&sig_mag_scale);
				break;
			}

			printf("Feature 1: %0.3f\t Feature 2: %0.3f\t Feature 3: %0.3f\n", feature_1, feature_2, feature_3);


			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;

			motion_softmax(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];

			printf("\n Softmax Input \t");

			for (r = 0; r < 3; r++) {
				printf("\t%0.3f", sig_xyz[r]);
			}
			printf("\n Softmax Output\t");

			for (r = 0; r < 3; r++) {
				printf("\t%0.3f", sig_xyz_norm[r]);

			}
			printf("\n\n");

		}
	}

	/*
	 * Enter NN training
	 */

	float Motion_1[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_2[6] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_3[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
	float Motion_4[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	float Motion_5[6] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	float Motion_6[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

	printf("\n\nTraining Start\n");

	training_cycles = TRAINING_CYCLES;

	for (k = 0; k < num_train_data_cycles; k++) {

		i = 0;
		while (i < training_cycles) {
			for (j = 0; j < 6; j++) {

				if ((i % 20 == 0 && i < 100) || i % 100 == 0) {
					printf("\n\nTraining Epochs: %i\n", i);

					LED_Code_Blink_Green(0);

					net_error = 0;
					for (m = 0; m < 6; m++) {
						run_ann(net, training_dataset[m][k]);
						printOutput_ANN(net, m, &error);
						if (error == 1) {
							net_error = 1;
						}
					}
					printf("\nError State: %i\n", net_error);

					if (net_error == 0) {
						return;
					}

				}

				switch (j) {

				case 0:
					train_ann(net, training_dataset[j][k], Motion_1);
					break;
				case 1:
					train_ann(net, training_dataset[j][k], Motion_2);
					break;
				case 2:
					train_ann(net, training_dataset[j][k], Motion_3);
					break;
				case 3:
					train_ann(net, training_dataset[j][k], Motion_4);
					break;
				case 4:
					train_ann(net, training_dataset[j][k], Motion_5);
					break;
				case 5:
					train_ann(net, training_dataset[j][k], Motion_6);
					break;
				default:
					break;
				}
				i++;
				HAL_Delay(5);
			}

		}

	}

	if (net_error == 0){
		LED_Code_Blink_Green(0);
		LED_Code_Blink_Green(0);
	} else {
		LED_Code_Blink_Red(1);
		LED_Code_Blink_Red(1);
	}

	printf("\n\nTraining Complete, Now Start Test Motions\n");
	return;
}

void TrainOrientation_SM_Six_Feature(ANN *net) {
	float training_dataset[6][8][6];
	float sig_xyz[6];
	float sig_xyz_norm[6];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, sig_mag_scale;


	printf("\n\n\nTraining Start in 2 seconds ..");
	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);
	HAL_Delay(2000);

	/*
	 * Maximum of 8 cycles
	 */
	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {


			//HAL_Delay(START_POSITION_INTERVAL);

			switch (i) {

			case 0:
				BSP_LED_On(LED6);
				printf("\n\nTrain Orientation 1");
				Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
						&sig_mag_scale);
				break;

			case 1:

				printf("\n\nTrain Orientation 2");
				Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
						&sig_mag_scale);
				break;

			case 2:
				printf("\n\nTrain Orientation 3");
				Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
						&sig_mag_scale);
				break;

			case 3:
				printf("\n\nTrain Orientation 4");
				Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
						&sig_mag_scale);
				break;

			case 4:
				printf("\n\nTrain Orientation 5");
				Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
						&sig_mag_scale);
				break;

			case 5:
				printf("\n\nTrain Orientation 6");
				Feature_Extraction_State_Machine_Six_Feature(&feature_1, &feature_2, &feature_3, &feature_4, &feature_5, &feature_6,
						&sig_mag_scale);
				break;
			}

			printf("Feature 1: %0.3f\t Feature 2: %0.3f\t Feature 3: %0.3f\t Feature 4: %0.3f\t Feature 5: %0.3f\t Feature 6: %0.3f\n", feature_1, feature_2, feature_3, feature_4, feature_5, feature_6);


			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;
			sig_xyz[3] = feature_4;
			sig_xyz[4] = feature_5;
			sig_xyz[5] = feature_6;

			motion_softmax_six_feature(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];
			training_dataset[i][k][3] = sig_xyz_norm[3];
			training_dataset[i][k][4] = sig_xyz_norm[4];
			training_dataset[i][k][5] = sig_xyz_norm[5];

			printf("\n Softmax Input \t");

			for (r = 0; r < 6; r++) {
				printf("\t%0.3f", sig_xyz[r]);
			}
			printf("\n Softmax Output\t");

			for (r = 0; r < 6; r++) {
				printf("\t%0.3f", sig_xyz_norm[r]);

			}
			printf("\n\n");

		}
	}

	/*
	 * Enter NN training
	 */

	float Motion_1[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_2[6] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_3[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
	float Motion_4[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	float Motion_5[6] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	float Motion_6[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

	printf("\n\nTraining Start\n");

	training_cycles = TRAINING_CYCLES;

	for (k = 0; k < num_train_data_cycles; k++) {

		i = 0;
		while (i < training_cycles) {
			for (j = 0; j < 6; j++) {

				if ((i % 20 == 0 && i < 100) || i % 100 == 0) {
					printf("\n\nTraining Epochs: %i\n", i);

					LED_Code_Blink_Green(0);

					net_error = 0;
					for (m = 0; m < 6; m++) {
						run_ann(net, training_dataset[m][k]);
						printOutput_ANN(net, m, &error);
						if (error == 1) {
							net_error = 1;
						}
					}
					printf("\nError State: %i\n", net_error);

					if (net_error == 0) {
						return;
					}
				}

				switch (j) {

				case 0:
					train_ann(net, training_dataset[j][k], Motion_1);
					break;
				case 1:
					train_ann(net, training_dataset[j][k], Motion_2);
					break;
				case 2:
					train_ann(net, training_dataset[j][k], Motion_3);
					break;
				case 3:
					train_ann(net, training_dataset[j][k], Motion_4);
					break;
				case 4:
					train_ann(net, training_dataset[j][k], Motion_5);
					break;
				case 5:
					train_ann(net, training_dataset[j][k], Motion_6);
					break;
				default:
					break;
				}
				i++;
				HAL_Delay(5);
			}
		}
	}

	if (net_error == 0){
		LED_Code_Blink_Green(0);
		LED_Code_Blink_Green(0);
	} else {
		LED_Code_Blink_Red(1);
		LED_Code_Blink_Red(1);
	}

	printf("\n\nTraining Complete, Now Start Test Motions\n");
	return;
}


void TrainOrientation_SM_Six_Feature_Gyro(ANN *net) {
	float training_dataset[6][8][6];
	float sig_xyz[6];
	float sig_xyz_norm[6];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, sig_mag_scale;


	printf("\n\n\nTraining Start in 2 seconds ..");
	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);
	HAL_Delay(2000);

	/*
	 * Maximum of 8 cycles
	 */
	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {


			//HAL_Delay(START_POSITION_INTERVAL);

			switch (i) {

			case 0:
				BSP_LED_On(LED6);
				printf("\n\nTrain Orientation 1");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				break;

			case 1:

				printf("\n\nTrain Orientation 2");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				break;

			case 2:
				printf("\n\nTrain Orientation 3");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				break;

			case 3:
				printf("\n\nTrain Orientation 4");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				break;

			case 4:
				printf("\n\nTrain Orientation 5");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				break;

			case 5:
				printf("\n\nTrain Orientation 6");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				break;
			}

			printf("Feature 1: %0.3f\t Feature 2: %0.3f\t Feature 3: %0.3f\t Feature 4: %0.3f\t Feature 5: %0.3f\t Feature 6: %0.3f\n", feature_1, feature_2, feature_3, feature_4, feature_5, feature_6);


			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;
			sig_xyz[3] = feature_4;
			sig_xyz[4] = feature_5;
			sig_xyz[5] = feature_6;


			motion_softmax_six_feature(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];
			training_dataset[i][k][3] = sig_xyz_norm[3];
			training_dataset[i][k][4] = sig_xyz_norm[4];
			training_dataset[i][k][5] = sig_xyz_norm[5];

			printf("\n Softmax Input \t");

			for (r = 0; r < 6; r++) {
				printf("\t%0.3f", sig_xyz[r]);
			}
			printf("\n Softmax Output\t");

			for (r = 0; r < 6; r++) {
				printf("\t%0.3f", sig_xyz_norm[r]);

			}
			printf("\n\n");

		}
	}

	/*
	 * Enter NN training
	 */

	float Motion_1[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_2[6] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_3[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
	float Motion_4[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	float Motion_5[6] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	float Motion_6[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

	printf("\n\nTraining Start\n");

	training_cycles = TRAINING_CYCLES;

	for (k = 0; k < num_train_data_cycles; k++) {

		i = 0;
		while (i < training_cycles) {
			for (j = 0; j < 6; j++) {

				if ((i % 20 == 0 && i < 100) || i % 100 == 0) {
					printf("\n\nTraining Epochs: %i\n", i);

					LED_Code_Blink_Green(0);

					net_error = 0;
					for (m = 0; m < 6; m++) {
						run_ann(net, training_dataset[m][k]);
						printOutput_ANN(net, m, &error);
						if (error == 1) {
							net_error = 1;
						}
					}
					printf("\nError State: %i\n", net_error);

					if (net_error == 0) {
						return;
					}

				}

				switch (j) {

				case 0:
					train_ann(net, training_dataset[j][k], Motion_1);
					break;
				case 1:
					train_ann(net, training_dataset[j][k], Motion_2);
					break;
				case 2:
					train_ann(net, training_dataset[j][k], Motion_3);
					break;
				case 3:
					train_ann(net, training_dataset[j][k], Motion_4);
					break;
				case 4:
					train_ann(net, training_dataset[j][k], Motion_5);
					break;
				case 5:
					train_ann(net, training_dataset[j][k], Motion_6);
					break;
				default:
					break;
				}
				i++;
				HAL_Delay(5);
			}

		}

	}




	if (net_error == 0){
		LED_Code_Blink_Green(0);
		LED_Code_Blink_Green(0);
	} else {
		LED_Code_Blink_Red(1);
		LED_Code_Blink_Red(1);
	}

	printf("\n\nTraining Complete, Now Start Test Motions\n");
	return;
}


void TrainOrientation_SM_Nine_Feature_Gyro(ANN *net) {
	float training_dataset[6][8][9];
	float sig_xyz[9];
	float sig_xyz_norm[9];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, feature_7, feature_8, feature_9, sig_mag_scale;


	printf("\n\n\nTraining Start in 2 seconds ..");
	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);
	HAL_Delay(2000);

	/*
	 * Maximum of 8 cycles
	 */
	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {


			//HAL_Delay(START_POSITION_INTERVAL);

			switch (i) {

			case 0:
				BSP_LED_On(LED6);
				printf("\n\nTrain Orientation 1");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);
				break;

			case 1:

				printf("\n\nTrain Orientation 2");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);
				break;

			case 2:
				printf("\n\nTrain Orientation 3");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);
				break;

			case 3:
				printf("\n\nTrain Orientation 4");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);
				break;

			case 4:
				printf("\n\nTrain Orientation 5");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);
				break;

			case 5:
				printf("\n\nTrain Orientation 6");
				Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Gyro(&feature_7, &feature_8, &feature_9, &sig_mag_scale);
				break;
			}

			printf("Features 1: %0.3f\t2: %0.3f\t3: %0.3f\t4: %0.3f\t5: %0.3f\t6: %0.3f\t7: %0.3f\t8: %0.3f\t9: %0.3f\n", feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, feature_7, feature_8, feature_9);


			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;
			sig_xyz[3] = feature_4;
			sig_xyz[4] = feature_5;
			sig_xyz[5] = feature_6;
			sig_xyz[6] = feature_7;
			sig_xyz[7] = feature_8;
			sig_xyz[8] = feature_9;


			motion_softmax_n_feature(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];
			training_dataset[i][k][3] = sig_xyz_norm[3];
			training_dataset[i][k][4] = sig_xyz_norm[4];
			training_dataset[i][k][5] = sig_xyz_norm[5];
			training_dataset[i][k][6] = sig_xyz_norm[6];
			training_dataset[i][k][7] = sig_xyz_norm[7];
			training_dataset[i][k][8] = sig_xyz_norm[8];

			printf("\n Softmax Input \t");

			for (r = 0; r < 9; r++) {
				printf("\t%0.3f", sig_xyz[r]);
			}
			printf("\n Softmax Output\t");

			for (r = 0; r < 9; r++) {
				printf("\t%0.3f", sig_xyz_norm[r]);

			}
			printf("\n\n");

		}
	}

	/*
	 * Enter NN training
	 */

	float Motion_1[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_2[6] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_3[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
	float Motion_4[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	float Motion_5[6] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	float Motion_6[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

	printf("\n\nTraining Start\n");

	training_cycles = TRAINING_CYCLES;

	for (k = 0; k < num_train_data_cycles; k++) {

		i = 0;
		while (i < training_cycles) {
			for (j = 0; j < 6; j++) {

				if ((i % 20 == 0 && i < 100) || i % 100 == 0) {
					printf("\n\nTraining Epochs: %i\n", i);

					LED_Code_Blink_Green(0);

					net_error = 0;
					for (m = 0; m < 6; m++) {
						run_ann(net, training_dataset[m][k]);
						printOutput_ANN(net, m, &error);
						if (error == 1) {
							net_error = 1;
						}
					}
					printf("\nError State: %i\n", net_error);

					if (net_error == 0) {
						return;
					}

				}

				switch (j) {

				case 0:
					train_ann(net, training_dataset[j][k], Motion_1);
					break;
				case 1:
					train_ann(net, training_dataset[j][k], Motion_2);
					break;
				case 2:
					train_ann(net, training_dataset[j][k], Motion_3);
					break;
				case 3:
					train_ann(net, training_dataset[j][k], Motion_4);
					break;
				case 4:
					train_ann(net, training_dataset[j][k], Motion_5);
					break;
				case 5:
					train_ann(net, training_dataset[j][k], Motion_6);
					break;
				default:
					break;
				}
				i++;
				HAL_Delay(5);
			}

		}

	}




	if (net_error == 0){
		LED_Code_Blink_Green(0);
		LED_Code_Blink_Green(0);
	} else {
		LED_Code_Blink_Red(1);
		LED_Code_Blink_Red(1);
	}

	printf("\n\nTraining Complete, Now Start Test Motions\n");
	return;
}

void TrainOrientation_SM_Translation(ANN *net) {
	float training_dataset[8][8][9];
	float sig_xyz[8];
	float sig_xyz_norm[8];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, feature_7, feature_8, sig_mag_scale;


	printf("\n\n\nTraining Start in 2 seconds ..");
	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);
	HAL_Delay(2000);

	/*
	 * Maximum of 8 cycles
	 */
	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {


			switch (i) {

			case 0:
				BSP_LED_On(LED6);
				printf("\nTrain Orientation 1\n");
				Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);
				break;

			case 1:

				printf("\n\nTrain Orientation 2\n");
				Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);
				break;

			case 2:
				printf("\n\nTrain Orientation 3\n");
				Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);
				break;

			case 3:
				printf("\n\nTrain Orientation 4\n");
				Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);
				break;

			case 4:
				printf("\n\nTrain Orientation 5\n");
				Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);
				break;

			case 5:
				printf("\n\nTrain Orientation 6\n");
				Feature_Extraction_State_Machine_Translation(&feature_1, &feature_2, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_3, &feature_4, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_5, &feature_6, &sig_mag_scale);
				Feature_Extraction_State_Machine_Translation(&feature_7, &feature_8, &sig_mag_scale);
				break;
			}

			printf("Features 1: %0.3f\t2: %0.3f\t3: %0.3f\t4: %0.3f\t5: %0.3f\t6: %0.3f\t7: %0.3f\t8: %0.3f\n", feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, feature_7, feature_8);


			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;
			sig_xyz[3] = feature_4;
			sig_xyz[4] = feature_5;
			sig_xyz[5] = feature_6;
			sig_xyz[6] = feature_7;
			sig_xyz[7] = feature_8;


			motion_softmax_n_feature(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];
			training_dataset[i][k][3] = sig_xyz_norm[3];
			training_dataset[i][k][4] = sig_xyz_norm[4];
			training_dataset[i][k][5] = sig_xyz_norm[5];
			training_dataset[i][k][6] = sig_xyz_norm[6];
			training_dataset[i][k][7] = sig_xyz_norm[7];

			printf("\n Softmax Input \t");

			for (r = 0; r < 8; r++) {
				printf("\t%0.3f", sig_xyz[r]);
			}
			printf("\n Softmax Output\t");

			for (r = 0; r < 8; r++) {
				printf("\t%0.3f", sig_xyz_norm[r]);

			}
			printf("\n\n");

		}
	}

	/*
	 * Enter NN training
	 */

	float Motion_1[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_2[6] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
	float Motion_3[6] = { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 };
	float Motion_4[6] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
	float Motion_5[6] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	float Motion_6[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

	printf("\n\nTraining Start\n");

	training_cycles = TRAINING_CYCLES;

	for (k = 0; k < num_train_data_cycles; k++) {

		i = 0;
		while (i < training_cycles) {
			for (j = 0; j < 6; j++) {

				if ((i % 20 == 0 && i < 100) || i % 100 == 0) {
					printf("\n\nTraining Epochs: %i\n", i);

					LED_Code_Blink_Green(0);

					net_error = 0;
					for (m = 0; m < 6; m++) {
						run_ann(net, training_dataset[m][k]);
						printOutput_ANN(net, m, &error);
						if (error == 1) {
							net_error = 1;
						}
					}
					printf("\nError State: %i\n", net_error);

					if (net_error == 0) {
						return;
					}

				}

				switch (j) {

				case 0:
					train_ann(net, training_dataset[j][k], Motion_1);
					break;
				case 1:
					train_ann(net, training_dataset[j][k], Motion_2);
					break;
				case 2:
					train_ann(net, training_dataset[j][k], Motion_3);
					break;
				case 3:
					train_ann(net, training_dataset[j][k], Motion_4);
					break;
				case 4:
					train_ann(net, training_dataset[j][k], Motion_5);
					break;
				case 5:
					train_ann(net, training_dataset[j][k], Motion_6);
					break;
				default:
					break;
				}
				i++;
				HAL_Delay(5);
			}

		}

	}


	if (net_error == 0){
		LED_Code_Blink_Green(0);
		LED_Code_Blink_Green(0);
	} else {
		LED_Code_Blink_Red(1);
		LED_Code_Blink_Red(1);
	}

	printf("\n\nTraining Complete, Now Start Test Motions\n");
	return;
}

/**
 * @}
 */

/**
 * @}
 */



