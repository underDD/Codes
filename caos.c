#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1000
#define Niter 600
#define fran rand()/((double)RAND_MAX+1)

double f(double x);

double r;

int main(){

    double x;
    double eps;
    FILE *fout;
    srand(time(NULL));

    fout=fopen("caos.txt","w");
    r=1;
    eps=0.005;
    x=fran;

    for (int i=0;i<N;i++)
    {
        if (r>4) break;

        for(int j=0;j<Niter;j++)
        {
            if(j<Niter/2) x=f(x);
            if(j>Niter/2)
            {
                x=f(x);
                fprintf(fout,"%lf %lf\n",r,x);
            }
        }


        r+=eps;
    }




    return 0;
}


double f(double x)
{

    return r*x*(1-x);

}





