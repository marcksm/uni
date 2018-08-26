all: pi text randtocomplete

a:
	make clean && make

pi: pi.c
	gcc pi.c graph.c graph.h -o pi

text: text.c
	gcc text.c graph.c graph.h -o text

randtocomplete: randtocomplete.c
	gcc randtocomplete.c graph.c graph.h -o randtocomplete

clean:
	rm pi && rm text && rm randtocomplete
