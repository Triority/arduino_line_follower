#include "modules.hpp"

#include "constants.h"
#include "pinConfig.h"

GPIO led(LED_BUILTIN);
GPIO beep(GPIO_BEEP);
GPIO btn(GPIO_BTN);
GPIO tcrtL(TCRT_L), tcrtR(TCRT_R);

// CCD ccd(CCD_CLK, CCD_SI, CCD_AO, CCD_SEP, CCD_THRESHOLD_LOW, CCD_THRESHOLD_HIGH);

#if (_L298N)
Motor motorL(MOTOR_L_E, MOTOR_L_A, MOTOR_L_B, MOTOR_L_DEADZONE_SIZE, MOTOR_L_DEADZONE_GAIN);
Motor motorR(MOTOR_R_E, MOTOR_R_A, MOTOR_R_B, MOTOR_R_DEADZONE_SIZE, MOTOR_R_DEADZONE_GAIN);
#else   // _L298N
Motor motorL(MOTOR_L_PWM, MOTOR_L_DIR, MOTOR_L_INV, MOTOR_L_DEADZONE_SIZE, MOTOR_L_DEADZONE_GAIN);
Motor motorR(MOTOR_R_PWM, MOTOR_R_DIR, MOTOR_R_INV, MOTOR_R_DEADZONE_SIZE, MOTOR_R_DEADZONE_GAIN);
#endif  // _L298N

BaseDriver baseDriver(motorL, motorR);

PID pid(PID_P, PID_I, PID_D);

TCRTArray tcrtArray((const uint8_t[]){TCRT_ARRAY}, TCRT_NUM);

Timer timer;