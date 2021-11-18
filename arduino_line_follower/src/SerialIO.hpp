#ifndef SERIAL_IO_HPP_
#define SERIAL_IO_HPP_

namespace SerialIO {

inline void begin(unsigned long baud) {
    Serial.setTimeout(100);
    Serial.begin(baud);
    while (!Serial)
        ;
}

inline bool available() { return Serial.available() && Serial.find((char*)"\x7f\x7f\x3f\x01", 4); }

template <typename T> inline bool read(T& t) {
    float buf;
    if (Serial.readBytes((char*)&buf, 4) != 4) return false;
    t = (T)buf;
    return true;
}
template <typename T, typename... U> inline bool read(T& t, U&... u) { return read(t) && read(u...); }

template <typename T> inline void write(T t) {
    float buf = (float)t;
    Serial.write((const uint8_t*)&buf, 4);
}
template <typename T, typename... U> inline void write(T t, U... u) { write(t), write(u...); }

inline void flush() { Serial.write("\x00\x00\x80\x7f", 4), Serial.flush(); }

}  // namespace SerialIO

#endif  // SERIAL_IO_HPP_
