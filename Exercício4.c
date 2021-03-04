#include <stdio.h> 

#include <string.h> 

#include <math.h>

#include <omp.h>

#define X_RESN 20000 /* x resolution */ 

#define Y_RESN 20000 /* y resolution */

typedef struct complextype 

{ 

float real, imag;

} Compl;

void main () {

/* Mandlebrot variables */ 

int i, j, k; 

int thread[] = {1,2,4,8,12,16};

int tnum;

Compl z, c; 

float lengthsq, temp,t0,t1; 

/* Calculate and draw points */
for (tnum = 0; tnum < 6; tnum++) {
t0 = omp_get_wtime();

#pragma omp parallel for default(none) firstprivate(j,z,c,k,lengthsq,temp) num_threads(thread[tnum])
for(i=0; i < X_RESN; i++) {
for(j=0; j < Y_RESN; j++) {

z.real = z.imag = 0.0;

c.real = ((float) j)/10000.0;
c.imag = ((float) i)/10000.0;

k = 0;

do { 

temp = z.real*z.real - z.imag*z.imag + c.real;

z.imag = 2.0*z.real*z.imag + c.imag;

z.real = temp;

lengthsq = z.real*z.real+z.imag*z.imag; 

k++;

} while (lengthsq < 4.0 && k < 100);
}
} 
t1 = omp_get_wtime();
printf("\nMandelbrot finalizado. Tempo de execução:%f numero de threads: %i",t1-t0,thread[tnum]);
}
}
