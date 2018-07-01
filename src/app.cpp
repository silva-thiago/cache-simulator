#include "app.hpp"

//----------------------------
// --- Construtor de App  ---
//----------------------------

App::App(Config cfg): cache(cfg.linhas_da_cache, cfg.numero_de_palavras), memoria(cfg.blocos_da_memoria, cfg.numero_de_palavras), config(cfg)
{
}

//------------------------------
// --- funções de Front-end  ---
//------------------------------

void App::read(unsigned int endereco)
{
    // Precisamos definir qual bloco tem aquele endereço
    // Pois cada bloco contém quatro endereços
    unsigned int n_bloco = endereco / this->config.numero_de_palavras;
    // Agora fazemos o mapeamento pra trazer ele para cache
    mapear(n_bloco);
    // Já que não é necessário lidar com o dado em si
    // não precisamos recuperar o resto da divisão
}
void App::write(unsigned int endereco, unsigned int valor)
{
    // Precisamos definir qual bloco tem aquele endereço
    // Pois cada bloco contém quatro endereços
    unsigned int n_bloco = endereco / this->config.numero_de_palavras;
    // Agora precisimos do módulo da divisão para descobrir
    // o indice da palavra
    unsigned int i_palavra = endereco % this->config.numero_de_palavras;
    // Agora fazemos o mapeamento pra obter a linha da cache.
    Linha& linha = mapear(n_bloco);
    // A linha recebe um novo valor
    linha.escrever(i_palavra, valor);
    // Se for write through, atualiza tbm na mémoria principal
    if(this->config.politica_de_escrita == 2)
    {
        this->memoria.blocos[n_bloco].conteudo[i_palavra] = valor;
    }

}
void App::show()
{
    unsigned int palavras = this->config.numero_de_palavras;
    // Mostra os dados da chace e da mémoria
    std::cout << "CACHE L1\nLinha – Bloco - Endereço – Conteúdo (x representa espaço não utilizado)\n";
    unsigned int tamanho = this->cache.linhas.size();
    for(unsigned int c = 0; c < tamanho; c++)
    {
        Linha& linha = this->cache.linhas[c];
        if(linha.total_de_usos == 0)
        {
            for(unsigned int i = 0; i < palavras; i++)
            {
                std::cout << c << " - x - x - x\n";
            }
        }
        else
        {
            for(unsigned int i = 0; i < palavras; i++)
            {
                std::cout << c << " - " << linha.numero_do_bloco << " - " << linha.numero_do_bloco*palavras + i << " - " << linha.conteudo[i] << std::endl;
            }
        }
    }

    std::cout << "MEMORIA PRINCIPAL\nBloco-Endereço –Conteúdo (conteúdo inicial preenchido aleatoriamente)\n";

    tamanho = this->memoria.blocos.size();
    for(unsigned int c = 0; c < tamanho; c++)
    {
        Bloco& bloco = this->memoria.blocos[c];
        for(unsigned int i = 0; i < palavras; i++)
        {
            std::cout << c << " - " << c*palavras + i << " - " << bloco.conteudo[i] << std::endl;
        }

    }

}

//--------------------------------------
// --- funções para cada mapeamento  ---
//--------------------------------------

Linha& App::mapear(unsigned int numero_do_bloco)
{
    this->cache.acessos++;
    switch (this->config.tipo_de_mapeamento) {
        case 1:
            return mapeamento_direto(numero_do_bloco);
        case 2:
            return mapeamento_associativo(numero_do_bloco);
        case 3:
            return mapeamento_misto(numero_do_bloco, this->config.numero_de_conjuntos);
        default:
            throw std::runtime_error("Regra de mapeamento não definida");
    }
}

Linha& App::mapeamento_direto(unsigned int numero_do_bloco)
{
    return this->mapeamento_misto(numero_do_bloco, this->cache.linhas.size());
}
Linha& App::mapeamento_associativo(unsigned int numero_do_bloco)
{
    return this->mapeamento_misto(numero_do_bloco, 1);
}

Linha& App::mapeamento_misto(unsigned int numero_do_bloco, unsigned int numero_de_conjuntos)
{
    unsigned int tamanho_da_cache = this->cache.linhas.size();
    unsigned int tamanho_do_conjunto = tamanho_da_cache / numero_de_conjuntos;
    unsigned int numero_do_conjunto = numero_do_bloco % numero_de_conjuntos;
    unsigned int indice_do_conjunto = numero_do_conjunto * tamanho_do_conjunto;

    int offset = indice_do_conjunto + tamanho_do_conjunto - tamanho_da_cache;
    if(offset > 0)
    {
        tamanho_do_conjunto -= offset;
    }
    for(unsigned int c = 0; c < tamanho_do_conjunto; c++)
    {
        Linha& linha = this->cache.linhas[indice_do_conjunto + c];
        if(linha.buscar(numero_do_bloco, this->cache.acessos) == true)
        {
            return linha;
        }
    }
    // Cache miss, traz da memória para a cache
    return substituir(numero_do_bloco, indice_do_conjunto, tamanho_do_conjunto);

}

//-------------------------------
// --- função de substituição ---
//-------------------------------

Linha& App::substituir(unsigned int numero_do_bloco, unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto)
{
    // cache miss, usa politica de substituição
    unsigned int politica = this->config.politica_de_substituicao;

    Linha* linha_substituida = nullptr;

    switch(politica)
    {
        case 1:
            linha_substituida = &subs_aleatoria(indice_do_conjunto, tamanho_do_conjunto);
            break;
        case 2:
            linha_substituida = &subs_fifo(indice_do_conjunto, tamanho_do_conjunto);
            break;
        case 3:
            linha_substituida = &subs_lfu(indice_do_conjunto, tamanho_do_conjunto);
            break;
        case 4:
            linha_substituida = &subs_lru(indice_do_conjunto, tamanho_do_conjunto);
            break;
        default:
            throw std::runtime_error("Politica de substituição não definida.");
    }
    if(linha_substituida->total_de_usos > 1)
    {
        politica = this->config.politica_de_escrita;
        switch (politica)
        {
            // Write back
            case 1:
                this->memoria.blocos[linha_substituida->numero_do_bloco].conteudo = linha_substituida->conteudo;
                break;
            // Write through
            case 2:
                break;
            default:
                throw std::runtime_error("Politica de escrita não definida.");
        }
    }
    linha_substituida->ler(this->memoria.blocos[numero_do_bloco], numero_do_bloco, tamanho_do_conjunto, this->cache.acessos);
    return *linha_substituida;
}

//----------------------------------------------------
// --- funções para cada política de substituição  ---
//----------------------------------------------------

Linha& App::subs_aleatoria(unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto)
{
    Random rand;
    Linha* linha_resultante = &this->cache.linhas[indice_do_conjunto + (  rand() % (tamanho_do_conjunto-1)  )];
    return *linha_resultante;
}
Linha& App::subs_fifo(unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto)
{
    Linha* linha_resultante = nullptr;
    for(unsigned int c = 0; c < tamanho_do_conjunto; c++)
    {
        Linha& linha_atual = this->cache.linhas[indice_do_conjunto+c];
        if(linha_atual.chegada == 0)
        {
            if(linha_resultante == nullptr)
                *linha_resultante = linha_atual;
            else
                break;
        }
        else
        {
            linha_atual.chegada--;
        }
    }
    if(linha_resultante == nullptr)
        throw std::runtime_error("Não foi possivel manter a ordenação no conjunto (politica FIFO)");
    return *linha_resultante;
}
Linha& App::subs_lfu(unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto)
{
    Linha* linha_resultante = &this->cache.linhas[indice_do_conjunto];
    for(unsigned int c = 0; c < tamanho_do_conjunto; c++)
    {
        Linha* linha_atual = &this->cache.linhas[indice_do_conjunto+c];
        if(linha_atual->total_de_usos < linha_resultante->total_de_usos)
        {
            linha_resultante = linha_atual;
        }
    }
    return *linha_resultante;
}
Linha& App::subs_lru(unsigned int indice_do_conjunto, unsigned int tamanho_do_conjunto)
{
    Linha* linha_resultante = &this->cache.linhas[indice_do_conjunto];
    for(unsigned int c = 0; c < tamanho_do_conjunto; c++)
    {
        Linha* linha_atual = &this->cache.linhas[indice_do_conjunto+c];

        if(linha_atual->refencia_temporal < linha_resultante->refencia_temporal)
        {
            linha_resultante = linha_atual;
        }
    }
    return *linha_resultante;

}
