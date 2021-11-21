#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// CCD
#define CCD_TARGET 63
#define CCD_SEP 10
#define CCD_THRESHOLD_LOW 10
#define CCD_THRESHOLD_HIGH 40

// TCRTARRAY
#define TCRT_TARGET 2560

// PID
#define PID_INVERT false
#define PID_P 4.0f
#define PID_I 0.0f
#define PID_D 0.10f
#define PID_LIMIT 3600.f  // (255-50)*16=3280

// BaseDriver
#define BASE_X_VEL 100.f

// Flags
#define FLAG_DURATION_TCRT_SIDE 200
#define FLAG_DURATION_TCRT_BOTH 200

#endif  // _CONSTANTS_H_