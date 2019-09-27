
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>






typedef struct{
    float x, y;
    char id[10], corBorda[30], corInterna[30], tamanhoBorda[10];
}Semaforos;


Semaforos* criarSemaforo(char idIn[10], float xIn, float yIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]){
    Semaforos *semaforo;
    semaforo = (Semaforos*) malloc(sizeof(Semaforos));
    sprintf(semaforo->corBorda, "%s", corBordaIn);
    sprintf(semaforo->corInterna, "%s", corInternaIn);
    sprintf(semaforo->tamanhoBorda, "%s", tamanhoBordaIn);
    sprintf(semaforo->id, "%s", idIn);
    semaforo->x = xIn;
    semaforo->y = yIn;

    return semaforo;
}


char* getIdSemaforo(Semaforos *semaforo){
    return semaforo->id;
} 



void imprimirSemaforo(Semaforos *semaforo, FILE *arqSVG){

    fprintf(arqSVG, "\t<rect x=\"%f\" y=\"%f\" width=\"5\" height=\"5\" style=\"fill:%s;stroke-width:%s;stroke:%s\" />\n", 
        semaforo->x, semaforo->y, semaforo->corInterna, semaforo->tamanhoBorda, semaforo->corBorda);

}



float getXS(Semaforos *semaforo){
    return semaforo->x;
}

float getYS(Semaforos *semaforo){
    return semaforo->y;
}

void setXS(Semaforos *semaforo, float x){
    semaforo->x = x;
}

void setYS(Semaforos *semaforo, float y){
    semaforo->y = y;
}