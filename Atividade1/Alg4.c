#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[]) { 
int meu_ranque, num_procs;
double tempo_inicial, tempo_final; /* Tempo de execução */
int ptotal=0.0, total; /* Total parcial e total "total" */
int origem, destino = 0;
long int N = 1000000;
/* Origem e destino das mensagens */
int etiq = 3;
/* Uma etiqueta qualquer */

MPI_Init(&argc, &argv);//Coisas de MPI
MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

/* Inicia e cria um vetor aleatório de tamanho N */
//seed pra garantir que o array gerado é sempre o mesmo.
srand(N); //Serei honesto aqui. Gerar o array em cada processo é horrivelmente ineficiente. Eu deveria gerar ele ants do init, e enviar a todos os outros processos.
int Array1[N],Array2[N],i;//Mas isso causava segmentation fault. Provalmente dois processos tentavam acessar o mesmo indice deus sabe por qual razão.
for (i = 0; i < N; i++) {
Array1[i] = rand()%500;//
Array2[i] = rand()%500;//Limita os elementos de 0 a 499.
}
if (meu_ranque == 0) {
tempo_inicial = MPI_Wtime();
}
/* Cada processo soma sua parte do produto interno*/
for (i = meu_ranque; i < N ; i += num_procs) {
ptotal += Array1[i]*Array2[i];
}
MPI_Send(&ptotal, 1, MPI_INT, destino,etiq,MPI_COMM_WORLD);

/* O processo 0 soma as integrais parciais recebidas */ 
/* Imprime o resultado */
if (meu_ranque == 0) {
for (destino ; destino < num_procs; destino++) {
MPI_Recv(&ptotal,1,MPI_INT,MPI_ANY_SOURCE,etiq,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
total += ptotal;
}
tempo_final = MPI_Wtime();
printf("Foram gastos %31f segundos\n",tempo_final-tempo_inicial);
printf("Com n = %li elementos, o produto interno\n", N);
printf("tem o valor de %i\n",total);
}
MPI_Finalize();
return (0);
}
