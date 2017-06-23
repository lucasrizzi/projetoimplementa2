CC=gcc
CFLAGS=-I.
SAIDA=projeto

DEPS = trabalho_privado.h trabalho_interface.h fila_privado.h fila_privado.h

OBJ = fila.o trabaho.o main.o

%.o: %.c $(DEPS)
	# %.o e a saida que teremos , ou seja arq.o %.c arquivos que buscamos e as dependencias que iremos verificar se hoveram alteracoes
	$(CC) -c -o $@ $< $(CFLAGS)
	# -c nao deixa criar executavel final $@ tem todos os .o $< tem todos os .c o ultimo adiciona -I. diz onde estao os headers

$(SAIDA): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	# $^ guarda os .h 
	#sudo valgrind ./$(SAIDA)
