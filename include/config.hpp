#ifndef CONFIG_HPP
#define CONFIG_HPP

struct Config
{
    int palavras_por_bloco;
    int linhas_da_cache;
    int blocos_da_memoria;
    int tipo_de_mapeamento;
    int numero_de_conjuntos;
    int politica_de_substituicao;
    int politica_de_escrita;
};

#endif // CONFIG_HPP
