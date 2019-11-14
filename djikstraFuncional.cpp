#include <limits.h>
#include <stdio.h>
#include <string.h>
#define t 9
int proximo(int grafo[t][t], int peso_antecessor[], bool pertence[], int antecessor[]){
   int pos_prox=-1;
   int peso_prox = 1024;
   int ant_prox;
   for(int i=0; i<t; i++){
     if (pertence[i]==true){
       for(int j=0; j<t; j++){
       if (pertence[j]!=true && peso_antecessor[i]+grafo[i][j]<peso_prox){
          peso_prox=peso_antecessor[i]+grafo[i][j];
          pos_prox=j;
          ant_prox=i;
        }
       }
     }
   }
   antecessor[pos_prox]=ant_prox;
   pertence[pos_prox] = true;
   peso_antecessor[pos_prox]=peso_prox;
   grafo[ant_prox][pos_prox]=1024;
   return pos_prox;
}
void solucao(int antecessor[t], int inicio, int fim){
   int aux = fim;
   int resultado[100];
   int tam = 0;
   while (aux!=-1){
    resultado[tam]=aux;
    tam++;
    aux=antecessor[aux];
   }
   while(tam!=0){
    tam--;
    printf("%d  ", resultado[tam]);
   }
}
void djikstra(int grafo[t][t], int inicio, int fim){
    int antecessor[t];
    int peso_antecessor[t];
    int aux_antecessor;
    bool destino = false;
    bool pertence[t];
    for (int i=0; i<t; i++){
       antecessor[i] = -1;
       peso_antecessor[i]=0;
       pertence[i] = false;
    }
    aux_antecessor=inicio;
    pertence[inicio]=true;
    while (destino==false){
        int m = proximo(grafo, peso_antecessor, pertence, antecessor);
        if (m==fim) destino=true;
    }
    solucao(antecessor, inicio, fim);
}
int main(){
    int grafo[t][t] = { { 1024, 4, 1024, 1024, 1024, 1024, 1024, 8, 1024 },
                        { 4, 1024, 8, 1024, 1024, 1024, 1024, 11, 1024 },
                        { 1024, 8, 1024, 7, 1024, 4, 1024, 1024, 2 },
                        { 1024, 1024, 7, 1024, 9, 14, 1024, 1024, 1024 },
                        { 1024, 1024, 1024, 9, 1024, 10, 1024, 1024, 1024 },
                        { 1024, 1024, 4, 14, 10, 1024, 2, 1024, 1024 },
                        { 1024, 1024, 1024, 1024, 1024, 2, 1024, 1, 6 },
                        { 8, 11, 1024, 1024, 1024, 1024, 1, 1024, 7 },
                        { 1024, 1024, 2, 1024, 1024, 1024, 6, 7, 1024 } };
    djikstra(grafo, 0, 3);
    return 0;
}
