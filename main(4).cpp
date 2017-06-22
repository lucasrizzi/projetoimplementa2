//
//  main.cpp
//
//
//  Created by Paulo Fernando Ferreira Silva Filho on 22/05/17.
//  Copyright © 2017 Paulo Fernando Ferreira Silva Filho. All rights reserved.
//


#include <iostream>
#include "math.h"
#include <stdio.h>

typedef struct lista List;
typedef struct elemento elem;

struct lista{
     elem * inicio;
     elem *linhaAtual;
     elem * fim;
};

struct elemento {
    
    char * linha;
    elem * next;
};

//Função apenas de teste.
void printBuffer(lista * buffer){
    
    elem * atual;
    atual=buffer->inicio;
    
    while(atual!=NULL){
        printf("%s", atual->linha);
        atual=atual->next;
    }
}

/*
R -> lê um arquivo de texto e armazena no buffer. Aparece na primeira linha
W -> Escreve o buffer no arquivo, dado o nome que o usuário der.
I -> insere uma linha de texto escrita pelo usuário na linha em que o usuário pedir.
D -> apaga linha corrente e vai para a de baixo.
F -> encontra a linha em que, a partir da linha corrente contém a string digitada.
L -> mostra a quantidade de caracteres na linha corrente e a quantidade de linhas no buffer
C ->
q -> Sai do programa
H ou ? -> Imprime os comandos e o que eles fazem
N -> Avança uma linha no buffer.
P -> Volta uma linha no buffer.
B -> Vai para a primeira linha do Buffer
E -> Vai para a ultima linha do buffer.
G -> Vai para a linha especificada pelo usuário
V -> Ver o conteúdo do Buffer (é a função de imprimir o buffer já implementada
S -> Substituir
*/

void zerarBuffer(List * buffer)
{
    //dar free em tudo que está no buffer e ter todos os ponteiros dele apontando para NULL.
}

void abrirArquivo(const char* endereco, List * buffer)
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    elem * elemento=NULL;
    
    zerarBuffer(buffer);
    
    //Abrindo arquivo de texto
    stream = fopen(endereco, "r");
    if (stream == NULL){
        printf("\nArquivo Inexistente!");
        return;
    }//Aqui é o teste se o endereço escrito não é válido.
  //Criando o Buffer de Leitura das linhas
    while ((read = getline(&line, &len, stream)) != -1) {
        elemento = (elem*)malloc(sizeof(elem));
        elemento->linha=line;
        elemento->next=NULL; //Essa linha foi colocada para tratar casos em que possa ter lixo sendo apontado por next, na criação dele, o que poderia fazer o programa ter comportamentos malucos. Quando for tratar o próximo elemento, o elemento anterior na lista terá o seu ponteiro de next efetivamete tratado.
        if(buffer->inicio==NULL){
            buffer->inicio=buffer->fim=elemento;
        }else{
            buffer->fim->next=elemento;
            buffer->fim=elemento;
        }
        line = NULL;
        elemento=NULL;
    }
    buffer->linhaAtual=buffer->inicio;
    free(line);
    free(elemento);
    fclose(stream);
    
   // printBuffer(buffer);
    
}
//conta quantas linhas tem o buffer (Essa função já deve ter sido implementada na TDA lista encadeada
int quantidadeLinhasBuffer(List * buffer){
    
    int total =0;
    elem * teste = buffer->inicio;

    while(teste!=NULL){
        total++;
        teste=teste->next;
    }
    
    return total;
}

void acharAnterior(List * buffer){
    
    elem *teste=buffer->inicio;
    
    if(teste==buffer->linhaAtual){
        printf("Error: Primeira Linha");
        return;
    }else{
        while(teste->next!=buffer->linhaAtual){
            teste=teste->next;
        }
        buffer->linhaAtual=teste;
    }
}

void lerArquivo(List * buffer){
    
    char * endereco;
    //Pedir endereço e nome do arquivo a ser lido.
    //receber em uma string ( tipo char*)
    abrirArquivo(endereco, buffer);
}

void gravarArquivo(List * buffer){
    
    FILE * output;
    elem * atual;
    
    //Pedir endereço onde gravar e nome do arquivo (pode também pensar que eles vão gravar sempre na mesma pasta orignial, talvez);
    //cria o arquivo output=fopen(nomearquivo,"w");
    
    atual=buffer->inicio;
    while(atual!=NULL){
      //usar o fprintf direto em um loop
        fprintf(output, "%s", atual->linha);
        atual=atual->next;
    }
    fclose(output);
}

void deletarLinhaAtual(List * buffer){
    //Essa função é basicamente a eliminação de um elemento de lista.
    elem * aSerDeletada;
    aSerDeletada=buffer->linhaAtual;
    acharAnterior(buffer);
    buffer->linhaAtual=aSerDeletada->next;
    free(aSerDeletada);
    
}

void imprimeHelp(){
    
    //Faz um grande printf com os dados de comandos apenas.
    
}

void consultaComando(char * comando, List * buffer){
    
   // char c;
    printf("Linha atual do Buffer: \n");
   if(buffer->inicio!=NULL){
      printf("%s", buffer->linhaAtual->linha);
    }
    printf("Tamanho do Buffer: %d\n", quantidadeLinhasBuffer(buffer));
    printf("Digite um comando: ");
    scanf(" %c",comando); // pegar 1 caracter. Tem que manter esse espaço antes do %c para o scanf ignorar o \n.
    printf("passou aqui");
}

void findString(List *buffer){
    //Essa é uma dos principais desafios de programação deste trabalho
    //Pega a string a ser buscada com scanf ou gets (lembrar de não guardar o \n dela)
    //fazer um loop duplo: um para as linhas do buffer e se não achar na linha específica, pular para a próxima linha, até encontrar, ou chegar na linha final
    //o segundo loop (interno) será A partir da linha atual, fazer busca em loop com strcmp e andando de 1 em 1 char no vetor.
    //Estou pensando em outra alternativa, porque essa é muito custosa e ruim, para ser sincero, mas funciona...
}

size_t quantidadeCaracteres(char * linha){
    
    return strlen(linha)-1;
}

void mostrarQuantidade(List * buffer){
    
    printf("\nQuantidade de Caracteres da linha atual: %zu", quantidadeCaracteres(buffer->linhaAtual->linha));
    printf("\nQuantidade de Linhas no Buffer: %d", quantidadeLinhasBuffer(buffer));
    
}

void vaiParaLinha(List *buffer){
    
    int linhaDestino=0;
    int i=1;
    elem * teste;
    //Pede, recebe e coloca na linhaDestino o valor do int que é a linha para onde ele quer ir.
    
    if((linhaDestino>quantidadeLinhasBuffer(buffer))||(linhaDestino<0)){ //teste para saber se o usuário não digitou uma linha fora do tamanho do buffer, ou um valor de linha inválido.
        printf("\nErro: Linha Inexistente");
    }
    teste=buffer->inicio;
    while(i<linhaDestino){
        teste=teste->next;
        i++;
    }
    buffer->linhaAtual=teste;
}

void subustituirString(List * buffer){
    //captura uma string digitada pelo usuário
    
    //pede a linha que ele quer substituir.(chama logo a função vaiParaLinha(buffer); porque ela pede a linha para se ir
    
    elem * teste; //pointer só pra facilitar
    elem * linhaNovaInserida=(elem *)malloc(sizeof(elem)); //onde vamos por a nova linha
    //coloca a string no linha dela e
    teste=buffer->linhaAtual; //teste vai pegar a linha que vai ser deletada
    acharAnterior(buffer); //o ponteiro do buffer vai para a linha anterior a atual (a atual está em teste agora)
    buffer->linhaAtual->next=linhaNovaInserida; //modifica para por a nova linha na lista
    linhaNovaInserida->next=teste->next; //finaliza por esta nova linha na lista e deixa a linha a ser deletada livre
    free(teste); //deleta efetivamente a linha antiga.
}

void trocaString(List * buffer){
    //Eu não entendi direito a explicação do que ele quer com essa função, maaaas pelo que entendi, seria:
    //Pelo que estou pensando, talvez seja a função mais difícil de implementar
    //Recebe a string a ser substituida;
    //Busca esta string na linha (pelo que ele escreveu, só precisa buscar na linha corrente (o que é uma quaaase facilidade, ou não)
    //recebe a string que vai substituir a anterior
    /*separa a linha em 3 strings:
     1)string anterior ao que tem que ser substituido
     2)string do que foi buscado
     3)string após o que foi buscado
     depois faz o strcat entre a string 1, a string que vai substituir e a string3.
     */
    //pensando nisso, essa função troca todas as ocorrências da string, ou apenas a primeira?
}

void inserirLinha(List * buffer){
    
    int posicao;
    //recebe a posicao a onde a linha será inserida. Será que se for um valor maior do que o tamanho do buffer, as linhas vazias terão que ser criadas só com '\n'?
    //leva a posição do linhaAtual do buffer para a posição indicada -> talvez usar a função vaiParaLinha(List *buffer).
    // recebe a string a partir de um "l: "
    elem * teste;
    elem * novaLinha = (elem *)(malloc(sizeof(elem)));
    //nova linha recebe a string em line.
    teste=buffer->linhaAtual;
    acharAnterior(buffer);
    buffer->linhaAtual->next=novaLinha;
    novaLinha->next=teste;
}

void executaComando(char comando, List * buffer){
    
    switch (comando){
        
        case 'r':
        case 'R':
            printf("\npassou aqui");
            lerArquivo(buffer);
            break;
        case 'w':
        case 'W':
            printf("\npassou aqui");
            gravarArquivo(buffer);
            break;
        case 'i':
        case 'I':
            printf("\npassou aqui");
            inserirLinha(buffer);
            break;
        case 'd':
        case 'D':
            printf("\npassou aqui");
            deletarLinhaAtual(buffer);
            break;
        case 'f':
        case 'F':
            printf("\npassou aqui");
            findString(buffer);
            break;
        case 'l':
        case 'L':
            printf("\npassou aqui");
            mostrarQuantidade(buffer);
            break;
        case 'c':
        case 'C':
            printf("\npassou aqui");
            trocaString(buffer);
            break;
        case 'q':
        case 'Q':
            //Faz nada aqui!!!! Só Precisa SAIR
            break;
        case 'h':
        case 'H':
        case '?':
            printf("\npassou aqui");
            imprimeHelp();
            break;
        case 'n':
        case 'N':
            buffer->linhaAtual=buffer->linhaAtual->next;
            break;
        case 'p':
        case 'P':
            acharAnterior(buffer);
            break;
        case 'b':
        case 'B':
            printf("\npassou aqui");
            buffer->linhaAtual=buffer->inicio;
            break;
        case 'e':
        case 'E':
            printf("\npassou aqui");
            buffer->linhaAtual=buffer->fim;
            break;
        case 'G':
        case 'g':
            printf("\npassou aqui");
            vaiParaLinha(buffer);
            break;
        case 'v':
        case 'V':
            printBuffer(buffer);
            break;
        case 's':
        case 'S':
            printf("\npassou aqui");
            subustituirString(buffer);
            break;
        default:
            printf("\nComando Invalido");
    };
    
}


int main (int argc, char* argv[]){
    
    char comando;
    List buffer;
    
    //criaLista(&buffer); -> Essa daqui você precisará criar de acordo com aquelas questões que ele deu de publico e privado. Eu não preciso dela porque tenho acesso direto ao buffer e a como o buffer é.
    
    abrirArquivo("/Users/Paulo/Desktop/Mestrado/Xmeans/Semaforo/Semaforo/constr.txt", &buffer);
    
    
    do{
        
        consultaComando(&comando, &buffer); //mostrar linha atual, o tamanho do buffer e solicita comando;
        printf("\nComando Escolhido: %c", comando);
        executaComando(comando, &buffer);
        printf("\npassou aqui");
    }while((comando!='q')&&(comando!='Q'));
    
    printf("\nFinalizando Programa...");
    
    return 0;
}




