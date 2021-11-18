#include "modules.hpp"

#include "pinConfig.h"

GPIO led(LED_BUILTIN);

CCD ccd(CCD_CLK, CCD_SI, CCD_AO);

Motor motorL(MOTOR_L_PWM, MOTOR_L_DIR);
Motor motorR(MOTOR_R_PWM, MOTOR_R_DIR);

BaseDriver baseDriver(motorL, motorR);
