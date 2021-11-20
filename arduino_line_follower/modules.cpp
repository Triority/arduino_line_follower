#include "modules.hpp"

#include "constants.h"
#include "pinConfig.h"

GPIO led(LED_BUILTIN);
GPIO beep(A3);
GPIO tcrtL(TCRT_L), tcrtR(TCRT_R);

CCD ccd(CCD_CLK, CCD_SI, CCD_AO, CCD_THRESHOLD);

Motor motorL(MOTOR_L_PWM, MOTOR_L_DIR, MOTOR_L_INV);
Motor motorR(MOTOR_R_PWM, MOTOR_R_DIR, MOTOR_R_INV);

BaseDriver baseDriver(motorL, motorR);

PID pid(PID_P, PID_I, PID_D, PID_LIMIT);
