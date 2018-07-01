#ifndef CONFIG_HPP
#define CONFIG_HPP
/*!
 * \brief Estrutura que armazena as variaveis com a configuração.
 */
struct Config
{
    int numero_de_palavras = 0;
    int linhas_da_cache = 0;
    int blocos_da_memoria = 0;
    int tipo_de_mapeamento = 0;
    int numero_de_conjuntos = 0;
    int politica_de_substituicao = 0;
    int politica_de_escrita = 0;
};

#endif // CONFIG_HPP
