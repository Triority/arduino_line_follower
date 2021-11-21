#ifndef _PIN_CONFIG_H
#define _PIN_CONFIG_H

// CCD
#define CCD_SI 5
#define CCD_CLK 4
#define CCD_AO A0

// TCRT
#define TCRT_L 3
#define TCRT_R 2

#define TCRT_ARRAY A0, A1, A2, A3, A4, A5
#define TCRT_NUM 6

// MOTOR
#define MOTOR_L_DIR 8
#define MOTOR_L_PWM 9
#define MOTOR_L_INV false

#define MOTOR_R_DIR 11
#define MOTOR_R_PWM 10
#define MOTOR_R_INV true

// L298N
#define MOTOR_L_A 9
#define MOTOR_L_B 8
#define MOTOR_L_E 11
#define MOTOR_R_A 7
#define MOTOR_R_B 6
#define MOTOR_R_E 10

#endif  // _PIN_CONFIG_H