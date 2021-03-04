#include <stdio.h>

#include <omp.h>



int main() {

int i, j, pos, val,tnum;

int N = 200000;

int rank[N];

int ranking[N];

int thread[] = {1,2,4,8,12,16};

double t0,t1;

for (i = 0; i < N; i++) { //Inicializamos o vetor a ser ordenado

rank[i] = i;

}//Com essa escolha de vetor a ser ordenado, vamos ter que no final o rank é igual a ranking.
for (tnum = 0; tnum < 6; tnum++) {
 
t0 = omp_get_wtime();

for (i = 0; i < N; i++) {

val =  rank[i];

pos = 0;

#pragma omp parallel for default(none) shared(val,N) firstprivate(rank) private(i,j) reduction(+:pos) num_threads(thread[tnum])

for (j = 0; j < N; j++) {

pos += val > rank[j];

}

ranking[pos] = val;//O elemento i do vetor rank está na “pos” posição

}

t1 =  omp_get_wtime();

printf("\nFinalizado com sucesso. Tempo de execução: %f. Numero de Threads: %i\n",t1-t0,thread[tnum]);

}

}





