#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// CCD
#define CCD_TARGET 63
#define CCD_SEP 10
#define CCD_THRESHOLD_LOW 10
#define CCD_THRESHOLD_HIGH 40

// PID
#define PID_INVERT false
#define PID_P 3.f
#define PID_I 1.f
#define PID_D 0.f
#define PID_LIMIT 255.f

// BaseDriver
#define BASE_X_VEL 50.f

// Flags
#define FLAG_DURATION_TCRT_SIDE 200
#define FLAG_DURATION_TCRT_BOTH 200

#endif  // _CONSTANTS_H_