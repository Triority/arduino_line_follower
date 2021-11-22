#ifndef _CONSTANTS_H
#define _CONSTANTS_H

// TCRTARRAY
#define TCRT_TARGET 2560  // 中间一排TCRT的pid目标值 每个TCRT代表 0,1024,2048,3072... 可以取中间两个TCRT代表值的平均值

// PID
// 公式：输出 = (KP * 当前误差 + I * 所有误差的积分 * 时间间隔 + D * (当前误差 - 上一次误差) / 时间间隔) * GAIN
#define PID_INVERT false  // PID的输出是否取反
#define PID_P 100.0       // KP
#define PID_I 0.0         // KI
#define PID_D 0.0         // KD
#define PID_PERIOD_MS 25  // PID目标控制周期，单位是毫秒，过小会导致积分和微分项失真，过大会影响系统响应速度
#define PID_GAIN 1e-5  // 乘在PID输出上的倍率，可以让PID参数的系数变大，看着更舒服一点

// BaseDriver
#define BASE_X_VEL 100.f  // 向前直走的速度

// Motor
// 电机死区：当输出pwm过小时，电流不足以支持电机转动，因此需要在算法所得输出较低时给pwm一个补偿
// 具体方案：真实pwm输出 = 所得输出 + GAIN * min(所得输出, SIZE)
// 由于arduino的pwm输出范围只有0~255，所以这个值不应该设置过大
#define MOTOR_L_DEADZONE_SIZE 10
#define MOTOR_L_DEADZONE_GAIN 3
#define MOTOR_R_DEADZONE_SIZE 10
#define MOTOR_R_DEADZONE_GAIN 3

// Flags
#define FLAG_DURATION_TCRT_SIDE 200  // 两侧TCRT检测到黑线的标志位有效时间
#define FLAG_DURATION_TCRT_BOTH 200  // 两侧TCRT标志位同时有效时会触发的both标志有效时间（这个其实并没有什么用）

#endif  // _CONSTANTS_H