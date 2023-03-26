#include "lista.h"
#include <locale.h>

Produto *aloca_produto()
{
	Produto *p = malloc(sizeof(Produto));
	memset(p, 0, sizeof(Produto));
	return p;
}

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
	fflush(stdin);
	return p;
}

Header_L *alocar_header_lista()
{
	Header_L *h = malloc(sizeof(Header_L));
	memset(h, 0, sizeof(Header_L));
	return h;
}

void imprime_header_lista(Header_L *h)
{
	printf("Livre: %d\n", h->livre);
	printf("Topo: %d\n", h->topo);
}

size_t calcula_offset_lista(int pos)
{
	return sizeof(Header_L) + pos * sizeof(Produto);
}

void escreve_header_lista(FILE *f, Header_L *h)
{
	fseek(f, 0, SEEK_SET);
	fwrite(h, sizeof(Header_L), 1, f);
}

Header_L *ler_header_lista(FILE *f)
{
	Header_L *h = alocar_header_lista();
	fseek(f, 0, SEEK_SET);
	fread(h, sizeof(Header_L), 1, f);
	return h;
}

int retorna_posicao_livre_lista(Header_L *h)
{
	if (h->livre == NULL_ARQ)
	{
		return h->topo;
	}
	return h->livre;
}

void escreve_produto_na_lista(FILE *f, Produto *p, int pos)
{
	fseek(f, calcula_offset_lista(pos), SEEK_SET);
	fwrite(p, sizeof(Produto), 1, f);
}

Produto *ler_produto_na_lista(FILE *f, int pos)
{
	Produto *p = aloca_produto();
	fseek(f, calcula_offset_lista(pos), SEEK_SET);
	fread(p, sizeof(Produto), 1, f);
	return p;
}

int inserir_dados_do_produto_no_arquivo(FILE *f, Produto *p)
{
	Header_L *h = ler_header_lista(f);
	Produto *paux;
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
		paux = ler_produto_na_lista(f, h->livre);
		pos = h->livre;
		h->livre = paux->codigo;
		escreve_produto_na_lista(f, p, pos);
		escreve_header_lista(f, h);
		return pos;
	}
}

void alterar_livre_na_lista(FILE *f, int pos)
{
	Header_L *h = ler_header_lista(f);
	Produto *p = aloca_produto();
	p->codigo = h->livre;
	h->livre = pos;
	escreve_header_lista(f, h);
	escreve_produto_na_lista(f, p, pos);
	free(p);
	free(h);
}

void ler_linha_txt(FILE *f, FILE *arvore, FILE *lista)
{
	No_A *no = aloca_no_arvore();
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

			Header_A *h = ler_header_arvore(arvore);
			int i = retorna_posicao_no_arquivo(arvore, cod, h->raiz);
			No_A *no = ler_dado_na_arvore(arvore, i);
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

void abrir_arquivo_texto(char *nome_arq, FILE *arvore, FILE *lista)
{
	FILE *f;
	if ((f = fopen(nome_arq, "r")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return;
	}
	while (!feof(f))
	{
		ler_linha_txt(f, arvore, lista);
	}
	fclose(f);
}
