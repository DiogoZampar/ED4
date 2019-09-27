#ifndef _ARQQRY_H_
#define _ARQQRY_H_



#include<stdio.h>
#include<stdlib.h>
#include"lista.h"


//Recebe listas dos elementos já adicionados, e ponteiros para os arquivos a serem modificados pelos comandos 
//encontrados no arquivo .qry recebido por parâmetro 
void processarQRY(FILE *arqSVG, FILE *arqQRY, FILE *arqTXT, Lista *formas, Lista *quadras, Lista *hidrantes, Lista *semaforos, Lista *torres, Lista *predios, Lista *muros);





#endif