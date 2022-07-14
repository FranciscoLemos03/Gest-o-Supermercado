#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "ListaLigada.h"
#include "Produto.h"
#include "Cliente.h"
#include "Gestor.h"
#include "Compra.h"

int main()
{
	// cria uma lista de clientes apartir de um ficheiros txt
    Cliente* listaCliente = lerBaseDeDados();
    Produto* listaProduto = lerBaseDeDadosP();
    Gestor* listaGestor = lerBaseDeDadosG();
    Compra* listaCompra = lerBaseDeDadosCompra();
    
    
    menuPrincipal(listaCliente , listaProduto, listaGestor, listaCompra);

	//guarda a lista num ficheiro txt e liberta a memoria alocada pela lista
    guardarBaseDeDados(listaCliente);
    libertarMemoria(listaCliente);
    
    guardarBaseDeDadosP(listaProduto);
    libertarMemoriaP(listaProduto);
    
    guardarBaseDeDadosG(listaGestor);
    libertarMemoriaG(listaGestor);
    
    guardarBaseDeDadosCompra(listaCompra);
    libertarMemoriaCompra(listaCompra);
    
    
}


