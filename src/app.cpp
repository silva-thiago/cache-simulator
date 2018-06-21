#include "app.hpp"
#include "config.hpp"

App::App(Config &cfg): cache(cfg.linhas_da_cache, 4), memoria(cfg.blocos_da_memoria, cfg.palavras_por_bloco)
{}
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

}
bool App::mapeamento_associativo(int numero_do_bloco)
{

}
bool App::mapeamento_misto(int numero_do_bloco)
{
}

// --- funções para cada política de substituição  ---
//! \brief Substitui um bloco antigo por bloco
//! \param bloco Novo bloco

void App::subs_aleatoria(Bloco& bloco)
{

}
void App::subs_fifo(Bloco& bloco)
{

}
void App::subs_lfu(Bloco& bloco)
{

}
void App::subs_lru(Bloco & bloco)
{

}
