#ifndef _PID_HPP
#define _PID_HPP

class PID {
    float kp, ki, kd, limit;
    float u, e_, e__;
    unsigned long t_;
    bool _first;
    friend void setPID();

 public:
    PID(float kp = 0, float ki = 0, float kd = 0, float limit = 0) { set(kp, ki, kd, limit), reset(); }
    void set(float kp, float ki, float kd, float limit) {
        this->kp = kp, this->ki = ki, this->kd = kd, this->limit = limit;
    }
    void reset() {
        u = e_ = e__ = 0;
        _first = true;
    }
    float update(float e, unsigned long t) {
        float dt = t - t_;
        t_ = t;
        if (!_first && dt > 0) {
            dt /= 1000;
            u += kp * ((e - e_) + ki * e * dt + kd * (e - 2 * e_ + e__) / dt);
        }
        _first = false;
        e__ = e_, e_ = e;
        u = constrain(u, -limit, limit);
        return u;
    }
    float output() const { return u; }
};

#endif  // _PID_HPP