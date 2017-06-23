#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trabalho_privado.h"
#include "getline.h"

void libera(void*dado){
    char *linha;
    linha=(char*)dado;
    free(linha);
}

void imprime (const void* dado){
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

void criaLista(lista_t**buffer){
    *buffer=lista_cria(imprime,libera,compara,salva);
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
            funcao_leitura(buffer);
            break;
        case 'w':
        case 'W':
            funcao_escritura(buffer);
            break;
        case 'i':
        case 'I':
            funcao_insere(buffer);
            break;
        case 'd':
        case 'D':
            funcao_apagalinha(buffer);
            break;
        case 'f':
        case 'F':
            funcao_encontra(buffer);
            break;
        case 'l':
        case 'L':
            funcao_tamanhos(buffer);
            break;
        case 'c':
        case 'C':
            printf("passou aqui  C");//meu deus falta muitoooo
            funcao_trocatexto(buffer);
            break;
        case 'q':
        case 'Q':
            printf("saidaaaa");
            break;
        case 'h':
        case 'H':
        case '?':
            printf("passou aqui  H");//faltaaaaaa
            //faz algo
            break;
        case 'n':
        case 'N':
            pequeno_altera_current(buffer,1);
            break;
        case 'p':
        case 'P':
            pequeno_altera_current(buffer,0);
            break;
        case 'b':
        case 'B':
            altera_current(buffer,lista_cabeca(buffer));
            break;
        case 'e':
        case 'E':
            altera_current(buffer,lista_cauda(buffer));
            break;
        case 'G':
        case 'g':
            funcao_vaipralinha(buffer);
            break;
        case 'v':
        case 'V':
            lista_imprime(buffer);
            system("pause");
            break;
        case 's':
        case 'S':
            funcao_substitui(buffer);
            break;
        default:
            printf("Comando Invalido\n");
            system("pause");
    };
}

void consultaComando(char *comando,lista_t *buffer){
    system("cls");//mudar para linux
    fflush(stdin);
    printf("Linha atual do Buffer: \n");
    if(lista_cabeca(buffer)){
      imprime_linha(buffer);
    }
    printf("Tamanho do Buffer: %d\n",lista_tamanho(buffer));
    printf("Digite um comando: ");
    scanf("%c",comando); // pegar 1 caracter. Tem que manter esse espaço antes do %c para o scanf ignorar o \n.
    fflush(stdin);
}

void funcao_leitura(lista_t *buffer){
    void *aux;
    char nome_do_local[101];
    while (!lista_vazia(buffer)){
        lista_remove(buffer,lista_cabeca(buffer),(void**)&aux);
        free(aux);
    }
    //escreva o nome do arquivo
    scanf("%s",nome_do_local);
    getchar();
    abriArquivo((const char*)nome_do_local,buffer);
}

void funcao_escritura(lista_t *buffer){
    char nome_do_local[101];
    printf("escreva o nome do arquivo para escritura . (ira sobrescrever qualquer arquivo de mesmo nome )");
    //escreva o nome do arquivo para escritura . (ira sobrescrever qualquer arquivo de mesmo nome )
    scanf("%s",nome_do_local);
    getchar();
    FILE *stream;
    stream = fopen(nome_do_local, "w");
    if (stream == NULL){
       return ;
    }
    lista_salva(buffer,stream);
    fclose(stream);
}

void funcao_apagalinha(lista_t *buffer){
    if(lista_vazia(buffer)){
        return;
    }
    char *linha;
    pequeno_altera_current(buffer,1);
    if(lista_remove(buffer,retorna_current_anterior(buffer),(void**)&linha))
        free(linha);
}

void funcao_encontra(lista_t*buffer){
    if(lista_vazia(buffer))
        return;
    char string_que_querem_achar[101];
    printf("escreva o texto que deseja encontrar:");
    //escreva a sting que deseja buscar
    scanf("%s",string_que_querem_achar);
    getchar();
    celula_t*batman_ta_felizao=retorna_current(buffer);
    while(!strstr((const char*)lista_dado(retorna_current(buffer)),(const char*)string_que_querem_achar)){
        if(!retorna_current_proximo(buffer)){
            //nao foi encontrada
            altera_current(buffer,batman_ta_felizao);
            return;
        }
        pequeno_altera_current(buffer,1);
    }
    printf("encontrado \n");
}

void funcao_tamanhos(lista_t *buffer){
    if (lista_vazia(buffer)){
        return;
    }
    int numletras;
    numletras=strlen(lista_dado(retorna_current(buffer)));
    //escreve numero de letras
    printf(" \n%i numero de letras\n",numletras-1);
    numletras=lista_tamanho(buffer);
    //escreve numero linhas
    printf(" \n%i numero de linhas\n",numletras);
}

void funcao_vaipralinha(lista_t *buffer){
    if(lista_vazia(buffer))
        return;
    int agr_o_batman_vai_participar;
    //escreva a linha desejada
    scanf("%i",&agr_o_batman_vai_participar);
    getchar();
    if(agr_o_batman_vai_participar>lista_tamanho(buffer)||agr_o_batman_vai_participar<=0)
        return;
    current_linha_especifica(buffer,agr_o_batman_vai_participar);
}

void funcao_insere(lista_t *buffer){
    int agr_o_batman_vai_participar;
    //escreva a linha desejada
    printf("escreva a linha desejada:");
    scanf("%i",&agr_o_batman_vai_participar);
    getchar();
    unsigned int i=0;
    char *texto,c;
    printf("\ntexto a ser inserido:");
    c=getchar();
    texto=NULL;
    while(c!='\n'){
        i++;
        texto=(char*)realloc(texto,sizeof(char)+i+2);
        texto[i-1]=c;
        c=getchar();
    }
    texto[i]='\n';
    texto[i+1]='\0';
    lista_insere_posicao(buffer,agr_o_batman_vai_participar,(void*)texto);
    current_linha_especifica(buffer,agr_o_batman_vai_participar);
}

void funcao_substitui(lista_t*buffer){
    int agr_o_batman_vai_participar;
    //escreva a linha desejada
    printf("escreva a linha desejada:");
    scanf("%i",&agr_o_batman_vai_participar);
    getchar();
    current_linha_especifica(buffer,agr_o_batman_vai_participar);
    imprime_linha(buffer);
    printf("\ndeseja mesmo substituir esta linha? S/N\n");
    char aux;
    aux=getchar();
    getchar();
    if(aux=='s'||aux=='S'){
        fflush(stdin);
        unsigned int i=0;
    char *texto,c;
    printf("\ntexto a ser inserido:");
    c=getchar();
    texto=NULL;
    while(c!='\n'){
        i++;
        texto=(char*)realloc(texto,sizeof(char)+i+2);
        texto[i-1]=c;
        c=getchar();
    }
    texto[i]='\n';
    texto[i+1]='\0';
    lista_insere_posicao(buffer,agr_o_batman_vai_participar,(void*)texto);
    current_linha_especifica(buffer,agr_o_batman_vai_participar);
    if(!lista_proximo(retorna_current(buffer)))
        return;
    pequeno_altera_current(buffer,1);
    funcao_apagalinha(buffer);
    pequeno_altera_current(buffer,0);
    }
}

void funcao_trocatexto(lista_t*buffer){
    if(lista_vazia(buffer))
            return;
    int i;
    printf("\nqual texto deseja substituir nesta linha?:");
    fflush(stdin);
    char *texto,c,*text2,*text3;
    c=getchar();
    texto=NULL;
    i=0;
    while(c!='\n'){
        i++;
        texto=(char*)realloc(texto,sizeof(char)+i+1);
        texto[i-1]=c;
        c=getchar();
    }
    texto[i]='\0';
    i=0;
    text3=strstr((const char*)lista_dado(retorna_current(buffer)),(const char*)texto);
    if(text3){
        printf("\nqual texto deseja colocar em seu local?:");
        text2=NULL;
        fflush(stdin);
        c=getchar();
        text2=NULL;
        while(c!='\n'){
            i++;
            text2=(char*)realloc(text2,sizeof(char)+i+1);
            text2[i-1]=c;
            c=getchar();
        }
        text2[i]='\0';
        int text4;
        text4=text3-(char*)lista_dado(retorna_current(buffer));
        text3=&text3[strlen(texto)];
        free(texto);
        texto=(char*)malloc(strlen(text2)+strlen((char*)lista_dado(retorna_current(buffer))));
        strncpy(texto,(const char*)lista_dado(retorna_current(buffer)),text4);
        texto[text4]='\0';
        strcat(texto,text2);
        strcat(texto,text3);
        lista_insere_proximo(buffer,retorna_current(buffer),texto);
        funcao_apagalinha(buffer);
        return;
    }
    free(texto);
    printf("texto nao encontrado nesta linha!!");
}
