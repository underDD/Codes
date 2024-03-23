#include "head1.h"

int main(){

    srand(time(NULL));

    int S[V];
    int xp[L],yp[L],xm[L],ym[L];
    //double H[N_DATA];
    Parameters p;

    printf("patata");
    loadParameters(&p);
    printf("\n\n");
    printf("Beta inicial --> %f\n",p.b_0);
    printf("Beta final --> %f\n",p.b_f);
    printf("Paso beta --> %f\n",p.dB);
    printf("Pasos Montecarlo -->  %d\n",p.Nmc);
    printf("Numero medidas --> %d\n",p.Nmed);
    printf("Pasos termalización --> %d\n",p.Nterm);

    genconfig(S,p);
    offsets(xp,yp,xm,ym);
    saveconfig(S);
    printf("La energia de la configuracion es: %lf\n", energia(xp,yp,S));
    printf("La magnetizacion de la configuracion es: %lf\n", magneto(S));

    return 0;
    
}
