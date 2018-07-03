/**
 * @file main.cpp
 * @brief Implementação da classe Main em C++
 * @author Pablo
 * @since 02/07/2018
 * @date 03/07/2018
 */

#include <iostream>
#include <fstream>

#include "config.hpp"
#include "app.hpp"

int main(int argc, char const *argv[])
{
	// --- Ler configuração do simulador ---

	// Arquivo de entrada do programa
	std::ifstream arquivo;
	arquivo.open("data/config.txt");
	if (!arquivo.is_open())
		throw std::runtime_error("Arquivo nao encontrado");

	// Variavel de configuração
	Config cfg;

	// Ler cada uma das configurações do arquivo
	arquivo >> cfg.numero_de_palavras;
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
	while (std::cin >> comando)
	{
		if (comando == "Show" || comando == "show" || comando == "s")
		{
			app.show();
		}
		else if (comando == "Read" || comando == "read" || comando == "r")
		{
			std::cin >> comando;
			try
			{
				int endereco = std::stoi(comando);
				if (endereco < 0 or endereco > (cfg.blocos_da_memoria * cfg.numero_de_palavras))
					throw std::out_of_range("");
				app.read(endereco);
			}
			catch (std::invalid_argument &)
			{
				std::cout << "Endereço ínvalido, digite novamete\n";
			}
			catch (std::out_of_range &)
			{
				std::cout << "Endereço fora do intervalo.\n";
			}
		}
		else if (comando == "Write" || comando == "write" || comando == "w")
		{
			try
			{
				std::cin >> comando;
				int endereco = std::stoi(comando);
				if (endereco < 0 or endereco > (cfg.blocos_da_memoria * cfg.numero_de_palavras))
				{
					throw std::out_of_range("Endereço fora do intervalo.");
				}
				std::cin >> comando;
				int valor = std::stoi(comando);
				if (valor < 0)
				{
					throw std::out_of_range("Valor fora do intervalo.");
				}
				app.write(endereco, valor);
			}
			catch (std::invalid_argument &)
			{
				std::cout << "Endereço ou valor ínvalido, digite novamente.\n";
			}
			catch (std::out_of_range &error)
			{
				if (error.what() == std::string("stoi"))
					std::cout << "Valor fora do intervalo do tipo int.\n";
				else
					std::cout << error.what() << std::endl;
			}
		}
		else if (comando == "Quit" || comando == "quit" || comando == "q")
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
