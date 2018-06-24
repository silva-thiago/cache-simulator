#ifndef APP_H
#define APP_H

#include "config.hpp"
#include "cache.hpp"

class App
{
public:
    App(Config& cfg);

    void read(int endereco);
    void write();
    void show();

private:

    bool mapeamento_direto      (int numero_do_bloco);
    bool mapeamento_associativo (int numero_do_bloco);
    bool mapeamento_misto       (int numero_do_bloco);

    void atualizar_contadores   (Linha& linha);

    void substituir             (Bloco& novo_bloco, int indice_inicial = 0, int tamanho_conjunto = 0);
    void subs_aleatoria         (Bloco& novo_bloco, int indice_inicial = 0, int tamanho_conjunto = 0);
    void subs_fifo              (Bloco& novo_bloco, int indice_inicial = 0, int tamanho_conjunto = 0);
    void subs_lfu               (Bloco& novo_bloco, int indice_inicial = 0, int tamanho_conjunto = 0);
    void subs_lru               (Bloco& novo_bloco, int indice_inicial = 0, int tamanho_conjunto = 0);

    Cache cache;
    Memoria memoria;
    Config config;
};

#endif // APP_H
