#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define L 128
#define V L*L
#define N_DATA 10000
#define N_Inter 100
#define fran rand()/((double)RAND_MAX+1)
#define NormRAnu (2.3283063671E-10F)

void genconfig(int *config);
int spinrandom(void);
double parisirapuano(void);
void offsets(int *xp,int *yp,int *xm,int *ym);
void calculos(float *estm,float *e,float *esq, float *msq,int *S,int *xp,int *yp);
float energia(int *xp,int *yp,int *S);
float magnetoest(int *S);
void saveconfig(int *config);
void Histograma(double *I,double *H,double *delta,double *mx,double *mn);

int main(){

    srand(time(NULL));

    int S[V];
    int xp[L],yp[L],xm[L],ym[L];
    double H[N_DATA];
    int i,j;

    genconfig(S);
    offsets(xp,yp,xm,ym);

    saveconfig(S);


}


double parisirapuano(void)
{

    unsigned int irr[256];
    unsigned int ir1;
    unsigned char ind_ran,ig1,ig2,ig3;
    int i;

    for(i=0;i<256;i++)
        irr[i]=(rand()<<16)+rand();

    ig1=ind_ran-24;
    ig2=ind_ran-55;
    ig3=ind_ran-61;
    irr[ind_ran]=irr[ig1]+irr[ig2];
    ir1=(irr[ind_ran]^irr[ig3]);
    ind_ran++;

    return ir1*NormRAnu;

}

int spinrandom(void)
{

    double omega;

    omega=parisirapuano();

    if (parisirapuano()>0.5) return -1;

    return 1;

}

void genconfig(int *config)
{

    int i;
    int flag;
    double omega;
    char line[20];
    FILE *f;

    f=fopen("IC.txt","rt");

    if (f==NULL) {printf("ERROR leyendo el fichero de CI"); exit(1);}

    fgets(line,sizeof(line),f);
    char *token=strtok(line," ");
    flag=atof(strtok(line," "));

    //fscanf(f,"%d",flag);

    printf("flag=%d",flag);

    switch(flag)
    {

    case 0:

        for(i=0;i<V;i++)
        {
            config[i]=spinrandom();
        }
        break;

    case 1:

        omega=parisirapuano();

        for(i=0;i<V;i++)
        {
            if (omega > 0.5) config[i]=1;
            if (omega < 0.5) config[i]=-1;
        }
        break;
    case 2:

        for(i=0;i<V;i++)
        {
            if (i%2==0) config[i]=1;
            if ((i+2)%(L+1)==0) config[i]=config[i-1];
            else
                config[i]=-1;
        }


    default:
        break;

    }

    fclose(f);

}

void offsets(int *xp,int *yp,int *xm,int *ym){

    int i,j;

    for(i=0;i<L;i++){
        xp[i]=1;
        yp[i]=L;
        xm[i]=-1;
        ym[i]=-L;
    }
    xp[L-1]=1-L;
    yp[L-1]=-L*(L-1);
    xm[0]=L-1;
    ym[0]=L*(L-1);

}

void calculos(float *estm,float *e,float *esq, float *msq,int *S,int *xp,int *yp){

    *estm=(magnetoest(S));      // Sin valor absoluto
    *e=energia(xp,yp,S);
    *esq=*e* *e;
    *msq=*estm* *estm;

}

float energia(int *xp,int *yp,int *S){

    double E;
    int n,i,j;

    E=0;
    n=0;

    for(i=0;i<L;i++){
        for(j=0;j<L;j++){
            E+=S[n]*(S[n+xp[j]]+S[n+yp[i]]);
            n++;
        }
    }

    return -E/(2*V);

}

float magnetoest(int *S){

    int M=0;
    int i;
    int LL=V;

    for(i=0;i<V;i++){
        M+=S[i];
    }

    //if(M<0) M=-M;

    return M/(double)LL;
}

void saveconfig(int *config)
{

    int i;
    FILE *f;

    f=fopen("savedconfig.txt","wt");

    for(i=0;i<V;i++)
    {
        fprintf(f, "%d%c", config[i], (i+1)%L==0? '\n':' ');

        //if((i+1)%L==0) fprintf(f,"\n");
        //fprintf(f,"%d ",config[i]);

    }

    fclose(f);

}

void Histograma(double *I,double *H,double *delta,double *mx,double *mn)
{

    int i,j;
    double max,min,d,norma;

    max=-100000000;
    min=+100000000;

    for(i=0;i<N_Inter;i++) H[i]=0;

    for(i=0;i<N_DATA;i++)
    {
        if (I[i]>max) max=I[i];
        if (I[i]<min) min=I[i];
    }

    d=(max-min)/N_Inter;
    norma=1.0/(N_DATA*d);

    for(i=0;i<N_DATA;i++)
    {
        j=(I[i]-min)/d;
        if (j==N_Inter) j=j-1;
        H[j]++;
        //printf("%d\n",j);
    }

    for(i=0;i<N_Inter;i++)
        H[i]*=norma;

    *delta=d;
    *mx=max;
    *mn=min;

}

