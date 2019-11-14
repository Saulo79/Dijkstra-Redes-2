#include <limits.h>
#include <stdio.h>
#include <string.h>
#define t 9

void geraGrafo(){
    FILE *arquivo;
    char l[t];
    char *linha=0;
    char *palavra=0;
    size_t tamanho=0;
    ssize_t possivel=0;
    arquivo = fopen("arquivo.txt", "r");
    while( possivel = getline( &linha, &tamanho, arquivo) >0 ){
//      fread(l, 1024, 1, arquivo);
//      fread(l, 1024, 1, arquivo);
        printf("LINHA: %s\n",linha);
        palavra = strtok( linha, " ");
        //while ( palavra = strtok( linha, " ") ){
        //for ( int k=0; k<=8;k++){
        while ( palavra != NULL ){
            printf("PALAVRA: %s\t",palavra);
            palavra = strtok( NULL, " ");
        }
        printf("\n");
    }
    fclose(arquivo);
}


int main(){
    geraGrafo(grafo);
    return 0;
}
