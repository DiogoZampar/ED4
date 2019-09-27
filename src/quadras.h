#ifndef _QUADRAS_H
#define _QUADRAS_H

#include<stdbool.h>


typedef void *Quadras;


//Cria o objeto quadra a partir dos parâmetros recebidos, tais como coordenada x, y e largura(w) e altura(h)
Quadras* criarQuadra(char cepIn[10], float xIn, float yIn, float wIn, float hIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]);


//Função que verifica se a quadra está dentro de uma área circular ou quadrada(losango) formada pelo raio R 
//em torno de um ponto(x,y), de acordo com as métricas L1 e L2 
bool checarQuadraInternaL1L2(Quadras *quadras, char metrica[], float px, float py, float raio);


//Retorna o cep associado à quadra recebida como parâmetro
char* getCepQuadra(Quadras* quadra);


//Imprime os dados do objeto no padrão apropriado ao formato SVG
void imprimirQuadra(Quadras *quadra, FILE *arqSVG);


//retorna a coordenada x do objeto
float getXQ(Quadras *quadra);


//retorna a coordenada y do objeto
float getYQ(Quadras *quadra);


//retorna o valor da largura da quadra
float getWQ(Quadras *quadra);


//retorna o valor da altura da quadra
float getHQ(Quadras *quadra);


//modifica a coordenada x do objeto de acordo com o valor recebido
void setXQ(Quadras *quadra, float x);


//modifica a coordenada y do objeto de acordo com o valor recebido
void setYQ(Quadras *quadra, float y);

//Modifica a cor da borda da quadra no caso de impressão em um arquivo SVG
void setCstrkQ(Quadras *quadra, char cstrk[]);





#endif