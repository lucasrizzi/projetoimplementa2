#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trabalho_privado.h"

void libera(void*dado){
    char *linha;
    linha=(char*)dado;
    free(linha);
}

void imprime (void* dado){
    char *linha;
    linha=(char*)dado;
    puts(linha);
}

int compara(const void*a,const void *b){
    if(strstr((char*)a,(char*)b)){
        return 0;
    }
    return 1;
}

void salva (const void * dado,FILE *arquivo){
    char *linha;
    linha=(char*)dado;
    fputs(linha,arquivo);
}

void criaLista(lista_t*buffer){
    buffer=lista_cria(imprime,libera,compara,salva);
}

int abriArquivo(const char* arquivo,lista_t*buffer){
    FILE *stream;
    stream = fopen(arquivo, "r");
    if (stream == NULL){
       return -1;
    }
    char *line=NULL;
    unsigned int len;
    while(getline(&line, &len, stream)!=-1){
        lista_insere_proximo(buffer,lista_cauda(buffer),(const void*)line);
        line=NULL;
    }
    altera_current(buffer,lista_cabeca(buffer));
    fclose(stream);
    return 1;
}

void executaComando(char comando, lista_t *buffer){
    switch (comando){
        case 'r':
        case 'R':
            printf("passou aqui  R");
            funcao_leitura(buffer);
            break;
        case 'w':
        case 'W':
            printf("passou aqui  W");
            funcao_escritura(buffer);
            break;
        case 'i':
        case 'I':
            printf("passou aqui  I");// aqui falta fazeeeer
            //faz algo
            break;
        case 'd':
        case 'D':
            printf("passou aqui  D");
            funcao_apagalinha(buffer);
            break;
        case 'f':
        case 'F':
            printf("passou aqui  F");
            funcao_encontra(buffer);
            break;
        case 'l':
        case 'L':
            printf("passou aqui  L");
            funcao_tamanhos(buffer);
            break;
        case 'c':
        case 'C':
            printf("passou aqui  C");
            //faz algo
            break;
        case 'q':
        case 'Q':
            printf("saidaaaa");
            break;
        case 'h':
        case 'H':
        case '?':
            printf("passou aqui  H");
            //faz algo
            break;
        case 'n':
        case 'N':
            printf("passou aqui  N");
            //faz algo
            break;
        case 'p':
        case 'P':
            printf("passou aqui  P");
            //faz algo
            break;
        case 'b':
        case 'B':
            printf("passou aqui  B");
            //faz algo
            break;
        case 'e':
        case 'E':
            printf("passou aqui  E");
            //faz algo
            break;
        case 'G':
        case 'g':
            printf("passou aqui  G");
            //faz algo
            break;
        case 'v':
        case 'V':
            printf("passou aqui  V");
            //faz algo
            break;
        case 's':
        case 'S':
            printf("passou aqui  S");
            //faz algo
            break;
        default:
            printf("Comando Invalido\n");
    };
}

void consultaComando(char *comando,lista_t *buffer){
    printf("Linha atual do Buffer: \n");
    if(lista_cabeca(buffer)){
      imprime_linha(buffer);
    }
    printf("Tamanho do Buffer: %d\n",lista_tamanho(buffer));
    printf("Digite um comando: ");
    scanf(" %c",comando); // pegar 1 caracter. Tem que manter esse espaço antes do %c para o scanf ignorar o \n.
}

void funcao_leitura(lista_t *buffer){
    char *aux;
    char nome_do_local[101];
    while (!lista_vazia(buffer)){
        lista_remove(buffer,NULL,(void**)&aux);
        free(aux);
    }
    //escreva o nome do arquivo
    scanf("%s\n",nome_do_local);
    abriArquivo((const char*)nome_do_local,buffer);
}

void funcao_escritura(lista_t *buffer){
    char nome_do_local[101];
    char *aux;
    int tam=lista_tamanho(buffer);
    //escreva o nome do arquivo para escritura . (ira sobrescrever qualquer arquivo de mesmo nome )
    scanf("%s\n",nome_do_local);
    FILE *stream;
    stream = fopen(arquivo, "w");
    if (stream == NULL){
       return -1;
    }
    lista_salva(buffer,stream);
    fclose(stream);
}

void funcao_apagalinha(liata_t *buffer){
    if(lista_vazia(buffer)){
        return;
    }
    char *linha;
    pequeno_altera_current(buffer,1);
    if(lista_remove(buffer,retorna_current_anterior(buffer),&linha))
        free(linha);
}

void funcao_encontra(lista_t*buffer){
    if(lista_vazia(buffer))
        return;
    char string_que_querem_achar[101];
    //escreva a sting que deseja buscar
    scanf("%s\n",string_que_querem_achar);
    int i;
    celula_t*batman_ta_felizao=retorna_current(buffer);
    while(!strstr((const char*)string_que_querem_achar,(const char*)lista_dado(retorna_current(buffer)))){
        if(!retorna_current_proximo(buffer)){
            //nao foi encontrada
            altera_current(buffer,batman_ta_felizao);
            return;
        }
        pequeno_altera_current(buffer,1);
    }
}

void funcao_tamanhos(lista_t *buffer){
    if (lista_vazia(buffer)){
        return;
    }
    int numletras;
    numletras=strlen(lista_dado(retorna_current(buffer)));

}
