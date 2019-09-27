#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"formas.h"
#include"quadras.h"
#include"hidrantes.h"
#include"semaforos.h"
#include"torres.h"

#define NULO -1

typedef struct{
    void *obj;
    int ant, prox;

}Elem;


typedef struct{
    int livre, prim, ult;
    Elem *l;
    int numElem, tamanho;

}Lista;




Lista* criarLista(int capacIn){
    Lista *lista;
    lista = (Lista*) malloc(sizeof(Lista));
    lista->l = (Elem*) malloc(capacIn * sizeof(Elem));
    for(int i=0;i<capacIn;i++){
        lista->l[i].prox = i+1;
        lista->l[i].ant = i-1;
    }
    
    lista->numElem = 0;
    lista->prim = NULO;
    lista->ult = NULO;
    lista->livre = 0;
    lista->tamanho = capacIn;
    return lista;
}



int getLength(Lista *lista){
    return lista->numElem;
}


int insertLista(Elem *elemento, Lista *lista){
    if(lista->livre!=NULO){
        int ind = lista->livre;        
        if(lista->numElem!=lista->tamanho)lista->livre = lista->l[ind].prox;
        else lista->livre = NULO;
        lista->l[ind].obj = elemento;
        lista->l[ind].ant = lista->ult;
        lista->l[ind].prox = NULO;
        if(lista->ult!=NULO)lista->l[lista->ult].prox = ind;
        lista->ult = ind;
        lista->numElem++;
        if(lista->prim==NULO){
            lista->prim = ind;
        }
        return ind;
    } else {
        return NULO;
    }
}


void removeLista(Lista *lista, int pos){

    int ant = lista->l[pos].ant;
    int prox = lista->l[pos].prox;


    if(pos==lista->prim){
        lista->l[prox].ant = NULO;
        lista->l[pos].prox = lista->livre;
        lista->prim = prox;
        lista->livre=pos;
    }else if(pos==lista->ult){
        lista->l[ant].prox = NULO;
        lista->l[pos].prox = lista->livre;
        lista->ult = ant;
        lista->livre = pos;
    }else{
        lista->l[prox].ant = ant;
        lista->l[ant].prox = prox;
        lista->l[pos].prox = lista->livre;
        lista->livre = pos;
    }
    free(lista->l[pos].obj);
    lista->numElem--;


}


void removeListaSecundaria(Lista *lista, int pos){

    int ant = lista->l[pos].ant;
    int prox = lista->l[pos].prox;


    if(pos==lista->prim){
        lista->l[prox].ant = NULO;
        lista->l[pos].prox = lista->livre;
        lista->prim = prox;
        lista->livre=pos;
    }else if(pos==lista->ult){
        lista->l[ant].prox = NULO;
        lista->l[pos].prox = lista->livre;
        lista->ult = ant;
        lista->livre = pos;
    }else{
        lista->l[prox].ant = ant;
        lista->l[ant].prox = prox;
        lista->l[pos].prox = lista->livre;
        lista->livre = pos;
    }
    //free(lista->l[pos].obj);
    lista->numElem--;


}



int getFirst(Lista *lista){
    return lista->prim;
}

int getLast(Lista *lista){
    if(lista->ult!=NULO){
        return lista->ult;
    } else return NULO;
}


int getNext(Lista *lista, int pos){
    if(pos!=lista->ult){    
        return lista->l[pos].prox;
    } else return NULO;
}

int getPrevious(Lista *lista, int pos){
    if(pos!=lista->prim){
        return lista->l[pos].ant;
    }else return NULO;
}

void* get(Lista *lista, int pos){
    return lista->l[pos].obj;
}



int FindIdForma(Lista *formas, char id[]){
    int ind=0;
    ind = getFirst(formas);
    while(ind!=NULO){
        if(strcmp((getIdFormas(get(formas,ind))), id)==0)return ind;
        ind = getNext(formas, ind);
    }
    return NULO;
}

int FindIdQuadra(Lista *quadras, char id[]){
    int ind=0;
    ind = getFirst(quadras);
    while(ind!=NULO){
        if(strcmp(getCepQuadra(get(quadras,ind)), id)==0)return ind;
        ind = getNext(quadras, ind);
    }
    return NULO;
}

int FindIdHidrante(Lista *hidrantes, char id[]){
    int ind=0;
    ind = getFirst(hidrantes);
    while(ind!=NULO){
        if(strcmp(getIdHidrante(get(hidrantes,ind)), id)==0)return ind;
        ind = getNext(hidrantes, ind);
    }
    return NULO;
}

int FindIdSemaforo(Lista *semaforos, char id[]){
    int ind=0;
    ind = getFirst(semaforos);
    while(ind!=NULO){
        if(strcmp(getIdSemaforo(get(semaforos,ind)), id)==0)return ind;
        ind = getNext(semaforos, ind);
    }
    return NULO;
}

int FindIdTorre(Lista *torres, char id[]){
    int ind=0;
    ind = getFirst(torres);
    while(ind!=NULO){
        if(strcmp(getIdTorre(get(torres,ind)), id)==0)return ind;
        ind = getNext(torres, ind);
    }
    return NULO;
}


int getPtr(Lista *lista, void *elem){
    int ptr = getFirst(lista);
    while(elem != get(lista,ptr)){
        ptr=getNext(lista,ptr);
    }
    return ptr;
}


void FreeLista(Lista *lista){
    int ptr = getFirst(lista);
    int prox;
    while(ptr!=NULO){
        prox = getNext(lista,ptr);
        free(lista->l[ptr].obj);
        ptr = prox;
    }
    free(lista->l);
    free(lista);
}

void FreeListaVazia(Lista *lista){
    free(lista->l);
    free(lista);
}