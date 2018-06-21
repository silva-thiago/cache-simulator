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
