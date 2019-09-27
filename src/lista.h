
#ifndef _LISTA_H
#define _LISTA_H


#define NULO -1



typedef void Elem;
typedef void Lista;



//Cria uma lista estática duplamente encadeada, de início composta integralmente por espaços vazios, 
//com os índices apropriados conectando os elementos de modo a permitir operações futuras.
Lista* criarLista(int capacIn);


//Retorna o número de elementos inseridos e ainda presentar na lista
int getLength(Lista *lista);


//Insere um elemento na lista no primeiro espaço livre, ordenando os ponteiros de anterior e próximo 
//conforme necessário, além de acrescentar o número de elementos por 1
int insertLista(Elem *elemento, Lista *lista);


//Remove o elemento encontrado na posição "pos" da lista, atualizando os ponteiros de anterior e próximo dos elementos
//vizinhos e diminuindo o contador de elementos internos
void removeLista(Lista *lista, int pos);

//mesmo propósito da função removeLista, mas não desaloca o elemento interno associado a "pos", que pode estar sendo utilizado em outras listas
void removeListaSecundaria(Lista *lista, int pos);


//Retorna um número inteiro apontando para o primeiro elemento da lista
int getFirst(Lista *lista);


//Retorna um número inteiro apontando para o último elemento da lista
int getLast(Lista *lista);


//Recebe um ponteiro inteiro e retorno outro ponteiro, também inteiro, do elemento seguinte na lista
int getNext(Lista *lista, int pos);


//Recebe um ponteiro inteiro e retorno outro ponteiro, também inteiro, do elemento anterior na lista
int getPrevious(Lista *lista, int pos);



//Recebe um indice inteiro para um elemento da lista, e retorna um ponteiro no formato(struct pointer) 
//do elemento que foi adicionado
Elem* get(Lista *lista, int pos);


//Retorna um ponteiro inteiro para o elemento da lista que possuir ID idêntico ao recebido pelo parâmetro
int FindIdForma(Lista *formas, char id[]);



//Retorna um ponteiro inteiro para a quadra da lista que possuir ID idêntico ao recebido pelo parâmetro
int FindIdQuadra(Lista *quadras, char id[]);

//Retorna um ponteiro inteiro para o hidrante da lista que possuir ID idêntico ao recebido pelo parâmetro
int FindIdHidrante(Lista *hidrantes, char id[]);

//Retorna um ponteiro inteiro para o semáforo da lista que possuir ID idêntico ao recebido pelo parâmetro
int FindIdSemaforo(Lista *semaforos, char id[]);

//Retorna um ponteiro inteiro para a torre da lista que possuir ID idêntico ao recebido pelo parâmetro
int FindIdTorre(Lista *torres, char id[]);

//Retorna o ponteiro(int) que indica, na lista, o elemento recebido por parâmetro
int getPtr(Lista *lista, Elem *elem);

//Libera espaço na memória, removendo a lista e todos os elementos alocados manualmente pela função malloc()
void FreeLista(Lista *lista);

//Semelhante a FreeLista, mas para listas cujo conteúdo já foi inteiramente desalocado (ex: lista que utilizava os mesmos ponteiros de outra) 
void FreeListaVazia(Lista *lista);


#endif