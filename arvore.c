#include "arvore.h"

// Verifica se o arquivo existe
// Entrada: Nome do arquivo que sera verificado
// Retorno: Se o item existe ou nao
// Pre-condicao: Nenhuma
// Pos-condicao: Verificacao realizada
int checa_se_arquivo_existe(char *nome_arq)
{
	FILE *f;
	if ((f = fopen(nome_arq, "r+b")) == NULL)
	{
		fclose(f);
		return 0;
	}
	fclose(f);
	return 1;
}

// Abre o arquivo binario
// Entrada: O nome do arquivo que sera aberto
// Retorno: O arquivo aberto
// Pre-condicao: Nenhuma
// Pos-condicao: Arquivo aberto
FILE *abre_arquivo_binario(char *nome_arq)
{
	FILE *f = fopen(nome_arq, "rb+");
	if (f == NULL)
	{
		f = fopen(nome_arq, "wb");

		if (strcmp(nome_arq, "arvore"))
		{
			Header_Arvore *h_a = alocar_header_arvore();
			h_a->raiz = NULL_ARQ;
			h_a->livre = NULL_ARQ;
			h_a->topo = 0;
			escreve_header_arvore(f, h_a);
		}else if(strcmp(nome_arq, "lista")){
			Header_Lista *h_l = alocar_header_lista();
			h_l->livre = NULL_ARQ;
			h_l->topo = 0;
			escreve_header_lista(f, h_l);
		}

		fclose(f);
		f = fopen(nome_arq, "rb+");
	}

	return f;
}

// Aloca memoria para um header de arvore
// Entrada: Nenhuma
// Retorno: Header alocado
// Pre-condicao: Nenhuma
// Pos-condicao: Memoria para header alocada
Header_Arvore *alocar_header_arvore()
{
	Header_Arvore *h = malloc(sizeof(Header_Arvore));
	memset(h, 0, sizeof(Header_Arvore));
	return h;
}

// Aloca memoria para um no arvore
// Entrada: Nenhuma
// Retorno: No arvore alocado
// Pre-condicao: Nenhuma
// Pos-condicao: Memoria para no arvore alocada
No_Arvore *aloca_no_arvore()
{
	No_Arvore *no = malloc(sizeof(No_Arvore));
	memset(no, 0, sizeof(No_Arvore));
	return no;
}

// Realiza a leitura dos dados de um no arvore
// Entraa: Nenhuma
// Retorno: No arvore com os dados preenchidos
// Pre-condicao: Nenhuma
// Pos-condicao: Leitura de dados realizada
No_Arvore *scaneia_no_arvore()
{
	No_Arvore *no = aloca_no_arvore();
	printf("Codigo: ");
	scanf("%d", &no->codigo);
	return no;
}

// Imprime o header da arvore
// Entrada: Header que sera impresso
// Retorno: Nenhum
// Pre-condicao: Header nao nulo
// Pos-condicao: Header impresso
void imprime_header_arvore(Header_Arvore *h)
{
	printf("Raiz: %d\n", h->raiz);
	printf("Livre: %d\n", h->livre);
	printf("Topo: %d\n", h->topo);
}

// Imprime o no arvore
// Entrada: No arvore que sera impresso
// Retorno: Nenhum
// Pre-condicao: No arvore nao nulo
// Pos-condicao: No arvore impresso
void imprime_no_arvore(No_Arvore *no)
{
	printf("%d\n", no->codigo);
	printf("%d\n", no->esq);
	printf("%d\n", no->dir);
	printf("%d\n", no->pos_dados);
}

// Calcula o deslocamento necessario para chegar a posicao determinada na arvore
// Entrada: A posicao que deseja alcancar
// Retorno: A quantidade de memoria necessaria para chegar a posicao
// Pre-condicao: Nenhuma
// Pos-condicao: Deslocamento calculado
size_t calcula_offset_arvore(int pos)
{
	return sizeof(Header_Arvore) + pos * sizeof(No_Arvore);
}

// Escreve o header na arvore
// Entrada: O arquivo onde o header sera escrito, e o header que sera escrito
// Retorno: Nenhum
// Pre-condicao: Arquivo e header nao nulos
// Pos-condicao: Header escrito no arquivo
void escreve_header_arvore(FILE *f, Header_Arvore *h)
{
	fseek(f, 0, SEEK_SET);
	fwrite(h, sizeof(Header_Arvore), 1, f);
}

// Le o header de um arquivo com a arvore
// Entrada: O arquivo em que sera realizada a leitura
// Retorno: O header que foi lido
// Pre-condicao: Arquivo nao nulo
// Pos-condicao: Header lido
Header_Arvore *ler_header_arvore(FILE *f)
{
	Header_Arvore *h = alocar_header_arvore();
	fseek(f, 0, SEEK_SET);
	fread(h, sizeof(Header_Arvore), 1, f);
	return h;
}

// Retorna a posicao primeira posicao livre na arvore
// Entrada: O header que contem os dados da arvore
// Retorno: A primeira posicao livre
// Pre-condicao: Header nao nulo
// Pos-condicao: Posicao retornada
int retorna_posicao_livre_arvore(Header_Arvore *h)
{
	if (h->livre == NULL_ARQ)
	{
		return h->topo;
	}
	return h->livre;
}

// Escreve um no arvore no arquivo contendo a arvore
// Entrada: O arquivo onde o no arvore sera escrito, o no arvore que sera escrito e a posicao onde ele sera escrito
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: No arvore escrito no arquivo
void escreve_dado_na_arvore(FILE *f, No_Arvore *no, int pos)
{
	fseek(f, calcula_offset_arvore(pos), SEEK_SET);
	fwrite(no, sizeof(No_Arvore), 1, f);
}

// Le um no arvore no arquivo contendo a arvore
// Entrada: O arquivo contendo a arvore, e a posicao que sera lida
// Retorno: No arvore com os dados presentes na arvore
// Pre-condicao: Nenhuma
// Pos-condicao: No arvore lido da arvore
No_Arvore *ler_dado_na_arvore(FILE *f, int pos)
{
	No_Arvore *no = aloca_no_arvore();
	fseek(f, calcula_offset_arvore(pos), SEEK_SET);
	fread(no, sizeof(No_Arvore), 1, f);
	return no;
}

// Procura o pai de um determinado elemento a partir de seu codigo
// Entrada: O arquivo onde esta o elemento e o codigo do elemento
// Retorno: A posicao do pai do elemento
// Pre-condicao: Nenhuma
// Pos-condicao: Pai do elemento encontrado
int procura_no_pai_do_elemento_inserido(FILE *f, int codigo)
{
	Header_Arvore *h = ler_header_arvore(f);
	No_Arvore *no = ler_dado_na_arvore(f, h->raiz);
	int encontrado = 0, posicao_no = 0;
	posicao_no = h->raiz;
	while (!encontrado)
	{
		if (codigo > no->codigo && no->dir == NULL_ARQ)
		{
			encontrado = 1;
		}
		if (codigo < no->codigo && no->esq == NULL_ARQ)
		{
			encontrado = 1;
		}
		if (codigo > no->codigo && no->dir != NULL_ARQ)
		{
			posicao_no = no->dir;
			no = ler_dado_na_arvore(f, no->dir);
		}
		if (codigo < no->codigo && no->esq != NULL_ARQ)
		{
			posicao_no = no->esq;
			no = ler_dado_na_arvore(f, no->esq);
		}
	}
	free(no);
	free(h);
	return posicao_no;
}

// Insere um no arvore no arquivo contendo a arvore
// Entrada: O arquivo onde o no arvore sera inserido, e o no arvore que sera inserido
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: No arvore inserido no arquivo contendo a arvore
void inserir_no_arquivo_arvore(FILE *f, No_Arvore *no)
{
	int pos, pos_do_pai, i;
	no->esq = NULL_ARQ;
	no->dir = NULL_ARQ;
	Header_Arvore *h = ler_header_arvore(f);
	No_Arvore *no_aux; // No que vai ler o no vazio para poder atualizar a posicao vazia, e apos isso recebera o no pai do elemento inserido para atualiza-lo.
	if (h->raiz == NULL_ARQ && h->livre == NULL_ARQ)
	{
		h->topo = 1;
		no->pos_dados = 0;
		h->raiz = 0;

		escreve_dado_na_arvore(f, no, 0);
		escreve_header_arvore(f, h);

		free(h);
		free(no_aux);
		return;
	}
	if (h->raiz == NULL_ARQ && h->livre != NULL_ARQ)
	{
		h->raiz = h->livre;
		no_aux = ler_dado_na_arvore(f, h->livre);
		h->livre = no_aux->esq;
		no->pos_dados = h->raiz;

		escreve_dado_na_arvore(f, no, h->raiz);
		escreve_header_arvore(f, h);

		free(h);
		free(no_aux);
		return;
	}
	if (h->livre != NULL_ARQ)
	{
		pos = h->livre;
		no->pos_dados = pos;
		no_aux = ler_dado_na_arvore(f, pos);
		h->livre = no_aux->esq;
		pos_do_pai = procura_no_pai_do_elemento_inserido(f, no->codigo);
		no_aux = ler_dado_na_arvore(f, pos_do_pai);
		if (no->codigo > no_aux->codigo)
		{
			no_aux->dir = pos;
		}
		if (no->codigo <= no_aux->codigo)
		{
			no_aux->esq = pos;
		}

		escreve_dado_na_arvore(f, no, pos);
		escreve_dado_na_arvore(f, no_aux, pos_do_pai);
		escreve_header_arvore(f, h);

		free(h);
		free(no_aux);
		return;
	}
	if (h->livre == NULL_ARQ)
	{
		pos = h->topo;
		no->pos_dados = pos;
		h->topo += 1;
		pos_do_pai = procura_no_pai_do_elemento_inserido(f, no->codigo);
		no_aux = ler_dado_na_arvore(f, pos_do_pai);
		if (no->codigo > no_aux->codigo)
		{
			no_aux->dir = pos;
		}
		if (no->codigo <= no_aux->codigo)
		{
			no_aux->esq = pos;
		}

		escreve_dado_na_arvore(f, no, pos);
		escreve_dado_na_arvore(f, no_aux, pos_do_pai);
		escreve_header_arvore(f, h);

		free(h);
		free(no_aux);
		return;
	}
}

// Imprime a arvore presente no arquivo contendo a arvore
// Entrada: O arquivo que contem a arvore, a raiz da arvore e uma variavel para informar se o elemento que vai ser impresso eh a raiz
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: Arvore impressa
void imprime_arvore_arquivo(FILE *f, int raiz, int i)
{
	No_Arvore *no = ler_dado_na_arvore(f, raiz);
	if (no->codigo <= 0 && i == 0)
	{
		printf("A arvore esta vazia.\n");
		return;
	}
	if (!i)
	{
		printf("[");
	}
	else
	{
		printf(",[");
	}
	printf("%d", no->codigo);
	if (no->esq != NULL_ARQ)
	{
		imprime_arvore_arquivo(f, no->esq, 1);
	}
	if (no->esq == NULL_ARQ)
	{
		printf(",[]");
	}
	if (no->dir != NULL_ARQ)
	{
		imprime_arvore_arquivo(f, no->dir, 1);
	}
	if (no->dir == NULL_ARQ)
	{
		printf(",[]");
	}
	printf("]");

	free(no);
}

// Calcula a altura da arvore presente no arquivo
// Entrada: O arquivo que contem a arvore e a raiz da arvore
// Retorno: A altura da arvore
// Pre-condicao: Nenhuma
// Pos-condicao: Altura da arvore retornada
int calcula_altura_arvore(FILE *f, int raiz)
{
	No_Arvore *no = ler_dado_na_arvore(f, raiz);
	if (no->codigo > 0)
	{
		int tam_esq = 0, tam_dir = 0;
		tam_esq = calcula_altura_arvore(f, no->esq);
		tam_dir = calcula_altura_arvore(f, no->dir);
		free(no);
		if (tam_dir > tam_esq)
		{
			return tam_dir + 1;
		}
		else
		{
			return tam_esq + 1;
		}
	}
	free(no);
	return 0;
}

// Imprime um nivel da arvore presente no arquivo
// Entrada: O arquivo que contem a arvore, o nivel que sera imprimido, e a raiz da arvore
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: Nivel impresso
void imprime_nivel(FILE *f, int n, int raiz)
{
	No_Arvore *no = ler_dado_na_arvore(f, raiz);
	if (no->codigo > 0)
	{
		if (n == 0)
		{
			printf("%d ", no->codigo);
		}
		else
		{
			imprime_nivel(f, n - 1, no->esq);
			imprime_nivel(f, n - 1, no->dir);
		}
	}
	free(no);
}

// Imprime todos os niveis da arvore presente no arquivo
// Entrada: O arquivo que contem a arvore
// Retorno: Nenhum
// Pre-condicao: Nenhuma
// Pos-condicao: Arvore impressa
void imprime_por_nivel()
{
	FILE *arvore;
	arvore = abre_arquivo_binario("arvore");
	Header_Arvore *h = ler_header_arvore(arvore);	
	int n = calcula_altura_arvore(arvore, h->raiz);
	int i;
	if (h->raiz == NULL_ARQ)
	{
		printf("A arvore esta vazia\n");
		return;
	}
	for (i = 0; i < n; i++)
	{
		imprime_nivel(arvore, i, h->raiz);
		printf("\n");
	}
	free(h);
	fclose(arvore);
}

// Retorna a posicao de um no arvore no arquivo que contem a arvore a partir de seu codigo
// Entrada: O arquivo que contem a arvore, o codigo do elemento desejado e a raiz da arvore
// Retorno: A posicao do elemento no arquivo
// Pre-condicao: Nenhuma
// Pos-condicao: Posicao do elemento no arquivo retornada
int retorna_posicao_no_arquivo(FILE *f, int codigo, int raiz)
{
	int n = -1;
	No_Arvore *no = ler_dado_na_arvore(f, raiz);
	if (no->codigo == codigo)
	{
		n = raiz;
	}
	if (no->codigo < codigo)
	{
		n = retorna_posicao_no_arquivo(f, codigo, no->dir);
	}
	if (no->codigo > codigo)
	{
		n = retorna_posicao_no_arquivo(f, codigo, no->esq);
	}
	free(no);
	return n;
}

// Procura o no pai de um elemento que vai ser removido a partir de seu codigo e posicao
// Entrada: O arquivo que contem a arvore, o codigo do elemento que deseja encontrar o pai, e a posicao do elemento no arquivo
// Retorno: A posicao do pai do elemento no arquivo
// Pre-condicao: Arvore nao nula
// Pos-condicao: Posicao do pai do elemento retornada
int procura_no_pai_do_elemento_que_sera_removido(FILE *f, int codigo, int pos)
{
	Header_Arvore *h = ler_header_arvore(f);
	No_Arvore *no_aux, *no = ler_dado_na_arvore(f, h->raiz);
	if (codigo == no->codigo)
	{
		free(no);
		printf("A raiz nao possui no pai.\n");
		return -1;
	}
	while (no->esq != NULL_ARQ || no->dir != NULL_ARQ)
	{
		if (no->esq == pos)
		{
			free(no);
			return retorna_posicao_no_arquivo(f, no->codigo, h->raiz);
		}
		if (no->dir == pos)
		{
			free(no);
			return retorna_posicao_no_arquivo(f, no->codigo, h->raiz);
		}
		if (codigo > no->codigo)
		{
			no = ler_dado_na_arvore(f, no->dir);
		}
		else if (codigo < no->codigo)
		{
			no = ler_dado_na_arvore(f, no->esq);
		}
	}
	free(no);
	printf("Elemento nao encontrado.\n");
	return -1;
}

// Retorna posicao do elemento com o maior codigo entre os filhos da esquerda
// Entrada: O arquivo que contem a arvore, e o filho a esquerda do elemento
// Retorno: Posicao do elemento desejado
// Pre-condicao: Filho a esquerda nao nulo
// Pos-condicao: Posicao do elemento retornada
int retorna_posicao_maximo(FILE *f, int raiz)
{
	No_Arvore *no = ler_dado_na_arvore(f, raiz);
	Header_Arvore *h = ler_header_arvore(f);
	int i = h->raiz;
	while (no->dir != NULL_ARQ)
	{
		no = ler_dado_na_arvore(f, no->dir);
	}
	free(no);
	free(h);
	return retorna_posicao_no_arquivo(f, no->codigo, i);
}

// Retorna posicao do elemento com o menor codigo entre os filhos da direita
// Entrada: O arquivo que contem a arvore, e o filho a direita do elemento
// Retorno: Posicao do elemento desejado
// Pre-condicao: Filho a direita nao nulo
// Pos-condicao: Posicao do elemento retornada
int retorna_posicao_minimo(FILE *f, int raiz)
{
	No_Arvore *no = ler_dado_na_arvore(f, raiz);
	Header_Arvore *h = ler_header_arvore(f);
	int i = h->raiz;
	while (no->esq != NULL_ARQ)
	{
		no = ler_dado_na_arvore(f, no->esq);
	}
	free(no);
	free(h);
	return retorna_posicao_no_arquivo(f, no->codigo, i);
}

// Remove um elemento no arquivo que contem a arvore a partir do seu codigo
// Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e o codigo do elemento
// Retorno: Nenhum
// Pre-condicao: Arvore e lista nao nulas
// Pos-condicao: Elemento removido
void remove_no_arquivo_arvore(FILE *f, FILE *lista, int codigo)
{
	Header_Arvore *h = ler_header_arvore(f);
	int i, j, sub, pai_original;
	No_Arvore *no = ler_dado_na_arvore(f, h->raiz);
	No_Arvore *no_aux = aloca_no_arvore();
	No_Arvore *no_para_substituir;
	No_Arvore *no_pai;
	No_Arvore *no_pai_original;
	no_aux->codigo = -1;
	no_aux->esq = h->livre;
	no_aux->dir = -1;
	no_aux->pos_dados = -1;

	if (no->codigo == codigo && no->esq != NULL_ARQ)
	{
		alterar_livre_na_lista(lista, h->raiz);
		no_para_substituir = ler_dado_na_arvore(f, retorna_posicao_maximo(f, no->esq));
		j = retorna_posicao_no_arquivo(f, no_para_substituir->codigo, h->raiz);
		no_pai = ler_dado_na_arvore(f, procura_no_pai_do_elemento_que_sera_removido(f, no_para_substituir->codigo, j));
		if (no_para_substituir->esq != NULL_ARQ)
		{
			no_pai->dir = no_para_substituir->esq;
		}
		else
		{
			no_pai->dir = NULL_ARQ;
		}
		if (j != no->dir)
		{
			no_para_substituir->dir = no->dir;
		}
		if (j != no->esq)
		{
			no_para_substituir->esq = no->esq;
		}
		i = retorna_posicao_no_arquivo(f, no_para_substituir->codigo, h->raiz);
		escreve_dado_na_arvore(f, no_pai, procura_no_pai_do_elemento_que_sera_removido(f, no_para_substituir->codigo, j));
		h->livre = h->raiz;
		h->raiz = i;
		escreve_dado_na_arvore(f, no_para_substituir, h->raiz);
		escreve_dado_na_arvore(f, no_aux, h->livre);
		escreve_header_arvore(f, h);
		return;
	}
	else if (no->codigo == codigo && no->esq == NULL_ARQ && no->dir != NULL_ARQ)
	{
		alterar_livre_na_lista(lista, h->raiz);
		no_para_substituir = ler_dado_na_arvore(f, retorna_posicao_minimo(f, no->dir));
		j = retorna_posicao_no_arquivo(f, no_para_substituir->codigo, h->raiz);
		no_pai = ler_dado_na_arvore(f, procura_no_pai_do_elemento_que_sera_removido(f, no_para_substituir->codigo, j));
		if (no_para_substituir->dir != NULL_ARQ)
		{
			no_pai->esq = no_para_substituir->dir;
		}
		else
		{
			no_pai->esq = NULL_ARQ;
		}
		if (j != no->dir)
		{
			no_para_substituir->dir = no->dir;
		}
		if (j != no->esq)
		{
			no_para_substituir->esq = no->esq;
		}
		i = retorna_posicao_no_arquivo(f, no_para_substituir->codigo, h->raiz);
		escreve_dado_na_arvore(f, no_pai, procura_no_pai_do_elemento_que_sera_removido(f, no_para_substituir->codigo, j));
		h->livre = h->raiz;
		h->raiz = i;
		escreve_dado_na_arvore(f, no_para_substituir, h->raiz);
		escreve_dado_na_arvore(f, no_aux, h->livre);
		escreve_header_arvore(f, h);
		return;
	}
	else if (no->codigo == codigo && no->esq == NULL_ARQ && no->dir == NULL_ARQ)
	{
		alterar_livre_na_lista(lista, h->raiz);
		h->livre = h->raiz;
		h->raiz = -1;
		escreve_dado_na_arvore(f, no_aux, h->livre);
		escreve_header_arvore(f, h);
		return;
	}
	else
	{
		while (no->codigo != codigo)
		{
			if (no->codigo < codigo)
			{
				no = ler_dado_na_arvore(f, no->dir);
			}
			if (no->codigo > codigo)
			{
				no = ler_dado_na_arvore(f, no->esq);
			}
		}
		if (no->esq == NULL_ARQ && no->dir == NULL_ARQ)
		{
			i = retorna_posicao_no_arquivo(f, no->codigo, h->raiz);
			alterar_livre_na_lista(lista, i);
			j = procura_no_pai_do_elemento_que_sera_removido(f, no->codigo, i);
			no_pai = ler_dado_na_arvore(f, j);
			if (no_pai->esq == i)
			{
				no_pai->esq = NULL_ARQ;
			}
			if (no_pai->dir == i)
			{
				no_pai->dir = NULL_ARQ;
			}
			h->livre = i;
			escreve_dado_na_arvore(f, no_aux, i);
			escreve_dado_na_arvore(f, no_pai, j);
			escreve_header_arvore(f, h);
			return;
		}
		if (no->esq != NULL_ARQ)
		{ // ALTERAR PAI DO NO SUBSTITUIDO E DO NO REMOVIDO
			i = retorna_posicao_no_arquivo(f, no->codigo, h->raiz);
			alterar_livre_na_lista(lista, i);
			pai_original = procura_no_pai_do_elemento_que_sera_removido(f, no->codigo, i);
			sub = retorna_posicao_maximo(f, no->esq);
			h->livre = i;
			no_pai_original = ler_dado_na_arvore(f, pai_original);
			if (no_pai_original->esq == i)
			{
				no_pai_original->esq = sub;
			}
			if (no_pai_original->dir == i)
			{
				no_pai_original->dir = sub;
			}
			no_para_substituir = ler_dado_na_arvore(f, sub);
			j = procura_no_pai_do_elemento_que_sera_removido(f, no_para_substituir->codigo, sub);
			no_pai = ler_dado_na_arvore(f, j);
			if (no_para_substituir->esq != NULL_ARQ)
			{
				no_pai->dir = no_para_substituir->esq;
			}
			else
			{
				no_pai->dir = NULL_ARQ;
			}
			if (no->esq != sub)
			{
				no_para_substituir->esq = no->esq;
			}
			if (no->dir != sub)
			{
				no_para_substituir->dir = no->dir;
			}
			escreve_dado_na_arvore(f, no_pai, j);
			escreve_dado_na_arvore(f, no_para_substituir, sub);
			escreve_dado_na_arvore(f, no_aux, i);
			escreve_dado_na_arvore(f, no_pai_original, pai_original);
			escreve_header_arvore(f, h);
			return;
		}
		if (no->esq == NULL_ARQ && no->dir != NULL_ARQ)
		{ // ALGO ERRADO CHECA AI.
			i = retorna_posicao_no_arquivo(f, no->codigo, h->raiz);
			alterar_livre_na_lista(lista, i);
			pai_original = procura_no_pai_do_elemento_que_sera_removido(f, no->codigo, i);
			sub = retorna_posicao_minimo(f, no->dir);
			h->livre = i;
			no_pai_original = ler_dado_na_arvore(f, pai_original);
			if (no_pai_original->esq == i)
			{
				no_pai_original->esq = sub;
			}
			if (no_pai_original->dir == i)
			{
				no_pai_original->dir = sub;
			}
			no_para_substituir = ler_dado_na_arvore(f, sub);
			j = procura_no_pai_do_elemento_que_sera_removido(f, no_para_substituir->codigo, sub);
			no_pai = ler_dado_na_arvore(f, j);
			if (no_para_substituir->dir != NULL_ARQ)
			{
				no_pai->esq = no_para_substituir->dir;
			}
			else
			{
				no_pai->esq = NULL_ARQ;
			}
			if (no->esq != sub)
			{
				no_para_substituir->esq = no->esq;
			}
			if (no->dir != sub)
			{
				no_para_substituir->dir = no->dir;
			}
			escreve_dado_na_arvore(f, no_pai, j);
			escreve_dado_na_arvore(f, no_para_substituir, sub);
			escreve_dado_na_arvore(f, no_aux, i);
			escreve_dado_na_arvore(f, no_pai_original, pai_original);
			escreve_header_arvore(f, h);
			return;
		}
	}
}

// Checa se ja existe um elemento na arvore com determinado codigo
// Entrada: O arquivo que contem a arvore e o codigo que sera buscado
// Retorno: 1 se o elemento ja esta presente na arvore e 0 se nao estiver
// Pre-condicao: Nenhuma
// Pos-condicao: Checagem realizada
int checa_se_codigo_ja_esta_na_arvore(FILE *f, int codigo)
{
	int i = 0, parada = 0;
	Header_Arvore *h = ler_header_arvore(f);
	if (h->raiz == NULL_ARQ)
	{
		return 0;
	}
	No_Arvore *no = ler_dado_na_arvore(f, h->raiz);
	if (no->codigo == codigo)
	{
		i = 1;
	}
	while (!parada)
	{
		if (no->codigo == codigo)
		{
			i = 1;
			parada = 1;
		}
		if (no->codigo > codigo && no->esq != NULL_ARQ)
		{
			no = ler_dado_na_arvore(f, no->esq);
		}
		if (no->codigo < codigo && no->dir != NULL_ARQ)
		{
			no = ler_dado_na_arvore(f, no->dir);
		}
		if (no->codigo > codigo && no->esq == NULL_ARQ)
		{
			parada = 1;
		}
		if (no->codigo < codigo && no->dir == NULL_ARQ)
		{
			parada = 1;
		}
	}
	return i;
}

// Altera o numero de exemplares na lista com as informacoes de um item presente na arvore a partir de seu codigo
// Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e o codigo do item que sofrera a alteracao
// Retorno: Nenhum
// Pre-condicao: Codigo presente na arvore
// Pos-condicao: Numero de exemplares do item alterado
void altera_preco(FILE *arvore, FILE *lista, int codigo)
{
	Header_Arvore *h = ler_header_arvore(arvore);
	int i = retorna_posicao_no_arquivo(arvore, codigo, h->raiz);
	No_Arvore *no = ler_dado_na_arvore(arvore, i);
	Produto *p = ler_produto_na_lista(lista, no->pos_dados);
	printf("Entre com o preço.\n");
	scanf("%lf", &p->preco);
	escreve_produto_na_lista(lista, p, no->pos_dados);
	free(h);
	free(no);
	free(p);
}

void altera_estoque(FILE *arvore, FILE *lista, int codigo)
{
	Header_Arvore *h = ler_header_arvore(arvore);
	int i = retorna_posicao_no_arquivo(arvore, codigo, h->raiz);
	No_Arvore *no = ler_dado_na_arvore(arvore, i);
	Produto *p = ler_produto_na_lista(lista, no->pos_dados);
	printf("Entre com o estoque.\n");
	scanf("%d", &p->estoque);
	escreve_produto_na_lista(lista, p, no->pos_dados);
	free(h);
	free(no);
	free(p);
}


// Busca e imprime os dados de um item presente na arvore a partir de seu codigo
// Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e o codigo do item cujas informacoes serao procuradas
// Retorno: Nenhum
// Pre-condicao: Codigo presente na arvore
// Pos-condicao: Dados do item desejado impressos
void busca_dados_do_produto(FILE *arvore, FILE *lista, int codigo)
{
	Header_Arvore *h = ler_header_arvore(arvore);
	int i = retorna_posicao_no_arquivo(arvore, codigo, h->raiz);
	No_Arvore *no = ler_dado_na_arvore(arvore, i);
	Produto *p = ler_produto_na_lista(lista, no->pos_dados);
	imprime_produto(p);
	free(h);
	free(no);
	free(p);
}

// Imprime os dados de todos os livros presentes na arvore
// Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e a raiz da arvore
// Retorno: Nenhum
// Pre-condicao: Arvore nao nula
// Pos-condicao: Dados impressos
void imprime_todos_produto(FILE *arvore, FILE *lista, int raiz)
{
	No_Arvore *no = ler_dado_na_arvore(arvore, raiz);
	Header_Arvore *h = ler_header_arvore(arvore);
	Produto *p;
	int i;
	if (no->esq != NULL_ARQ)
	{
		imprime_todos_produto(arvore, lista, no->esq);
	}
	i = retorna_posicao_no_arquivo(arvore, no->codigo, h->raiz);
	no = ler_dado_na_arvore(arvore, i);
	p = ler_produto_na_lista(lista, no->pos_dados);
	printf("\n");
	imprime_produto(p);
	printf("\n");
	if (no->dir != NULL_ARQ)
	{
		imprime_todos_produto(arvore, lista, no->dir);
	}
}
