build:
		gcc -o tenis tenis.c tasks.c list.c stack.c queue.c bst.c
clean:
		rm -f *.o
		rm -f tenis