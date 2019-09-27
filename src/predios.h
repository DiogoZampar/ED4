#ifndef _PREDIOS_H
#define _PREDIOS_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"geometria.h"
#include"lista.h"
#include"quadras.h"



typedef void *Predios;

//Cria o prédio e atribui os argumentos obtidos no comando do arquivo GEO
Predios* criarPredio(char cepIn[10], int numIn, float fIn, float pIn, float mrgIn, char faceIn[2]);




//retorna o CEP do prédio requisitado
char* getCepPredio(Predios* predio);


//imprime o prédio no arquivo GEO
void imprimirPredio(Predios *predio, FILE *arqSVG, Lista *listaQuadras);


//retorna a coordenada X do ponto âncora do prédio
float getXP(Predios *predio);

//retorna a coordenada Y do ponto âncora do prédio
float getYP(Predios *predio);

//retorna a medida da largura do prédio (coord. X)
float getWP(Predios *predio);

//retorna a medida da altura do prédio (coord. Y)
float getHP(Predios *predio);


#endif