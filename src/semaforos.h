#ifndef _SEMAFOROS_H
#define _SEMAFOROS_H


#include<stdio.h>

typedef void *Semaforos;

//Cria o obejto semáforo de acordo com os vários parâmetros recebidos, tais como o id e as coordenadas x e y
Semaforos* criarSemaforo(char idIn[10], float xIn, float yIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]);


//Retorna o Id referente ao semáforo cujo ponteiro foi recebido por parâmetro
char* getIdSemaforo(Semaforos *semaforo);


//Imprime, de acordo com os padrões dos arquivos SVG, uma representação do semáforo em um arquivo recebido
//por parâmetro
void imprimirSemaforo(Semaforos *semaforo, FILE *arqSVG);


//Retorna o valor da coordenada X do semáforo em questão
float getXS(Semaforos *semaforo);


//Retorna o valor da coordenada Y do semáforo em questão
float getYS(Semaforos *semaforo);


//Modifica o valor da coordenada X do semáforo em questão, de acordo com o parâmetro recebido
void setXS(Semaforos *semaforo, float x);


//Modifica o valor da coordenada X do semáforo em questão, de acordo com o parâmetro recebido
void setYS(Semaforos *semaforo, float y);


#endif