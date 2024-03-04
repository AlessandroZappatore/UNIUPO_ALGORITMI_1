/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/* Es. Completa il programma:
    1. Implementando il timer come una struttura con due campi (stop e start)
    2. Includendo la definizione del timer in un file di intestazione timer2.h
    3. Usando il timer per calcolare e stampare il tempo di esecuzione di do_something().
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer2.h"

static void do_something(long n)
{
    while (n > 0)
    {
        exp(sqrt(n));
        --n;
    }
}

int main(int argc, char* argv[])
{
    long n = 200000000L;
    timer2_t tim;
    if (argc > 1)
    {
        n = atol(argv[1]);
    }

    time(&tim.inizio);    
    do_something(n);
    time(&tim.fine);

printf("Elapsed: %f seconds.\n", difftime(tim.fine, tim.inizio));

    return 0;
}
