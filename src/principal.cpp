#include "../includes/principal.h"
#include<iostream>

/*------------------------------------------------------------------*/

Game::Principal::Principal()
{

    gerenciadorGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

    gerenciadorDeEventos = gerenciadorDeEventos->getGerenciadorDeEventos();

    pEstado = Gerenciador::GerenciadorDeEstado::getGerenciadorDeEstado();

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
    while (gerenciadorGrafico->verificaJanelaAberta())
    {

        gerenciadorDeEventos->executar();

        gerenciadorGrafico->limpaJanela();
        
        pEstado->executar();

        gerenciadorGrafico->mostraElementos();

        gerenciadorGrafico->resetarRelogio();
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
    pEstado->addEstado(IDs::IDs::main_menu);
}
