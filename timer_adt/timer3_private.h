/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#ifndef MY_TIMER3_PRIVATE_H
#define MY_TIMER3_PRIVATE_H
#include "timer3.h"
#include <time.h>

typedef struct timer3_s{
    time_t start;
    time_t stop;
};
/** Prints the given message to the standard error and abort the program. */
static void timer3_throw_error(const char *msg);

#endif /* MY_TIMER3_PRIVATE_H */
