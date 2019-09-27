#ifndef _FORMAS_H
#define _FORMAS_H

#include<stdbool.h>



typedef void *Formas;

//Cria uma forma geométrica, podendo ser um círculo ou retângulo, de acordo com os parâmetros recebidos,
//tais como o tipo(indica se é círculo ou retângulo), coordenadas x e y do centro do círculo ou ponto âncora
//do retângulo e cores de representação no formato SVG
Formas* criarFormas(char idIn[10], char tipoIn[], float xIn, float yIn, float wIn, float hIn, float rIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]);


//Verifica se há intersecção entre as formas relacionadas aos ponteiros recebidos como parâmetros, retornando
//valor booleano apropriado
bool checarInterseccaoFormas(Formas *forma1, Formas *forma2);


//Verifica se o ponto (x,y) recebido por parâmetro é interno à figura também recebida por parâmetro
bool checarPontoInternoFormas(Formas *forma, float x, float y);


//Checa e retorna a distância euclidiana entre os centros de massa das duas formas recebidas
float checarDistanciaFormas(Formas *forma1, Formas *forma2);


//Retorna o Id relacionado à forma recebida por parâmetro
char* getIdFormas(Formas *forma);


//Imprime a representação da forma recebida por parâmetro em um arquivo de acordo com os moldes de arquivo SVG
void imprimirForma(Formas *forma, FILE *arqSVG);


//Recebe dois pontos: x e y como parâmetros (por ref.) e os modifica de modo a representar o centro de massa
//da forma cujo ponteiro também foi recebido 
void atribuirCentroMassa(Formas *forma, float *x, float *y);


//Retorna as coordenadas x e y dos dois pontos necessários para compor uma bounding box capaz de conter
//ambas as formas recebidas por parâmetro ao mesmo tempo
void obterCoordenadasBoundingBox(Formas *forma1, Formas *forma2, float *x1, float *x2, float *y1, float *y2);

#endif