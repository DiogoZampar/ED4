
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"lista.h"
#include"predios.h"
#include"muros.h"

#define M_PI   3.14159265358979323846264338327950288


typedef struct{
    void *V1, *V2;
    bool ativo;
}Segmentos;


typedef struct{
    float x, y;
    float ang, dist;
    Segmentos *segmento;
}Vertices;



Segmentos* criarSegmento(){
    Segmentos *segmento;
    segmento = (Segmentos*) malloc(sizeof(Segmentos));
    segmento->ativo = false;

    return segmento;
}



Vertices* getV1Seg(Segmentos *segmento){
    return segmento->V1;
}

Vertices* getV2Seg(Segmentos *segmento){
    return segmento->V2;
}

void setV1Seg(Segmentos *segmento, Vertices *v){
    segmento->V1=v;
}

void setV2Seg(Segmentos *segmento, Vertices *v){
    segmento->V2=v;
}

bool verifSegAtivo(Segmentos *segmento){
    return segmento->ativo;
}

void mudarEstadoSeg(Segmentos *segmento, bool estado){
    segmento->ativo = estado;
}


float getXV(Vertices *vertice){
    return vertice->x;
}

float getYV(Vertices *vertice){
    return vertice->y;
}


float getAngV(Vertices *vertice){
    return vertice->ang;
}

float getDistV(Vertices *vertice){
    return vertice->dist;
}

Segmentos* getSegV(Vertices *vertice){
    return vertice->segmento;
}



Vertices* criarVertice(Segmentos *segmento, float x, float y, float xPonto, float yPonto){
    Vertices *vertice;
    vertice = (Vertices*) malloc(sizeof(Vertices));
    vertice->segmento = segmento;
    vertice->x = x;
    vertice->y = y;
    vertice->ang = (atan2(yPonto-y,xPonto-(x))) * 180 / M_PI;
    vertice->dist = distancia(xPonto-x,yPonto-y);

    return vertice;
}


Lista* criarListaSegmentos(Lista *segmentos, Lista *quadras, Lista *predios, Lista *muros, float xP, float yP){
    //segmentos = malloc( (4 + (4*getLength(predios)) + getLength(muros))*(sizeof(Segmentos)) );
    int capac = 4 + 4*(getLength(predios)) + getLength(muros);
    segmentos = criarLista(capac);
    
    float xLim1, xLim2, yLim1, yLim2;
    
    //descobrir limites da cidade
    xLim1 = xP;
    xLim2 = xP;
    yLim1 = yP;
    yLim2 = yP;
    //definindo limites a partir das coordenadas das quadras
    void *quadra;
    int ptr=getFirst(quadras);
    if(ptr!=NULO){
        while(ptr!=NULO){
            quadra = get(quadras,ptr); 
            if(getXQ(quadra) < xLim1 ) xLim1 = getXQ(quadra);
            if(getXQ(quadra) + getWQ(quadra) > xLim2 ) xLim2 = getXQ(quadra) + getWQ(quadra);
            if(getYQ(quadra) < yLim1 ) yLim1 = getYQ(quadra);
            if(getYQ(quadra) + getHQ(quadra) > yLim2 ) yLim2 = getYQ(quadra) + getHQ(quadra);            
            ptr = getNext(quadras,ptr);
        }
    }
    ptr = getFirst(muros);
    void *muro = get(muros,ptr);
    if(ptr!=NULO){
        while(ptr!=NULO){
            muro = get(muros,ptr); 
            if(getX1M(muro) < xLim1 ) xLim1 = getX1M(muro);
            if(getX1M(muro) > xLim2 ) xLim2 = getX1M(muro);
            if(getY1M(muro) < yLim1 ) yLim1 = getY1M(muro);
            if(getY1M(muro) > yLim2 ) yLim2 = getY1M(muro);
            if(getX2M(muro) < xLim1 ) xLim1 = getX2M(muro);
            if(getX2M(muro) > xLim2 ) xLim2 = getX2M(muro);
            if(getY2M(muro) < yLim1 ) yLim1 = getY2M(muro);
            if(getY2M(muro) > yLim2 ) yLim2 = getY2M(muro);            
            ptr = getNext(muros,ptr);
        }
    }
    xLim1 -= 1;
    xLim2 += 1;
    yLim1 -= 1;
    yLim2 += 1;
    //criando segmentos dos limites da cidade
    //direita(O), inicialmente ativo, primeiro da lista
    void *segO;
    segO = criarSegmento();
    setV1Seg(segO, criarVertice(segO,xLim2,yLim1-10,xP,yP));    
    setV2Seg(segO,criarVertice(segO,xLim2,yLim2+10,xP,yP));
    mudarEstadoSeg(segO,true);
    insertLista(segO,segmentos);
    //esquerdo (L)
    void *segL;
    segL = criarSegmento();
    setV1Seg(segL, criarVertice(segL,xLim1,yLim1-10,xP,yP));    
    setV2Seg(segL,criarVertice(segL,xLim1,yLim2+10,xP,yP));
    insertLista(segL,segmentos);
    //cima(S)
    void *segS;
    segS = criarSegmento();
    setV1Seg(segS, criarVertice(segS,xLim1-10,yLim1,xP,yP));    
    setV2Seg(segS,criarVertice(segS,xLim2+10,yLim1,xP,yP));
    insertLista(segS,segmentos);
    //baixo(N)
    void *segN;
    segN = criarSegmento();
    setV1Seg(segN, criarVertice(segN,xLim1-10,yLim2,xP,yP));    
    setV2Seg(segN,criarVertice(segN,xLim2+10,yLim2,xP,yP));
    insertLista(segN,segmentos);
    
    ptr = getFirst(muros);
    int ptrSeg;
    while(ptr!=NULO){
        muro = get(muros,ptr);
        ptrSeg = insertLista(criarSegmento(),segmentos);
        setV1Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg),getX1M(get(muros,ptr)),getY1M(get(muros,ptr)),xP,yP));
        setV2Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg),getX2M(get(muros,ptr)),getY2M(get(muros,ptr)),xP,yP));
        ptr = getNext(muros,ptr);
    }
    
    //int ptrSeg;
    void *predio;
    ptr = getFirst(predios);
    while(ptr!=NULO){
        predio = get(predios,ptr);
        //Segmento N
        ptrSeg = insertLista(criarSegmento(),segmentos);
        setV1Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio), getYP(predio), xP, yP));
        setV2Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio) + getWP(predio), getYP(predio),xP,yP));
        //Segmento S
        ptrSeg = insertLista(criarSegmento(),segmentos);
        setV1Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio), getYP(predio) + getHP(predio),xP,yP));
        setV2Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio) + getWP(predio), getYP(predio) + getHP(predio),xP,yP));
        //Segmento O
        ptrSeg = insertLista(criarSegmento(),segmentos);
        setV1Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio) + getWP(predio), getYP(predio), xP, yP));
        setV2Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio) + getWP(predio), getYP(predio) + getHP(predio),xP,yP));
        //Segmento L
        ptrSeg = insertLista(criarSegmento(),segmentos);
        setV1Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio), getYP(predio), xP, yP));
        setV2Seg(get(segmentos,ptrSeg), criarVertice(get(segmentos,ptrSeg), getXP(predio), getYP(predio) + getHP(predio),xP,yP));
         
        ptr = getNext(predios,ptr);

    }
   
    return segmentos;
}

void* criarVetorVertices(Vertices* vet[], int capacidade, Lista *segmentos){
    
    int ptrSeg = getFirst(segmentos);
    for(int i=0;i<capacidade;i+=2){
        
        vet[i] = getV1Seg(get(segmentos,ptrSeg));
        vet[i+1] = getV2Seg(get(segmentos,ptrSeg));
        ptrSeg = getNext(segmentos,ptrSeg);
    }
}



int compararVertices(const void *v1, const void *v2){
    float Av1 = getAngV(*(Vertices**)v1);
    float Av2 = getAngV(*(Vertices**)v2);
    if(Av1<Av2)return -1;
    if(Av1>Av2)return 1;
    float Dv1 = getDistV(*(Vertices**)v1);
    float Dv2 = getDistV(*(Vertices**)v2);
    if(Dv1>Dv2)return -1;
    if(Dv1<Dv2)return 1;
    else return 0;

}



void ativarSegmentosIniciais(Lista *segmentos, Lista *segsAtivos, float xBomba, float yBomba){
    //ponto de intersecção
    float x;
    float y;
    float delta;
    //bomba
    float A1 = 0.00000f;                       //deltaY
    float B1 = 1.00000f;                  //deltaX (muito grande para simular reta infinita y=0)
    float C1 = A1*xBomba + B1*yBomba;   //C = Ax1 + By1
    //segmento
    float A2;                           
    float B2;
    float C2;
    float xMaior, xMenor, yMaior, yMenor;   //determina as coordenadas limites x e y do segmento
    int ptr = getFirst(segmentos);
    Segmentos *seg;
    while(ptr!=NULO){
        seg = get(segmentos,ptr);
        A2 = getYV(getV2Seg(seg)) - getYV(getV1Seg(seg));                       //deltaY segmento
        B2 = getXV(getV1Seg(seg)) - getXV(getV2Seg(seg));                      //deltaX segmento
        C2 = A2*getXV(getV1Seg(seg)) + B2*getYV(getV1Seg(seg));                  //C = Ax2 + Bx2
        delta = ((A1*B2)-(A2*B1));
        if(delta!=0){
            if(getYV(getV1Seg(seg)) > getYV(getV2Seg(seg))){
                yMaior = getYV(getV1Seg(seg)); yMenor = getYV(getV2Seg(seg));
            }else{
                yMaior = getYV(getV2Seg(seg)); yMenor = getYV(getV1Seg(seg));
            }


            if(getXV(getV1Seg(seg)) > getXV(getV2Seg(seg))){
                xMaior = getXV(getV1Seg(seg)); xMenor = getXV(getV2Seg(seg));
            }else{
                xMaior = getXV(getV2Seg(seg)); xMenor = getXV(getV1Seg(seg));
            }
            
            x = (B2*C1 - B1*C2)/delta;
            y = (A1*C2 - A2*C1)/delta;
            if( y<yMaior && y>yMenor && x>xBomba){
                mudarEstadoSeg(seg,true);
                insertLista(seg,segsAtivos);
            }
        }
        ptr = getNext(segmentos,ptr);
    }

}





float intRetaSegmento(float xBomba, float yBomba, float xV, float yV, Segmentos *seg, float *xInt, float *yInt){

    //ponto de intersecção
    float x;
    float y;
    float delta;
    //bomba
    float A1 = yV-yBomba;                //deltaY
    float B1 = xBomba-xV;                //deltaX (muito grande para simular reta infinita y=0)
    float C1 = A1*xBomba + B1*yBomba;   //C = Ax1 + By1
    //segmento
    float A2;                           
    float B2;
    float C2;
    float xMaior, xMenor, yMaior, yMenor;                   //determina as coordenadas limites x e y do segmento
    A2 = getYV(getV2Seg(seg)) - getYV(getV1Seg(seg));              //deltaY segmento
    B2 = getXV(getV1Seg(seg)) - getXV(getV2Seg(seg));              //deltaX segmento
    C2 = A2*getXV(getV1Seg(seg)) + B2*getYV(getV1Seg(seg));        //C = Ax2 + Bx2
    delta = ((A1*B2)-(A2*B1));
    if(delta!=0){
            *xInt = (B2*C1 - B1*C2)/delta;
            *yInt = (A1*C2 - A2*C1)/delta;
            return distancia(*xInt-xBomba,*yInt-yBomba);
    }else{//caso segmento seja paralelo ao vetor (PosV-PosBomba)
        float dist,xV1,yV1, xV2,yV2;
        
        xV1 = getXV(getV1Seg(seg));xV2 = getXV(getV2Seg(seg));
        yV1 = getYV(getV1Seg(seg));yV2 = getYV(getV2Seg(seg));
        
        dist = distancia(xV1-xBomba,yV1-yBomba);
        *xInt = xV1; *yInt = yV1;
        if(dist>distancia(xV2-xBomba,yV2-yBomba)){
            dist=distancia(xV2-xBomba,yV2-yBomba);
            *xInt = xV2; *yInt = yV2;
        }
        return dist;
    }



}



Segmentos* buscarSegmentoMaisProximo(Lista *segsAtivos, Vertices *vertice, float xBomba, float yBomba, float *xInt, float *yInt){

    Segmentos *segMP;
    float distCorrente, menorDist;
    
    int ptr = getFirst(segsAtivos);
    segMP = get(segsAtivos,ptr);
    menorDist = intRetaSegmento(xBomba,yBomba,getXV(vertice),getYV(vertice),segMP,xInt,yInt);
    while(ptr!=NULO){
        distCorrente = intRetaSegmento(xBomba,yBomba,getXV(vertice),getYV(vertice),get(segsAtivos,ptr),xInt,yInt);
        //printf("\nDistancia corrente: %f e menor dist: %f", distCorrente,menorDist);
        if(distCorrente < menorDist){
            menorDist = distCorrente;
            segMP = get(segsAtivos,ptr);
        }
    ptr = getNext(segsAtivos,ptr);
    }
    intRetaSegmento(xBomba,yBomba,getXV(vertice),getYV(vertice),segMP,xInt,yInt);
    //printf("\nRetornando segmento mais proximo: Dist:%f V1 x:%f y:%f; V2 x:%f y:%f .", menorDist, getXV(getV1Seg(segMP)),getYV(getV1Seg(segMP)),getXV(getV2Seg(segMP)),getYV(getV2Seg(segMP)));
    return segMP;

}

void imprimirBRL(FILE *arqSVG, Lista *segsAtivos, Vertices* vet[], int tamVet, float xBomba, float yBomba){

    fprintf(arqSVG,"\t<polygon points=\"");
    //Vertices *v;
    float x,y;
    Segmentos *segundoSeg;
    for(int i=0;i<tamVet;i++){
        if(verifSegAtivo(getSegV(vet[i]))){
            if(getSegV(vet[i]) == buscarSegmentoMaisProximo(segsAtivos,vet[i],xBomba,yBomba,&x,&y)){//ativo e mais próximo
                fprintf(arqSVG, "%f,%f ",getXV(vet[i]),getYV(vet[i]));  // último ponto do segmento
                removeListaSecundaria(segsAtivos,getPtr(segsAtivos,getSegV(vet[i])));                // desativa/remove o segmento da lista
                mudarEstadoSeg(getSegV(vet[i]),false);    
                segundoSeg = buscarSegmentoMaisProximo(segsAtivos,vet[i],xBomba,yBomba,&x,&y);
                fprintf(arqSVG, "%f,%f ", x,y);
            }else{//ativo e encoberto por outro segmento
                removeListaSecundaria(segsAtivos,getPtr(segsAtivos,getSegV(vet[i]))); // desativa/remove o segmento da lista
                mudarEstadoSeg(getSegV(vet[i]),false);
                segundoSeg = buscarSegmentoMaisProximo(segsAtivos,vet[i],xBomba,yBomba,&x,&y); //imprime ultimo ponto do segundo segmento
                fprintf(arqSVG, "%f,%f ", x,y);
            }
        }else{//caso segmento não esteja ativo
            insertLista(getSegV(vet[i]),segsAtivos);//Ativa/Adiciona o segmento à lista
            if(getSegV(vet[i]) == buscarSegmentoMaisProximo(segsAtivos,vet[i],xBomba,yBomba,&x,&y)){
                removeListaSecundaria(segsAtivos,getPtr(segsAtivos,getSegV(vet[i])));
                segundoSeg = buscarSegmentoMaisProximo(segsAtivos,vet[i],xBomba,yBomba,&x,&y); //imprime ultimo ponto do segundo segmento
                fprintf(arqSVG, "%f,%f ", x,y);
                insertLista(getSegV(vet[i]),segsAtivos);//Ativa/Adiciona o segmento à lista
                mudarEstadoSeg(getSegV(vet[i]),true);
                fprintf(arqSVG, "%f,%f ",getXV(vet[i]),getYV(vet[i]));  // último ponto do segmento
            }else{//caso não seja o mais próximo
                //insertLista(getSegV(vet[i]),segsAtivos);//Ativa/Adiciona o segmento à lista
                mudarEstadoSeg(getSegV(vet[i]),true);
                segundoSeg = buscarSegmentoMaisProximo(segsAtivos,vet[i],xBomba,yBomba,&x,&y); //imprime ultimo ponto do segundo segmento
                fprintf(arqSVG, "%f,%f ", x,y);
            }


        }
    }


    fprintf(arqSVG,"\" style=\"fill:yellow;fill-opacity:0.5\" />\n");
}