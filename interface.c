#include "arvore.c"
#include "lista.c"
#include <stdio.h>
#include <locale.h>
void init()
{

	FILE *arvore, *lista;
	Header_A *h_a = alocar_header_arvore();
	arvore = abre_arquivo_binario("arvore");
	
	h_a->raiz = NULL_ARQ;
	h_a->livre = NULL_ARQ;
	h_a->topo = 0;
	escreve_header_arvore(arvore, h_a);

	Header_L *h_l = alocar_header_lista();
	lista = abre_arquivo_binario("lista");	
	
	h_l->livre = NULL_ARQ;
	h_l->topo = 0;
	escreve_header_lista(lista, h_l);
	
	fclose(arvore);
	fclose(lista);
}

void imprime_produto(Produto *p)
{
	printf("\n========== cod: %d ==============\n", p->codigo);
	printf("Nome: %s | Marca: %s\n", p->nome, p->marca);
	printf("Categoria: %s\n", p->categoria);
	printf("Estoque: %d | Preco R$: %.2f\n", p->estoque, p->preco);
}


void menu_inserir()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	Produto *pro;
	int pos;
	No_A *no = aloca_no_arvore();
	pro = ler_dados_produto();
	if (checa_se_codigo_ja_esta_na_arvore(arvore, pro->codigo))
	{
		printf("O produto ja esta cadastrado.\n");
	}
	else
	{
		pos = inserir_dados_do_produto_no_arquivo(lista, pro);
		no->codigo = pro->codigo;
		no->pos_dados = pos;
		inserir_no_arquivo_arvore(arvore, no);
		printf("Produto inserido.\n");
	}
	fclose(lista);
	fclose(arvore);
}

void menu_alterar_preco()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	int cod;
	printf("Digite o codigo do produto:\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		altera_preco(arvore, lista, cod);
		printf("Preco atualizado!\n");
	}
	else
	{
		printf("O codigo escolhido nao esta na arvore.\n");
	}
	fclose(lista);
	fclose(arvore);
}

void menu_alterar_estoque()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	int cod;
	printf("Digite o codigo do produto:\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		altera_estoque(arvore, lista, cod);
		printf("Estoque atualizado!\n");
	}
	else
	{
		printf("O codigo escolhido nao esta na arvore.\n");
	}
	fclose(lista);
	fclose(arvore);
}

void menu_remover()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	int cod;
	printf("Digite o codigo do produto:\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		remove_no_arquivo_arvore(arvore, lista, cod);
		printf("Produto removido.\n");
	}
	else
	{
		printf("O codigo escolhido nao esta na arvore.\n");
	}
	fclose(lista);
	fclose(arvore);
}

void menu_buscar()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	int cod;
	printf("Digite o codigo do produto:\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		busca_dados_do_produto(arvore, lista, cod);
	}
	else
	{
		printf("O codigo escolhido nao esta na arvore.\n");
	}
	fclose(lista);
	fclose(arvore);
}

void menu_imprimir()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	Header_A *h_a = alocar_header_arvore();
	h_a = ler_header_arvore(arvore);
	if (h_a->raiz != NULL_ARQ)
	{
		imprime_todos_produto(arvore, lista, h_a->raiz);
	}
	else
	{
		printf("A arvore esta vazia.\n");
	}
	fclose(lista);
	fclose(arvore);
}

void menu_ler_arquivo()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	Header_A *h_a = ler_header_arvore(arvore);
	Header_L *h_l = ler_header_lista(lista);
	char nome_arq[100];
	escreve_header_arvore(arvore, h_a);
	escreve_header_lista(lista, h_l);

	fflush(stdin);

	printf("Digite o nome do arquivo.\n");
	scanf("%[^\n]%*c", nome_arq);
	if (strstr(nome_arq, ".txt") == NULL) {
        strcat(nome_arq, ".txt");
    }
	abrir_arquivo_texto(nome_arq, arvore, lista);
	printf("\nArquivo carregado.\n");
	fclose(lista);
	fclose(arvore);
}

int menu()
{
	int index;
	printf("|  1 -> Carregar arquivo txt\n");
	printf("|  2 -> Inserir produto\n");
	printf("|  3 -> Atualizar preço\n");
	printf("|  4 -> Atualizar estoque\n");
	printf("|  5 -> Remover produto\n");
	printf("|  6 -> Buscar dados do produto \n");
	printf("|  7 -> Imprimir arvore binaria por nivel\n");
	printf("|  8 -> Imprimir tudo\n");
	printf("|  9 -> Imprimir Livres (Corrigir)\n");
	printf("|  0 -> Sair\n");

	scanf("%d%*c", &index);
	return index;
}
