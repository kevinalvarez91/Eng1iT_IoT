
/**
 ******************************************************************************
 * @file    Examples/BSP/Inc/main.h
 * @author  MCD Application Team
 * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MAIN_H
#define MAIN_H



/* Includes ------------------------------------------------------------------*/
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "stm32u5xx_hal.h"
#include "b_u585i_iot02a.h"
#include "b_u585i_iot02a_bus.h"
#include "b_u585i_iot02a_ospi.h"
#include "b_u585i_iot02a_motion_sensors.h"
#include "b_u585i_iot02a_env_sensors.h"
#include "b_u585i_iot02a_light_sensor.h"
#include "b_u585i_iot02a_ranging_sensor.h"
#include "b_u585i_iot02a_camera.h"
#include "b_u585i_iot02a_audio.h"
#include "b_u585i_iot02a_eeprom.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	int32_t  (*DemoFunc)(void);
	uint8_t  DemoName[50];
} BSP_DemoTypedef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define COUNT_OF_EXAMPLE(x)    (sizeof(x)/sizeof(BSP_DemoTypedef))

/* Exported variables --------------------------------------------------------*/
extern __IO FlagStatus UserButtonPressed;

/* Exported functions ------------------------------------------------------- */
int32_t  Led_demo(void);
int32_t  Button_demo(void);
void     User_Button_Wait_Stop();
void 	 User_Button_Wait();
void     User_Button_Pause();
int32_t  Ms_demo(void);
int32_t  Ms_Accel_Init(void);
int32_t  Ms_Gyro_Init(void);
int32_t	 Ms_Init(void);
int32_t	 Mg_Init();
int32_t  Ms_Button_Init(void);
void     Ms_Disable(void);
int32_t	 Rs_Init(void);
int32_t  Rs_Measure(void);
void     plot_single_time_series(int plot_1_disp, char * symbol_1);
void     plot_dual_time_series(int plot_1_disp, int plot_2_disp, char * symbol_1, char * symbol_2);
void     plot_dual_time_series_compass(int plot_1_disp, int plot_2_disp, char * symbol_1, char * symbol_2);
void     plot_time_series_compass(int plot_1_disp, char * symbol_1);
void     plot_time_series_header(char * LeftFullScaleRange, char * RightFullScaleRange);
void     second_time_mark();

/************ Addition **********/

int32_t  Es_demo(void);
int32_t  Ls_demo(void);
void 	 Rs_init(void);
int32_t  Rs_demo(void);
int32_t  Camera_demo(void);
int32_t  AudioRecord_demo(void);
int32_t  OSPI_NOR_demo(void);
int32_t  OSPI_RAM_demo(void);
int32_t  EEPROM_demo(void);

void Error_Handler(void);
uint32_t CheckResult(void);
void     StartExample(void);

#endif /* MAIN_H */

#define DATA_PERIOD_MS  2

#define N_EPOCH   20000
#define N_REPORT  2000
#define XORAND_CYCLES 1

#define SYSTEM_TEST 0						// Selects demonstration execution

#define ENABLE_EMBEDDED_ML_SINGLE_STATE_ORIENTATION_CLASSIFICATION 0
#define ENABLE_EMBEDDED_ML_XORAND_DEMONSTRATION 1
#define ENABLE_EMBEDDED_ML_STATE_MACHINE_MOTION_CLASSIFICATION 0
#define ENABLE_EMBEDDED_ML_STATE_MACHINE_MOTION_CLASSIFICATION_SIX_FEATURE 0
#define ENABLE_EMBEDDED_ML_STATE_MACHINE_MOTION_CLASSIFICATION_GYRO 0
#define ENABLE_EMBEDDED_ML_STATE_MACHINE_MOTION_CLASSIFICATION_GYRO_9_FEATURE 0
#define ENABLE_EMBEDDED_ML_STATE_MACHINE_MOTION_CLASSIFICATION_TRANSLATION 1


#define NUMBER_TEST_CYCLES 20
#define CLASSIFICATION_ACC_THRESHOLD 1
#define CLASSIFICATION_DISC_THRESHOLD 1.05
#define START_POSITION_INTERVAL 3000
#define TRAINING_CYCLES 2000
#define LED_BLINK_INTERVAL 200
#define STATE_MACHINE_AVG_COUNT 100

#define DATA_PERIOD_INERTIAL   2
#define HIGH_PASS_FILTER_FREQUENCY 	0.1		// Displacement computation high pass corner frequency
#define HP_FILTER_ENABLE 		1
#define LOW_PASS_FILTER_FREQUENCY 	10.0	// Displacement computation low pass corner frequency
#define LP_FILTER_ENABLE 		1
#define INTEGRATION_INTERVAL    0.00238     // Estimated integration interval prior to calibration

#define N_SAMPLES_DISP 10
#define DATA_PERIOD_INERTIAL_DISP   2
#define HIGH_PASS_FILTER_FREQUENCY_DISP  2		// Displacement computation high pass corner frequency
#define HP_FILTER_ENABLE_DISP 		1
#define LOW_PASS_FILTER_FREQUENCY_DISP 	5.0	    // Displacement computation low pass corner frequency
#define LP_FILTER_ENABLE_DISP 		1
#define INTEGRATION_INTERVAL_DISP    0.004      // Integration interval as calibrated


#define LP_FILTER_ENABLE_DSP 1
#define HP_FILTER_ENABLE_DSP 1
#define LOW_PASS_FILTER_FREQUENCY_DSP  2.0
#define HIGH_PASS_FILTER_FREQUENCY_DSP 2.0
#define DSP_DISPLAY_INTERVAL 1000
#define DSP_SAMPLE_COUNT 200000
#define DSP_CALIBRATION_COUNT 40000
#define DSP_SIGNAL_FREQUENCY 4.0


#define DATA_PERIOD_GYRO   2
#define HIGH_PASS_FILTER_GYRO_FREQUENCY 	0.1		// Displacement computation high pass corner frequency
#define HP_FILTER_GYRO_ENABLE 		0
#define LOW_PASS_FILTER_GYRO_FREQUENCY 	100.0	// Displacement computation low pass corner frequency
#define LP_FILTER_GYRO_ENABLE 		0


#define N_SAMPLES 				4000		// Sample Count period between plot headers
#define SAMPLE_PERIOD_TOLERANCE 1.01
#define REPORT_RATE 			40			// Number of samples between print or plot
#define ENABLE_PLOT_PRINT_ACCEL	1
#define ENABLE_PLOT_PRINT_MAG	1
#define ENABLE_PLOT_PRINT_GYRO	1

#define ENABLE_MAGNETOMETER_OFFSET_MEASUREMENT 0
#define MAG_OFFSET_X 16
#define MAG_OFFSET_Y 43
#define MAG_OFFSET_Z 70

#ifndef EmbeddedML_H__
#define EmbeddedML_H__


//-----ANN Structure-----
typedef struct {
    float *weights;
    float *dedw;
    float *bias;
    unsigned int *topology;
    unsigned int n_layers;
    unsigned int n_weights;
    unsigned int n_bias;
    float *output;

    float (*output_activation_function)(float);
    float (*output_activation_derivative)(float);
    float (*hidden_activation_function)(float);
    float (*hidden_activation_derivative)(float);

    float eta;      //Learning Rate
    float beta;     //Bias Learning Rate
    float alpha;    //Momentum Coefficient
} ANN;


int Test_ANN(ANN *net, int prev_loc);
void Feature_Extraction_State_0(float * ttt_1, float * ttt_2, float * ttt_3, float *sig_mag_scale);
void Feature_Extraction_State_Machine(float * ttt_1, float * ttt_2, float * ttt_3, float * sig_mag_scale);
void Feature_Extraction_State_Machine_Six_Feature(float * ttt_1, float * ttt_2, float * ttt_3, float * ttt_4, float * ttt_5, float * ttt_6, float * sig_mag_scale);
void Feature_Extraction_State_Machine_Gyro(float * feature_1, float * feature_2, float * feature_3, float * sig_mag_scale);
void Feature_Extraction_State_Machine_Translation(float * feature_1, float * feature_2, float * sig_mag_scale);
void print_Z_Score_ANN(ANN *net, int input_state, int * error);
void printOutput_ANN(ANN *net, int input_state, int * error);
void TrainOrientation(ANN *net);
void TrainOrientation_SM(ANN *net);
void TrainOrientation_SM_Six_Feature(ANN *net);
void TrainOrientation_SM_Six_Feature_Gyro(ANN *net);
void TrainOrientation_SM_Nine_Feature_Gyro(ANN *net);
void TrainOrientation_SM_Translation(ANN *net);
int Test_ANN_SM(ANN *net, int prev_loc);
int Test_ANN_SM_Six_Feature(ANN *net, int prev_loc);
int Test_ANN_SM_Six_Feature_Gyro(ANN *net, int prev_loc);
int Test_ANN_SM_Nine_Feature_Gyro(ANN *net, int prev_loc);
int Test_ANN_SM_Translation(ANN *net, int prev_loc);
void motion_softmax(int size, float *x, float *y);
void motion_softmax_six_feature(int size, float *x, float *y);
void motion_softmax_n_feature(int n, float *x, float *y);
void LED_Code_Blink_Red(int count);
void LED_Notification_Blink_Red(int count);
void LED_Code_Blink_Green(int count);
void LED_Notification_Blink_Green(int count);
/* Exported types ------------------------------------------------------------*/




void Output_Error(int size, ANN *net, float * ground_truth, float *error);
void generate_xorand(float *x, float *y, int i);

void train_ann(ANN *net, float *input, float *output);
void run_ann(ANN *net, float *input);

void init_ann(ANN *net);
void init_pretrained_ann(ANN *net);

void set_model_memory(ANN *model, float *weights, float *dedw, float *bias, float *output);
void set_model_parameters(ANN *model, unsigned int *topology, unsigned int nlayers, char activation_function);
void set_model_hyperparameters(ANN *model, float learning_rate, float bias_learning_rate, float momentum_factor);

void set_learning_rate(ANN *model, float eta);
void set_bias_learning_rate(ANN *model, float beta);
void set_momentum_factor(ANN *model, float alpha);
void set_output_actfunc(ANN *model, char func);
void set_hidden_actfunc(ANN *model, char func);

//-----Utility-----
void fill_zeros(float *v, unsigned int size);
void fill_number(float *v, unsigned int size, float number);

//------Activation Functions-----
float relu(float x);
float relu_derivative(float x);

float relu2(float x);
float relu2_derivative(float x);

#endif /* EmbeddedML_H__*/




