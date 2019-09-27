
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>






typedef struct{
    float x, y;
    char id[10], corBorda[30], corInterna[30], tamanhoBorda[10];
}Hidrantes;


Hidrantes* criarHidrante(char idIn[10], float xIn, float yIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]){
    Hidrantes *hidrante;
    hidrante = (Hidrantes*) malloc(sizeof(Hidrantes));
    sprintf(hidrante->corBorda, "%s", corBordaIn);
    sprintf(hidrante->corInterna, "%s", corInternaIn);
    sprintf(hidrante->tamanhoBorda, "%s", tamanhoBordaIn);
    sprintf(hidrante->id, "%s", idIn);
    hidrante->x = xIn;
    hidrante->y = yIn;
    
    return hidrante;
}


char* getIdHidrante(Hidrantes *hidrante){
    return hidrante->id;
}

float getXH(Hidrantes *hidrante){
    return hidrante->x;
}

float getYH(Hidrantes *hidrante){
    return hidrante->y;
}

void setXH(Hidrantes *hidrante, float x){
    hidrante->x = x;
}

void setYH(Hidrantes *hidrante, float y){
    hidrante->y = y;
}

void imprimirHidrante(Hidrantes *hidrante, FILE *arqSVG){
    fprintf(arqSVG,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\"style=\"fill:%s;stroke-width:%s;stroke:%s\" />\n", hidrante->x, hidrante->y,5.0,5.0,hidrante->corInterna,hidrante->tamanhoBorda,hidrante->corBorda);
}