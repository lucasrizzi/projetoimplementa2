#include <stdio.h>
#include <stdlib.h>
#include "lista_interface.h"
#include "trabalho_interface.h"

int main(){
char comando;
char argv[101];
printf("digite o nome de um arquivo para abrir com o editor\n");
scanf("%s",argv);
getchar();
int teste;
lista_t *buffer;
criaLista(&buffer);
teste=abriArquivo(argv,buffer);
if(teste<0){
    printf("\n arquivo nao encontrado ou inexistente!\n");
}
do{
consultaComando(&comando, buffer); //Mostra a linha atual, o tamanho do buffer e solicita o comando.
executaComando(comando, buffer); //Executa o comando solicitado.
}while((comando!='q')&&(comando!='Q'));
lista_destroi(&buffer);
return 0;
}

