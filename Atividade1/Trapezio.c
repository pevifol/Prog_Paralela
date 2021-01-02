#include <stdio.h>
#include <math.h>

int main(void) {
    double i,k = 1000000,a = 0.,b = 1.,h = (b-a)/k, Total = 0.;
    for ( i = a; (b-i) > 0.0f; i=i+h) {
    Total+= (exp(i)+exp(i+h))/2;
    }
    Total=Total*h;
    printf("Total igual a: %.6f\n",Total);
    return 0;
}
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                                                                                                                                                        
~                                      
