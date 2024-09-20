#include "../includes/principal.h"
#include<iostream>

/*------------------------------------------------------------------*/

Game::Principal::Principal()
{

    gerenciadorGrafico = Manager::GraphicManager::getGraphicManager();

    gerenciadorDeEventos = Manager::EventManager::getEventManager();

    pEstado = Manager::StateManager::getStateManager();

    if(pEstado == nullptr)
    {
        std::cout<<"nao foi possivel criar o pEstado";
        exit(1);
    }

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

    criarEstadoInicial();
    executar();

}

/*------------------------------------------------------------------*/

void Game::Principal::executar()
{
    while (gerenciadorGrafico->checkIsOpenWindow())
    {

        gerenciadorDeEventos->execute();

        gerenciadorGrafico->clearWindow();
        
        pEstado->execute();

        gerenciadorGrafico->showElements();

        gerenciadorGrafico->resetClock();
    }
}

/*------------------------------------------------------------------*/

Game::Principal::~Principal()
{
    if(gerenciadorDeEventos != nullptr)
        delete gerenciadorDeEventos;
    if(gerenciadorGrafico != nullptr)
        delete gerenciadorGrafico;

}

/*------------------------------------------------------------------*/

void Game::Principal::criarEstadoInicial()
{
    pEstado->addState(IDs::IDs::main_menu);
}
