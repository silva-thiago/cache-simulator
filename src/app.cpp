#include "app.hpp"
#include "config.hpp"

App::App(Config &cfg): cache(cfg.linhas_da_cache, 4), memoria(cfg.blocos_da_memoria, cfg.palavras_por_bloco)
{
//    Linha::usos_para_reinicializacao = 10;
}
void App::read(int endereco)
{}
void App::show()
{}
void App::write()
{}

// --- funções para cada mapeamento  ---
//! \brief
//! Procura um bloco da memória na cache, se for encontrado: cache hit.
//! Caso o valor não seja encontrado um dos dois casos acontece:
//! Caso 1: Coloca o bloco no espaço vazio.
//! Caso 2: Substitui por outra linha da cache.
//! \param numero_do_bloco Bloco a ser procurado na cache
//! \return retorna true em caso de cache hit; ou false caso o contrário.
//-----------------------------------------------------

bool App::mapeamento_direto(int numero_do_bloco)
{
    return false;
}
bool App::mapeamento_associativo(int numero_do_bloco)
{
    return false;
}

bool App::mapeamento_misto(int numero_do_bloco)
{
    unsigned int numero_do_conjunto = numero_do_bloco % this->config.numero_de_conjuntos;
    size_t tamanho_do_conjunto = this->cache.tamanho / this->config.numero_de_conjuntos;
    int indice_do_conjunto = numero_do_conjunto * tamanho_do_conjunto;

    Bloco& bloco_na_memoria = this->memoria[numero_do_bloco];

    for(unsigned int c = 0; c < tamanho_do_conjunto; c++)
    {
        Linha& bloco = this->cache[indice_do_conjunto + c];

        if(bloco == bloco_na_memoria)
        {
            atualizar_contadores(bloco);
            return true; // cache hit!
        }
    }

    // Cache miss, traz da memória para a cache
    substituir(bloco_na_memoria, indice_do_conjunto, tamanho_do_conjunto);
    return false;

}

// --- função de intermediaria para atualizados estado da linha ---
void App::atualizar_contadores(Linha &linha)
{
    linha.total_de_usos++;
    linha.usos_recentes++;
}

// --- função de substituição intermediaria ---
void App::substituir(Bloco& novo_bloco, int indice_inicial, int tamanho_do_conjunto)
{
    // Atualizar usos recentes
    if(this->cache.reinicializar_usos_recentes == 0)
    {
        for(unsigned int i = 0; i < this->cache.tamanho; i++)
        {
            Linha& linha = this->cache[i];
            linha.usos_recentes = 0;
        }
        this->cache.reinicializar_usos_recentes = this->cache.tamanho;
    }
    else
    {
        this->cache.reinicializar_usos_recentes--;
    }
    // cache miss, usa politica de substituição
    unsigned int politica = this->config.politica_de_substituicao;

    switch(politica)
    {
    case 1:
        subs_aleatoria(novo_bloco, indice_inicial, tamanho_do_conjunto);
        return;
    case 2:
        subs_fifo(novo_bloco, indice_inicial, tamanho_do_conjunto);
        return;
    case 3:
        subs_lfu(novo_bloco, indice_inicial, tamanho_do_conjunto);
        return;
    case 4:
        subs_lru(novo_bloco, indice_inicial, tamanho_do_conjunto);
        return;
    }
}

// --- funções para cada política de substituição  ---
//! \brief Substitui um bloco antigo por bloco
//! \param bloco Novo bloco

void App::subs_aleatoria(Bloco& novo_bloco, int indice_inicial, int tamanho_do_conjunto)
{

}
void App::subs_fifo(Bloco& novo_bloco, int indice_inicial, int tamanho_do_conjunto)
{
    // trazer os elemento uma posição para traz, sobreescrevendo o first
    int c = 0;
    for(c = 0; c <= tamanho_do_conjunto; c++)
    {
        this->cache[indice_inicial+c] = this->cache[indice_inicial+1];
    }
     this->cache[indice_inicial+c] = novo_bloco;
}
void App::subs_lfu(Bloco& novo_bloco, int indice_inicial, int tamanho_do_conjunto)
{

}
void App::subs_lru(Bloco& novo_bloco, int indice_inicial, int tamanho_do_conjunto)
{

}
