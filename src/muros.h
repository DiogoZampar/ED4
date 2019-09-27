
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"lista.h"


typedef void *Muros;


//Cria um muro com os pontos P1 e P2, e retorna um ponteiro para ele
Muros* criarMuro(float x1, float y1, float x2, float y2);

//imprime representação do muro no arquivo SVG
void imprimirMuro(Muros *muro, FILE *arqSVG);


//retorna a coordenada X do ponto 1
float getX1M(Muros *muro);

//retorna a coordenada Y do ponto 1
float getY1M(Muros *muro);

//retorna a coordenada X do ponto 2
float getX2M(Muros *muro);

//retorna a coordenada Y do ponto 2
float getY2M(Muros *muro);






