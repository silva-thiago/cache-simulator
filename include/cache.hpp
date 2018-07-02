#ifndef CACHE_HPP
#define CACHE_HPP

#include <vector>
#include <random>

/*!
 * \brief Functor (objeto de função) para gerar números aléatorios não negativos de três digitos.
 */
struct Random {
    std::random_device                              rd;
    std::mt19937                                    mt;
    std::uniform_int_distribution<unsigned int>     dist;

    Random() : rd{}, mt{rd()}, dist{0, 999} {}
    int operator()()
    {
      return dist(mt);
    }
};
/*!
 * \brief A classe bloco representa um endereço da mémoria que armazena {numero_de_palavras} palavras.
 */
struct Bloco
{

    /*!
     * \brief Cria um bloco de {tamanho} palavras.
     * \param tamanho quantidade de palavras.
     */
    Bloco(unsigned int tamanho)
    {
        conteudo.resize(tamanho);
    }
    /*!
     * \brief Criar um bloco de {tamanho} palavras com conteúdo aleatório.
     * \param tamanho quantidade de palavras.
     * \param rand Functor de geração de números ramdomicos.
     */
    Bloco(unsigned int tamanho, Random& rand)
    {
        conteudo.resize(tamanho);
        for(unsigned int c = 0; c < tamanho; c++)
        {
            conteudo[c] = rand();
        }
    }


    /*!
     * \brief Palavras contidas no bloco.
     */
    std::vector<unsigned int> conteudo;
};

/*!
 * \brief A linha é um bloco da cache, com a diferença que ela contém os contadores
 */
struct Linha : public Bloco
{
    /*!
     * \brief Cria uma Linha (Bloco) de {tamanho} palavras.
     * \param tamanho quantidade de palavras.
     */
    Linha(unsigned int tamanho): Bloco(tamanho)
    {
        this->chegada = 0;
        this->total_de_usos = 0;
        this->refencia_temporal = 0;
    }
    /*!
     * \brief lê um bloco da mémoria (armazena na linha).
     * \param bloco bloco da mémoria.
     * \param numero_do_bloco Número do bloco dentro da mémoria principal.
     * \param tamanho_do_conjunto tamanho do conjunto usado no mapeamento.
     * \param acessos A quantidade de acessos é usada como referência temporal.
     * \return a própria linha.
     * \note os contadores são inicializados aqui.
     */
    Linha& ler(Bloco& bloco, unsigned int numero_do_bloco, unsigned int tamanho_do_conjunto, unsigned int acessos)
    {
        // -- Contadores --
        this->chegada = tamanho_do_conjunto-1;
        this->total_de_usos = 1;
        this->refencia_temporal = acessos;
        // -- Atributos --
        this->numero_do_bloco = numero_do_bloco;
        this->conteudo = bloco.conteudo;

        return *this;
    }
    /*!
     * \brief escreve uma valor dentro do vetor de palavras.
     * \param palavra índice da palavra (endereço da palavra - endereço da primeira palavra do conjunto).
     * \param valor valor a ser colocado.
     * \return a própria linha.
     */
    Linha& escrever(unsigned int palavra, unsigned int valor)
    {
        this->conteudo[palavra] = valor;
        return *this;
    }
    /*!
     * \brief Verifica se o bloco está nessa linha.
     * \param numero_do_bloco numero do bloco na mémoria.
     * \param acessos quantidade de acessos (usada como referência temporal para o LRU).
     * \return true, em caso de cache hit, false caso o contrário.
     * \note Os contadores de uso e referência temporal são atualizados aqui.
     */
    bool buscar(unsigned int numero_do_bloco, unsigned int acessos)
    {
        if(this->total_de_usos > 0 and numero_do_bloco == this->numero_do_bloco)
        {
            total_de_usos++;
            refencia_temporal = acessos;
            return true;
        }
        return false;
    }

    /*!
     * \brief Cada linha tem o número do bloco que está armazenado.
     */
    unsigned int numero_do_bloco;
    /*!
     * \brief contador usado no LFU.
     */
    unsigned int total_de_usos;
    /*!
     * \brief contador usado no LRU.
     */
    unsigned int refencia_temporal;
    /*!
     * \brief contador usado no FIFO.
     */
    unsigned int chegada;

};
/*!
 * \brief A mémoria é um conjunto de blocos.
 */
struct Memoria
{
    /*!
     * \brief Constrói uma memoria de {tamanho} blocos com cada bloco contendo {numero_de_palavras} palavras.
     * \param tamanho numero de blocos (definido na configuração)..
     * \param numero_de_palavras número de palavras de cada bloco (definido na configuração)..
     */
    Memoria(unsigned int tamanho, unsigned int numero_de_palavras)
    {
        Random rand;
        for(unsigned int c = 0; c < tamanho; c++)
        {
            blocos.push_back(Bloco(numero_de_palavras, rand));
        }
    }
    /*!
     * \brief Vetor de blocos.
     */
    std::vector<Bloco> blocos;
};
/*!
 * \brief A cache é uma mémoria próxima do processador.
 */
struct Cache
{
    /*!
     * \brief Constrói uma memoria cache de {tamanho} linha(blocos) com cada bloco contendo {numero_de_palavras} palavras.
     * \param tamanho numero de linhas (definido na configuração)..
     * \param numero_de_palavras número de palavras de cada linha (definido na configuração).
     */
    Cache(unsigned int tamanho,  unsigned int numero_de_palavras)
    {
        linhas.resize(tamanho, Linha(numero_de_palavras));
    }
    /*!
     * \brief Contador de acessos (referência temporal).
     */
    unsigned int acessos = 0;
    /*!
     * \brief Vetor de linhas.
     */
    std::vector<Linha> linhas;
};

#endif // CACHE_HPP
