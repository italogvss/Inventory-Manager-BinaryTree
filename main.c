#include "interface.c"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	char nome_arq[100], c;
	int i, j, cod, pos, tam, n;
	Produto *l;
	Produto vet[100];
	for (tam = 0; tam < 100; tam++)
	{
		strcpy(vet[tam].nome, "0");
	}
	No_Arvore *no = aloca_no_arvore();
	FILE *f, *arvore, *lista;
	lista = abre_arquivo_binario("lista");
	//fclose(lista);
	arvore = abre_arquivo_binario("arvore");
	//fclose(arvore);
	Header_Lista *h_l = alocar_header_lista();
	h_l->livre = NULL_ARQ;
	h_l->topo = 0;
	Header_Arvore *h_a = alocar_header_arvore();
	h_a->raiz = NULL_ARQ;
	h_a->livre = NULL_ARQ;
	h_a->topo = 0;
	//lista = abre_arquivo_binario("lista");
	//arvore = abre_arquivo_binario("arvore");
	escreve_header_lista(lista, h_l);
	escreve_header_arvore(arvore, h_a);
	int sair = 0;
	system("cls");
	printf("inicio programa \n");
	h_a = ler_header_arvore(arvore);
	h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);
	fclose(arvore);
	fclose(lista);

	while (1)
	{
		i = menuInicial();
		fflush(stdin);

		switch (i)
		{
		case 1:
			menu_ler_arquivo();
			break;

		case 2:
			system("cls");
			menu_inserir();
			break;

		case 3:
			system("cls");
			h_a = ler_header_arvore(arvore);
			h_l = ler_header_lista(lista);
			imprime_header_arvore(h_a);
			imprime_header_lista(h_l);
			menu_alterar(arvore, lista);
			break;

		case 4:
			system("cls");
			h_a = ler_header_arvore(arvore);
			h_l = ler_header_lista(lista);
			imprime_header_arvore(h_a);
			imprime_header_lista(h_l);
			menu_remover(arvore, lista);
			break;

		case 5:
			h_a = ler_header_arvore(arvore);
			h_l = ler_header_lista(lista);
			imprime_header_arvore(h_a);
			imprime_header_lista(h_l);
			system("cls");
			menu_buscar(arvore, lista);
			break;

		case 6:
			system("cls");
			h_a = ler_header_arvore(arvore);
			imprime_arvore_arquivo(arvore, h_a->raiz, 0);
			printf("\n\n");
			break;

		case 7:
			system("cls");
			imprime_por_nivel(arvore);
			break;

		case 8:
			system("cls");
			menu_imprimir();
			break;

		case 9:
			system("cls");
			break;

		case 0:
			system("cls");
			sair = sairPrograma();
			if (sair == 1)
				exit(1);
			else if (sair == 2)
			{
			}
			else
			{
				printf("Op��o n�o v�lida.\n");
			}
			break;

		default:
			system("cls");
			printf("Op��o n�o v�lida.\n");
		}
	}
	fclose(lista);
	fclose(arvore);
	return 0;
}
