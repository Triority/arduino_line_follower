#ifndef _TASKS_HPP
#define _TASKS_HPP

#define TaskLoopWhile(statement, condition) \
    while (condition) { statement }

#define TaskLoopDelay(statement, delay_ms) \
    for (unsigned long _start = millis(); millis() - _start < delay;) { statement }

#define TaskOnceWhile(statement, condition) \
    { statement }                           \
    while (condition)                       \
        ;

#define TaskOnceDelay(statement, delay_ms)                            \
    { statement }                                                     \
    for (unsigned long _start = millis(); millis() - _start < delay;) \
        ;

#endif  // _TASKS_HPP