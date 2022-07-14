#include "ListaLigada.h"
#include "Produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>

Produto* lerBaseDeDadosP(){
    Produto* lista = NULL;
    Produto* novo = NULL;
	
	FILE *dbProduto = fopen("dbProduto.txt", "r");
    // Verificar se existe na diretoria
	if(dbProduto == NULL) {
		printf("\nERRO!");
	}
	
    // Iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
    while(!feof(dbProduto)) {
        novo = (Produto*)calloc(1, sizeof(Produto));
        fscanf(dbProduto,"%d:%[^:]:%f:%d:%d\n", &(novo->ID), &(novo->nome), &(novo->preco), &(novo->quantidade), &(novo->validade));
        lista = adicionarProduto(lista, novo);
    }

    fclose(dbProduto);

    return lista;
}

// Guarda as variaveis num ficheiro txt
void guardarBaseDeDadosP(Produto* lista){
	Produto* pr;
	
	FILE *dbProduto = fopen("dbProduto.txt", "w");
    // Verificar se existe na diretoria
	if(dbProduto == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( pr = lista; pr != NULL; pr = pr->next){
            fprintf(dbProduto,"%d:%s:%f:%d:%d\n", pr->ID, pr->nome, pr->preco, pr->quantidade, pr->validade);
    }
    fclose(dbProduto);
}

// Liberta a memoria alocada pela lista
// uso de recursao 
void libertarMemoriaP(Produto* lista){
    if(lista == NULL)
        return;

    libertarMemoriaP(lista->next);

    free(lista);
}

// Sub-menu da funcionalidade adicionar produto
void adicionarP(Produto* listaProduto) {
    Produto* novoProduto = (Produto*)calloc(1, sizeof(Produto));
    int auxInt = -1;
    float auxF = -1;
    
    printf("Digite o nome do produto: ");
	fflush(stdin); 
    fgets(novoProduto->nome, 20, stdin);
    novoProduto->nome[strcspn(novoProduto->nome, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
    novoProduto->ID= obterIdAleatorioP(listaProduto);
    
	printf("Digite o preco do produto:");
	fflush(stdin);
	scanf("%f", &auxF);
	novoProduto->preco = auxF;

	auxInt = -1;
	fflush(stdin);
    printf("Digite a validade do produto:");
	scanf("%d", &auxInt);
	novoProduto->validade = auxInt;
	
	auxInt = -1;
	fflush(stdin);
    printf("Digite a Quantidade do stock:");
	scanf("%d", &auxInt);
	novoProduto->quantidade = auxInt;
    
    
   	printf("%d:%s:%f:%d:%d\n", novoProduto->ID, novoProduto->nome, novoProduto->preco, novoProduto->quantidade, novoProduto->validade);
    
    listaProduto = adicionarProduto(listaProduto, novoProduto);

    printf("\nAdicionado com sucesso!\n");
    
}

//procedimento para adicionar um produto
Produto* adicionarProduto(Produto *listaProduto, Produto *novoProduto)
{
	//se a lista for NULL, devolve o meu novo produto
	if(listaProduto == NULL) return novoProduto;
	//se lista for diferente de NULL, o proximo produto vai continuar a procurar um espaco "NULL" 
	listaProduto->next = adicionarProduto(listaProduto->next, novoProduto);
	//d? return a lista depois da atualiza??o
	return listaProduto;
}

// Obter um id aleatorio
int obterIdAleatorioP(Produto* listaProdutos) {
    int randomId;
    time_t t;

    srand((unsigned) time(&t));
    
    do {
        randomId = rand() % 100; 
    } while(existeProduto(listaProdutos,randomId));
    
    return randomId;
}

// verificar se existe produto
bool existeProduto(Produto* lista, int id) {
    if(lista == NULL)
        return false;
    
    if(lista->ID == id)
        return true;
    
    return existeProduto(lista->next, id);    
}

//Sub-menu da funcionalidade editar
void editarP(Produto* listaProduto)
{
    int auxInt = -1;
    int idEscolhido;
    Produto* produtoEscolhido;

    printf("\nQual o numero do Produto?\n");
    do {
        auxInt = -1;
    	fflush(stdin);
    	if(scanf("%d", &auxInt) != 0){
    		idEscolhido = auxInt;
		}
		if(auxInt < 0 ) {
			printf("erro, Escolha um valor positivo!\n");
		}
	} while(auxInt < 0 );

    produtoEscolhido = encontrarProduto(listaProduto, idEscolhido);

    if(produtoEscolhido != NULL)
        editarProduto(listaProduto, produtoEscolhido);
    else
        printf("Produto nao encontrado!\n");
}

//dado um produto, inicia um sub-menu para edita-lo
void editarProduto(Produto* listaProduto, Produto* produtoEscolhido) {
	
    int auxInt = -1;
    float auxF = -1;
    
    printf("Digite o nome do produto: ");
	fflush(stdin); 
    fgets(produtoEscolhido->nome, 20, stdin);
    produtoEscolhido->nome[strcspn(produtoEscolhido->nome, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
	printf("Digite o preco do produto:");
	fflush(stdin);
	scanf("%f", &auxF);
	produtoEscolhido->preco = auxF;

	auxInt = -1;
    printf("Digite a validade do produto:");
	fflush(stdin);
	scanf("%d", &auxInt);
	produtoEscolhido->validade = auxInt;
	
	auxInt = -1;
    printf("Digite a Quantidade do stock:");
	fflush(stdin);
	scanf("%d", &auxInt);
	produtoEscolhido->quantidade = auxInt;

    printf("\nAlterado com sucesso!\n");
}

//funcao para encontrar um produto
Produto* encontrarProduto(Produto* lista, int id) {
    if(lista == NULL)
        return NULL;

    if(lista->ID == id) 
        return lista;
    
    return encontrarProduto(lista->next, id);
}

//sub-menu para remover o produto
void removerP(Produto* listaProduto) {
    int auxInt = -1;
    int idEscolhido;
    Produto* produtoRemovido;

    printf("\nDigite o ID do Produto?\n");
    do {
        auxInt = -1;
    	fflush(stdin);
    	if(scanf("%d", &auxInt) != 0){
    		idEscolhido = auxInt;
		}
		if(auxInt < 0 ) {
			printf("erro, Escolha um valor positivo!\n");
		}
	} while(auxInt < 0 );

    produtoRemovido = removerProduto(listaProduto, idEscolhido);

    if(produtoRemovido != NULL) {
        printf("Produto removido com sucesso\n");
    } else {
        printf("Produto nao encontrado!\n");
    }
}

//remover um produto da lista
Produto* removerProduto(Produto* lista, int id) {
    Produto* prox = NULL;

    if(lista == NULL)
        return NULL;

    if(lista->ID == id) {
        prox = lista->next;
        free(lista);
        return prox;
    }
    
    lista->next = removerProduto(lista->next, id);
    return lista;
}

void visualizarProduto(Produto* listaProduto) {
	int auxInt = -1;
    int idEscolhido;
    Produto* produtoEscolhido;

    printf("\nQual o ID do Produto?\n");
    do {
        auxInt = -1;
    	fflush(stdin);
    	if(scanf("%d", &auxInt) != 0){
    		idEscolhido = auxInt;
		}
		if(auxInt < 0 ) {
			printf("erro, Escolha um valor positivo!\n");
		}
	} while(auxInt < 0 );

    produtoEscolhido = encontrarProduto(listaProduto, idEscolhido);

    if(produtoEscolhido != NULL)
        printf("%d\n%s\n%d\n%d\n%d\n", produtoEscolhido->ID, produtoEscolhido->nome, produtoEscolhido->preco, produtoEscolhido->validade, produtoEscolhido->quantidade);
    else
        printf("Produto nao encontrado!\n");
}

void listarProdutos(Produto* lista){
	Produto* pr;
	
	FILE *dbProduto = fopen("dbProduto.txt", "r");
    // Verificar se existe na diretoria
	if(dbProduto == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( pr = lista; pr != NULL; pr = pr->next){
            printf("ID: %d\nNome: %s\nPreco: %f\nQuantidade: %d\nValidade: %d\n\n", pr->ID, &pr->nome, pr->preco, pr->quantidade, pr->validade);
    }
    fclose(dbProduto);
}
