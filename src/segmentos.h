#ifndef _SEGMENTOS_H
#define _SEGMENTOS_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



typedef void *Segmentos;
typedef void *Vertices;

//Cria um segmento composto dos dois vértices recebidos
Segmentos* criarSegmento();

//Retorna o vértice 1
Vertices getV1Seg(Segmentos *segmento);

//Retorna o vértice 2
Vertices getV2Seg(Segmentos *segmento);

//Insere o vértice recebido na estrutura(primeiro lugar) do segmento
void setV1Seg(Segmentos *segmento, Vertices *v);

//Insere o vértice recebido na estrutura(segundo lugar) do segmento
void setV2Seg(Segmentos *segmento, Vertices *v);

//Retorna true caso o segmento esteja ativado, ou false caso contrário
bool verifSegAtivo(Segmentos *segmento);

//modifica estado do segmento para ativo(true) ou desativado(false)
void mudarEstadoSeg(Segmentos *segmento, bool estado);

//Cria um vertice com os dados recebidos e retorna um ponteiro para o mesmo
Vertices* criarVertice(Segmentos *segmento, float x, float y, float xPonto, float yPonto);

//retorna a coordenada X do vértice
float getXV(Vertices *vertice);

//retorna a coordenada Y do vértice
float getYV(Vertices *vertice);

//retorna o ângulo entre o vértice e o ponto da bomba de luz(comando brl)
float getAngV(Vertices *vertice);

//retorna a distância entre o vértice e o ponto da bomba de luz(comando brl)
float getDistV(Vertices *vertice);

//retorna um ponteiro para o segmento do qual o vértice faz parte
Segmentos* getSegV(Vertices *vertice);

//cria uma lista com os segmentos presentes nas listas de prédios e muros recebidas, assim como segmentos que delimitam os limites máximos da cidade
Lista* criarListaSegmentos(Lista *segmentos, Lista *quadras, Lista *predios, Lista *muros, float xP, float yP);

//cria um vetor com todos os vértices que fazem parte dos segmentos presentes na lista recebida
void* criarVetorVertices(void *vet, int capacidade, void *segmentos);

//compara dois vértices em função de seus ângulos em torno do ponto da bomba de luz(comando brl), ou, como segunda opção, pela distância
int compararVertices(const void *v1, const void *v2);

//ativa segmentos à direita do ponto da bomba de luz, possibilitando determinar se um vértice encontrado é início ou fim de um segmento
void ativarSegmentosIniciais(Lista *segmentos, Lista *segsAtivos, float xBomba, float yBomba);

//identifica se, e em que ponto, uma reta, iniciando em xBomba,yBomba e passando por xV,yV intercepta o segmento recebido
float intRetaSegmento(float xBomba, float yBomba, float xV, float yV, Segmentos *seg, float *xInt, float *yInt);

//retorna ponteiro para o segmento mais próximo da direção sugerido pela subtração das coordenadas do vértice e da explosão da bomba de luz 
Segmentos* buscarSegmentoMaisProximo(Lista *segsAtivos, Vertices *vertice, float xBomba, float yBomba, float *xInt, float *yInt);

//analise o vetor de vértices, já ordenado, e imprime os pontos adequados para formação de um polígono representando a área de visibilidade(PVR) de luz da bomba no arquivo SVG
void imprimirBRL(FILE *arqSVG, Lista *segsAtivos, Vertices vet[], int tamVet, float xBomba, float yBomba);


#endif