#include "interface.c"
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");
	init();

	while (1)
	{

		int op = menu();
		fflush(stdin);

		switch (op)
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

			menu_remover();
			break;

		case 6:

			system("cls");
			menu_buscar();
			break;

		case 7:
			system("cls");
			imprime_por_nivel();
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
				exit(1);			
			break;

		default:
			system("cls");
			printf("Opcao Invalida.\n");
		}
	}
	return 0;
}
