#ifndef _ARQGEO_H
#define _ARQGEO_H

#include<stdlib.h>
#include<stdio.h>

//Faz a leitura do arquivo GEO e cria e integra todos os objetos às suas listas de tipos adequados
void LeituraGeo(FILE *arqGEO, FILE *arqSVG, FILE *arqTXT, Lista *listaFormas, Lista *listaQuadras, Lista *listaHidrantes, Lista *listaSemaforos, Lista *listaTorres, Lista *listaPredios, Lista *listaMuros);


//Imprime um arquivo SVG tendo como base todos os elementos presentes nas listas recebidas como parâmetro
void ImprimirSVG(FILE *arqSVG, Lista *listaFormas,Lista *listaQuadras,Lista *listaHidrantes,Lista *listaSemaforos,Lista *listaTorres, Lista *listaPredios, Lista *listaMuros);


//Verifica se o arquivo geo é iniciado pelo comando "nx", assim podendo modificar os parâmetros recebidos a
//fim de criar as listas com tamanhos adequados
void verificarTamanhoListas(FILE *arqGEO, int *i, int *nq, int *nh, int *ns, int *nr, int *np, int *nm);


#endif