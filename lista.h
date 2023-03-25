#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"

struct header_lista{
	int livre;
	int topo;
}typedef Header_Lista;

struct item{
	int codigo;
	char nome[100];
	char marca[100];
	int preco;	
}typedef Produto;

//Aloca memoria para um livro
//Entrada: Nenhuma
//Retorno: Produto alocado
//Pre-condicao: Nenhuma
//Pos-condicao: Memoria para livro alocada
Produto *aloca_produto();

//Realiza a leitura dos dados de um livro
//Entrada: Nenhuma
//Retorno: Produto com os dados preenchidos
//Pre-condicao: Nenhuma
//Pos-condicao: Leitura de dados realizada
Produto *ler_dados_produto();

//Imprime o livro
//Entrada: Produto que sera impresso
//Retorno: Nenhum
//Pre-condicao: Produto nao nulo
//Pos-condicao: Produto impresso
void imprime_produto(Produto *l);

//Aloca memoria para um header de lista
//Entrada: Nenhuma
//Retorno: Header alocado
//Pre-condicao: Nenhuma
//Pos-condicao: Memoria para header alocada
Header_Lista *alocar_header_lista();

//Imprime o header da lista
//Entrada: Header que sera impresso
//Retorno: Nenhum
//Pre-condicao: Header nao nulo
//Pos-condicao: Header impresso
void imprime_header_lista(Header_Lista *h);

//Calcula o deslocamento necessario para chegar a uma determinada posicao na lista
//Entrada: A posicao que deseja alcancar
//Retorno: A quantidade de memoria necessaria para chegar a posicao
//Pre-condicao: Nenhuma
//Pos-condicao: Deslocamento calculado
size_t calcula_offset_lista(int pos);

//Escreve o header na lista
//Entrada: O arquivo onde o header sera escrito, e o header que sera escrito
//Retorno: Nenhum
//Pre-condicao: Arquivo e header nao nulos
//Pos-condicao: Header escrito no arquivo
void escreve_header_lista(FILE *f, Header_Lista *h);

//Le o header de um arquivo com a lista
//Entrada: O arquivo em que sera realizada a leitura
//Retorno: O header que foi lido
//Pre-condicao: Arquivo nao nulo
//Pos-condicao: Header lido
Header_Lista *ler_header_lista(FILE *f);

//Retorna a primeira posicao livre na lista
//Entrada: O header que contem os dados da lista
//Retorno: A primeira posicao livre
//Pre-condicao: Header nao nulo
//Pos-condicao: Posicao retornada
int retorna_posicao_livre_lista(Header_Lista *h);	

//Escreve um livro na lista contendo os dados dos livros
//Entrada: O arquivo onde o livro sera escrito, o livro que sera escrito e a posicao onde ele sera escrito
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: Produto escrito no arquivo
void escreve_produto_na_lista(FILE *f, Produto *l, int pos);

//Le um livro no arquivo contendo a lista com as informacoes dos livros
//Entrada: O arquivo contendo a lista com as informacoes dos livros, e a posicao que sera lida
//Retorno: Produto com os dados presentes na lista
//Pre-condicao: Nenhuma
//Pos-condicao: Produto lido da lista
Produto *ler_produto_na_lista(FILE *f, int pos);

//Insere os dados de um livro no arquivo contendo a lista com as informacoes dos livros
//Entrada: O arquivo contendo a lista com as informacoes dos livros e o livro que sera inserido
//Retorno: A posicao onde o livro foi inserido
//Pre-condicao: Nenhuma
//Pos-condicao: Produto inserido no arquivo contendo a lista
int inserir_dados_do_produto_no_arquivo(FILE *f, Produto *l);

//Le uma linha de um arquivo txt enquanto armazena seus dados em um livro
//Entrada: O arquivo cuja linha sera lida
//Retorno: Produto com os dados preenchidos
//Pre-condicao: Nenhuma
//Pos-condicao: Linha lida e seus dados armazenados em um livro
Produto *ler_linha_txt(FILE *f);

//Le os dados de um arquivo txt e insere-os nos arquivos contendo a arvore e a lista com as informacoes dos livros
//Entrada: Nome do arquivo txt que sera lido, o arquivo contendo a arvore e o arquivo contendo a lista com as informacoes dos livros
//Retorno: Nenhum
//Pre-condicao: Nome do arquivo nao nulo
//Pos-condicao: Arquivo lido
void ler_dados_do_arquivo_txt(char *nome_arq, FILE *arvore, FILE *lista);

//Altera a posicao livre no cabecalho do arquivo que contem as informacoes dos livros
//Entrada: O arquivo contendo a lista com as informacoes dos livros e o valor da nova posicao livre para ser alterada
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: Posicao livre no cabecalho alterada
void alterar_livre_na_lista(FILE *f, int pos);

//Preenche um vetor com os titulos dos livros presentes na arvore
//Entrada: O arquivo contendo a arvore, o arquivo contendo a lista com as informacoes dos livros, o vetor que sera preenchido e a raiz da arvore
//Retorno: Nenhum
//Pre-condicao: Arvore nao vazia
//Pos-condicao: Vetor preenchido
void preenche_vetor(FILE *arvore, FILE *lista, Produto vet[], int raiz);

//Ordena um vetor de strings por ordem alfabetica utilizando o metodo QuickSort
//Entrada: O vetor que sera ordenado, a primeira posicao do vetor e a ultima posicao do vetor
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: Vetor ordenado alfabeticamente
void quick_sort(Produto vet[], int inicio, int fim);

//printa o menu inicial
//entrada = nenhuma
//retorno = op��o do menu escolhida pelo usuario
//Pr�-condi��o = nenhum
//p�s-condi��o = nenhum
int menuInicial();

//printa o menu de sa�da do programa
//entrada = nenhuma
//retorno = op��o do menu escolhida pelo usuario
//Pr�-condi��o = nenhum
//p�s-condi��o = nenhum
int sairPrograma();

#endif
