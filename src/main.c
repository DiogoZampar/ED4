#include<stdlib.h>
#include<stdio.h>
#include"geometria.h"
#include"quadras.h"
#include"lista.h"
#include"formas.h"
#include"arqGEO.h"
#include"arqQRY.h"
#include<string.h>
//teste
#include"segmentos.h"


char* obterNomeArquivo(char* str){
    char *temp;
    temp = (char*)malloc(200*sizeof(char));
    int ultima_barra=0, ponto=0;
    int j=0;
    for(int i=0;i<strlen(str);i++){
        if(str[i]=='.' && i>1){
            ponto = i;
            break;
        }else if(str[i]=='/'){
            ultima_barra=i;
        }
    }
    for(int i=ultima_barra;i<ponto;i++){
        if(str[i]=='.' || str[i]=='/'){

        }else{
            temp[j] = str[i];
            j++;
        }
    }
    temp[j] = '\0';
    
    sprintf(str, "%s", temp);
    free(temp);
    return str;
}








int main(int argc, char **argv){

    //parâmetros da main
    char *par_e=NULL, *par_f=NULL, *par_q=NULL, *par_o=NULL;
    char nome_geo[200], nome_qry[200], nome_svg[200], nome_svg2[200], nome_txt[200], nome_txt2[200];
    char nome_arq_geo[200], nome_arq_qry[200];
    int primLetra=0,ultLetra=0, cont=0;
    
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-e")==0){
            //par_e = (char*)malloc(strlen(argv[i+1]+1)*sizeof(char));
            par_e = argv[i+1];
        }
        if(strcmp(argv[i],"-f")==0){
            //par_f = (char*)malloc(strlen(argv[i+1]+1)*sizeof(char));
            par_f = argv[i+1];      
        }
        if(strcmp(argv[i],"-q")==0){
            //par_q = (char*)malloc(strlen(argv[i+1]+1)*sizeof(char));
            par_q = argv[i+1];
        }
        if(strcmp(argv[i],"-o")==0){
            //par_o = (char*)malloc(strlen(argv[i+1]+1)*sizeof(char));
            par_o = argv[i+1];
        }
    }

    //nomes de arquivos
    sprintf(nome_arq_geo, "%s", obterNomeArquivo(par_f));
    if(par_q!=NULL)sprintf(nome_arq_qry, "%s", obterNomeArquivo(par_q));

    sprintf(nome_svg,"%s/%s.svg", par_o,nome_arq_geo);
    sprintf(nome_txt,"%s/%s.txt", par_o,nome_arq_geo);
    

    if(par_e!=NULL){
        sprintf(nome_geo,"%s/%s.geo", par_e, par_f);
        if(par_q!=NULL){
            sprintf(nome_qry,"%s/%s.qry",par_e,par_q);
            sprintf(nome_svg2,"%s/%s-%s.svg",par_o,nome_arq_geo,nome_arq_qry);
            sprintf(nome_txt2,"%s/%s-%s.txt",par_o,nome_arq_geo,nome_arq_qry);
        }
    }else{
        sprintf(nome_geo,"%s.geo",par_f);

        if(par_q!=NULL){
            sprintf(nome_qry,"%s.qry",par_q);
            sprintf(nome_svg2,"%s/%s-%s.svg",par_o,nome_arq_geo,nome_arq_qry);
            sprintf(nome_txt2,"%s/%s-%s.txt",par_o,nome_arq_geo,nome_arq_qry);
        }
    }

    

    //arquivos
    FILE *arqGEO = NULL;
    FILE *arqSVG = NULL;
    FILE *arqSVG2 = NULL;
    FILE *arqTXT = NULL;
    FILE *arqTXT2 = NULL;
    FILE *arqQRY = NULL;
    
    arqGEO = fopen(nome_geo,"r");
    arqSVG = fopen(nome_svg, "w+");
    arqTXT = fopen(nome_txt,"w+");
    if(par_q!=NULL){
        arqSVG2 = fopen(nome_svg2,"w+");
        arqTXT2 = fopen(nome_txt2,"w+"); 
        arqQRY = fopen(nome_qry,"r");
    }


    //listas
    int i=1000,nq=1000,nh=1000,ns=1000,nr=1000,np=1000,nm=1000;
    verificarTamanhoListas(arqGEO,&i,&nq,&nh,&ns,&nr,&np,&nm);

    Lista *formas = NULL;
    Lista *quadras = NULL;
    Lista *hidrantes = NULL;
    Lista *semaforos = NULL;
    Lista *torres = NULL;
    Lista *predios = NULL;
    Lista *muros = NULL;

    formas = criarLista(i);
    quadras = criarLista(nq);
    hidrantes = criarLista(nh);
    semaforos = criarLista(ns);
    torres = criarLista(nr);
    predios = criarLista(np);
    muros = criarLista(nm);
    

    //chamadas de funções principais

    LeituraGeo(arqGEO, arqSVG, arqTXT, formas, quadras, hidrantes, semaforos, torres, predios, muros);
    
    ImprimirSVG(arqSVG, formas,quadras,hidrantes,semaforos,torres, predios, muros);
    

    if(par_q!=NULL){
        processarQRY(arqSVG2,arqQRY,arqTXT2,formas,quadras,hidrantes,semaforos,torres, predios, muros);
    
        ImprimirSVG(arqSVG2,formas,quadras,hidrantes,semaforos,torres, predios, muros);
    }
    

    
    //limpar memória
    fclose(arqGEO);
    fclose(arqSVG);
    fclose(arqTXT);
    if(par_q!=NULL){
        fclose(arqTXT2);
        fclose(arqQRY);
        fclose(arqSVG2);
    }
    FreeLista(formas);
    FreeLista(quadras);
    FreeLista(hidrantes);
    FreeLista(semaforos);
    FreeLista(torres);
    FreeLista(predios);
    FreeLista(muros);
    
    
    return 0;
}







