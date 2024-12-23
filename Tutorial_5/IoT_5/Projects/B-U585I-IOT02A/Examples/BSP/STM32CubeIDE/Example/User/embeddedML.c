

/*
 * EMBEDDEDML v1.3b
 */

/*
    embeddedML.c - Embedded Machine Learning Library
    Copyright (C) 2018  Charles Zaloom

    EmbeddedML is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EmbeddedML is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EmbeddedML.  If not, see <https://www.gnu.org/licenses/>
*/

#include "main.h"



void Feature_Extraction_State_0(float * feature_1, float * feature_2, float * feature_3,
		float * sig_mag_scale) {

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

//	accel_mag = pow((ttt.xval - ttt_diff.xval), 2);
//	accel_mag = accel_mag + pow((ttt.yval - ttt_diff.yval), 2);
//	accel_mag = sqrt(accel_mag);
	accel_mag = pow((ttt.xval - ttt_diff.xval), 2);
	accel_mag += pow((ttt.yval - ttt_diff.yval), 2);
	accel_mag += pow((ttt.zval - ttt_diff.zval), 2);
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
	float rms_output, mean_output, next_max;
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


int Test_ANN(ANN *net, int prev_loc) {

	float point;
	float sig_xyz_norm[3];
	float sig_xyz[3];
	float feature_1, feature_2, feature_3, sig_mag_scale;
	int i, r, loc;
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

	printf("\n Softmax Input \t");

	for (r = 0; r < 3; r++) {
		printf("\t%0.3f", sig_xyz[r]);
	}
	printf("\n Softmax Output\t");

	for (r = 0; r < 3; r++) {
		printf("\t%0.3f", sig_xyz_norm[r]);

	}
	printf("\n\n");

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
		printf("\n\rNeural Network Classification - Motion 1\n\r");
		break;
	case 1:
		printf("\n\rNeural Network Classification - Motion 2\n\r");
		break;
	case 2:
		printf("\n\rNeural Network Classification - Motion 3\n\r");
		break;
	case 3:
		printf("\n\rNeural Network Classification - Motion 4\n\r");
		break;
	case 4:
		printf("\n\rNeural Network Classification - Motion 5\n\r");
		break;
	case 5:
		printf("\n\rNeural Network Classification - Motion 6\n\r");
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
	BSP_LED_Off(LED6);  // Red LED
	BSP_LED_Off(LED7);  // Green LED
	HAL_Delay(2000);

	num_train_data_cycles = 1;

	for (k = 0; k < num_train_data_cycles; k++) {
		for (i = 0; i < 6; i++) {

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

			printf("Feature 1: %0.3f\t Feature 2: %0.3f\t Feature 3: %0.3f\n",
					feature_1, feature_2, feature_3);


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


