#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define N 1000000
#define Nt 3
#define fran rand()/((double)RAND_MAX+1)

double h,s,r,b;

void rk4(double *x, double *y, double *z);
double fx(double x,double y,double z);
double fy(double x,double y,double z);
double fz(double x,double y,double z);


int main()
{
    double x[Nt], y[Nt], z[Nt];
    int i,j;
    FILE *f;
    char name[20]="Lorenz.txt";
    srand(time(NULL));

    f = fopen(name,"w");
    h = 0.01;
    s = 10.0;
    r = 18.0;
    b = 8.0/3.0;

    for(i=0;i<Nt;i++)
    {
        x[i] = fran;
        y[i] = fran;
        z[i] = fran;
    }

    if (f==NULL) return 1;

    for(i=0;i<N;i++)
    {
        rk4(x,y,z);

        for(j=0;j<Nt;j++)
        {
            fprintf(f,"%lf\t%lf\t%lf\t%lf\t",h*i,x[j],y[j],z[j]);
        }

        fprintf(f,"\n");
    }

    fclose(f);

}

double fx(double x,double y,double z)
{
    return s * (y - x);
}

double fy(double x,double y,double z)
{
    return x * (r - z) - y;
}

double fz(double x,double y,double z)
{
    return x * y - b * z;
}


void rk4(double *x, double *y, double *z)
{
    int i;
    double xn,yn,zn;
    double k1[3], k2[3], k3[3], k4[3];

    for(i=0;i<Nt;i++)
    {

        xn = x[i];
        yn = y[i];
        zn = z[i];

        k1[0] = h * fx(xn,yn,zn);
        k1[1] = h * fy(xn,yn,zn);
        k1[2] = h * fz(xn,yn,zn);
        k2[0] = h * fx(xn+0.5*k1[0],yn+0.5*k1[1],zn+0.5*k1[2]);
        k2[1] = h * fy(xn+0.5*k1[0],yn+0.5*k1[1],zn+k1[2]*0.5);
        k2[2] = h * fz(xn+0.5*k1[0],yn+0.5*k1[1],zn+k1[2]*0.5);
        k3[0] = h * fx(xn+0.5*k2[0],yn+0.5*k2[1],zn+k2[2]*0.5);
        k3[1] = h * fy(xn+0.5*k2[0],yn+0.5*k2[1],zn+k2[2]*0.5);
        k3[2] = h * fz(xn+0.5*k2[0],yn+0.5*k2[1],zn+k2[2]*0.5);
        k4[0] = h * fx(xn+k3[0],yn+k3[1],zn+k3[2]);
        k4[1] = h * fy(xn+k3[0],yn+k3[1],zn+k3[2]);
        k4[2] = h * fz(xn+k3[0],yn+k3[1],zn+k3[2]);

        x[i] = xn + (k1[0]+2*k2[0]+2*k3[0]+k4[0])/6.0;
        y[i] = yn + (k1[1]+2*k2[1]+2*k3[1]+k4[1])/6.0;
        z[i] = zn + (k1[2]+2*k2[2]+2*k3[2]+k4[2])/6.0;

    }
}

