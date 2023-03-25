#ifndef ARVORE_H
#define ARVORE_H

#define NULL_ARQ -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"


struct header_arvore{
	int raiz;
	int livre;
	int topo;
} typedef Header_Arvore;

struct no{
	int codigo;
	int esq;
	int dir;
	int pos_dados;
}typedef No_Arvore;

//Verifica se o arquivo existe
//Entrada: Nome do arquivo que sera verificado
//Retorno: Se o item existe ou nao
//Pre-condicao: Nenhuma
//Pos-condicao: Verificacao realizada
int checa_se_arquivo_existe(char *nome_arq);

//Abre o arquivo binario
//Entrada: O nome do arquivo que sera aberto
//Retorno: O arquivo aberto
//Pre-condicao: Nenhuma
//Pos-condicao: Arquivo aberto
FILE *abre_arquivo_binario(char *nome_arq);

//Aloca memoria para um header de arvore
//Entrada: Nenhuma
//Retorno: Header alocado
//Pre-condicao: Nenhuma
//Pos-condicao: Memoria para header alocada
Header_Arvore *alocar_header_arvore();

//Aloca memoria para um no arvore
//Entrada: Nenhuma
//Retorno: No arvore alocado
//Pre-condicao: Nenhuma
//Pos-condicao: Memoria para no arvore alocada
No_Arvore *aloca_no_arvore();

//Realiza a leitura dos dados de um no arvore
//Entraa: Nenhuma
//Retorno: No arvore com os dados preenchidos
//Pre-condicao: Nenhuma
//Pos-condicao: Leitura de dados realizada
No_Arvore *scaneia_no_arvore();

//Imprime o header da arvore
//Entrada: Header que sera impresso
//Retorno: Nenhum
//Pre-condicao: Header nao nulo
//Pos-condicao: Header impresso
void imprime_header_arvore(Header_Arvore *h);

//Imprime o no arvore
//Entrada: No arvore que sera impresso
//Retorno: Nenhum
//Pre-condicao: No arvore nao nulo
//Pos-condicao: No arvore impresso
void imprime_no_arvore(No_Arvore *no);

//Calcula o deslocamento necessario para chegar a uma determinada posicao na arvore
//Entrada: A posicao que deseja alcancar
//Retorno: A quantidade de memoria necessaria para chegar a posicao
//Pre-condicao: Nenhuma
//Pos-condicao: Deslocamento calculado
size_t calcula_offset_arvore(int pos);

//Escreve o header na arvore
//Entrada: O arquivo onde o header sera escrito, e o header que sera escrito
//Retorno: Nenhum
//Pre-condicao: Arquivo e header nao nulos
//Pos-condicao: Header escrito no arquivo
void escreve_header_arvore(FILE *f, Header_Arvore *h);

//Le o header de um arquivo com a arvore
//Entrada: O arquivo em que sera realizada a leitura
//Retorno: O header que foi lido
//Pre-condicao: Arquivo nao nulo
//Pos-condicao: Header lido
Header_Arvore *ler_header_arvore(FILE *f);

//Retorna a posicao primeira posicao livre na arvore
//Entrada: O header que contem os dados da arvore
//Retorno: A primeira posicao livre
//Pre-condicao: Header nao nulo
//Pos-condicao: Posicao retornada
int retorna_posicao_livre_arvore(Header_Arvore *h);

//Escreve um no arvore no arquivo contendo a arvore
//Entrada: O arquivo onde o no arvore sera escrito, o no arvore que sera escrito e a posicao onde ele sera escrito
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: No arvore escrito no arquivo
void escreve_dado_na_arvore(FILE *f, No_Arvore *no, int pos);

//Le um no arvore no arquivo contendo a arvore
//Entrada: O arquivo contendo a arvore, e a posicao que sera lida
//Retorno: No arvore com os dados presentes na arvore
//Pre-condicao: Nenhuma
//Pos-condicao: No arvore lido da arvore
No_Arvore *ler_dado_na_arvore(FILE *f, int pos);

//Insere um no arvore no arquivo contendo a arvore
//Entrada: O arquivo onde o no arvore sera inserido, e o no arvore que sera inserido
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: No arvore inserido no arquivo contendo a arvore
void inserir_no_arquivo_arvore(FILE *f, No_Arvore *no);

//Procura o pai de um determinado elemento a partir de seu codigo
//Entrada: O arquivo onde esta o elemento e o codigo do elemento
//Retorno: A posicao do pai do elemento
//Pre-condicao: Nenhuma
//Pos-condicao: Pai do elemento encontrado
int procura_no_pai_do_elemento_inserido(FILE *f, int codigo);

//Imprime a arvore presente no arquivo contendo a arvore
//Entrada: O arquivo que contem a arvore, a raiz da arvore e uma variavel para informar se o elemento que vai ser impresso eh a raiz
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: Arvore impressa
void imprime_arvore_arquivo(FILE *f, int raiz, int i);

//Calcula a altura da arvore presente no arquivo
//Entrada: O arquivo que contem a arvore e a raiz da arvore
//Retorno: A altura da arvore
//Pre-condicao: Nenhuma
//Pos-condicao: Altura da arvore retornada
int calcula_altura_arvore(FILE *f, int raiz);

//Imprime um nivel da arvore presente no arquivo
//Entrada: O arquivo que contem a arvore, o nivel que sera imprimido, e a raiz da arvore
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: Nivel impresso
void imprime_nivel(FILE *f, int n, int raiz);

//Imprime todos os niveis da arvore presente no arquivo
//Entrada: O arquivo que contem a arvore
//Retorno: Nenhum
//Pre-condicao: Nenhuma
//Pos-condicao: Arvore impressa
void imprime_por_nivel(FILE *f);

//Retorna a posicao de um no arvore no arquivo que contem a arvore a partir de seu codigo
//Entrada: O arquivo que contem a arvore, o codigo do elemento desejado e a raiz da arvore
//Retorno: A posicao do elemento no arquivo
//Pre-condicao: Nenhuma
//Pos-condicao: Posicao do elemento no arquivo retornada
int retorna_posicao_no_arquivo(FILE *f, int codigo, int raiz);

//Procura o no pai de um elemento que vai ser removido a partir de seu codigo e posicao
//Entrada: O arquivo que contem a arvore, o codigo do elemento que deseja encontrar o pai, e a posicao do elemento no arquivo
//Retorno: A posicao do pai do elemento no arquivo
//Pre-condicao: Arvore nao nula
//Pos-condicao: Posicao do pai do elemento retornada
int procura_no_pai_do_elemento_que_sera_removido(FILE *f, int codigo, int pos);

//Retorna posicao do elemento com o maior codigo entre os filhos da esquerda
//Entrada: O arquivo que contem a arvore, e o filho a esquerda do elemento
//Retorno: Posicao do elemento desejado
//Pre-condicao: Filho a esquerda nao nulo
//Pos-condicao: Posicao do elemento retornada
int retorna_posicao_maximo(FILE *f, int raiz);

//Retorna posicao do elemento com o menor codigo entre os filhos da direita
//Entrada: O arquivo que contem a arvore, e o filho a direita do elemento
//Retorno: Posicao do elemento desejado
//Pre-condicao: Filho a direita nao nulo
//Pos-condicao: Posicao do elemento retornada
int retorna_posicao_minimo(FILE *f, int raiz);

//Remove um elemento no arquivo que contem a arvore a partir do seu codigo
//Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e o codigo do elemento
//Retorno: Nenhum
//Pre-condicao: Arvore e lista nao nulas
//Pos-condicao: Elemento removido
void remove_no_arquivo_arvore(FILE *f, FILE *lista, int codigo);

//Checa se ja existe um elemento na arvore com determinado codigo
//Entrada: O arquivo que contem a arvore e o codigo que sera buscado
//Retorno: 1 se o elemento ja esta presente na arvore e 0 se nao estiver
//Pre-condicao: Nenhuma 
//Pos-condicao: Checagem realizada
int checa_se_codigo_ja_esta_na_arvore(FILE *f, int codigo);

//Altera o numero de exemplares na lista com as informacoes de um item presente na arvore a partir de seu codigo
//Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e o codigo do item que sofrera a alteracao
//Retorno: Nenhum
//Pre-condicao: Codigo presente na arvore
//Pos-condicao: Numero de exemplares do item alterado
void altera_preco(FILE *arvore, FILE *lista, int codigo);

//Busca e imprime os dados de um item presente na arvore a partir de seu codigo
//Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e o codigo do item cujas informacoes serao procuradas
//Retorno: Nenhum
//Pre-condicao: Codigo presente na arvore
//Pos-condicao: Dados do item desejado impressos
void busca_dados_do_produto(FILE *arvore, FILE *lista, int codigo);

//Imprime os dados de todos os livros presentes na arvore
//Entrada: O arquivo que contem a arvore, o arquivo que contem a lista com as informacoes dos livros e a raiz da arvore
//Retorno: Nenhum
//Pre-condicao: Arvore nao nula
//Pos-condicao: Dados impressos
void imprime_todos_produto(FILE *arvore, FILE *lista, int raiz);

#endif