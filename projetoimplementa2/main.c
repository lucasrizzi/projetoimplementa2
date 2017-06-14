#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
char comando;
List buffer;
criaLista(&buffer);
abriArquivo(argc,argv,&buffer);
do{
consultaComando(&comando, &buffer); //Mostra a linha atual, o
tamanho do buffer e solicita o comando.
executaComando(comando, &buffer); //Executa o comando
solicitado.
}while(command != ’q’);

return 0;
}
