#ifndef INTERFACE_H
#define INTERFACE_H

#include "arvore.h"
#include "lista.h"

/*
 * @brief Inicia arquivos binarios e headers
 * @pre Nenhuma
 * @post Arquivos binarios são criados e configurados
 */
void init();

/*
 * @brief Imprime os dados de um produto
 * @param p Produto a ser impresso
 * @pre Produto não é nulo
 * @post Dados do produto são impressos
 */
void imprime_produto(Produto *p);

/*
 * @brief Menu pata inserção de novos produtos
 * @pre nenhum
 * @post Produto é inserido caso não exista
 */
void menu_inserir();

/*
 * @brief Menu pora alterar o preço de um produto
 * @pre Nenhuma
 * @post Preço do produto é alterado caso ele seja encontrado
 */
void menu_alterar_preco();

/*
 * @brief Menu pora alterar o estoque de um produto
 * @pre Nenhuma
 * @post estoque do produto é alterado caso ele seja encontrado
 */
void menu_alterar_estoque();

/*
 * @brief Menu para remover um produto
 * @pre Nenhuma
 * @post Remove um produto caso ele seja encontrado
 */
void menu_remover();

/*
 * @brief Menu para buscar e imp´rimir os dados de um produto
 * @pre Nenhuma
 * @post Produto é procurado
 */
void menu_buscar();

/*
 * @brief Ira imprimir todos os produtos gravados no arquivo
 * @pre Nenhum
 * @post Produtos são impressos
 */
void menu_imprimir();

/*
 * @brief Menu para abrir um arquivo txt de operações em lote
 * @pre Nenhum
 * @post Operações são realizadas
 */
void menu_ler_arquivo();

/*
 * @brief Menu com as opções possiveis de serem realizadas
 * @pre Nenhuma
 * @post É impresso as opções
 */
int menu();

#endif