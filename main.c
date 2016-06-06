#include"hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int main (int argc, char *argv[]) {

	TD *atd;
	FILE *input = NULL,*output = NULL;
	if (argc != 4) {
		printf("Please, input three arguments!\n");
		return 1;
	}
	//convertesc argumentul la int
	int d = atoi(argv[1]);
	
	//aloc tabela
	if (!(atd = hashtable_create(d, NULL))) {
		DistrugeTD(&atd);
	}

	input = fopen( argv[2], "r" );

	if (input == NULL) {
		printf("\nCould not open file");
	}

	output = fopen( argv[3], "w" );
	
	if (output == NULL) {
		printf("\nCould not open file");
	}
	

	int k;
	char a[20], b[25], c[20];

	//citesc comenzile din fisier
	while (fscanf(input, " %s", a) == 1) {
		if (!strcmp(a, "put")) {
			fscanf(input," %s %s", b, c);
			hashtable_insert(atd, b, c);
		}
		if (!strcmp(a, "print"))
			afisare(atd, output);

		if (!strcmp(a, "print_bucket")) {
			fscanf(input, "%d", &k);
				afisare_bucket(atd, k, output);
		}
		if (!strcmp(a, "get")) {
			fscanf(input, "%s", b);
			hashtable_get(atd, b, output);
		}
		if (!strcmp(a, "find")) {
			fscanf(input, "%s", b);
			hashtable_find(atd, b, output);
		}
		if (!strcmp(a, "remove")) {
			fscanf(input, "%s", b);
			hashtable_remove(atd, b);
		}
	}


	fclose(input);
	fclose(output);
	DistrugeTD(&atd);
	
	return 0;
 }
