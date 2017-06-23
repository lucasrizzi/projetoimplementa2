CC=gcc

CFLAGS=-I../include/ -I.
SAIDA=projeto

2
DEPS = trabalho_privado.h trabalho_interface.h lista_privado.h lista_privado.h


OBJ = lista.o trabaho.o main.o

SRC= ../src/


%.o: %.c $(DEPS)
	
# %.o e a saida que teremos , ou seja arq.o %.c arquivos que buscamos e as dependencias que iremos verificar se hoveram alteracoes
	
$(CC) -c -o $@ $(CRC)< $(CFLAGS)
	
# -c nao deixa criar executavel final $@ tem todos os .o $< tem todos os .c o ultimo adiciona -I. diz onde estao os headers


$(SAIDA): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	
# $^ guarda os .h 
	
sudo valgrind ./$(SAIDA)

clean :
       -rm *.o $(SAIDA)