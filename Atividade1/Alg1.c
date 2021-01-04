#include <stdio.h>
#include <math.h>
#include "mpi.h"




int main(int argc, int* argv[]){	
    MPI_Init(NULL,NULL);
    double n = 1000000,a = 0.,b = 1., h = (b-a)/n, subdiv;
    int rank, tamanho;//Iniciamos as variáveis
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//Identificamos que proesso nós estamos. 0 é o base, os outros são os que calculam os valores.    
    MPI_Comm_size(MPI_COMM_WORLD,&tamanho);//Identificamos quando processos temos. 
    subdiv = (b-a)/(tamanho-1);//Um dos processos não calcula valores, apenas recebe a mensagem. Provavelmente é possível ganhar performance utilizando ele. 
    if ( rank == 0 ){
    double Total = 0.,t0,t1,ptotal;//Variaveis locais sendo criadas
    int i = 1 ;
    t0 = MPI_Wtime();//Capturamos o tempo inicial\

    for (i;i < tamanho;i++) {//Recebemos uma mensagem pra cada processo, não importando a ordem.
    MPI_Recv(&ptotal,1,MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE );//Recebemos um valor ptotal, de tamanho 1, do tipo double,
    Total = Total + ptotal;//de qualquer processo, com qualquer tag, pelo comunicador MPI_COMM_WORLD. Ignoramos o status da mensagem.  
    }

    t1 =  MPI_Wtime();//Capturamos o tempo final.
    printf( "O total é igual a %.6f.\nTempo de execução: %.6f segundos.\n",Total,t1-t0);//Calculamos o tempo final e entregamos o resultado.
    MPI_Finalize();//Finalizamos o uso dessa thread.
    return 0;
    }

    else {   
    double inic = a + subdiv *(rank-1),final = inic + subdiv, ptotal = 0., i;
    for (i = inic ; final-i > 0.; i = i+h) { //Subdividimos o intervalo grande em intervalos menores e iteramos por eles.
    ptotal = ptotal + ((exp(i)+exp(i+h))/2);
    }
    ptotal = ptotal*h; //Calculamos o resultado do intervalo.
    MPI_Send(&ptotal, 1, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);//Enviamos o total por um buffer de tamanho 1, do tipo double, para o processo 0 	
    //Usando a tag 3 (por nenhuma razão específica. podiamos usar qualquer tag.), pelo comunicador MPI_COMM_WORLD.
    MPI_Finalize();
    return 0;
    }
}
