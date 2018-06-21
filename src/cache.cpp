#include "cache.hpp"



// --- funções para cada mapeamento  ---
//! \brief
//! Procura um bloco da memória na cache, se for encontrado: cache hit.
//! Caso o valor não seja encontrado um dos dois casos acontece:
//! Caso 1: Coloca o bloco no espaço vazio.
//! Caso 2: Substitui por outra linha da cache.
//! \param memoria Memória principal.
//! \param cache Memória cache.
//! \param bloco Bloco a ser procurado na cache
//! \return retorna true em caso de cache hit; ou false caso o contrário.
//-----------------------------------------------------

bool mapeamento_direto(Memoria& memoria, Cache cache, int numero_do_bloco)
{

}
bool mapeamento_associativo(Memoria& memoria, Cache cache, int numero_do_bloco)
{

}
bool mapeamento_misto(Memoria& memoria, Cache cache, int numero_do_bloco)
{

}

// --- funções para cada política de substituição  ---
//! \brief Substitui um blocos antigo por bloxk
//! \param cache Memória cache.
//! \param bloco Novo bloco

void subs_aleatoria(Cache& cache, Bloco& bloco)
{

}
void subs_fifo(Cache& cache, Bloco& bloco)
{

}
void subs_lfu(Cache& cache, Bloco& bloco)
{

}
void subs_lru(Memoria& memoria, Cache cache, Bloco & bloco)
{

}
