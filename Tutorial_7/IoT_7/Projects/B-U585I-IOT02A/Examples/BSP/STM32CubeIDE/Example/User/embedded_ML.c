
/**
 ******************************************************************************
 * @file    embedded_M.c
 * @author  UCLA IoT Team
 * @brief   This code includes the functions enabling EmbeddedML developed by
 *          Charles Zaloom
 *          https://github.com/merrick7/EmbeddedML
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
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include <math.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>


void Feature_Extraction_State_Machine_Gyro(float * feature_1, float * feature_2,
		float * feature_3, float * sig_mag_scale) {


	int ttt[3], ttt_initial[3];
	int axis_index, sample_index;
	int32_t start_tick;
	int32_t Motion_Start_Tick;
	int32_t motion_duration_threshold_ticks;
	int32_t start_state;
	int32_t result;

	BSP_MOTION_SENSOR_Axes_t	rate_axes;


	float rotate_angle[3];
	float angle_mag, angle_mag_max_threshold, angle_mag_start_threshold;
	float Tsample;

	angle_mag_max_threshold = 45;
	angle_mag_start_threshold = 5;
	motion_duration_threshold_ticks = 2000;
	start_state = 0;

	/*
	 * Sample period measurement is required to determine value of differential
	 * time integration interval.
	 *
	 * Calibrate differential time by measuring time for 10 gyroscope measurement
	 * and angle computation cycles
	 */

	/* Apply initial estimate for Tsample to enable computation */

	Tsample = 0.004;

	start_tick = HAL_GetTick();

	for (sample_index = 0; sample_index < 10; sample_index++) {

		for (axis_index = 0; axis_index < 3; axis_index++) {
			ttt_initial[axis_index] = ttt[axis_index];
		}

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

	/*
	 * Compute average sample period over 10 cycles and convert from millldecond
	 * units to second units
	 */

	Tsample = (float)((HAL_GetTick() - start_tick)/(10.0 * 1000.0));

	if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
	if (result < 0){
		printf("Sampling Error %i\n\r", result);
	}

	ttt_initial[0] = rate_axes.xval;
	ttt_initial[1] = rate_axes.yval;
	ttt_initial[2] = rate_axes.zval;

	printf("\nMove to New Position While Green LED On ");
	BSP_LED_Off(LED6);  // Red LED Off
	LED_Notification_Blink_Green(5);
	BSP_LED_On(LED7);

	for (axis_index = 0; axis_index < 3; axis_index++) {
		rotate_angle[axis_index] = 0;
	}

	/*
	 * Rotation rate integration to obtain orientation angle.
	 * Note that this loop will exit when the magnitude of anvle exceeds a threshold.
	 * However, if a time of greater than 20,000 ticks (20 seconds) pass without this
	 * threshold exceedance, the loop will exit.
	 */
	for (sample_index = 0; sample_index < 20000; sample_index++) {


		for (axis_index = 0; axis_index < 3; axis_index++) {
			ttt_initial[axis_index] = ttt[axis_index];
		}

		if (BSP_MOTION_SENSOR_GetAxes(0, MOTION_GYRO, &rate_axes) != BSP_ERROR_NONE) result--;
		if (result < 0){
			printf("Sampling Error %i\n\r", result);
		}

		/* Note: Z-axis rotation is not included */

		ttt[0] = rate_axes.xval;
		ttt[1] = rate_axes.yval;
		ttt[2] = rate_axes.zval;

		/* Perform trapezoidal integration */
		for (axis_index = 0; axis_index < 3; axis_index++) {
			rotate_angle[axis_index] = rotate_angle[axis_index]
			+ (float)((ttt_initial[axis_index] + ttt[axis_index]) * Tsample / 2);
		}

		/* Note: Z-axis rotation is not included */
		rotate_angle[2] = 0;

		angle_mag = 0;
		for (axis_index = 0; axis_index < 3; axis_index++) {
			angle_mag = angle_mag + pow((rotate_angle[axis_index]), 2);
		}

		/*
		 * Convert angle magnitude from milli-degrees to degrees
		 */

		angle_mag = sqrt(angle_mag)/1000;

		/*
		 * Detect start condition and set start_state variable value
		 * Record start time
		 */

		if (angle_mag >= angle_mag_start_threshold && start_state == 0){
			Motion_Start_Tick = HAL_GetTick();
			start_state = 1;
		}

		if (angle_mag >= angle_mag_max_threshold) {
			BSP_LED_Off(LED7); // Green LED Off
			LED_Notification_Blink_Red(5);
			BSP_LED_On(LED6);
			break;
		}
	}

	*feature_1 = (float)rotate_angle[0]/1000;
	*feature_2 = (float)rotate_angle[1]/1000;
	if(HAL_GetTick() - Motion_Start_Tick >= motion_duration_threshold_ticks){
		*feature_3 = (*feature_1 + *feature_2) / 2;
		printf("This is slow");
	}

	if(HAL_GetTick() - Motion_Start_Tick < motion_duration_threshold_ticks){
		*feature_3 = -(*feature_1 + * feature_2) / 2;
		printf("This is fast");
	}

	*sig_mag_scale = angle_mag;
	return;
}

void TrainOrientation_SM_Gyro(ANN *net) {
	float training_dataset[6][8][6];
	float sig_xyz[6];
	float sig_xyz_norm[6];

	int num_train_data_cycles;
	int training_cycles;
	int i, j, k, m, r, error, net_error;
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, sig_mag_scale;
	float Z_Threshold;

	Z_Threshold = 1.2;

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


			/* Message contents may be modified for each application */

			switch (i) {

			case 0:
				printf("\n\nTrain Orientation %i - Move to Start Position While Red LED On", i + 1);
				break;

			case 1:
				printf("\n\nTrain Orientation %i - Move to Start Position While Red LED On", i + 1);
				break;

			case 2:
				printf("\n\nTrain Orientation %i - Move to Start Position While Red LED On", i + 1);
				break;

			case 3:
				printf("\n\nTrain Orientation %i - Move to Start Position While Red LED On", i + 1);
				break;

			case 4:
				printf("\n\nTrain Orientation %i - Move to Start Position While Red LED On", i + 1);
				break;

			case 5:
				printf("\n\nTrain Orientation %i - Move to Start Position While Red LED On", i + 1);
				break;
			}

			LED_Notification_Blink_Red(5);
			BSP_LED_On(LED6);
			HAL_Delay(2000);
			Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
			LED_Notification_Blink_Red(5);
			BSP_LED_On(LED6);
			Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);





			sig_xyz[0] = feature_1;
			sig_xyz[1] = feature_2;
			sig_xyz[2] = feature_3;
			sig_xyz[3] = feature_4;
			sig_xyz[4] = feature_5;
			sig_xyz[5] = feature_6;


			motion_softmax(net->topology[0], sig_xyz, sig_xyz_norm);

			training_dataset[i][k][0] = sig_xyz_norm[0];
			training_dataset[i][k][1] = sig_xyz_norm[1];
			training_dataset[i][k][2] = sig_xyz_norm[2];
			training_dataset[i][k][3] = sig_xyz_norm[3];
			training_dataset[i][k][4] = sig_xyz_norm[4];
			training_dataset[i][k][5] = sig_xyz_norm[5];

			printf("\n Softmax Input \t");

			for (r = 0; r < 6; r++) {
				printf("\t%0.1f", sig_xyz[r]);
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
						printOutput_ANN_Threshold(net, m, &error, &Z_Threshold);
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


void Test_ANN_SM_Gyro(ANN *net, int *loc) {

	float point;
	float sig_xyz_norm[6];
	float sig_xyz[6];
	float feature_1, feature_2, feature_3, feature_4, feature_5, feature_6, sig_mag_scale;
	int i, j;
	float Z_Threshold;
	int error;


	Z_Threshold = 1.2;

	BSP_LED_Off(LED6);
	BSP_LED_Off(LED7);

	printf("\nMove to Start Position While Red LED On - Then Wait for Green LED On");

	LED_Notification_Blink_Red(5);
	BSP_LED_On(LED6);
	HAL_Delay(2000);
	Feature_Extraction_State_Machine_Gyro(&feature_1, &feature_2, &feature_3, &sig_mag_scale);
	LED_Notification_Blink_Red(5);
	BSP_LED_On(LED6);
	Feature_Extraction_State_Machine_Gyro(&feature_4, &feature_5, &feature_6, &sig_mag_scale);


	sig_xyz[0] = feature_1;
	sig_xyz[1] = feature_2;
	sig_xyz[2] = feature_3;
	sig_xyz[3] = feature_4;
	sig_xyz[4] = feature_5;
	sig_xyz[5] = feature_6;

	motion_softmax(net->topology[0], sig_xyz, sig_xyz_norm);

	printf("\n Softmax Input: \t");
	for (j = 0; j < 6; j++) {
		printf("%0.1f\t", sig_xyz[j]);
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
			*loc = i;
		}
	}

	printOutput_ANN_Threshold(net, *loc, &error, &Z_Threshold);


	if (error == 1){
		*loc = -1;
	}

	switch (*loc) {
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

	if (*loc == -1){
		LED_Code_Blink_Red(0);
	} else {
		LED_Code_Blink_Green(*loc + 1);
	}
}

void printOutput_ANN_Threshold(ANN *net, int input_state, int * error, float * Z_Threshold) {

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

	if (loc == input_state
			&& ( classification_metric < *Z_Threshold
					|| point/next_max < CLASSIFICATION_DISC_THRESHOLD)) {
		*error = 1;
		printf("\t Classification Accuracy Limit");
	}

	printf("\n");
}



void motion_softmax(int n, float *x, float *y) {
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
