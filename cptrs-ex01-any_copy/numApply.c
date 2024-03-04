/* Esercizio:
   lavora con puntatori a funzioni per implementare una funzione num_apply
   per manipolare ogni elemento di un array di double 
*/
#include <stdio.h>
#include <math.h>
#include <stddef.h>

void num_apply(double arr[], double (*fun)(double), size_t array_size) {
    for(size_t i=0; i<array_size; ++i)
        arr[i]=fun(arr[i]);
}

double sqr(double x) { return x * x; }
double mult2(double x) { return 2 * x; }

int main() {
    double dary[] = {4, 16, 36};
    size_t n = sizeof dary / sizeof dary[0];

    //Applica ora le funzioni sqr, mult2, e sqrt (da math.h)
    //num_apply(/*ADD CODE HERE*/);   // -> {2, 4, 6}
    //num_apply(/*ADD CODE HERE*/);  // -> {4, 8, 12}
    num_apply(dary, sqrt, n);    // -> {16, 64, 144}

    // Print array dary on the standard output
    printf("Modified Array after sqrt: {%lf, %lf, %lf}\n", dary[0], dary[1], dary[2]);

    num_apply(dary, mult2, n);
    printf("Modified Array after mult2: {%lf, %lf, %lf}\n", dary[0], dary[1], dary[2]);

    num_apply(dary, sqr, n);
    printf("Modified Array after sqr: {%lf, %lf, %lf}\n", dary[0], dary[1], dary[2]);

    return 0;
}