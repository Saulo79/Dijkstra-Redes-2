#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
//Tamanho de cada dimens�o da matriz. N�o consegui encontrar uma forma de passar a matriz sem utilizar
// a fun��o define em c.
#define t 8
//Calcula o pr�ximo elemento a ser visitado no grafo;
int proximo(int grafo[t][t], int peso_antecessor[], bool pertence[], int antecessor[]){
   //vari�veis utilizadas para comparar ou guardar os dados necess�rios.
   int pos_prox=-1;
   int peso_prox = 1024;
   int ant_prox;
   for(int i=0; i<t; i++){
     //verifica cada elemento que j� pertence � �rvore de escoamento;
     if (pertence[i]==true){
       for(int j=0; j<t; j++){
         // Caso o elemento n�o perten�a � �rvore de escoamento, e se o peso para chegar na mesma for o menor,
         //guarda as informa��es do n� a ser adicionado;
         if (pertence[j]!=true && peso_antecessor[i]+grafo[i][j]<peso_prox){
          peso_prox=peso_antecessor[i]+grafo[i][j];
          pos_prox=j;
          ant_prox=i;
         }
       }
     }
   }
   //Salva as informa��es do n� nos vetores para compara��es futuras.
   antecessor[pos_prox]=ant_prox;
   pertence[pos_prox] = true;
   peso_antecessor[pos_prox]=peso_prox;
   grafo[ant_prox][pos_prox]=1024; //Evita que um n� volte.
   return pos_prox;
}
//Imprime a solu��o final do programa;
void solucao(int antecessor[t], int inicio, int fim){
   int aux = fim;
   int resultado[100];
   int tam = 0;
   //Salva o caminho utilizado em ordem inversa em um vetor;
   while (aux!=-1){
    resultado[tam]=aux;
    tam++;
    aux=antecessor[aux];
   }
   //Imprime a solu��o;
   while(tam!=0){
    tam--;
    printf("%d  ", resultado[tam]);
   }
}

//fun��o principal; inicializa os vetores necess�rios e realiza o controle de parada.
void djikstra(int grafo[t][t], int inicio, int fim){
    int antecessor[t];
    int peso_antecessor[t];
    int aux_antecessor;
    int prox;
    bool destino = false;
    bool pertence[t];
    //inicializa vari�veis com valores padr�o;
    for (int i=0; i<t; i++){
       antecessor[i] = -1;
       peso_antecessor[i]=0;
       pertence[i] = false;
    }
    //Insere o primeiro n� na �rvore de escoamento;
    aux_antecessor=inicio;
    pertence[inicio]=true;
    //enquanto n�o chegar ao destino, procura o pr�ximo n� a ser inserido na �rvore de escoamento;
    while (destino==false){
        prox= proximo(grafo, peso_antecessor, pertence, antecessor);
        if (prox==fim) destino=true;
        //Em caso de �rvores desconexas, exibe mensagem de erro e encerra o programa;
        if (prox==-1){
            printf("Erro. Grafo desconexo. Imposs�vel chegar ao destino.");
            return;
        }
    }
    solucao(antecessor, inicio, fim);
}
//L� a matriz do arquivo e insere na matriz utilizada;;
void geraGrafo(int grafo[t][t]){
   FILE *arquivo;
   char l[t];
   char *vetor=0;
   char *palavra=0;
   size_t tamanho=0;
   ssize_t possivel=0;
   int linha=0,coluna=0;
   arquivo = fopen("grafo.txt", "r");
   while(possivel = getline( &vetor, &tamanho, arquivo) >0 ){
    palavra = strtok( vetor, " ");
    while ( palavra != NULL ){
      grafo[linha][coluna]=(int)palavra;
      coluna++;
      }
    linha++;
    coluna=0;
    }
   fclose(arquivo);
}

int main(int inicio, int fim){
    int grafo[t][t];
    geraGrafo(grafo);
    djikstra(grafo, inicio, fim);
    return 0;
}
