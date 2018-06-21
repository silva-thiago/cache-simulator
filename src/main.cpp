#include <iostream>
#include <fstream>

#include "config.hpp"
#include "app.hpp"

int main(void)
{
    // --- Ler configuração do simulador ---

    // Arquivo de entrada do programa
    std::ifstream arquivo;
    arquivo.open("data/config.txt");
    if(arquivo.fail())
        throw std::runtime_error("Arquivo nao encontrado");

    // Variavel de configuração
    Config cfg;

    // Ler cada uma das configurações do arquivo

    arquivo >> cfg.palavras_por_bloco;
    arquivo >> cfg.linhas_da_cache;
    arquivo >> cfg.blocos_da_memoria;
    arquivo >> cfg.tipo_de_mapeamento;
    arquivo >> cfg.numero_de_conjuntos;
    arquivo >> cfg.politica_de_substituicao;
    arquivo >> cfg.politica_de_escrita;

    arquivo.close();

    // Classe app que contém todos os comandos que podem ser usados

    App app(cfg);

    // --- Rodar interface de usuário ---

    // Comando que o usuário usou
    std::string comando;
    // Esperar comando
    std::cout << "Command> ";
    while(std::cin >> comando)
    {
        std::string cmd = comando.substr(0, comando.find_first_of(' '));
        if(cmd == "Show")
        {
            app.show();
        }
        else if(cmd == "Read")
        {
            app.read(stoi(comando.substr(comando.find_first_of(' '))));
        }
        else if(cmd == "Write")
        {
            app.write();
        }
        else if(cmd == "Quit")
        {
            std::exit(0);
        }
        else
        {
            std::cout << "Comando invalido, digite novamente.\n";
        }
        std::cout << "Command> ";
    }

}
