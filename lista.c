#include "lista.h"
#include <locale.h>

// Aloca memoria para um item
// Entrada: Nenhuma
// Retorno: Produto alocado
// Pre-condicao: Nenhuma
// Pos-condicao: Memoria para item alocada
Produto *aloca_produto()
{
	Produto *p = malloc(sizeof(Produto));
	memset(p, 0, sizeof(Produto));
	return p;
}

// Realiza a leitura dos dados de um item
// Entrada: Nenhuma
// Retorno: Produto com os dados preenchidos
// Pre-condicao: Nenhuma
// Pos-condicao: Leitura de dados realizada
Produto *ler_dados_produto()
{
	Produto *p = aloca_produto();
	printf("Entre com os dados do produto:\n");
	printf("Codigo: ");
	scanf("%d", &p->codigo);
	fflush(stdin);
	printf("Nome: ");
	scanf("%[^\n]%*c", p->nome);
	printf("Marca: ");
	scanf("%[^\n]%*c", p->marca);
	printf("Categoria: ");
	scanf("%[^\n]%*c", p->categoria);
	printf("Estoque: ");
	scanf("%d", &p->estoque);
	fflush(stdin);
	printf("Preco: ");
	scanf("%lf", &p->preco);
	return p;
}



// Aloca memoria para um header de lista
// Entrada: Nenhuma
// Retorno: Header alocado
// Pre-condicao: Nenhuma
// Pos-condicao: Memoria para header alocada
Header_Lista *alocar_header_lista()
{
	Header_Lista *h = malloc(sizeof(Header_Lista));
	memset(h, 0, sizeof(Header_Lista));
	return h;
}

// Imprime o header da lista
// Entrada: Header que sera impresso
// Retorno: Nenhum
// Pre-condicao: Header nao nulo
// Pos-condicao: Header impresso
void imprime_header_lista(Header_Lista *h)
{
	printf("Livre: %d\n", h->livre);
	printf("Topo: %d\n", h->topo);
}

// Calcula o deslocamento necessario para chegar a uma determinada posicao na lista
// Entrada: A posicao que deseja alcancar
// Retorno: A quantidade de memoria necessaria para chegar a posicao
// Pre-condicao: Nenhuma
// Pos-condicao: Deslocamento calculado
size_t calcula_offset_lista(int pos)
{
	return sizeof(Header_Lista) + pos * sizeof(Produto);
}

// Escreve o header na lista
// Entrada: O arquivo onde o header sera escrito, e o header que sera escrito
// Retorno: Nenhum
// Pre-condicao: Arquivo e header nao nulos
// Pos-condicao: Header escrito no arquivo
void escreve_header_lista(FILE *f, Header_Lista *h)
{
	fseek(f, 0, SEEK_SET);
	fwrite(h, sizeof(Header_Lista), 1, f);
}

// Le o header de um arquivo com a lista
// Entrada: O arquivo em que sera realizada a leitura
// Retorno: O header que foi lido
// Pre-condicao: Arquivo nao nulo
// Pos-condicao: Header lido
Header_Lista *ler_header_lista(FILE *f)
{
	Header_Lista *h = alocar_header_lista();
	fseek(f, 0, SEEK_SET);
	fread(h, sizeof(Header_Lista), 1, f);
	return h;
}

// Retorna a primeira posicao livre na lista
// Entrada: O header que contem os dados da lista
// Retorno: A primeira posicao livre
// Pre-condicao: Header nao nulo
// Pos-condicao: Posicao retornada
int retorna_posicao_livre_lista(Header_Lista *h)
{
	if (h->livre == NULL_ARQ)
	{
		return h->topo;
	}
	return h->livre;
}

// Escreve um item na lista contendo os dados dos livros
// Entrada: O arquivo onde o item sera escrito, o item que sera escrito e a posicao onde ele sera escrito
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: Produto escrito no arquivo
void escreve_produto_na_lista(FILE *f, Produto *p, int pos)
{
	fseek(f, calcula_offset_lista(pos), SEEK_SET);
	fwrite(p, sizeof(Produto), 1, f);
}

// Le um item no arquivo contendo a lista com as informacoes dos livros
// Entrada: O arquivo contendo a lista com as informacoes dos livros, e a posicao que sera lida
// Retorno: Produto com os dados presentes na lista
// Pre-condicao: Nenhuma
// Pos-condicao: Produto lido da lista
Produto *ler_produto_na_lista(FILE *f, int pos)
{
	Produto *p = aloca_produto();
	fseek(f, calcula_offset_lista(pos), SEEK_SET);
	fread(p, sizeof(Produto), 1, f);
	return p;
}

// Insere os dados de um item no arquivo contendo a lista com as informacoes dos livros
// Entrada: O arquivo contendo a lista com as informacoes dos livros e o item que sera inserido
// Retorno: A posicao onde o item foi inserido
// Pre-condicao: Nenhuma
// Pos-condicao: Produto inserido no arquivo contendo a lista
int inserir_dados_do_produto_no_arquivo(FILE *f, Produto *p)
{
	Header_Lista *h = ler_header_lista(f);
	Produto *l_aux;
	int pos;
	if (h->livre == NULL_ARQ)
	{
		escreve_produto_na_lista(f, p, h->topo);
		pos = h->topo;
		h->topo += 1;
		escreve_header_lista(f, h);
		return pos;
	}
	if (h->livre != NULL_ARQ)
	{
		l_aux = ler_produto_na_lista(f, h->livre);
		pos = h->livre;
		h->livre = l_aux->codigo;
		escreve_produto_na_lista(f, p, pos);
		escreve_header_lista(f, h);
		return pos;
	}
}

// Altera a posicao livre no cabecalho do arquivo que contem as informacoes dos livros
// Entrada: O arquivo contendo a lista com as informacoes dos livros e o valor da nova posicao livre para ser alterada
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: Posicao livre no cabecalho alterada
void alterar_livre_na_lista(FILE *f, int pos)
{
	Header_Lista *h = ler_header_lista(f);
	Produto *aux = aloca_produto();
	aux->codigo = h->livre;
	h->livre = pos;
	escreve_header_lista(f, h);
	escreve_produto_na_lista(f, aux, pos);
	free(aux);
	free(h);
}

// Le uma linha de um arquivo txt enquanto armazena seus dados em um item
// Entrada: O arquivo cuja linha sera lida
// Retorno: Produto com os dados preenchidos
// Pre-condicao: Nenhuma
// Pos-condicao: Linha lida e seus dados armazenados em um item
void ler_linha_txt(FILE *f, FILE *arvore, FILE *lista)
{
	Produto *p = aloca_produto();
	No_Arvore *no = aloca_no_arvore();
	int i = 0;
	char str[255];
	char op[2];

	fscanf(f, " %[^;];", op); // Operação
	printf("\n \n %s \n \n", op);
	if (strcmp(op, "I"))
	{

		fscanf(f, " %[^;];", str); // Código do item

		p->codigo = atoi(str);

		fscanf(f, " %[^;];", str); // Nome do item

		strcpy(p->nome, str);

		fscanf(f, " %[^;];", str); // marca do item

		strcpy(p->marca, str);

		fscanf(f, " %[^;];", str); // categoria do item

		strcpy(p->categoria, str);

		fscanf(f, " %[^;]; ", str); // Numero estoque

		p->estoque = atoi(str);

		fscanf(f, " %[^\n] ", str);

		if (checa_se_codigo_ja_esta_na_arvore(arvore, p->codigo))
		{
			printf("Produto ja esta cadastrado.\n");
		}
		else
		{
			imprime_produto(p);
			i = inserir_dados_do_produto_no_arquivo(lista, p);
			no->codigo = p->codigo;
			no->pos_dados = i;
			inserir_no_arquivo_arvore(arvore, no);
		}
	}
	else if (strcmp(op, "A"))
	{
	}
	else if (strcmp(op, "R"))
	{
	}
}

void lerlinha(FILE *f, FILE *arvore, FILE *lista)
{
	No_Arvore *no = aloca_no_arvore();
	Produto *p = aloca_produto();
	char linha[150];
	char *token;

	while (fgets(linha, sizeof(linha), f))
	{

		// remove o caractere de quebra de linha do final da string
		linha[strcspn(linha, "\n")] = 0;

		// separa a linha em campos usando o separador ";"
		token = strtok(linha, ";");
		if (strcmp(token, "I") == 0)
		{
			// operação de inserção
			p->codigo = atoi(strtok(NULL, ";"));
			strcpy(p->nome, strtok(NULL, ";"));
			strcpy(p->marca, strtok(NULL, ";"));
			strcpy(p->categoria, strtok(NULL, ";"));
			p->estoque = atoi(strtok(NULL, ";"));
			p->preco = atof(strtok(NULL, ";"));

			if (checa_se_codigo_ja_esta_na_arvore(arvore, p->codigo))
			{
				printf("Produto ja esta cadastrado.\n");
			}
			else
			{
				imprime_produto(p);
				int i = inserir_dados_do_produto_no_arquivo(lista, p);
				no->codigo = p->codigo;
				no->pos_dados = i;
				inserir_no_arquivo_arvore(arvore, no);
			}
		}
		else if (strcmp(token, "R") == 0)
		{
			remove_no_arquivo_arvore(arvore, lista, atoi(strtok(NULL, ";")));
		}
		else if (strcmp(token, "A") == 0)
		{

			int cod = atoi(strtok(NULL, ";"));

			Header_Arvore *h = ler_header_arvore(arvore);
			int i = retorna_posicao_no_arquivo(arvore, cod, h->raiz);
			No_Arvore *no = ler_dado_na_arvore(arvore, i);
			Produto *p = ler_produto_na_lista(lista, no->pos_dados);

			int estoque = 0, preco = 0;

			token = strtok(NULL, ";");
			if (token != NULL && strlen(token) > 0)
			{
				p->estoque = atoi(token);
			}
			token = strtok(NULL, ";");
			if (token != NULL && strlen(token) > 0)
			{
				p->preco = atof(token);
			}

			escreve_produto_na_lista(lista, p, no->pos_dados);
		}
		else
		{
			// operação desconhecida
			printf("Operacao desconhecida: %s\n", token);
		}
	}
}

// Le os dados de um arquivo txt e insere-os nos arquivos contendo a arvore e a lista com as informacoes dos livros
// Entrada: Nome do arquivo txt que sera lido, o arquivo contendo a arvore e o arquivo contendo a lista com as informacoes dos livros
// Retorno: Nenhum
// Pre-condicao: Nome do arquivo nao nulo
// Pos-condicao: Arquivo lido
void ler_dados_do_arquivo_txt(char *nome_arq, FILE *arvore, FILE *lista)
{
	FILE *f;
	Produto *p;
	No_Arvore *no = aloca_no_arvore();
	int i;
	if ((f = fopen(nome_arq, "r")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	while (!feof(f))
	{
		// ler_linha_txt(f, arvore, lista);
		lerlinha(f, arvore, lista);
	}

	free(p);
	free(no);
	fclose(f);
}
