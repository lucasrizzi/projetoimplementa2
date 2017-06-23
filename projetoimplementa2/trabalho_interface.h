#ifndef trabalho_interface_h
#define trabalho_interface_h
#include "lista_interface.h"

void criaLista(lista_t**buffer);

int abriArquivo(const char *arquivo,lista_t*buffer);

void executaComando(char comando, lista_t*buffer);

void consultaComando(char *comando,lista_t *buffer);

void funcao_leitura(lista_t *buffer);

void funcao_escritura(lista_t *buffer);

void funcao_apagalinha(lista_t *buffer);

void funcao_tamanhos(lista_t *buffer);

void funcao_vaipralinha(lista_t *buffer);

void funcao_insere(lista_t *buffer);

void funcao_encontra(lista_t *buffer);

void funcao_insere(lista_t *buffer);

void funcao_substitui(lista_t*buffer);

#endif
