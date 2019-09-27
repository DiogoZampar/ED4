#ifndef _HIDRANTES_H
#define _HIDRANTES_H

#include<stdio.h>


typedef void *Hidrantes;

//Cria o objeto hidrante a partir dos parâmetros recebidos, tais como coordenada x e y
Hidrantes* criarHidrante(char idIn[10], float xIn, float yIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]);

//Retorna o id associado ao hidrante recebido como parâmetro
char* getIdHidrante(Hidrantes *hidrante);

//Imprime os dados do objeto no padrão apropriado ao formato SVG
void imprimirHidrante(Hidrantes *hidrante, FILE *arqSVG);

//retorna a coordenada x do objeto
float getXH(Hidrantes *hidrante);

//retorna a coordenada y do objeto
float getYH(Hidrantes *hidrante);

//modifica a coordenada x do objeto de acordo com o valor recebido
void setXH(Hidrantes *hidrante, float x);

//modifica a coordenada y do objeto de acordo com o valor recebido
void setYH(Hidrantes *hidrante, float y);

#endif