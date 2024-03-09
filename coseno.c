#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100
#define Niter 100
#define fran rand()/((double)RAND_MAX+1)

int main(){

    double x;



    for (int i=0;i<N;i++)
    {
        x=fran;
        printf("x_0=%lf --> ",x);
        for(int j=0;j<Niter;j++)
        {
            x=cos(x);
        }
        printf("%lf\n",x);
    }




    return 0;
}






