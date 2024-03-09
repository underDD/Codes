#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100
#define Niter 1000
double f(double x);

int main(){

    double x;



    for (int i=0;i<N;i++)
    {
        x=fran;
        printf("x_0=%lf --> ",x);
        for(int j=0;j<Niter;j++)
        {
            x=f(x);
        }
        printf("%lf\n",x);
    }

    return 0;

}




double f(double x)
{
 
    return cos(x);

}


