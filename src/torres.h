#ifndef _TORRES_H
#define _TORRES_H




typedef void *Torres;


//Cria o objeto torre de acordo com os parâmetros recebidos, tais como as coordenadas x e y
Torres* criarTorre(char idIn[10], float xIn, float yIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]);


//Retorna o Id referente à torre do ponteiro recebido como parâmetro
char* getIdTorre(Torres* torre);


//Imprime o objeto em um arquivo de acordo com seus parâmetros no padrão dos arquivos SVG
void imprimirTorre(Torres *torre, FILE *arqSVG);


//Retorna o valor da coordenada x da torre em questão
float getXT(Torres *torre);


//Retorna o valor da coordenada y da torre em questão
float getYT(Torres *torre);


//Modifica o valor da coordenada x da torre em questão, de acordo com o parâmetro recebido
void setXT(Torres *torre, float x);


//Modifica o valor da coordenada x da torre em questão, de acordo com o parâmetro recebido
void setYT(Torres *torre, float y);

#endif

