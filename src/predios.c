
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"geometria.h"
#include"lista.h"
#include"quadras.h"




typedef struct{
    float f, p, mrg;
    float x, y, w, h;
    char cep[10], face[2];
    int num;

}Predios;


Predios* criarPredio(char cepIn[10], int numIn, float fIn, float pIn, float mrgIn, char faceIn[2] ){
    Predios *predio;
    predio = (Predios*) malloc(sizeof(Predios));
    sprintf(predio->cep, "%s", cepIn);
    sprintf(predio->face, "%s", faceIn);
    predio->num = numIn;
    predio->f = fIn;
    predio->p = pIn;
    predio->mrg = mrgIn;

    return predio;
}




char* getCepPredio(Predios* predio){
    return predio->cep;
}



void imprimirPredio(Predios *predio, FILE *arqSVG, Lista *listaQuadras){
    int posic;
    void *quadra;
    posic = getFirst(listaQuadras);
    while(1){
        if(strcmp(getCepQuadra(get(listaQuadras,posic)),predio->cep)==0){
            quadra = get(listaQuadras,posic);
            break;
        }else{
            posic = getNext(listaQuadras, posic);
        }
    }
     
    if(strcmp(predio->face,"N")==0){
        predio->x = getXQ(quadra) + predio->num - predio->f/2;
        predio->y = getYQ(quadra) + getHQ(quadra) - predio->p - predio->mrg;
        predio->w = predio->f;
        predio->h = predio->p; 
    }else if(strcmp(predio->face,"L")==0){
        predio->x = getXQ(quadra) + predio->mrg;
        predio->y = getYQ(quadra) + predio->num - predio->f/2;
        predio->w = predio->p;
        predio->h = predio->f;
    }else if(strcmp(predio->face,"S")==0){
        predio->x = getXQ(quadra) + predio->num - predio->f/2;
        predio->y = getYQ(quadra) + predio->mrg;
        predio->w = predio->f;
        predio->h = predio->p;
    }else if(strcmp(predio->face,"O")==0){
        predio->x = getXQ(quadra) + getWQ(quadra) - predio->p - predio->mrg;
        predio->y = getYQ(quadra) + predio->num - predio->f/2;
        predio->w = predio->p;
        predio->h = predio->f;
    }
    
    fprintf(arqSVG, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:rgb(245, 235, 235);stroke-width:3;stroke:rgb(117, 107, 107)\" />\n",
    predio->x, predio->y, predio->w, predio->h);
}



float getXP(Predios *predio){
    return predio->x;
}

float getYP(Predios *predio){
    return predio->y;
}

float getWP(Predios *predio){
    return predio->w;
}

float getHP(Predios *predio){
    return predio->h;
}






