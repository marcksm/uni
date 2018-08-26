####################################################
##                                                ##
##    MAC0211 - Laboratório de Programação I      ##
##          Exercício-programa - Fase 4           ##
##                                                ##
##    Bárbara de Castro Fernandes - 7577351       ##
##    Duílio Henrique Haroldo Elias - 6799722     ##
##    Marcos Vinicius do Carmo Sousa - 9298274	  ##
##                                                ##
####################################################

CC = gcc
CFLAGS = -Wall -ansi -O2 -Wno-unused-result
LDFLAGS = -lGL -lGLU -lglut -lm -lSOIL -lopenal -lalut
OBJ = app/batalha-espacial.o app/models/model_auxiliar.o app/models/model_fisica.o app/models/model_nave.o \
app/models/model_planeta.o app/models/model_projetil.o app/models/model_universo.o app/models/model_vetor.o app/views/view.o \
app/views/view_nave.o app/views/view_planeta.o app/views/view_projetil.o app/views/view_universo.o \
app/controllers/controller.o

batalha-espacial: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

.PHONY: clean tar
clean:
	rm -f $(OBJ)
	rm -f batalha-espacial

tar:
	tar -cvzf ep4-labprogi.tar.gz Makefile app/ test/ doc/
