#include "ListaLigada.h"
#include "Compra.h"
#include "Produto.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>


Compra* lerBaseDeDadosCompra(){
    Compra* lista = NULL;
    Compra* novo = NULL;
	
	FILE *dbCompra = fopen("dbCompra.txt", "r");
    // Verificar se existe na diretoria
	if(dbCompra == NULL) {
		printf("\nERRO!");
	}
	
    //iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
    while(!feof(dbCompra)) {
        novo = (Compra*)calloc(1, sizeof(Compra));
        fscanf(dbCompra,"%d:%d:%d\n", &(novo->id_cliente), &(novo->id_produto), &(novo->quantidade));
            lista = adicionarCompra(lista, novo);
    }

    fclose(dbCompra);

    return lista;
}

// Guarda as variaveis num ficheiro txt
void guardarBaseDeDadosCompra(Compra* lista){
	Compra* co;
	
	FILE *dbCompra = fopen("dbCompra.txt", "w");
    // Verificar se existe na diretoria
	if(dbCompra == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( co = lista; co != NULL; co = co->next){
            fprintf(dbCompra,"%d:%d:%d\n", co->id_cliente, co->id_produto, co->quantidade);
    }
    fclose(dbCompra);
}

Compra* adicionarCompra(Compra *listaCompra, Compra *novaCompra)
{
	//se a lista for NULL, devolve o meu novo cliente
	if(listaCompra == NULL) return novaCompra;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaCompra->next = adicionarCompra(listaCompra->next, novaCompra);
	//da return a lista depois da atualiza??o
	return listaCompra;
}

void comprar(Cliente* listaCliente, Produto* listaProduto, Compra* listaCompra, int idEscolhido) {
    Compra* novaCompra = (Compra*)calloc(1, sizeof(Compra));
    int auxIDProduto = -1,auxQuantidade = -1;
    Produto* produtoEscolhido;
    Cliente* clienteEscolhido;
    
    printf("Digite o id do produto: ");
	fflush(stdin); 
    scanf("%d", &auxIDProduto);
    
    produtoEscolhido = encontrarProduto(listaProduto, auxIDProduto);
    
    if(produtoEscolhido != NULL){
    	novaCompra->id_produto = auxIDProduto;
    
		novaCompra->id_cliente = idEscolhido;
		
		printf("Digite a quantidade: ");
		fflush(stdin); 
		scanf("%d", &auxQuantidade);
		
		novaCompra->quantidade = auxQuantidade;

		listaCompra = comprarProduto(listaCompra, novaCompra);

		printf("\nComprado com sucesso!\n");
    	
			
	} else {
        printf("Produto nao encontrado!\n");
	}
}

//procedimento para adicionar um cliente
Compra* comprarProduto(Compra* listaCompra, Compra* novaCompra)
{
	//se a lista for NULL, devolve o meu novo cliente
	if(listaCompra == NULL) return novaCompra;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaCompra->next = comprarProduto(listaCompra->next, novaCompra);
	
	//da return a lista depois da atualiza??o
	return listaCompra;
}
