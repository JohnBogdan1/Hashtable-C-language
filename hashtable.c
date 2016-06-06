
#include"hashtable.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//functia de creare a tabelei hash
TD *hashtable_create(size_t nM, HASH ffd)
{
	TD *atd;

	if ( !(atd = (TD*) malloc(sizeof(TD) ) ) ) return NULL;

	//aloc vectorul de liste
	if ( !(atd -> v = calloc(nM, sizeof(TLG) ) ) ) {
		free(atd);
		return NULL;
	}

	atd -> M = nM;
	atd -> fd = ffd;

	return atd;
}


//functia hash
int ffd(char *cheie, int M)
{
	size_t hash = 0;
	
	while (*cheie) 
		hash += (unsigned char) *cheie++;
	return hash % M;
}

//functia de inserare(put)
int hashtable_insert(TD *atd, char *cheie, char *valoare)
{
	//calculez indexul unde trebuie adaugata cheia
    int index = ffd(cheie, atd -> M);
    TLG aux = NULL, p = NULL;
	ALG aL = NULL;
	aL = atd -> v + index;

	//parcurg lista pana gasesc elementul
	//cand il gasesc, ma opresc si retin pozitia
	while (*aL != NULL) {
		if (strcmp(cheie, ( (DNS*)( (*aL) -> info) ) -> key ) < 0)
            break;
		p = *aL;
		aL = &(*aL) -> urm;
	}
	
	//daca lista este vida, inserez la inceput
	if (p == NULL) {

		//creez o celula in care voi pune cheia si valoarea
		aux = malloc( sizeof(TCelulaG) );
		aux -> info = (DNS*) malloc( sizeof(DNS) );

		//copiez informatia in celula
        ( (DNS *)(aux->info) ) -> key = strdup(cheie);
		( (DNS *)(aux->info) ) -> value = strdup(valoare);

		//creez legaturile
		aux -> urm = *aL;
		*aL = aux;      
    } else {
		//verific daca exista cheia
		TLG duplicat = lookup_string(atd, cheie);
		if(duplicat != NULL) return 2;

		//creez o celula in care voi pune cheia si valoarea
		aux = malloc( sizeof(TCelulaG) );
		aux -> info = (DNS*) malloc( sizeof(DNS) );
		//copiez informatia in celula
		( (DNS *)(aux -> info) ) -> key = strdup(cheie);
		( (DNS *)(aux -> info) ) -> value = strdup(valoare);
	
		//creez legaturile
		aux -> urm = *aL;
  		*aL = aux;
	}
	

	return 0;
}

//functia de verificare a unicitatii cheii
TLG lookup_string(TD *atd, char *str)
{
    
	int index = ffd(str, atd -> M);
	ALG aL = atd -> v + index;

	//parcurg lista si verific daca mai exista aceeasi cheie
	while (*aL) {
       if (!strcmp(str, ( (DNS *)((*aL) -> info) ) -> key)) {
			return *aL;
			break;
		}
	//incrementez pozitia in lista
	aL = &(*aL) -> urm;
    }
    return NULL;
}

//functia de eliminare a perechii <key,value>
int hashtable_remove(TD *atd, char *cheie)
{
	TLG node = NULL, prevnode = NULL;

	int index = ffd(cheie, atd -> M);
	
	//parcurg lista si gasesc pozitia unde se afla cheia
	node = atd -> v[index];
	while (node) {
		if (!strcmp( ( (DNS *)(node -> info) ) -> key, cheie) ) {

			free( ((DNS *)(node -> info)) -> key);
			free( ((DNS *)(node -> info)) -> value);
			free((DNS *)(node -> info));
			//refac legaturile
			if(prevnode) 
				prevnode -> urm = node -> urm;
			else 
				atd -> v[index] = node -> urm;

			free(node);
			return 0;
		}
		prevnode = node;
		node = node -> urm;
	}
	return -1;
}

//functia de obtinere a valorii, de la cheia respectiva
void *hashtable_get(TD *atd, char *cheie, FILE *output)
{
	TLG node = NULL;
	int hash = ffd(cheie, atd -> M);

	node = atd -> v[hash];
	while ( node != NULL && ((DNS *)(node -> info))->key != NULL && strcmp( cheie, ((DNS *)(node -> info)) -> key ) > 0 ) {
		node = node->urm;
	}
 
	//am gasit ceea ce cautam?
	if ( node == NULL || ((DNS *)(node -> info)) -> key == NULL || strcmp( cheie, ((DNS *)(node -> info)) -> key ) != 0 ) {
		fprintf(output, "NULL\n");
 
	} else {
		fprintf(output, "%s\n", ((DNS *)(node -> info)) -> value);
	}
	return NULL;
}

//functia de cautare a cheii
void* hashtable_find(TD *atd, char *cheie, FILE *output)
{
	int hash = ffd(cheie, atd -> M), ok = 0;
	TLG node = NULL;
	
	node = atd -> v[hash];

	//veerific daca exista cheia in lista
	while (node) {
		if (!strcmp( ((DNS *)(node -> info)) -> key, cheie)) {
			ok = 1;
			fprintf(output, "True\n");
			break;
		}
		node = node->urm;
	}
	if (ok == 0)
		fprintf(output, "False\n");
    return NULL;
}

//functia de afisare a tabelei
void *afisare(TD *atd, FILE *output){

	int x = 0, ok = 0;
	
	TLG node;

	//parcurg vectorul de liste
	for (x = 0; x < atd -> M; ok = 0, x++) {
		node = atd -> v[x];
		if (node)
			fprintf(output,"%d: ", x);

		//parcurg fiecare lista in parte si afisez valorile
		while (node) {
			ok = 1;
			fprintf (output, "%s ", ((DNS *)(node -> info)) -> value);
			node = node -> urm;
						
		}
		if(ok == 1)
			fprintf(output, "\n");
	}

	return NULL;
}

//functia de afisare a unei singure liste de la un anumit indice dat, din tabela
void *afisare_bucket(TD *atd, int index, FILE *output)
{

	TLG node = NULL;
	int ok = 0;

	//daca indicele exista in tabela
	if (index < atd -> M) {

		node = atd -> v[index];

		while(node) {
			ok = 1;
			fprintf(output,"%s ", ((DNS *)(node -> info)) -> value);
			node = node -> urm;
		}
		if(ok == 1)
				fprintf(output, "\n");
		if (ok == 0)
			fprintf(output, "VIDA\n");
	}
    return NULL;
}

//functia de distrugere a listei
void DistrugeLG(ALG aL) 
{ 
	TLG aux = NULL, p = NULL;

	p = *aL;

	//parcurg lista
	//elimin cheia, valoarea, info si apoi celula
	while (p) {

		//retin pozitia celulei
		aux = p;

		//incrementez pozitia
		p = p->urm;

		//eliberez celula
		free(((DNS *)(aux -> info)) -> key);
		free(((DNS *)(aux -> info)) -> value);
		free(aux -> info);
		free(aux);
	}
	*aL = NULL;
}

//functia de distrugere a tabelei
void DistrugeTD(TD **atd)
{
	size_t n;
	TLG L = NULL;
	
	//parcurg vectorul
	for (n = 0; n < (*atd) -> M; n++) {
		L = (*atd) -> v[n];
		DistrugeLG(&L);
	}

	//eliberez tabela
	free((*atd) -> v);
	free(*atd);
	*atd = NULL;
}
