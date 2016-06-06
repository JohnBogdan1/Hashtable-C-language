build: main.c hashtable.c hashtable.h
	gcc -Wall main.c hashtable.c hashtable.h -o tema1
clean:
	rm -f tema1
