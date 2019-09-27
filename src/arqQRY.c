#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"geometria.h"
#include"formas.h"
#include"lista.h"
#include"hidrantes.h"
#include"quadras.h"
#include"semaforos.h"
#include"torres.h"
#include"heapsort.h"
#include"segmentos.h"

//Recebe como parâmetros um arquivo SVG, onde serão desenhadas as modificações requisitadas pelos comandos,
//um arquivo TXT, onde são registrados dados dos elementos envolvidos nas operações requisitadas pelo .qry,
// o arquivo .qry em si, para leitura, assim como todas as listas de elementos necessárias às operações.


void processarQRY(FILE *arqSVG, FILE *arqQRY, FILE *arqTXT, Lista *formas, Lista *quadras, Lista *hidrantes, Lista *semaforos, Lista *torres, Lista *predios, Lista *muros){

        char comando[30], id1[30],id2[30], metrica[10], tipo[20], cstrk[30], cor[30], sufixo[30];
        char cep[30], face[2];
        int ind1, ind2, ptr, ptrAux, ns, num; 
        float x, y, x1, x2, y1, y2, r, w1, h1, w2, h2, dx, dy;

        fprintf(arqSVG,"<svg fill-opacity=\"0.5\">\n");

        while(1){
            sprintf(comando,"zzzzzz");
            fscanf(arqQRY,"%s",comando);
            if(strcmp(comando,"o?")==0){
                fscanf(arqQRY,"%s %s",id1, id2);
                fprintf(arqTXT,"%s %s %s\n",comando,id1, id2);
                ind1 = FindIdForma(formas,id1);
                ind2 = FindIdForma(formas,id2);
                obterCoordenadasBoundingBox(get(formas,ind1),get(formas,ind2),&x1,&x2,&y1,&y2);
                if(checarInterseccaoFormas(get(formas,ind1),get(formas,ind2))){
                        fprintf(arqTXT,"SIM\n");
                        fprintf(arqSVG,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"transparent\" stroke-width=\"2\" stroke=\"black\"  </rect>\n",x1,y1, x2-x1,y2-y1);
                }else {
                        fprintf(arqTXT,"NAO\n");
                        fprintf(arqSVG,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"transparent\" stroke-width=\"2\" stroke=\"black\" stroke-dasharray=\"2\" </rect>\n",x1,y1, x2-x1,y2-y1);
                }
            }else if(strcmp(comando,"i?")==0){
                fscanf(arqQRY,"%s %f %f", id1,&x1,&y1);
                ind1 = FindIdForma(formas,id1);
                atribuirCentroMassa(get(formas,ind1),&x2,&y2);
                if(checarPontoInternoFormas(get(formas,ind1),x1,y1) ){
                        fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" fill= \"green\" r=\"3\" />\n",x1,y1);
                }else{
                        fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" fill= \"red\" r=\"3\" />\n",x1,y1);
                }
                fprintf(arqSVG,"\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"black\" stroke-width=\"2\" />\n",x1,y1,x2,y2);
            }else if(strcmp(comando,"d?")==0){
                    fscanf(arqQRY,"%s %s", id1, id2);
                    ind1 = FindIdForma(formas,id1);
                    ind2 = FindIdForma(formas,id2);
                    atribuirCentroMassa(get(formas,ind1),&x1,&y1);
                    atribuirCentroMassa(get(formas,ind2),&x2,&y2);
                    fprintf(arqTXT,"%s %s %s\n",comando,id1, id2);
                    fprintf(arqTXT,"%f\n", distancia(x2-x1,y2-y1));
                    fprintf(arqSVG,"\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"black\" stroke-width=\"2\" />\n",x1,y1,x2,y2);
                    fprintf(arqSVG,"\t<text x=\"%f\" y=\"%f\" fill=\"black\">%f</text>", x1 + (x2-x1)/2 ,y1 + (y2-y1)/2, distancia(x2-x1,y2-y1) );

            }else if(strcmp(comando,"bb")==0){
                    fscanf(arqQRY,"%s %s",sufixo, cor);
            }else if(strcmp(comando,"dq")==0){
                    fscanf(arqQRY,"%s %s %f", metrica, id1, &r);
                    int enc=0;
                    ptr = FindIdHidrante(hidrantes,id1);
                    if(ptr!=NULO){
                            x1 = getXH(get(hidrantes,ptr));
                            y1 = getYH(get(hidrantes,ptr));
                            sprintf(tipo, "hidrante");
                            removeLista(hidrantes,ptr);
                            enc++;
                    }else{
                            ptr = FindIdSemaforo(semaforos,id1);
                            if(ptr!=NULO){  
                                    x1 = getXS(get(semaforos,ptr));
                                    y1 = getYS(get(semaforos,ptr));
                                    sprintf(tipo, "semaforo");
                                    removeLista(semaforos,ptr);
                                    enc++;
                            }else{
                                    ptr = FindIdTorre(torres, id1);
                                    if(ptr!=NULO){
                                        x1 = getXT(get(torres,ptr));
                                        y1 = getYT(get(torres,ptr));
                                        sprintf(tipo, "torre de celular");
                                        removeLista(torres,ptr);
                                        enc++;
                                    }
                            }
                    }
                    if(enc>0){
                            ptr = getFirst(quadras);
                            while(ptr!=NULO){
                                enc=0;
                                if(checarQuadraInternaL1L2(get(quadras,ptr),metrica,x1,y1,r)){
                                        fprintf(arqTXT,"dq cep:%s\n", getCepQuadra(get(quadras,ptr)) );
                                        ptrAux= getNext(quadras,ptr);
                                        removeLista(quadras,ptr);
                                        enc++;
                                }
                                if(enc==0)ptr = getNext(quadras,ptr);
                                else ptr=ptrAux;
                            }
                    }
                    fprintf(arqTXT,"dq %s id:%s x:%f y:%f\n",tipo,id1,x1,y1);
                    fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"7\" fill=\"transparent\" stroke-width=\"2\" stroke=\"yellow\"/>\n",
                     x1+1.5, y1+1.5 );
                    fprintf(arqSVG, "\t <circle cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"transparent\" stroke-width=\"2\" stroke=\"blue\"/>\n",
                     x1+1.5, y1+1.5 );
                    enc=0;

            }else if(strcmp(comando,"del")==0){
                    fscanf(arqQRY," %s",id1);   
                    int enc=0;
                    ptr = FindIdHidrante(hidrantes,id1);
                    if(ptr!=NULO){
                            x1 = getXH(get(hidrantes,ptr));
                            y1 = getYH(get(hidrantes,ptr));
                            sprintf(tipo, "hidrante");
                            removeLista(hidrantes,ptr);
                            enc++;
                    }else{
                            ptr = FindIdSemaforo(semaforos,id1);
                            if(ptr!=NULO){  
                                    x1 = getXS(get(semaforos,ptr));
                                    y1 = getYS(get(semaforos,ptr));
                                    sprintf(tipo, "semaforo");
                                    removeLista(semaforos,ptr);
                                    enc++;
                            }else{
                                    ptr = FindIdTorre(torres, id1);
                                    if(ptr!=NULO){
                                        x1 = getXT(get(torres,ptr));
                                        y1 = getYT(get(torres,ptr));
                                        sprintf(tipo, "torre de celular");
                                        removeLista(torres,ptr);
                                        enc++;
                                    } else {
                                                ptr = FindIdQuadra(quadras, id1);
                                                if(ptr!=NULO){
                                                x1 = getXQ(get(quadras,ptr));
                                                y1 = getYQ(get(quadras,ptr));
                                                sprintf(tipo,"quadra");
                                                removeLista(quadras,ptr);
                                                enc++;
                                            }
                                    }
                            }
                    }
                    if(enc>0)fprintf(arqTXT,"del %s %s x:%f y:%f\n", tipo, id1, x1, y1);
                    enc=0;


            }else if(strcmp(comando,"cbq")==0){
                fscanf(arqQRY,"%f %f %f %s", &x1, &y1, &r, cstrk);
                ptr = getFirst(quadras);
                while(ptr!=NULO){
                        x2 = getXQ(get(quadras,ptr));
                        y2 = getYQ(get(quadras,ptr));
                        w2 = getWQ(get(quadras,ptr));
                        h2 = getHQ(get(quadras,ptr));
                        if(     distancia( x1 - x2+w2 , y1 - y2 ) < r &&
                                distancia( x1 - x2+w2 , y1 - y2+h2 ) < r &&
                                distancia( x1 - x2    , y1 - y2 ) < r &&
                                distancia( x1 - x2    , y1 - y2+h2 ) < r ){
                                        setCstrkQ(get(quadras,ptr),cstrk);
                                        fprintf(arqTXT,"cbq id:%s x:%f y:%f \n", getCepQuadra(get(quadras,ptr)), x2,y2);
                                }
                        ptr = getNext(quadras, ptr);
                }

            }else if(strcmp(comando,"crd?")==0){
                    fscanf(arqQRY,"%s",id1);
                    int enc=0;                
                    ptr = FindIdHidrante(hidrantes,id1);
                    if(ptr!=NULO){
                            x1 = getXH(get(hidrantes,ptr));
                            y1 = getYH(get(hidrantes,ptr));
                            sprintf(tipo, "hidrante");
                            enc++;
                    }else{
                            ptr = FindIdSemaforo(semaforos,id1);
                            if(ptr!=NULO){  
                                    x1 = getXS(get(semaforos,ptr));
                                    y1 = getYS(get(semaforos,ptr));
                                    sprintf(tipo, "semaforo");
                                    enc++;
                            }else{
                                    ptr = FindIdTorre(torres, id1);
                                    if(ptr!=NULO){
                                        x1 = getXT(get(torres,ptr));
                                        y1 = getYT(get(torres,ptr));
                                        sprintf(tipo, "torre de celular");
                                        enc++;
                                    } else {
                                            ptr = FindIdQuadra(quadras,id1);
                                            if(ptr!=NULO){
                                                x1 = getXQ(get(quadras,ptr));
                                                y1 = getYQ(get(quadras,ptr));
                                                sprintf(tipo, "quadra");
                                                enc++;                                                    
                                            } else {}
                                    }
                            }
                    }
                    if(enc>0)fprintf(arqTXT,"crd? %s x:%f y:%f\n",tipo, x1, y1);
                    enc=0;
            }else if(strcmp(comando,"trns")==0){
                    fscanf(arqQRY,"%f %f %f %f %f %f", &x1, &y1, &w1, &h1, &dx, &dy);

                        ptr = getFirst(quadras);
                        while(ptr!=NULO){
                                x2 = getXQ(get(quadras,ptr));
                                y2 = getYQ(get(quadras,ptr));
                                w2 = getWQ(get(quadras,ptr));
                                h2 = getHQ(get(quadras,ptr));
                                if(
                                        x2 >= x1 && x2 <= x1+w1 &&
                                        x2+w2 >= x1 && x2+w2 <= x1+w1 &&
                                        y2 >= y1 && y2 <= y1+h1 &&
                                        y2+h2 >= y1 && y2+h2 <= y1+h1
                                ){
                                        setXQ(get(quadras,ptr),x2+dx);
                                        setYQ(get(quadras,ptr),y2+dy);
                                        fprintf(arqTXT,"trns cep:%s pos antiga - x:%f y:%f pos nova - x:%f y:%f\n",
                                        getCepQuadra(get(quadras,ptr)),x2,y2,x2+dx,y2+dy);
                                }
                                ptr = getNext(quadras,ptr);
                        }
                        ptr = getFirst(hidrantes);
                        while(ptr!=NULO){
                                x2 = getXH(get(hidrantes,ptr));
                                y2 = getYH(get(hidrantes,ptr));
                                if(
                                        x2 >= x1 && x2 <= x1+w1 &&
                                        x2+3 >= x1 && x2+3 <= x1+w1 &&
                                        y2 >= y1 && y2 <= y1+h1 &&
                                        y2+3 >= y1 && y2+3 <= y1+h1
                                ){
                                        setXH(get(hidrantes,ptr),x2+dx);
                                        setYH(get(hidrantes,ptr),y2+dy);
                                        fprintf(arqTXT,"trns id:%s pos antiga - x:%f y:%f pos nova - x:%f y:%f\n",
                                        getIdHidrante(get(hidrantes,ptr)),x2,y2,x2+dx,y2+dy);
                                }
                                ptr = getNext(hidrantes,ptr);
                        }
                        ptr = getFirst(semaforos);
                        while(ptr!=NULO){
                                x2 = getXS(get(semaforos,ptr));
                                y2 = getYS(get(semaforos,ptr));
                                if(
                                        x2 >= x1 && x2 <= x1+w1 &&
                                        x2+3 >= x1 && x2+3 <= x1+w1 &&
                                        y2 >= y1 && y2 <= y1+h1 &&
                                        y2+3 >= y1 && y2+3 <= y1+h1
                                ){
                                        setXS(get(semaforos,ptr),x2+dx);
                                        setYS(get(semaforos,ptr),y2+dy);
                                        fprintf(arqTXT,"trns id:%s pos antiga - x:%f y:%f pos nova - x:%f y:%f\n",
                                        getIdSemaforo(get(semaforos,ptr)),x2,y2,x2+dx,y2+dy);
                                }
                                ptr = getNext(semaforos,ptr);
                        }
                        ptr = getFirst(torres);
                        while(ptr!=NULO){
                                x2 = getXT(get(torres,ptr));
                                y2 = getYT(get(torres,ptr));
                                if(
                                        x2 >= x1 && x2 <= x1+w1 &&
                                        x2+3 >= x1 && x2+3 <= x1+w1 &&
                                        y2 >= y1 && y2 <= y1+h1 &&
                                        y2+3 >= y1 && y2+3 <= y1+h1
                                ){
                                        setXT(get(torres,ptr),x2+dx);
                                        setYT(get(torres,ptr),y2+dy);
                                        fprintf(arqTXT,"trns id:%s pos antiga - x:%f y:%f pos nova - x:%f y:%f\n",
                                        getIdTorre(get(torres,ptr)),x2,y2,x2+dx,y2+dy);
                                }
                                ptr = getNext(torres,ptr);
                                

                        }

            } else if(strcmp(comando,"fi")==0){
                fscanf(arqQRY, " %f %f %d %f", &x, &y, &ns, &r);
                
                ptr=getFirst(hidrantes);
                while(ptr!=NULO){
                        if(ptr==NULO){break;}
                        if(distancia(getXH(get(hidrantes,ptr))-x,getYH(get(hidrantes,ptr))-y)<r){
                                fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" fill=\"darkblue\" />\n", getXH(get(hidrantes,ptr))+2.5, getYH(get(hidrantes,ptr))+2.5);
                                fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:yellow;stroke-width:1\" />\n", x, y, getXH(get(hidrantes,ptr))+2.5,getYH(get(hidrantes,ptr))+2.5);
                                fprintf(arqTXT, "Hidrante ativado: %s em (%f,%f)\n", getIdHidrante(get(hidrantes,ptr)),getXH(get(hidrantes,ptr)),getYH(get(hidrantes,ptr)));
                        }
                        ptr=getNext(hidrantes,ptr);
                        
                }
                
                Semaforos *vet;
                vet=malloc(getLength(semaforos)*sizeof(Semaforos));
                int ptr = getFirst(semaforos);
                for(int i=0;i<getLength(semaforos);i++){
                        vet[i]=get(semaforos,ptr);
                        ptr=getNext(semaforos,ptr);
                }
                encontrarSemaforosProximos(vet, getLength(semaforos), ns, x,y);
                
                for(int i=0;i<ns;i++){
                        fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"20\" stroke-width=\"10\" stroke=\"red\" stroke-opacity=\"1\" fill-opacity=\"0\" />\n", getXS(vet[i])+2.5, getYS(vet[i])+2.5);
                        fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:yellow;stroke-width:1\" />\n", x, y, getXS(vet[i])+2.5,getYS(vet[i])+2.5);
                        fprintf(arqTXT,"Semáforo alterado: ID %s em (%f,%f).\n",getIdSemaforo(vet[i]),getXS(vet[i]),getYS(vet[i]));
                }
                
                free(vet);
                
                
            }else if(strcmp(comando,"fh")==0){
                    fscanf(arqQRY, " %d %s %s %d", &ns, cep, face, &num );
                    void* quadra = get(quadras,FindIdQuadra(quadras,cep));
                    if(strcmp(face,"N")==0){
                            x = getXQ(quadra) + num;
                            y = getYQ(quadra) + getHQ(quadra);
                    }else if(strcmp(face,"S")==0){
                            x = getXQ(quadra) + num;
                            y = getYQ(quadra);
                    }else if(strcmp(face,"O")==0){
                            x = getXQ(quadra) + getWQ(quadra);
                            y = getYQ(quadra) + num;
                    }else if(strcmp(face,"L")==0){
                            x = getXQ(quadra);
                            y = getYQ(quadra) + num;
                    }

                    Hidrantes *vet;
                vet=malloc(getLength(hidrantes)*sizeof(Hidrantes));
                int ptr = getFirst(hidrantes);
                for(int i=0;i<getLength(hidrantes);i++){
                        vet[i]=get(hidrantes,ptr);
                        ptr=getNext(hidrantes,ptr);
                }

                if(ns<0){
                        encontrarHidrantesProximos(vet,getLength(hidrantes),-ns,x,y);
                }else{
                        encontrarHidrantesDistantes(vet,getLength(hidrantes),ns,x,y);
                }
                if(ns<0)ns=-ns;
                for(int i=0;i<ns;i++){
                        fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke-width=\"5\" stroke=\"darkblue\" stroke-opacity=\"1\" fill-opacity=\"0\" />\n", getXH(vet[i])+2.5, getYH(vet[i])+2.5);
                        fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:yellow;stroke-width:1\" />\n", x, y, getXH(vet[i])+2.5,getYH(vet[i])+2.5);
                        fprintf(arqTXT,"fh Hidrante = ID: %s em (%f,%f).\n",getIdHidrante(vet[i]),getXH(vet[i]),getYH(vet[i]));
                }
                
                free(vet);


                
                    

                    

            }else if(strcmp(comando,"fs")==0){
                    fscanf(arqQRY, " %d %s %s %d", &ns, cep, face, &num);
                    void* quadra = get(quadras,FindIdQuadra(quadras,cep));
                    if(strcmp(face,"N")==0){
                            x = getXQ(quadra) + num;
                            y = getYQ(quadra) + getHQ(quadra);
                    }else if(strcmp(face,"S")==0){
                            x = getXQ(quadra) + num;
                            y = getYQ(quadra);
                    }else if(strcmp(face,"O")==0){
                            x = getXQ(quadra) + getWQ(quadra);
                            y = getYQ(quadra) + num;
                    }else if(strcmp(face,"L")==0){
                            x = getXQ(quadra);
                            y = getYQ(quadra) + num;
                    }

                    Semaforos *vet;
                vet=malloc(getLength(semaforos)*sizeof(Semaforos));
                int ptr = getFirst(semaforos);
                for(int i=0;i<getLength(semaforos);i++){
                        vet[i]=get(semaforos,ptr);
                        ptr=getNext(semaforos,ptr);
                }

                
                encontrarSemaforosProximos(vet,getLength(semaforos),ns,x,y);
                
                if(ns<0)ns=-ns;
                for(int i=0;i<ns;i++){
                        fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke-width=\"5\" stroke=\"red\" stroke-opacity=\"1\" fill-opacity=\"0\" />\n", getXS(vet[i])+2.5, getYS(vet[i])+2.5);
                        fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:yellow;stroke-width:1\" />\n", x, y, getXS(vet[i])+2.5,getYS(vet[i])+2.5);
                        fprintf(arqTXT,"fs Semaforo = ID: %s em (%f,%f).\n",getIdSemaforo(vet[i]),getXS(vet[i]),getYS(vet[i]));
                }
                
                free(vet);
            }else if(strcmp(comando,"brl")==0){
                    fscanf(arqQRY, " %f %f", &x, &y);
                    Lista *segmentos;
                    segmentos = criarListaSegmentos(segmentos,quadras,predios,muros,x,y);
                    Vertices *vet;
                    int capacidade = 2*(4 + getLength(muros)+(4*getLength(predios)));
                    vet = malloc(capacidade * sizeof(Vertices));
                    criarVetorVertices(vet,(2*(4 + getLength(muros)+(4*getLength(predios)))),segmentos);
                    qsort(vet,capacidade,sizeof(Vertices),compararVertices);
                    Lista *segsAtivos;
                    segsAtivos = criarLista(capacidade);
                    ativarSegmentosIniciais(segmentos,segsAtivos,x,y);
                    imprimirBRL(arqSVG,segsAtivos,vet,capacidade,x,y);
                    


                //Limpando memória
                for(int i=0;i<capacidade;i++){                    
                        free(vet[i]);
                }
                free(vet);
                FreeLista(segmentos);
                FreeListaVazia(segsAtivos);
                
                  
            }else break;

        }
}


