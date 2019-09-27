#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"geometria.h"



typedef struct{
    float x, y, w, h;
    float r;
    char tipo[3], id[10], corBorda[30], corInterna[30], tamanhoBorda[10];
}Formas;





Formas* criarFormas(char idIn[10], char tipoIn[5], float xIn, float yIn, float wIn, float hIn, float rIn, char corBordaIn[30], char corInternaIn[30], char tamanhoBordaIn[10]){
    Formas *forma;
    forma = (Formas*) malloc(sizeof(Formas));
    sprintf(forma->corBorda, "%s", corBordaIn);
    sprintf(forma->corInterna, "%s", corInternaIn);
    sprintf(forma->tamanhoBorda, "%s", tamanhoBordaIn);
    sprintf(forma->id, "%s", idIn);
    sprintf(forma->tipo, "%s", tipoIn);
    forma->r = rIn;
    forma->x = xIn;
    forma->y = yIn;
    forma->w = wIn;
    forma->h = hIn;

    return forma;
}


bool checarPontoInternoFormas(Formas *forma, float x, float y){
    if(strcmp(forma->tipo,"c")==0){
        if(distancia(forma->x-x, forma->y-y) > forma->r) return false;
        else return true;
    }else{
        if(x >= forma->x && x <= forma->x+forma->w && y >= forma->y && y <= forma->y+forma->h) return true;
        else return false;
    }
}




bool checarInterseccaoFormas(Formas *forma1, Formas *forma2){
    if(strcmp(forma1->tipo, forma2->tipo)==0){
        if(strcmp(forma1->tipo,"c")==0){ //dois circulos
            if( (forma1->r + forma2->r) < (distancia(forma1->x - forma2->x , forma1->y - forma2->y) )){
                return false;
            }else {return true;}
        } else{ // dois retangulos (ver. pontos de 1 dentro de 2)
            if( (forma1->x >= forma2->x && forma1->x <= forma2->x+forma2->w && forma1->y>=forma2->y && forma1->y <=forma2->y+forma2->h) ||
                (forma1->x+forma1->w >= forma2->x && forma1->x+forma1->w <= forma2->x+forma2->w && forma1->y>=forma2->y && forma1->y <=forma2->y+forma2->h) ||
                (forma1->x >= forma2->x && forma1->x <= forma2->x+forma2->w && forma1->y+forma1->h>=forma2->y && forma1->y+forma1->h <=forma2->y+forma2->h) ||
                (forma1->x+forma1->w >= forma2->x && forma1->x+forma1->w <= forma2->x+forma2->w && forma1->y+forma1->h>=forma2->y && forma1->y+forma1->h <=forma2->y+forma2->h)
            ) {return true;}
            else {return false;}
        }
    }else{//retangulo e circulo
        Formas *ret, *cir;
        if(strcmp(forma1->tipo,"c")==0){
            cir=forma1; 
            ret=forma2;
        }else{
            ret=forma1; 
            cir=forma2;
        }
        if(
            checarPontoInternoFormas(ret,cir->x, cir->y) ||
            checarPontoInternoFormas(ret,cir->x+cir->r, cir->y) ||     
            checarPontoInternoFormas(ret,cir->x, cir->y+cir->r) ||
            checarPontoInternoFormas(ret,cir->x-cir->r, cir->y) ||
            checarPontoInternoFormas(ret,cir->x, cir->y-cir->r) ||
            cir->r >= distancia(cir->x - ret->x, cir->y - ret->y) ||
            cir->r >= distancia(cir->x - ret->x+ret->w, cir->y - ret->y) ||  
            cir->r >= distancia(cir->x - ret->x, cir->y - ret->y+ret->h) ||
            cir->r >= distancia(cir->x - ret->x+ret->w, cir->y - ret->y+ret->h)
        ) {return true;}
        else {return false;}
    }
}







float checarDistanciaFormas(Formas *forma1, Formas *forma2){
    if(strcmp(forma1->tipo, forma2->tipo)==0){
        if(strcmp(forma1->tipo,"c")==0){ //dois circulos
            return (distancia(forma1->x-forma2->x,forma1->y-forma2->y));
        } else{ // dois retangulos (ver. pontos de 1 dentro de 2)
            return (distancia(forma1->x+forma1->w/2 - forma2->x+forma2->w/2,
                    forma1->y+forma1->h/2 - forma2->y+forma2->h/2));
        }
    } else {//retangulo e circulo
        Formas *ret, *cir;
        if(strcmp(forma1->tipo,"c")==0){
            cir=forma1; ret=forma2;
        }else{
            ret=forma1; cir=forma2;
        }
        return (distancia(ret->x+ret->w/2 - cir->x, ret->y+ret->h/2 - cir->y));
    }
}

char* getIdFormas(Formas *forma){
    return forma->id;
}


void imprimirForma(Formas *forma, FILE *arqSVG){

    if(strcmp(forma->tipo,"r")==0){
        fprintf(arqSVG,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke-width:%s;stroke:%s\" />\n",
        forma->x, forma->y, forma->w, forma->h, forma->corInterna, forma->tamanhoBorda,forma->corBorda);
    }else{
        fprintf(arqSVG,"\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n",
        forma->x,forma->y,forma->r,forma->corBorda,forma->tamanhoBorda,forma->corInterna);
    }

}

void atribuirCentroMassa(Formas *forma, float *x, float *y){
    if(strcmp(forma->tipo,"c")==0){
        *x = forma->x; *y = forma->y;
    }else {
        *x = forma->x+forma->w/2; *y = forma->y+forma->h/2;
    }
}


void obterCoordenadasBoundingBox(Formas *forma1, Formas *forma2, float *x1, float *x2, float *y1, float *y2){
    if(strcmp(forma1->tipo,forma2->tipo)==0){
        if(strcmp(forma1->tipo,"c")==0){//dois círculos
            if(forma1->x-forma1->r < forma2->x-forma2->r){
                *x1 = forma1->x-forma1->r;
            }else *x1 = forma2->x-forma2->r;
            if(forma1->x+forma1->r > forma2->x+forma2->r){
                *x2 = forma1->x+forma1->r;
            }else *x2 = forma2->x+forma2->r;
            if(forma1->y-forma1->r < forma2->y-forma2->r){
                *y1 = forma1->y-forma1->r;
            }else *y1 = forma2->y-forma2->r;
            if(forma1->y+forma1->r > forma2->y+forma2->r){
                *y2 = forma1->y+forma1->r;
            }else *y2 = forma2->y+forma2->r;
            
        }else{//dois retângulos
            if(forma1->x < forma2->x){
                *x1 = forma1->x;
            }else *x1 = forma2->x;
            if(forma1->x+forma1->w > forma2->x+forma2->w){
                *x2 = forma1->x+forma1->w;
            }else *x2 = forma2->x+forma2->w;
            if(forma1->y < forma2->y){
                *y1 = forma1->y;
            }else *y1 = forma2->y;
            if(forma1->y+forma1->h > forma2->y+forma2->h){
                *y2 = forma1->y+forma1->h;
            }else *y2 = forma2->y+forma2->h;
        }
    }else{ //tipos diferentes
        Formas *ret, *cir;
        if(strcmp(forma1->tipo,"c")==0){
            cir = forma1;
            ret = forma2;
        }else{
            ret = forma1;
            cir = forma1;
        }
        if(ret->x < cir->x-cir->r){
            *x1 = ret->x;
        }else *x1 = cir->x-cir->r;
        if(ret->x+ret->w > cir->x+cir->r){
            *x2 = ret->x+ret->w;
        }else *x2 = cir->x + cir->r;
        if(ret->y < cir->y-cir->r){
            *y1 = ret->y;
        }else *y1 = cir->y-cir->r;
        if(ret->y+ret->h > cir->y+cir->r){
            *y2 = ret->y+ret->h;
        }else *y2 = cir->y+cir->r;

    }
}