#include "../includes/principal.h"
#include<iostream>

/*------------------------------------------------------------------*/

Game::Principal::Principal()
{
    gerenciadorGrafico = gerenciadorGrafico->getGerenciadorGrafico();

    gerenciadorDeEventos = gerenciadorDeEventos->getGerenciadorDeEventos();

    fase = nullptr;


    if(gerenciadorGrafico == nullptr)
    {
       std::cout<<"nao foi possivel criar o geerenciador grafico";
       exit(1);
    }
    if(gerenciadorDeEventos == nullptr)
    {
        std::cout<<"nao foi possivel criar o geerenciador de eventos";
        exit(1);
    }
    criarFase();
    executar();

}

/*------------------------------------------------------------------*/

void Game::Principal::executar()
{
    while (gerenciadorGrafico->verificaJanelaAberta()){

        gerenciadorDeEventos->executar();

        gerenciadorGrafico->limpaJanela();

        fase->executar();

        gerenciadorGrafico->mostraElementos();

        gerenciadorGrafico->resetarRelogio();
    }
    return;
}

/*------------------------------------------------------------------*/

Game::Principal::~Principal()
{
    if(fase)
    {
        delete(fase);
        fase = nullptr;
    }
}

/*------------------------------------------------------------------*/

void Game::Principal::criarFase()
{
    //Fase::Caverna* aux = new Fase::Caverna();
    Fase::Forest* aux = new Fase::Forest();

    if(aux == nullptr)
    {
       std::cout<<"nao foi possivel criar a fase";
       exit(1);
    }
    fase = static_cast<Fase::Fase*>(aux);

    fase->criarFundo();
    fase->criarMapa();

}
