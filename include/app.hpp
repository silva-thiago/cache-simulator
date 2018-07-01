#ifndef APP_H
#define APP_H

#include "config.hpp"
#include "cache.hpp"

#include <stdexcept>
#include <iostream>

/*!
 * \brief Classe responsável tanto pelo front-end quanto pelo back-end da aplicação. Essa decisão foi tomada para deixar o código mais simples.
 */
class App
{
public:
    /*!
     * \brief Construtor da classe App.
     * \param cfg Configuração já lida.
     */
    App(Config cfg);
    /*!
     * \brief Ler um bloco da mémoria (trazer para uma linha da cache).
     * \param endereco
     */
    void read(unsigned int endereco);
    /*!
     * \brief Escreve em um endereço de mémoria um valor.
     * \note O endereço não precisa necessáriamente estar na cache, pois será feito o mapeamento.
     * \note Faz o Write Though se definido nas configurações.
     * \param endereco Endereco de escrita.
     * \param valor Valor a ser escrita.
     */
    void write(unsigned int endereco, unsigned int valor);
    /*!
     * \brief Exibe o mapa de mémoria atual da cache e da mémoria.
     */
    void show();

private:
    /*!
     * \brief Obtêm a linha da cache que contém o bloco. Em caso de cache miss será feita a substituição.
     * \param numero_do_bloco numero do bloco a ser encontrado.
     * \note Essa função atualiza o contador de número de acessos.
     * \return Linha da cache que contém o bloco da mémoria.
     */
    Linha& mapear(unsigned int numero_do_bloco);

    /*!
     * \brief mapeamento_direto Faz o mapeamento usando a política de mapeamento direto.
     * \param numero_do_bloco numero_do_bloco numero do blo
     * \note Chama o método de substituição em caso de cache miss, mesmo se existir espaço vazio.co a ser encontrado.
     * \return Linha que contêm o bloco da mémoria.
     */
    Linha& mapeamento_direto        (unsigned int numero_do_bloco);
    /*!
     * \brief mapeamento_direto Faz o mapeamento usando a política de mapeamento totalmente associativo.
     * \param numero_do_bloco numero_do_bloco numero do bloco a ser encontrado.
     * \return Linha que contêm o bloco da mémoria.
     * \note Chama o método de substituição em caso de cache miss, mesmo se existir espaço vazio.
     */
    Linha& mapeamento_associativo   (unsigned int numero_do_bloco);
    /*!
     * \brief mapeamento_direto Faz o mapeamento usando a política de mapeamento associativo por conjunto.
     * \param numero_do_bloco numero_do_bloco numero do bloco a ser encontrado.
     * \return Linha que contêm o bloco da mémoria.
     * \note Chama o método de substituição em caso de cache miss, mesmo se existir espaço vazio.
     */
    Linha& mapeamento_misto         (unsigned int numero_do_bloco, unsigned int numero_de_conjuntos);

    /*!
     * \brief Realiza a substituição usando a política configurada.
     * \param numero_do_bloco Número do bloco a ser inserido
     * \param numero_do_conjunto Número do conjunto que o bloco será inserido.
     * \param tamanho_do_conjunto Tamanho do conjunto que conterá o bloco.
     * \return Linha contendo o bloco inserido.
     * \note Realiza o Write-back se estiver definido nas configurações e a linha
     * substituída já tiver sido usada.
     */
    Linha& substituir               (unsigned int numero_do_bloco, unsigned int numero_do_conjunto, unsigned int tamanho_do_conjunto);
    /*!
     * \brief Realiza a substituição usando a política de substituição aleatória.
     * \param indice_do_conjunto Número da linha que dá inicio ao conjunto.
     * \param tamanho_do_conjunto Tamanho do conjunto que conterá o bloco.
     * \return Linha que será substituída.
     */
    Linha& subs_aleatoria           (unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto);
    /*!
     * \brief Realiza a substituição usando a política de substituição first-in-first-out.
     * \param indice_do_conjunto Número da linha que dá inicio ao conjunto.
     * \param tamanho_do_conjunto Tamanho do conjunto que conterá o bloco.
     * \return Linha que será substituída.
     */
    Linha& subs_fifo                (unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto);
    /*!
     * \brief Realiza a substituição usando a política de substituição Less Frenquently Used.
     * \param indice_do_conjunto Número da linha que dá inicio ao conjunto.
     * \param tamanho_do_conjunto Tamanho do conjunto que conterá o bloco.
     * \return Linha que será substituída.
     */
    Linha& subs_lfu                 (unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto);
    /*!
     * \brief Realiza a substituição usando a política de substituição Less Recently Used.
     * \param indice_do_conjunto Número da linha que dá inicio ao conjunto.
     * \param tamanho_do_conjunto Tamanho do conjunto que conterá o bloco.
     * \return Linha que será substituída.
     */
    Linha& subs_lru                 (unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto);

    /*!
     * \brief Mémoria cache da aplicação.
     */
    Cache cache;
    /*!
     * \brief Memória principal da aplicação.
     */
    Memoria memoria;
    /*!
     * \brief Configuração lida.
     */
    Config config;
};

#endif // APP_H
