#ifndef _TASKS_HPP
#define _TASKS_HPP

#define WaitLeft(statement)                   \
    while (!flags::tcrt[flags::TCRT::left]) { \
        flags::tcrt.update();                 \
        { statement; }                        \
    }

#define WaitRight(statement)                   \
    while (!flags::tcrt[flags::TCRT::right]) { \
        flags::tcrt.update();                  \
        { statement; }                         \
    }

#define WaitBoth(statement)                   \
    while (!flags::tcrt[flags::TCRT::both]) { \
        flags::tcrt.update();                 \
        { statement; }                        \
    }

#define WaitDelay(statement, delay_ms) \
    for (unsigned long _start = millis(); millis() - _start < delay;) { statement; }

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