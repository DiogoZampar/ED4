

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lista.h"
#include"formas.h"
#include"quadras.h"
#include"hidrantes.h"
#include"semaforos.h"
#include"torres.h"
#include"predios.h"
#include"muros.h"


void LeituraGeo(FILE *arqGEO, FILE *arqSVG, FILE *arqTXT, Lista *listaFormas, Lista *listaQuadras, Lista *listaHidrantes, Lista *listaSemaforos, Lista *listaTorres, Lista *listaPredios, Lista *listaMuros){

    char comando[10], id[30], face[20], cfill[30], cstrk[30], sw[30], cw[30], rw[30], texto[300];
    float x, y, x2, y2, w, h, r, f, p, mrg;
    int nx, num;
    char cfillQ[30], cstrkQ[30], cfillH[30], cstrkH[30], 
        cfillT[30], cstrkT[30], cfillS[30], cstrkS[30];
    char tamBordaC[10] = "2px", tamBordaR[10] = "2px", tamBordaQ[10] = "2px", tamBordaH[10] = "2px",
            tamBordaT[10] = "2px", tamBordaS[10] = "2px";
    
    sprintf(tamBordaC, "2px"); sprintf(tamBordaR, "2px");
    sprintf(cstrkQ,"yellow");sprintf(cfillQ,"red");sprintf(tamBordaQ,"5px");
    sprintf(cstrkH, "red"); sprintf(cfillH, "black"); sprintf(tamBordaH,"2px");
    sprintf(cstrkS,"black"); sprintf(cfillS,"yellow"); sprintf(tamBordaS,"3px");
    sprintf(cstrkT,"black"); sprintf(cfillT,"lightblue"); sprintf(tamBordaT,"3px");
   
    while(1){

        sprintf(comando,"zzzzzz");
        fscanf(arqGEO,"  %s",comando);
        if(strcmp(comando, "nx")==0){
            fscanf(arqGEO, " %s",comando);
            fscanf(arqGEO, " %s",comando);
            fscanf(arqGEO, " %s",comando);
            fscanf(arqGEO, " %s",comando);
            fscanf(arqGEO, " %s",comando);
            //nada
        }else if(strcmp(comando,"c")==0){
            fscanf(arqGEO, " %s %f %f %f %s %s", id, &r, &x, &y, cstrk, cfill);
            insertLista(criarFormas(id,"c",x,y,0,0,r,cstrk,cfill,tamBordaC), listaFormas);
        }else if(strcmp(comando,"r")==0){
            fscanf(arqGEO," %s %f %f %f %f %s %s", id, &w, &h, &x, &y, cstrk, cfill);
            insertLista(criarFormas(id,"r",x,y,w,h,0,cstrk,cfill,tamBordaR),listaFormas);
        }else if(strcmp(comando,"t")==0){
            fscanf(arqGEO," %f %f %s", &x, &y, texto);
            fprintf(arqTXT,"\t<text x=\"%f\" y=\"%f\" fill=\"green\">%s</text>", x,y, texto);
        }else if(strcmp(comando,"q")==0){
            fscanf(arqGEO, " %s %f %f %f %f", id, &x, &y, &w, &h);
            insertLista(criarQuadra(id,x,y,w,h,cstrkQ,cfillQ,tamBordaQ),listaQuadras);
        }else if(strcmp(comando,"h")==0){
            fscanf(arqGEO, " %s %f %f", id, &x, &y);
            insertLista(criarHidrante(id,x,y,cstrkH,cfillH,tamBordaH),listaHidrantes);
        }else if(strcmp(comando,"s")==0){
            fscanf(arqGEO, " %s %f %f", id, &x, &y);
            insertLista(criarSemaforo(id,x,y,cstrkH,cfillS,tamBordaS),listaSemaforos);
        }else if(strcmp(comando,"rb")==0){
            fscanf(arqGEO, " %s %f %f", id, &x, &y);
            insertLista(criarTorre(id,x,y,cstrkT,cfillT,tamBordaT),listaTorres);
        }else if(strcmp(comando,"cq")==0){
            fscanf(arqGEO, " %s %s %s",cfillQ,cstrkQ,tamBordaQ);
        }else if(strcmp(comando,"ch")==0){
            fscanf(arqGEO, " %s %s %s", cfillH,cstrkH,tamBordaH);
        }else if(strcmp(comando,"cr")==0){
            fscanf(arqGEO, " %s %s %s", cfillT,cstrkT,tamBordaT);
        }else if(strcmp(comando,"cs")==0){
            fscanf(arqGEO, " %s %s %s", cfillS,cstrkS,tamBordaS);
        }else if(strcmp(comando,"sw")==0){
            fscanf(arqGEO, " %s %s", tamBordaC, tamBordaR);
        }else if(strcmp(comando,"prd")==0){
            fscanf(arqGEO, " %s %s %d %f %f %f", id, face, &num, &f, &p , &mrg);
            insertLista(criarPredio(id,num,f,p,mrg,face),listaPredios);
        }else if(strcmp(comando,"mur")==0){
            fscanf(arqGEO, " %f %f %f %f", &x, &y, &x2, &y2);
            insertLista(criarMuro(x,y,x2,y2),listaMuros);
        }else return;
    }

}



void ImprimirSVG(FILE *arqSVG, Lista *listaFormas,Lista *listaQuadras,Lista *listaHidrantes,Lista *listaSemaforos,Lista *listaTorres, Lista *listaPredios, Lista *listaMuros){
    
    int ind=0;

    fprintf(arqSVG, "<svg>\n");


    
    ind = getFirst(listaFormas);
    while(ind!=NULO){
        imprimirForma(get(listaFormas,ind),arqSVG);
        ind = getNext(listaFormas,ind);
    }

    ind = getFirst(listaQuadras);
    while(ind!=NULO){
        imprimirQuadra(get(listaQuadras,ind),arqSVG);
        ind = getNext(listaQuadras,ind);
    }

    ind = getFirst(listaHidrantes);
    while(ind!=NULO){
        imprimirHidrante(get(listaHidrantes,ind),arqSVG);
        ind = getNext(listaHidrantes,ind);
    }
    ind = getFirst(listaSemaforos);
    while(ind!=NULO){
        imprimirSemaforo(get(listaSemaforos,ind),arqSVG);
        ind = getNext(listaSemaforos,ind);
    }

    ind = getFirst(listaTorres);
    while(ind!=NULO){
        imprimirTorre(get(listaTorres,ind),arqSVG);
        ind = getNext(listaTorres,ind);
    }

    ind = getFirst(listaPredios);
    while(ind!=NULO){
        imprimirPredio(get(listaPredios,ind),arqSVG, listaQuadras);
        ind = getNext(listaPredios,ind);
    }

    ind = getFirst(listaMuros);
    while(ind!=NULO){
        imprimirMuro(get(listaMuros,ind),arqSVG);
        ind = getNext(listaMuros,ind);
    }
    
}


void verificarTamanhoListas(FILE *arqGEO, int *i, int *nq, int *nh, int *ns, int *nr, int *np, int *nm){
    char comando[3];
    fscanf(arqGEO,"%s",comando);
    if(strcmp(comando,"nx")==0){
        fscanf(arqGEO," %d %d %d %d %d %d %d", i,nq,nh,ns,nr,np,nm);
    }
}
