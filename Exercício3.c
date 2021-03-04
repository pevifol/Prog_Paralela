#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void main() {

long int N = 100000000;

int i, j;

int thread[] = {1,2,4,8,12,16};

int *list;

int tnum;
double t0,t1;

list = malloc(sizeof(int)*N);
for (i = 0; i<N; i++) {

list[i] = 1;

}

for (tnum = 0; tnum < 6; tnum++) {
t0 = omp_get_wtime();

for (i = 2; i*i <=N;i++) {

if (list[i]==1) {
#pragma omp parallel for default(none) shared(list,N,i) private(j) num_threads(thread[tnum])
for (j = 2*i; j <= N; j+=i) {
list[j] = 0;
}
}
}

t1 = omp_get_wtime();

printf("\n Crivo finalizado com sucesso. Tempo de execução: %f. Numero de Threads: %i",t1-t0,thread[tnum]);

}
}
