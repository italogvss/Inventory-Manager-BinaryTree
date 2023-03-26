#include "interface.c"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	init();

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
