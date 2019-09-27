
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"geometria.h"





typedef struct{
    float x, y, w, h;
    char cep[10], corBorda[30], corInterna[30], tamanhoBorda[10];
}Quadras;


Quadras* criarQuadra(char cepIn[10], float xIn, float yIn, float wIn, float hIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]){
    Quadras *quadra;
    quadra = (Quadras*) malloc(sizeof(Quadras));
    sprintf(quadra->corBorda, "%s", corBordaIn);
    sprintf(quadra->corInterna, "%s", corInternaIn);
    sprintf(quadra->tamanhoBorda, "%s", tamanhoBordaIn);
    sprintf(quadra->cep, "%s", cepIn);
    quadra->x = xIn;
    quadra->y = yIn;
    quadra->w = wIn;
    quadra->h = hIn;

    return quadra;
}





bool checarQuadraInternaL1L2(Quadras *quadras, char metrica[], float px, float py, float raio){
    if(strcmp(metrica,"L1")==0){
        float dx = fabs(quadras->x - px);
        float dy = fabs(quadras->y - py);
        if(raio>= dx+dy){
            dx = fabs(quadras->x + quadras->w - px);
            if(raio>= dx+dy){
                dy = fabs(quadras->y + quadras->h - py);
                if(raio>= dx+dy){
                    dx = fabs(quadras->x - px);
                    if(raio>= dx+dy){
                        return true;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    } else if(strcmp(metrica, "L2")==0){
        if(raio>= distancia(quadras->x-px,quadras->y-py)){
            if(raio>= distancia(quadras->x+quadras->w-px,quadras->y-py)){
                if(raio>= distancia(quadras->x-px,quadras->y+quadras->h-py)){
                    if(raio>= distancia(quadras->x+quadras->w-px,quadras->y+quadras->h-py)){
                        return true;
                    } else return false;
                } else return false;
            } else return false;
        } else return false;
    }else return NULL;

}


char* getCepQuadra(Quadras* quadra){
    return quadra->cep;
}



void imprimirQuadra(Quadras *quadra, FILE *arqSVG){

    fprintf(arqSVG,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke-width:%s;stroke:%s\" />\n",
        quadra->x, quadra->y, quadra->w, quadra->h, quadra->corInterna, quadra->tamanhoBorda,quadra->corBorda);

}


float getXQ(Quadras *quadra){
    return quadra->x;
}

float getYQ(Quadras *quadra){
    return quadra->y;
}

float getWQ(Quadras *quadra){
    return quadra->w;
}

float getHQ(Quadras *quadra){
    return quadra->h;
}


void setXQ(Quadras *quadra, float x){
    quadra->x = x;
}

void setYQ(Quadras *quadra, float y){
    quadra->y = y;
}

void setCstrkQ(Quadras *quadra, char cstrk[]){
    sprintf(quadra->corBorda, cstrk);
}