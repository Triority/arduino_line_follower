#ifndef _PID_HPP
#define _PID_HPP

class PID {
 private:
    float e_, i;

 public:
    float KP, KI, KD;
    void set(float kp, float ki, float kd);
    void reset() { e_ = i = 0; }
    float update(float e);
};

#endif  // _PID_HPP