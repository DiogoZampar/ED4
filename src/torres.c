
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>






typedef struct{
    float x, y;
    char id[10], corBorda[30], corInterna[30], tamanhoBorda[10];
}Torres;


Torres* criarTorre(char idIn[10], float xIn, float yIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]){
    Torres *torre;
    torre = (Torres*) malloc(sizeof(Torres));
    sprintf(torre->corBorda, "%s", corBordaIn);
    sprintf(torre->corInterna, "%s", corInternaIn);
    sprintf(torre->tamanhoBorda, "%s", tamanhoBordaIn);
    sprintf(torre->id, "%s", idIn);
    torre->x = xIn;
    torre->y = yIn;

    return torre;
}

char* getIdTorre(Torres* torre){
    return torre->id;
}


void imprimirTorre(Torres *torre, FILE *arqSVG){

    fprintf(arqSVG,"\t<rect x = \"%f\" y = \"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke-width:%s;stroke:%s\" />\n",
    torre->x,torre->y,5.0,5.0,torre->corInterna,torre->tamanhoBorda,torre->corBorda);

}


float getXT(Torres *torre){
    return torre->x;
}

float getYT(Torres *torre){
    return torre->y;
}

void setXT(Torres *torre, float x){
    torre->x = x;
}

void setYT(Torres *torre, float y){
    torre->y = y;
}