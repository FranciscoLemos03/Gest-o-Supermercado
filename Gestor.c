#include "ListaLigada.h"
#include "Gestor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//esta funcao le as variaveis do ficheiro txt e guarda-as na lista
Gestor* lerBaseDeDadosG(){
    Gestor* lista = NULL;
    Gestor* novo = NULL;
	
	FILE *dbGestor = fopen("dbGestor.txt", "r");
    // Verificar se existe na diretoria
	if(dbGestor == NULL) {
		printf("\nERRO!");
	}
	
    //iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
    while(!feof(dbGestor)) {
        novo = (Gestor*)calloc(1, sizeof(Gestor));
        fscanf(dbGestor,"%d:%[^:]:%s\n", &(novo->ID), &(novo->nome), &(novo->passwd));
            lista = adicionarGestor(lista, novo);
    }

    fclose(dbGestor);

    return lista;
}

// Guarda as variaveis num ficheiro txt
void guardarBaseDeDadosG(Gestor* lista){
	Gestor* ge;
	
	FILE *dbGestor = fopen("dbGestor.txt", "w");
    // Verificar se existe na diretoria
	if(dbGestor == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( ge = lista; ge != NULL; ge = ge->next){
            fprintf(dbGestor,"%d:%s:%s\n", ge->ID, ge->nome, ge->passwd);
    }
    fclose(dbGestor);
}

// Liberta a memoria alocada pela lista
// uso de recursao 
void libertarMemoriaG(Gestor* lista){
    if(lista == NULL)
        return;

    libertarMemoriaG(lista->next);

    free(lista);
}

Gestor* adicionarGestor(Gestor *listaGestor, Gestor *novoGestor)
{
	//se a lista for NULL, devolve o meu novo Gestor
	if(listaGestor == NULL) return novoGestor;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaGestor->next = adicionarGestor(listaGestor->next, novoGestor);
	//da return a lista depois da atualiza??o
	return listaGestor;
}
