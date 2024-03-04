/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#ifndef TIMER2_H
#define TIMER2_H

#include <time.h>

struct Timer2{
    time_t inizio;
    time_t fine;
};

typedef struct Timer2 timer2_t;
#endif /* TIMER2_H */
