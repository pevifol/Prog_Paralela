#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#define NELEM 1024

int main(int argc, char *argv[]) {

int i, meu_ranque, num_procs, n_partes = 0,cvecsize = 0;
float *medias_parc = NULL;
float *sub_nums_aleat = NULL;
float soma_local = 0, soma_medias = 0,soma_tot = 0;
float s,media, *media_local = NULL;


  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  srand(MPI_Wtime()*(meu_ranque+1));

  cvecsize = floor(rand()/(float)RAND_MAX * NELEM);//O vetor pode ser de até 1024 elementos. 
  sub_nums_aleat = (float *)malloc(sizeof(float) * cvecsize);// Aloca dinamicamente.
  media_local = (float *)malloc(sizeof(float)*2);

  for (i = 0; i < cvecsize; i++){//Adiciona um elemento aleatório pra cada elemento do nosso maravilhoso gerador aleatório.
  sub_nums_aleat[i] = (rand() / (float)RAND_MAX);
  soma_local += sub_nums_aleat[i];
  }
  media_local[0] = cvecsize != 0? soma_local / cvecsize : 0;//Tratamento de exceção
  media_local[1] = cvecsize; //Media local agora é um vetor de dois elementos.
  /* Imprime a soma e média dos números aleatórios em cada processo */
  printf("Soma local para o processo %d - %f, media local = %f, de tamanho %i\n",meu_ranque, soma_local, media_local[0],cvecsize);
  /* Coleta todas as médias parciais de todos os processos */
  medias_parc = (float*)malloc(sizeof(float)*num_procs*2);//Alocando memória.
  MPI_Allgather(media_local, 2, MPI_FLOAT, medias_parc, 2, MPI_FLOAT,MPI_COMM_WORLD);
  /* Calcula a média total de todos os números. */
  for (i = 0; i < num_procs * 2; i++) { // (i+1%2) vale 0 quando o indice é impar, e 0 quando ela é par. (i%2) faz o contrário.
  n_partes += medias_parc[i]*(i%2);// Achamos o numero total de elementos
  if (i+1 > num_procs*2)//Pula a parte de baixo na ultima operação.
  continue;
  soma_tot += medias_parc[i+1]*medias_parc[i]*((i+1)%2);//retornamos a media_local a "soma_local"
  }
  media = soma_tot / n_partes;//Calculamos a média. 
  printf("Média de todos os elementos calculada no processo %d é %f\n", meu_ranque, media);
  /* Libera espaço alocado */
  free(medias_parc);
  free(sub_nums_aleat);
  MPI_Finalize();
  return(0);
}
