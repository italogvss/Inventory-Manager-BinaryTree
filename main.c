#include "interface.c"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	FILE *arvore, *lista;
	Header_Arvore *h_a = alocar_header_arvore();
	Header_Lista *h_l = alocar_header_lista();
	lista = abre_arquivo_binario("lista");
	arvore = abre_arquivo_binario("arvore");
	system("cls");
	printf("inicio programa \n");
	h_a = ler_header_arvore(arvore);
	h_l = ler_header_lista(lista);
	imprime_header_arvore(h_a);
	imprime_header_lista(h_l);

	while (1)
	{

		int i = menuInicial();
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

			menu_alterar_preco();
			break;
		case 4:
			system("cls");

			menu_alterar_estoque();
			break;

		case 5:
			system("cls");

			menu_remover(arvore, lista);
			break;

		case 6:

			system("cls");
			menu_buscar(arvore, lista);
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
			int sair = sairPrograma();
			if (sair == 1)
				exit(1);
			else if (sair == 2)
			{
			}
			else
			{
				printf("Opção invalida.\n");
			}
			break;

		default:
			system("cls");
			printf("Opção Invalida.\n");
		}
	}
	return 0;
}
