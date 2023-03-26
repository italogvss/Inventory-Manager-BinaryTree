#ifndef ARVORE_H
#define ARVORE_H

#define NULL_ARQ -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"


struct h_A{
	int raiz;
	int livre;
	int topo;
} typedef Header_A;

struct no{
	int codigo;
	int esq;
	int dir;
	int pos_dados;
}typedef No_A;

/*
 * @brief Verifica se arquivo existe
 * @param nome_arq Nome do arquivo
 * @return 1 se existe 0 se não existe
 * @pre Nome do arquivo não pode ser nulo
 * @post Verificação é realizada
 */
int checa_se_arquivo_existe(char *nome_arq);

/*
 * @brief Abre ou cria o arquivo binario
 * @param nome_arq Nome do arquivo
 * @return Arquivo binario aberto
 * @pre Nome do arquivo não pode ser nulo
 * @post Arquivo é aberto
 */
FILE *abre_arquivo_binario(char *nome_arq);

/*
 * @brief Aloca memoria para um header de lista
 * @return Header alocado
 * @pre Nenhuma
 * @post Header alocado na memoria
 */
Header_A *alocar_header_arvore();

/*
 * @brief Aloca memoria para um nó na arvore
 * @pre nenhuma
 * @post Memoria para o nó alocada
 */
No_A *aloca_no_arvore();


/*
 * @brief Imprime informações do header da arvore
 * @param h Header da arvore a ser lido
 * @pre header não é nulo
 * @post Header é impresso
 */
void imprime_header_arvore(Header_A *h);

/*
 * @brief Imprime o nó da arvore
 * @param no Nó a ser lido
 * @pre o Nó não é nulo
 * @post Nó da arvore é impresso
 */
void imprime_no_arvore(No_A *no);

/*
 * @brief Calcula o deslocamento necessario para chegar a uma posicao no arquivo binario "arvore"
 * @param pos Posição desejada
 * @return Offset de memoria necessaria para chegar a posicao
 * @pre Nenhuma
 * @post Deslocamento calculado
 */
size_t calcula_offset_arvore(int pos);

/*
 * @brief Escreve o header no arquivo binario "arvore"
 * @param f Arquivo binario "arvore"
 * @param h Header da arvore
 * @pre Arquivo e header nao são nulos
 * @post O header é escrito no arquivo binario
 */
void escreve_header_arvore(FILE *f, Header_A *h);

/*
 * @brief Le o header de um arquivo com a arvore
 * @param f Arquivo binario "arvore"
 * @pre Arquivo não pode ser nulo
 * @return Header com os dados do arquivo
 * @post Header lido
 */
Header_A *ler_header_arvore(FILE *f);
/*
 * @brief Retorna a primeira posicao livre na arvore
 * @param h Header do arquivo "lista"
 * @pre Header não é nulo
 * @return Primeira posição livre no header da arvore
 * @post posição retornada
 */
int retorna_posicao_livre_arvore(Header_A *h);

/*
 * @brief Escreve um produto na arvore
 * @param f Arquivo binario da arvore
 * @param no Nó a ser inserido na arvore
 * @param pos Posição em que ele deve ser inserido
 * @pre Nenhuma
 * @post Produto escrito no arquivo
 */
void escreve_dado_na_arvore(FILE *f, No_A *no, int pos);

/*
 * @brief Lê um produto no arquivo com os dados dos produtos "arvore"
 * @param f Arquivo binario da "arvore"
 * @param pos Posição do Nó na arvore
 * @return Nó com as informações lidas no arquivo
 * @pre Nenhuma
 * @post nó lido da arvore
 */
No_A *ler_dado_na_arvore(FILE *f, int pos);

/*
 * @brief Insere os dados de um nó no arquivo contendo a arvore 
 * @param f Arquivo binario da arvore
 * @param no Nó a ser inserido no arquivo
 * @pre Nenhuma
 * @post Produto inserido no arquivo contendo a arvore
 */
void inserir_no_arquivo_arvore(FILE *f, No_A *no);

/*
 * @brief Procua o pai de um elemento a partir do codigo
 * @param f Arquivo binario da arvore
 * @param codigo Codigo do elemento
 * @return Posiçao do pai do elemento
 * @pre Nenhuma
 * @post Pai do elemento é encontrado
 */
int procura_no_pai_do_elemento_inserido(FILE *f, int codigo);


/*
 * @brief Calcula a altura da arvore bninaria
 * @param f Arquivo contendo a arvore
 * @param raiz Raiz na qual ira começar a contagem
 * @return A altura da arvore
 * @pre Raiz não nula
 * @post É calculado a altura da arvore
 */
int calcula_altura_arvore(FILE *f, int raiz);

/*
 * @brief Imprime um nivel da arvore
 * @param f Arquivo binarion contendo a arvore
 * @param n Nivel a ser impresso
 * @param raiz Raiz da arvore
 * @pre Nenhuma
 * @post Nivel é impresso
 */
void imprime_nivel(FILE *f, int n, int raiz);

/*
 * @brief Imprime todos os elementos da arvore por nivel
 * @pre Nenhum
 * @post Arvore é impressa por nivel
 */
void imprime_por_nivel();

/*
 * @brief Retorna a posicao de um no arvore no arquivo que contem a arvore a partir de seu codigo
 * @param f Arquivo que contem a arvore
 * @param codigo Codigo do elemento que deseja buscar
 * @param raiz Raiz da arvore
 * @return Posição do elemento no arquivo
 * @pre Nenhuma
 * @post Retorna Posição do elemento no arquivo
 */
int retorna_posicao_no_arquivo(FILE *f, int codigo, int raiz);

/*
 * @brief Procura o nó do pai de um elemento que vai ser removido a partir de seu codigo e posicao
 * @param f Arquivo contendo a arvore
 * @param codigo Codigo do elemento que se quer achar o pai
 * @param pos Posição do nó no arquivo
 * @return Posição do pai no arquivo
 * @pre Arvore não nula
 * @post É encontrado a posição do pai do elemento
 */
int procura_no_pai_do_elemento_que_sera_removido(FILE *f, int codigo, int pos);


/*
 * @brief Retorna posicao do elemento com o menor codigo entre os filhos da esquerda
 * @param f Arquivo contendo a arvore
 * @param raiz Raiz da arvore
 * @return posição do elemento
 * @pre Filho a esquerda não é nulo
 * @post Posição do elemento é encontrada
 */
int retorna_posicao_maximo(FILE *f, int raiz);

/*
 * @brief Retorna posicao do elemento com o menor codigo entre os filhos da direita
 * @param f Arquivo contendo a arvore
 * @param raiz Raiz da arvore
 * @return posição do elemento
 * @pre Filho a direita não é nulo
 * @post Posição do elemento é encontrada
 */
int retorna_posicao_minimo(FILE *f, int raiz);

/*
 * @brief Remove um elemento no arquivo que contem a arvore a partir do seu codigo
 * @param f Arquivo contendo a arvore
 * @param lista Arquivo contendo a lista
 * @param codigo Codigo a ser removido
 * @pre Arvore e lista não são nulas
 * @post Elemento é removido dos arquivos
 */
void remove_no_arquivo_arvore(FILE *f, FILE *lista, int codigo);

/*
 * @brief Verifica se o codigo ja esta presente na arvore
 * @param f Arquivo contendo a arvore
 * @param codigo Codigo para ser verificado
 * @return 1 caso o codigo esteja na arvore, 0 se não estiver
 * @pre Nenhuma
 * @post Codigo é checado
 */
int checa_se_codigo_ja_esta_na_arvore(FILE *f, int codigo);

/*
 * @brief Altera o preço de um produto
 * @param arvore Arquivo contendo a arvore
 * @param lista Arquivo contendo os dados dos produtos
 * @param  codigo Codigo do produto que ira sofrer alteração
 * @pre Codigo presente na arvore
 * @post Preço do produto é alterado
 */
void altera_preco(FILE *arvore, FILE *lista, int codigo);

/*
 * @brief Altera o estoque de um produto
 * @param arvore Arquivo contendo a arvore
 * @param lista Arquivo contendo os dados dos produtos
 * @param  codigo Codigo do produto que ira sofrer alteração
 * @pre Codigo presente na arvore
 * @post Preço do produto é alterado
 */
void altera_estoque(FILE *arvore, FILE *lista, int codigo);

/*
 * @brief Busca e imprime os dados de um item presente na arvore a partir de seu codigo
 * @param arvore Arquivo contendo a arvore
 * @param lista Arquivo contendo a lista de dados dos produtos
 * @param codigo Codigo do item que devera ser encontrado
 * @pre Codigo deve estar presente na arvore
 * @post Os dados do item são impressos
 */
void busca_dados_do_produto(FILE *arvore, FILE *lista, int codigo);

/*
 * @brief Imprime os dados de todos os produtos presentes na arvore
 * @param arvore Arquivo contendo a arvore
 * @param lista Arquivo contendo a lista de dados dos produtos
 * @param raiz Raiz da arvore
 * @pre Arvore não nula
 * @post Dados são impressos
 */
void imprime_todos_produto(FILE *arvore, FILE *lista, int raiz);

#endif