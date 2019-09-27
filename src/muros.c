
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"lista.h"




typedef struct{
    float x1, y1, x2, y2;
}Muros;


Muros* criarMuro(float x1, float y1, float x2, float y2){
    Muros *muro;
    muro = (Muros*) malloc(sizeof(Muros));
    muro->x1 = x1;
    muro->y1 = y1;
    muro->x2 = x2;
    muro->y2 = y2;

    return muro;
}


void imprimirMuro(Muros *muro, FILE *arqSVG){
    fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:rgb(46, 39, 39);stroke-width:5\" />\n",
    muro->x1,muro->y1,muro->x2,muro->y2);
}



float getX1M(Muros *muro){
    return muro->x1;
}

float getY1M(Muros *muro){
    return muro->y1;
}

float getX2M(Muros *muro){
    return muro->x2;
}

float getY2M(Muros *muro){
    return muro->y2;
}






