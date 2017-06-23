CC=gcc

CFLAGS=-I../include/ -I.
SAIDA=projeto

2
DEPS = trabalho_privado.h trabalho_interface.h  lista_interface.h lista_privado.h


OBJ = trabaho.o lista.o main.o


CRC= ../src/

%.o: %.c $(DEPS)
	
	# %.o e a saida que teremos , ou seja arq.o %.c arquivos que buscamos e as dependencias que iremos verificar se hoveram alteracoes

$(CC) -c -Wall -Wimplicit -Wextra -o $@ $(CRC)< $(CFLAGS)

	#talvez seja $(CRC)$<
	# -c nao deixa criar executavel final $@ tem todos os .o $< tem todos os .c o ultimo adiciona -I. diz onde estao os headers


$(SAIDA): $(OBJ)
	gcc -Wall -Wimplicit -Wextra -o $@ $^ $(CFLAGS)

	# $^ guarda os .h 

	#sudo valgrind ./$(SAIDA)
clean:
	-rm *.o $(SAIDA)