#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

template <typename T = float> struct PID {
    T kp, ki, kd;
    T e, i;
    PID(T kp = 0, T ki = 0, T kd = 0) { set(kp, ki, kd), reset(); }
    void set(T kp, T ki, T kd) { this->kp = kp, this->ki = ki, this->kd = kd; }
    void reset() { e = 0, i = 0; }
    T update(T e, T dt) {
        this->e = e;
        i += e * dt;
        T d = (e - this->e) / dt;
        return kp * e + ki * i + kd * d;
    }
};

#endif  // CONTROLLER_HPP_