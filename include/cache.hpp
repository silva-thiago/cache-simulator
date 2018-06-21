#ifndef CACHE_HPP
#define CACHE_HPP

#include <cstdio>
#include <vector>

class Bloco
{
public:
    Bloco(size_t tamanho)
    {
        palavras.resize(tamanho);
    }
    ~Bloco()
    {
        palavras.clear();
    }
private:
    std::vector<int> palavras;
};

class Linha : public Bloco
{
public:
    Linha(size_t tamanho): Bloco(tamanho)
    {
    }
private:
    int numero_de_usos;
    int ultima_vez_usado;
    // O bloco com o menor numero é o mais velho
    int numero_do_bloco;
    static int ultimo_numero;
};

class Memoria
{
public:
    Memoria(size_t tamanho, size_t palavras_por_linha)
    {
        blocos.resize(tamanho, Bloco(palavras_por_linha));
    }
    ~Memoria()
    {
        blocos.clear();
    }
private:
    std::vector<Bloco> blocos;
};

class Cache
{
public:
    Cache(size_t tamanho,  size_t palavras_por_linha)
    {
        linhas.resize(tamanho, Linha(palavras_por_linha));
    }
    ~Cache()
    {
        linhas.clear();
    }
private:
    std::vector<Linha> linhas;
    size_t tamanho;

};

#endif // CACHE_HPP
