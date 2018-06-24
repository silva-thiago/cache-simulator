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
    bool operator==(Bloco& rhs)
    {
       // dois blocos são iguais se eles tiverem o mesmo endereço na memória
       return this->endereco == rhs.endereco;
    }
    int& operator[](unsigned int indice)
    {
        return palavras[indice];
    }
    unsigned int& get_endereco()
    {
        return this->endereco;
    }
    std::vector<int>& get_palavras()
    {
        return palavras;
    }
protected:
    unsigned int endereco;
    std::vector<int> palavras;
};

class Linha : public Bloco
{
public:
    Linha(size_t tamanho): Bloco(tamanho)
    {
    }
    Linha& operator=(Bloco& bloco)
    {
        this->endereco = bloco.get_endereco();
        this->palavras = bloco.get_palavras();
        total_de_usos = 1;
        usos_recentes = 1;
        return *this;
    }
    int total_de_usos = 0;
    int usos_recentes = 0;

};

class Memoria
{
public:
    Memoria(size_t tamanho, size_t palavras_por_linha)
    {
        blocos.resize(tamanho, Bloco(palavras_por_linha));
    }
    Bloco& operator[](unsigned int indice)
    {
        return blocos[indice];
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
    Linha& operator[](unsigned int indice)
    {
        return linhas[indice];
    }
    size_t tamanho;
    int reinicializar_usos_recentes = tamanho;
private:
    std::vector<Linha> linhas;

};

#endif // CACHE_HPP
