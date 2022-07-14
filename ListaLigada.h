#include <stdbool.h>


// estrutura cliente
typedef struct _cliente{
   	int num_cliente;
   	char nome[20];
   	char morada[30];
   	int contribuinte;
   	int num_cartaocredito;
   	char passwd[10];
   	struct _cliente* next;
} Cliente; 

// estrutura produto
typedef struct _produto{
   	int ID;
   	char nome[20];
   	float preco;
   	int validade;
   	int quantidade;
   	struct _produto* next;
} Produto;

// estrutura gestor
typedef struct _gestor{
   	int ID;
   	char nome[20];
   	char passwd[10];
   	struct _gestor* next;
} Gestor;

// estrutura compra
typedef struct _compra{
   	int id_cliente;
   	int id_produto;
   	int quantidade;
   	struct _compra* next;
} Compra;


int clientelogin(Cliente* );
bool gestorlogin(Gestor* );

void mudarPass(Cliente* );
void mudarPassCliente(Cliente* , Cliente* );

//menus
void menuGestor(Cliente* , Produto*);
void menuCliente(Cliente* , Produto*, Compra*, int);
void menuPrincipal(Cliente* , Produto*, Gestor*, Compra*);
