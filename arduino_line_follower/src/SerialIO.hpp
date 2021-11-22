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

inline void clear() {
    while (Serial.available()) Serial.read();
}

template <typename T> inline bool write(T t) {
    if (!Serial.availableForWrite()) return false;
    float buf = (float)t;
    Serial.write((const uint8_t*)&buf, 4);
    return true;
}
template <typename T, typename... U> inline bool write(T t, U... u) { return write(t) && write(u...); }

inline void flush() {
    if (Serial.availableForWrite()) Serial.write("\x00\x00\x80\x7f", 4);
    Serial.flush();
}

inline int getChar() {
    char c;
    if (Serial.readBytes(&c, 1) != 1) return -1;
    return c;
}

}  // namespace SerialIO

#endif  // SERIAL_IO_HPP_
