#include "ListaLigada.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>

// Esta funcao le as variaveis do ficheiro txt e guarda-as na lista
Cliente* lerBaseDeDados(){
    Cliente* lista = NULL;
    Cliente* novo = NULL;
	
	FILE *dbCliente = fopen("dbCliente.txt", "r");
    // Verificar se existe na diretoria
	if(dbCliente == NULL) {
		printf("\nERRO!");
	}
	
    // Iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
    while(!feof(dbCliente)) {
        novo = (Cliente*)calloc(1, sizeof(Cliente));
        fscanf(dbCliente,"%d:%[^:]:%[^:]:%[^:]:%d:%d\n", &(novo->num_cliente), &(novo->nome), &(novo->morada), &(novo->passwd), &(novo->num_cartaocredito), &(novo->contribuinte));
            lista = adicionarCliente(lista, novo);
    }

    fclose(dbCliente);

    return lista;
}

// Guarda as variaveis num ficheiro txt
void guardarBaseDeDados(Cliente* lista){
	Cliente* cl;
	
	FILE *dbCliente = fopen("dbCliente.txt", "w");
    // Verificar se existe na diretoria
	if(dbCliente == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( cl = lista; cl != NULL; cl = cl->next){
            fprintf(dbCliente,"%d:%s:%s:%s:%d:%d\n", cl->num_cliente, cl->nome, cl->morada, cl->passwd ,cl->num_cartaocredito, cl->contribuinte);
    }
    fclose(dbCliente);
}

// Liberta a memoria alocada pela lista
// uso de recursao 
void libertarMemoria(Cliente* lista){
    if(lista == NULL)
        return;

    libertarMemoria(lista->next);

    free(lista);
}

// funcao para adicionar cliente
void adicionar(Cliente* listaCliente) {
	// variavel do tipo Cliente que retorna um ponteiro para o espaço alocado
    Cliente* novoCliente = (Cliente*)calloc(1, sizeof(Cliente));
    int auxInt = -1;
    
    printf("Digite o nome: ");
	fflush(stdin); 
    fgets(novoCliente->nome, 20, stdin);
    novoCliente->nome[strcspn(novoCliente->nome, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
    printf("Digite a morada: ");
	fflush(stdin); 
	fgets(novoCliente->morada, 30, stdin);
	novoCliente->morada[strcspn(novoCliente->morada, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
	
	printf("Digite a password: ");
	fflush(stdin); 
	fgets(novoCliente->passwd, 10, stdin);
	novoCliente->passwd[strcspn(novoCliente->passwd, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
    //gerar um id aleatorio 
    novoCliente->num_cliente= obterIdAleatorio(listaCliente);
    
	auxInt = -1;
	printf("Digite o numero de contribuinte:");
	fflush(stdin);
	scanf("%d", &auxInt);
	novoCliente->contribuinte = auxInt;

	auxInt = -1;
    printf("Digite o numero do cartao de credito:");
	fflush(stdin);
	scanf("%d", &auxInt);
	novoCliente->num_cartaocredito = auxInt;
    
    //vai percorrer a lista ate encontrar um espaço null
    listaCliente = adicionarCliente(listaCliente, novoCliente);

    printf("\nAdicionado com sucesso!\n");
}

//procedimento para adicionar um cliente no espaço null
Cliente* adicionarCliente(Cliente *listaCliente, Cliente *novoCliente)
{
	//se a lista for NULL, devolve o meu novo cliente
	if(listaCliente == NULL) return novoCliente;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaCliente->next = adicionarCliente(listaCliente->next, novoCliente);
	//da return a lista depois da atualizacao
	return listaCliente;
}

// Obter um id aleatorio
int obterIdAleatorio(Cliente* listaClientes) {
    int randomId;
    time_t t;

	//inicia um numero random
    srand((unsigned) time(&t));
    
    //dar valor ao id até encontrar um numero entre 0 e 100 que nao exista
    do {
        randomId = rand() % 100; 
    } while(existeCliente(listaClientes,randomId));
    
    return randomId;
}

// verificar se existe cliente
bool existeCliente(Cliente* lista, int id) {
	//se a lista for null retorna falso
    if(lista == NULL)
        return false;
    
    // se o id dado for igual ao da lista retorna verdadeiro
    if(lista->num_cliente == id)
        return true;
    
    return existeCliente(lista->next, id);    
}

//funcao para editar
void editar(Cliente* listaCliente)
{
    int auxInt = -1;
    int idEscolhido;
    Cliente* clienteEscolhido;

    printf("\nQual o numero do Cliente?\n");
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

	//funcao para encontrar cliente
    clienteEscolhido = encontrarCliente(listaCliente, idEscolhido);

	// se existir algum cliente na lista com esse id edita, senao mensagem a avisar que nao encontrou
    if(clienteEscolhido != NULL)
        editarCliente(listaCliente, clienteEscolhido);
    else
        printf("Cliente nao encontrado!\n");
}

//Dado um cliente, pede-se os dados para edita-lo
void editarCliente(Cliente* listaCliente, Cliente* clienteEscolhido) {
    int auxInt = -1;
    
    printf("Digite o nome: ");
	fflush(stdin); 
    fgets(clienteEscolhido->nome, 20, stdin);
    clienteEscolhido->nome[strcspn(clienteEscolhido->nome, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
    printf("Digite a morada: ");
	fflush(stdin); 
	fgets(clienteEscolhido->morada, 30, stdin);
    clienteEscolhido->morada[strcspn(clienteEscolhido->morada, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
    printf("Digite a password: ");
    fflush(stdin); 
	fgets(clienteEscolhido->passwd, 10, stdin);
	clienteEscolhido->passwd[strcspn(clienteEscolhido->passwd, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
	auxInt = -1;
	printf("Digite o numero de contribuinte:");
	fflush(stdin);
	scanf("%d", &auxInt);
	clienteEscolhido->contribuinte = auxInt;

	auxInt = -1;
    printf("Digite o numero do cartao de credito:");
	fflush(stdin);
	scanf("%d", &auxInt);
	clienteEscolhido->num_cartaocredito = auxInt;

    printf("\nAlterado com sucesso!\n");
}

// funcao para encontrar um cliente
Cliente* encontrarCliente(Cliente* lista, int id) {
    if(lista == NULL)
        return NULL;

    if(lista->num_cliente == id) 
        return lista;
    
    return encontrarCliente(lista->next, id);
}

//funcao para remover o cliente
void remover(Cliente* listaCliente) {
    int auxInt = -1;
    int idEscolhido;
    Cliente* clienteRemovido;

    printf("\nDigite o numero do Cliente?\n");
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
	
	
	//funcao para encontrar e remover cliente	
    clienteRemovido = removerCliente(listaCliente, idEscolhido);

	// se existir algum cliente na lista mensagem a avisar que removeu, senao mensagem a avisar que nao encontrou
    if(clienteRemovido != NULL) {
        printf("Cliente removido com sucesso\n");
    } else {
        printf("Cliente nao encontrado!\n");
    }
}

// remover um cliente da lista
Cliente* removerCliente(Cliente* lista, int id) {
    Cliente* prox = NULL;

    if(lista == NULL)
        return NULL;

    if(lista->num_cliente == id) {
        prox = lista->next;
        free(lista);
        return prox;
    }
    
    lista->next = removerCliente(lista->next, id);
    return lista;
}

//funcao para visualizar cliente
void visualizarCliente(Cliente* listaCliente) {
	int auxInt = -1;
    int idEscolhido;
    Cliente* clienteEscolhido;

    printf("\nQual o numero do Cliente?\n");
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

	//funcao para encontrar o cliente pelo id
    clienteEscolhido = encontrarCliente(listaCliente, idEscolhido);

	// se existir algum cliente com o mesmo id lista o cliente, senao mensagem a avisar que nao encontrou
    if(clienteEscolhido != NULL)
        printf("Numero Cliente: %d\nNome: %s\nMorada: %s\nPassword: %s\nCartao Credito: %d\nNumero Contribuinte: %d\n", clienteEscolhido->num_cliente, clienteEscolhido->nome, clienteEscolhido->morada, clienteEscolhido->passwd, clienteEscolhido->num_cartaocredito, clienteEscolhido->contribuinte);
    else
        printf("Cliente nao encontrado!\n");
}
