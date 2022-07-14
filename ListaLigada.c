#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "ListaLigada.h"
#include "Produto.h"
#include "Cliente.h"
#include "Gestor.h"
#include "Compra.h"

//menu principal da lista de gestores
void menuGestor(Cliente* listaCliente, Produto* listaProduto)
{
	
	
	// sera usada como condicao para que o laco DO WHILE ocorra. Assim, caso o usuario digite 0, ele vai sair do programa. 
	// Caso ele digite qualquer outro numero, a opcao ? tratada pelo teste condicional SWITCH.	
    int continuar=-1;
    int aux=-1;
    do {
        system("cls || clear");
        printf("=======================\n");
        printf("\n\tGestor\n\n");
        printf("=======================\n\n");
        printf(" 1. Adicionar Cliente\n");
        printf(" 2. Remover Cliente\n");
        printf(" 3. Editar Cliente\n");
        printf(" 4. Ver Cliente\n\n");
        printf("=======================\n\n");
        printf(" 5. Adicionar Produto\n");
        printf(" 6. Remover Produto\n");
        printf(" 7. Editar Produto\n");
        printf(" 8. Ver Produto\n\n");
        printf("=======================\n\n");
        printf(" 0. Sair\n\n");
        printf("=======================\n");

        do
        {
            fflush(stdin);
            if(scanf("%d", &aux) != 0){
                continuar = aux;
            }
            if(continuar < 0 || continuar > 8) {
                system("cls || clear");
                printf("erro, opcao invalida!\n");
                
                printf("=======================\n");
		        printf("\n\tGestor\n\n");
		        printf("=======================\n\n");
		        printf(" 1. Adicionar Cliente\n");
		        printf(" 2. Remover Cliente\n");
		        printf(" 3. Editar Cliente\n");
		        printf(" 4. Ver Cliente\n\n");
		        printf("=======================\n\n");
		        printf(" 5. Adicionar Produto\n");
		        printf(" 6. Remover Produto\n");
		        printf(" 7. Editar Produto\n");
		        printf(" 8. Ver Produto\n\n");
		        printf("=======================\n\n");
		        printf(" 0. Sair\n\n");
		        printf("=======================\n");
            }
        } while(continuar < 0 || continuar > 8 );

        switch(continuar)
        {
            case 1:
                adicionar(listaCliente);
                break;

            case 2:
                remover(listaCliente);
                break;

            case 3:
                editar(listaCliente);
                break;
            
            case 4:
                visualizarCliente(listaCliente);
                break;
                
            case 5:
                adicionarP(listaProduto);
                break;

            case 6:
                removerP(listaProduto);
                break;

            case 7:
                editarP(listaProduto);
                break;
            
            case 8:
                visualizarProduto(listaProduto);
                break;

            case 0:
                printf("\n***  A regressar para o Menu Principal  ***");
                break;

            default:
                printf("Digite uma opcao valida\n");
                break;
            
        }
		//guardar variaveis a cada alteracao
		guardarBaseDeDados(listaCliente);
		guardarBaseDeDadosP(listaProduto);

        printf("\n");
        system("pause");
        
    } while(continuar != 0);
}

//procedimento para mudar a pass
void mudarPass(Cliente* listaCliente)
{
    int auxInt = -1;
    int idEscolhido;
    Cliente* clienteEscolhido;

    printf("\nDigite o seu numero: ");
    auxInt = -1;
	fflush(stdin);
	if(scanf("%d", &auxInt) != 0){
		idEscolhido = auxInt;
	}

    clienteEscolhido = encontrarCliente(listaCliente, idEscolhido);

    if(clienteEscolhido != NULL){
        mudarPassCliente(listaCliente, clienteEscolhido);
    	guardarBaseDeDados(listaCliente);
	} else {
        printf("Cliente nao encontrado!\n");
	}
}

//procedimento para pedir a nova pass
void mudarPassCliente(Cliente* listaCliente, Cliente* clienteEscolhido) {
    int auxInt = -1;
    
    printf("Digite uma nova password: ");
    fflush(stdin); 
	fgets(clienteEscolhido->passwd, 10, stdin);
	clienteEscolhido->passwd[strcspn(clienteEscolhido->passwd, "\n")] = 0; // tira a nova linha "\n" que tenho no nome

    printf("\nPassword alterada com sucesso!\n");
}



// Liberta a memoria alocada pela lista
// uso de recursao 
void libertarMemoriaCompra(Compra* lista){
    if(lista == NULL)
        return;

    libertarMemoriaCompra(lista->next);

    free(lista);
}

//funcao para fazer login como cliente
int clientelogin(Cliente* listaCliente){
	
    int idEscolhido = -1;
    char pwd[10];

    Cliente* inicio;
    
	fflush(stdin);
	printf("Digite o seu num cliente: ");
	scanf("%d", &idEscolhido);
    
    fflush(stdin); 
    printf("\nDigite a password: ");
    fgets(pwd, 10, stdin);
    pwd[strcspn(pwd, "\n")] = 0; // tira a nova linha "\n" que tenho no nome

	for( inicio = listaCliente ; inicio != NULL; inicio = inicio->next){
            if( inicio->num_cliente == idEscolhido && strcmp ( inicio->passwd, pwd) == 0) {
                    return idEscolhido;
        	}
    }

    return -1;
}

//funcao para fazer login como cliente
bool gestorlogin(Gestor* listaGestor){
	
    int idEscolhido = -1;
    char pwd[10];

    Gestor* inicio;
    
	fflush(stdin);
	printf("Digite o seu id: ");
	scanf("%d", &idEscolhido);
	
    fflush(stdin); 
    printf("\nDigite a password: ");
    fgets(pwd, 10, stdin);
    pwd[strcspn(pwd, "\n")] = 0; // tira a nova linha "\n" que tenho no nome

	for( inicio = listaGestor ; inicio != NULL; inicio = inicio->next){
            if( inicio->ID == idEscolhido && strcmp ( inicio->passwd, pwd) == 0) {
                    return true;
        	}
    }

    return false;
}

// sub-menu cliente
void menuCliente(Cliente* listaCliente, Produto* listaProduto, Compra* listaCompra, int idEscolhido)
{
	// sera usada como condicao para que o laco DO WHILE ocorra. Assim, caso o usuario digite 0, ele vai sair do programa. 
	// Caso ele digite qualquer outro numero, a opcao ? tratada pelo teste condicional SWITCH.	
    int continuar=-1;
    int aux=-1;
    do {
        system("cls || clear");
		printf("=========================\n");
        printf("\n\tCliente\n\n");
        printf("=========================\n\n");
        printf(" 1. Remover conta\n\n");
        printf("=========================\n\n");    
        printf(" 2. Ver Produtos\n");
        printf(" 3. Comprar Produtos\n\n");    
        printf("=========================\n\n");
        printf(" 0. Sair\n\n");
        printf("=========================\n");

        do
        {
            fflush(stdin);
            if(scanf("%d", &aux) != 0){
                continuar = aux;
            }
            if(continuar < 0 || continuar > 3) {
                system("cls || clear");
                printf("erro, opcao invalida!\n");
                
                
		        printf("=========================\n");
		        printf("\n\tCliente\n\n");
		        printf("=========================\n\n");
		        printf(" 1. Remover conta\n\n");
		        printf("=========================\n\n");    
		        printf(" 2. Ver Produtos\n");
		        printf(" 3. Comprar Produtos\n\n");    
		        printf("=========================\n\n");
		        printf(" 0. Sair\n\n");
		        printf("=========================\n");
            }
        } while(continuar < 0 || continuar > 3 );

        switch(continuar)
        {
            case 1:
                removerCliente(listaCliente, idEscolhido);
                continuar = 0;
                break;
            
            case 2:
            	listarProdutos(listaProduto);
                break;
                
            case 3:
				comprar(listaCliente, listaProduto, listaCompra, idEscolhido);
                break;

            case 0:
                printf("\n*** A regressar para o Menu Principal  ***");
                break;

            default:
                printf("Digite uma opcao valida\n");
                break;
            
        }
        
		//guardar variaveis a cada alteracao
		guardarBaseDeDados(listaCliente);
		guardarBaseDeDadosP(listaProduto);

        printf("\n");
        system("pause");
        
    } while(continuar != 0);
}

//menu principal
void menuPrincipal(Cliente* listaCliente, Produto* listaProduto, Gestor* listaGestor, Compra* listaCompra)
{
	// sera usada como condicao para que o laco DO WHILE ocorra. Assim, caso o usuario digite 0, ele vai sair do programa. 
	// Caso ele digite qualquer outro numero, a opcao tratada pelo teste condicional SWITCH.	
    int continuar=-1;
    int aux=-1;
    int idEscolhido=-1;
    do {
    	
        system("cls || clear");
        printf("==============================\n");
        printf("\n\tSupermercado\n\n");
        printf("==============================\n\n");
        printf(" 1. Area Gestor\n");
        printf(" 2. Area Cliente\n");
        printf(" 3. Nova Conta\n");
        printf(" 4. Esqueci-me da password\n\n");
        printf("==============================\n\n");    
        printf(" 0. Sair\n\n");
        printf("==============================\n");

        do
        {
            fflush(stdin);
            if(scanf("%d", &aux) != 0){
                continuar = aux;
            }
            if(continuar < 0 || continuar > 8) {
                system("cls || clear");
                printf("erro, opcao invalida!\n");
                 
		        printf("==============================\n");
		        printf("\n\tSupermercado\n\n");
		        printf("==============================\n\n");
		        printf(" 1. Area Gestor\n");
		        printf(" 2. Area Cliente\n");
		        printf(" 3. Nova Conta\n");
		        printf(" 4. Esquecime da password\n\n");
		        printf("==============================\n\n");    
		        printf(" 0. Sair\n\n");
		        printf("==============================\n");
            }
        } while(continuar < 0 || continuar > 8 );

        switch(continuar)
        {
            case 1:
            	if(gestorlogin(listaGestor) == true){	
					menuGestor(listaCliente, listaProduto);
				}
                break;

            case 2:
                idEscolhido = clientelogin(listaCliente);
                if(idEscolhido != -1) {
				    menuCliente(listaCliente, listaProduto, listaCompra, idEscolhido); 
                    idEscolhido = -1;             
                }
              
                break;

            case 3:
				adicionar(listaCliente);
                break;
            
            case 4:
                mudarPass(listaCliente);
				break;

            case 0:
                printf("\n***  Adeus!  ***");
                break;

            default:
                printf("\nDigite uma opcao valida\n\n\n");
                break;
            
        }

        printf("\n");
        system("pause");
        
    } while(continuar != 0);
}
