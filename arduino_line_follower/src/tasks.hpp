#ifndef _TASKS_HPP
#define _TASKS_HPP

// 等待左侧TCRT检测到黑线，期间循环执行 statement
#define WaitLeft(statement)                   \
    while (!flags::tcrt[flags::TCRT::left]) { \
        flags::tcrt.update();                 \
        { statement; }                        \
    }

// 等待右侧TCRT检测到黑线，期间循环执行 statement
#define WaitRight(statement)                   \
    while (!flags::tcrt[flags::TCRT::right]) { \
        flags::tcrt.update();                  \
        { statement; }                         \
    }

// 等待左右两侧TCRT都检测到黑线，期间循环执行 statement
#define WaitBoth(statement)                   \
    while (!flags::tcrt[flags::TCRT::both]) { \
        flags::tcrt.update();                 \
        { statement; }                        \
    }

// 在 delay_ms 时间内循环执行 statement
#define WaitDelay(statement, delay_ms)                                  \
    for (unsigned long _start = millis(); millis() - _start < delay;) { \
        flags::tcrt.update();                                           \
        { statement; }                                                  \
    }

#define WaitLeftOnce(statement) \
    { statement; }              \
    WaitLeft()

#define WaitRightOnce(statement) \
    { statement; }               \
    WaitRight()

#define WaitBothOnce(statement) \
    { statement; }              \
    WaitBoth()

#define WaitDelayOnce(statement, delay_ms) \
    { statement; }                         \
    WaitDelay(, delay_ms)

#endif  // _TASKS_HPP