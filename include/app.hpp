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
    Cache cache;
    Memoria memoria;
    Config config;
};

#endif // APP_H
