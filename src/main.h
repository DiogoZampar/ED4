#ifndef _MAIN_H_
#define _MAIN_H_



#include"lista.h"

//Adequa o endereço de arquivo formado a partir da concatenação de strings que possam ter /s em excesso
char* removerBarrasExtras(char* str);



//Recebe um ponteiro para endereço de arquivo e retorna o nome de forma isolada
char* obterNomeArquivo(char* str);


#endif