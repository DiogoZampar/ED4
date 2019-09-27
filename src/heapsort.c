
#include<stdlib.h>
#include<stdbool.h>
#include"semaforos.h"
#include"hidrantes.h"
#include"lista.h"
#include"geometria.h"



float distSemaforoPonto(Semaforos *semaforo, float x, float y){
    return distancia(getXS(semaforo)-x,getYS(semaforo)-y);
}


float distHidrantePonto(Hidrantes *hidrante, float x, float y){
    return distancia(getXH(hidrante)-x,getYH(hidrante)-y);
}


void encontrarSemaforosProximos(Semaforos *vet, int num, int k, float x, float y){
    int capacidade = num;
    
    int i = num / 2, pai, filho;
    Semaforos *t;
    
    while(true) {
      if (i > 0) {
          i--;
          t = vet[i];
      } else {
          num--;
          if (num <= capacidade-k-2) break;
          t = vet[num];
          vet[num] = vet[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < num) {
          if ((filho + 1 < num)  &&  (distSemaforoPonto(vet[filho + 1],x,y) < distSemaforoPonto(vet[filho],x,y)))
              filho++;
          if (distSemaforoPonto(vet[filho],x,y) < distSemaforoPonto(t,x,y)) {
             vet[pai] = vet[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else{
             break;
          }
      }
      vet[pai] = t;
    }
    
    void *temp;
    for(int i=0;i<k;i++){
        
        temp = vet[capacidade-i-1];
        vet[capacidade-i-1]=vet[i];
        vet[i] = temp;
        
    }

    return;
} 






Hidrantes* encontrarHidrantesProximos(Hidrantes *vet, int num, int k, float x, float y){
    int capacidade = num;

    int i = num / 2, pai, filho;
    Hidrantes *t;
    
    while(true) {
      if (i > 0) {
          i--;
          t = vet[i];
      } else {
          num--;
          if (num <= capacidade-k-2) break;
          t = vet[num];
          vet[num] = vet[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < num) {
          if ((filho + 1 < num)  &&  (distHidrantePonto(vet[filho + 1],x,y) < distHidrantePonto(vet[filho],x,y)))
              filho++;
          if (distHidrantePonto(vet[filho],x,y) < distHidrantePonto(t,x,y)) {
             vet[pai] = vet[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else{
             break;
          }
      }
      vet[pai] = t;
    }


    void *temp;
    for(int i=0;i<k;i++){
        
        temp = vet[capacidade-i-1];
        vet[capacidade-i-1]=vet[i];
        vet[i] = temp;
        
    }

    return vet;
} 





Hidrantes* encontrarHidrantesDistantes(Hidrantes *vet, int num, int k, float x, float y){
    int capacidade = num; 
    
    int i = num / 2, pai, filho;
    Hidrantes *t;
    
    while(true) {
      if (i > 0) {
          i--;
          t = vet[i];
      } else {
          num--;
          if (num <= capacidade-k-2) break;
          t = vet[num];
          vet[num] = vet[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < num) {
          if ((filho + 1 < num)  &&  (distHidrantePonto(vet[filho + 1],x,y) > distHidrantePonto(vet[filho],x,y)))
              filho++;
          if (distHidrantePonto(vet[filho],x,y) > distHidrantePonto(t,x,y)) {
             vet[pai] = vet[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else{
             break;
          }
      }
      vet[pai] = t;
    }


    void *temp;
    for(int i=0;i<k;i++){
        
        temp = vet[capacidade-i-1];
        vet[capacidade-i-1]=vet[i];
        vet[i] = temp;
        
    }

    return vet;
} 
