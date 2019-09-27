#ifndef _HEAPSORT_H
#define _HEAPSORT_H

#include<stdlib.h>
#include<stdbool.h>
#include"semaforos.h"
#include"hidrantes.h"
#include"lista.h"
#include"geometria.h"


float distSemaforoPonto(Semaforos *semaforo, float x, float y);


float distHidrantePonto(Hidrantes *hidrante, float x, float y);


void encontrarSemaforosProximos(Semaforos *vet, int num, int k, float x, float y);

Hidrantes* encontrarHidrantesProximos(Hidrantes *vet, int num, int k, float x, float y);

Hidrantes* encontrarHidrantesDistantes(Hidrantes *vet, int num, int k, float x, float y);


#endif