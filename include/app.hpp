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

    void subs_aleatoria         (Bloco& bloco);
    void subs_fifo              (Bloco& bloco);
    void subs_lfu               (Bloco& bloco);
    void subs_lru               (Bloco& bloco);

    Cache cache;
    Memoria memoria;
    Config config;
};

#endif // APP_H
