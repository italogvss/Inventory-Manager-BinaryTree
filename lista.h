#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

struct h_L{
	int livre;
	int topo;
}typedef Header_L;

struct item{
	int codigo;
	char nome[50];
	char marca[30];
	char categoria[50];
	int estoque;
	double preco;	
}typedef Produto;

/*
 * @brief Aloca memoria para um produto
 * @pre nenhuma
 * @post Memoria para produto alocada
 */
Produto *aloca_produto();

/*
 * @brief Realiza a entrada dos dados de um produto
 * @return Produto com dados preenchidos
 * @pre Nenhuma
 * @post Todos os dados do produto são lidos
 */
Produto *ler_dados_produto();

/*
 * @brief Imprime os dados do produto
 * @param p Produto a ser imprimido
 * @pre Produto não nulo
 * @post Dados do produto são imprimidos
 */
void imprime_produto(Produto *p);

/*
 * @brief Aloca memoria para um header de lista
 * @return Header alocado
 * @pre Nenhuma
 * @post Header alocado na memoria
 */
Header_L *alocar_header_lista();

/*
 * @brief Imprime o header da lista
 * @param h Header da lista
 * @pre Header nao nulo
 * @post Os dados do header são imprimidos
 */
void imprime_header_lista(Header_L *h);

/*
 * @brief Calcula o deslocamento necessario para chegar a uma posicao no arquivo binario "lista"
 * @param pos Posição desejada
 * @return Offset de memoria necessaria para chegar a posicao
 * @pre Nenhuma
 * @post Deslocamento calculado
 */
size_t calcula_offset_lista(int pos);

/*
 * @brief Escreve o header no arquivo binario "lista"
 * @param f Arquivo binario "lista"
 * @param h Header da lista
 * @pre Arquivo e header nao são nulos
 * @post O header é escrito no arquivo binario
 */
void escreve_header_lista(FILE *f, Header_L *h);

/*
 * @brief Le o header de um arquivo com a lista
 * @param f Arquivo binario "lista"
 * @pre Arquivo não pode ser nulo
 * @return Header com os dados do arquivo
 * @post Header lido
 */
Header_L *ler_header_lista(FILE *f);

/*
 * @brief Retorna a primeira posicao livre na lista
 * @param h Header do arquivo "lista"
 * @pre Header não é nulo
 * @return Primeira posição livre no header da lista
 * @post posição retornada
 */
int retorna_posicao_livre_lista(Header_L *h);	

/*
 * @brief Escreve um produto no arquivo da lista
 * @param f Arquivo binario da lista
 * @param p Produto a ser inserido
 * @param pos Posição em que ele deve ser inserido
 * @pre Nenhuma
 * @post Produto escrito no arquivo
 */
void escreve_produto_na_lista(FILE *f, Produto *p, int pos);

/*
 * @brief Lê um produto no arquivo com os dados dos produtos "lista"
 * @param f Arquivo binario da "lista"
 * @param pos Posição do produto na lista
 * @return Produto com as informações lidas no arquivo
 * @pre Nenhuma
 * @post Produto lido da lista
 */
Produto *ler_produto_na_lista(FILE *f, int pos);

/*
 * @brief Insere os dados de um produto no arquivo contendo a lista de dados dos produtos
 * @param f Arquivo binario da lista de dados dos produtos
 * @param p Produto a ser inserido no arquivo
 * @return Posição onde o produto foi inserido
 * @pre Nenhuma
 * @post Produto inserido no arquivo contendo a lista
 */
int inserir_dados_do_produto_no_arquivo(FILE *f, Produto *p);

/*
 * @brief Lê as linhas de um arquivo txt e adiciona na lista de produtos e na arvore ou realiza operações de alterar e remover
 * @param f Produto txt com as informações em lote
 * @param arvore Arquivo binario contendo a arvore
 * @param lista Arquivo binario contendo a lista de dados dos produtos
 * @pre Nenhuma
 * @post O arquivo txt inteiro é lido e as operações são realizadas
 */
void ler_linha_txt(FILE *f, FILE *arvore, FILE *lista);

/*
 * @brief Tenta abrir o arquivo de texto
 * @param nome_arq Nome do arquivo txt a ser aberto
 * @param arvore Arquivo binario contendo a arvore
 * @param lista Arquivo binario contendo a lista
 * @pre Nome do arquivo nao nulo
 * @post Arquivo é lido
 */
void abrir_arquivo_texto(char *nome_arq, FILE *arvore, FILE *lista);

/*
 * @brief Altera a posicao livre no cabecalho do arquivo que contem as informacoes dos produtos
 * @param f Arquivo binario contendo a lista de dados dos produtos
 * @param pos Posição que esta livre
 * @pre Nenhuma
 * @post Posicao livre do cabeçalho da lista é alterado
 */
void alterar_livre_na_lista(FILE *f, int pos);

#endif
