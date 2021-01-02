#include <stdio.h>
#include <math.h>

int main(int argc, int* argv[]){

    double n = 1000000,a = 0, b = 1, h = (b-a)/n, Total = 0.;//Recebemos os parametros da execução de fora da função    
    for ( a; (b-a) > 0.0f; a=a+h) { 
    Total+= (exp(a)+exp(a+h))/2;
    }
    Total=Total*h;//Economizamos uma operação por loop apenas multiplicando H no final
    printf("Total igual a: %.6f\n.",Total);
    return 0;
}                                                                                                                                                     
                                                                                                                                                                                                                               
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                                                                                                                                                                                
~                                                                                                                                                                        
~                                                                                                                                                                         
