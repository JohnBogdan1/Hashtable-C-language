
#include <stdio.h>
#include <stdlib.h>

#ifndef _HASHTABLE_
#define _HASHTABLE_

//structura listei generice
typedef struct celula
{
	struct celula* urm;
	void* info;
}TCelulaG, *TLG, **ALG;

typedef int (*HASH)(char *key, int n);

//structura tabelei hash
typedef struct
{
	size_t M;
	HASH fd;
	TLG* v;
}TD;

//structura perechii <key, value>
typedef struct
{
	char *key, *value;
}DNS;

//declararile functiilor
TD *hashtable_create(size_t M, HASH ffd);
TLG lookup_string(TD *atd, char *str);

void *afisare_bucket(TD *atd, int index, FILE *output);
void *afisare(TD *atd, FILE *output);
void DistrugeLG(ALG);
void DistrugeTD(TD** atd);
int hashtable_insert(TD *atd, char *cheie, char *valoare);
int hashtable_remove(TD *atd, char *cheie);
void *hashtable_get(TD *atd, char *cheie, FILE *output);
void* hashtable_find(TD *atd, char *cheie, FILE *output);

#endif

