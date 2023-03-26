#include "arvore.c"
#include "lista.c"
#include <stdio.h>
#include <locale.h>
void init()
{

	FILE *arvore, *lista;
	Header_Arvore *h_a = alocar_header_arvore();
	Header_Lista *h_l = alocar_header_lista();
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");

	h_a->raiz = NULL_ARQ;
	h_a->livre = NULL_ARQ;
	h_a->topo = 0;
	escreve_header_arvore(arvore, h_a);

	h_l->livre = NULL_ARQ;
	h_l->topo = 0;
	escreve_header_lista(lista, h_l);
	h_a = ler_header_arvore(arvore);
	h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);
}
void menu_inserir()
{
	FILE *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	Header_Arvore *h_a = ler_header_arvore(arvore);
	Header_Lista *h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);

	Produto *pro;
	int pos;
	No_Arvore *no = aloca_no_arvore();
	pro = ler_dados_produto();
	if (checa_se_codigo_ja_esta_na_arvore(arvore, pro->codigo))
	{
		printf("O livro ja esta cadastrado.\n");
	}
	else
	{
		pos = inserir_dados_do_produto_no_arquivo(lista, pro);
		no->codigo = pro->codigo;
		no->pos_dados = pos;
		inserir_no_arquivo_arvore(arvore, no);
		printf("Livro inserido.\n");
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
	printf("Entre com o codigo do livro que sofrera a alteracao.\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		altera_preco(arvore, lista, cod);
		printf("N�mero de exemplares atualizado com sucesso.\n");
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
	printf("Entre com o codigo do livro que sofrera a alteracao.\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		altera_estoque(arvore, lista, cod);
		printf("N�mero de exemplares atualizado com sucesso.\n");
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
	printf("Entre com o codigo do livro que deseja remover.\n");
	scanf("%d", &cod);
	fflush(stdin);
	if (checa_se_codigo_ja_esta_na_arvore(arvore, cod))
	{
		remove_no_arquivo_arvore(arvore, lista, cod);
		printf("Livro removido.\n");
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
	printf("Entre com o codigo do livro que deseja buscar.\n");
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
	Header_Arvore *h_a = ler_header_arvore(arvore);
	Header_Lista *h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);
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
	Header_Arvore *h_a = ler_header_arvore(arvore);
	Header_Lista *h_l = ler_header_lista(lista);
	char nome_arq[100];
	h_a = ler_header_arvore(arvore);
	h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);
	/*
	fclose(arvore);
	fclose(lista);
	arvore = fopen("arvore", "w");
	lista = fopen("arvore", "w");
	*/
	h_l->livre = NULL_ARQ;
	h_l->topo = 0;
	h_a->raiz = NULL_ARQ;
	h_a->livre = NULL_ARQ;
	h_a->topo = 0;
	/*
	arvore = abre_arquivo_binario("arvore");
	lista = abre_arquivo_binario("lista");
	*/
	escreve_header_arvore(arvore, h_a);
	escreve_header_lista(lista, h_l);

	fflush(stdin);
	printf("Entre com o nome do arquivo txt com os dados que deseja inserir.\n");
	scanf("%[^\n]%*c", nome_arq);
	ler_dados_do_arquivo_txt(nome_arq, arvore, lista);
	printf("Arquivo carregado.\n");
	printf("final leitura");
	h_a = ler_header_arvore(arvore);
	h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);
	fclose(lista);
	fclose(arvore);
}

int menuInicial()
{
	int resposta;

	printf("|   (1) Carregar arquivo\n");
	printf("|   (2) Inserir item\n");
	printf("|   (3) Atualizar preço\n");
	printf("|   (4) Atualizar estoque\n");
	printf("|   (5) Remover produto\n");
	printf("|   (6) Buscar dados do produto \n");
	printf("|   (7) Imprimir arvore binaria por nivel\n");
	printf("|   (8) Imprimir tudo\n");
	printf("|   (9) (Experimental)Abrir Arquivo\n");

	scanf("%d%*c", &resposta);
	return resposta;
}

int sairPrograma()
{
	int opcao;

	system("cls");
	printf("\x1B[1;31m");
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|            Site                   |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|      Deseja sair do programa?     |\n");
	printf("|         (1) SIM   (2)NAO          |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("\x1B[0;0m");
	scanf("%d", &opcao);

	return opcao;
}