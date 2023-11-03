#include "../includes/principal.h"
#include<iostream>

/*------------------------------------------------------------------*/

Game::Principal::Principal()
{

    gerenciadorGrafico = gerenciadorGrafico->getGerenciadorGrafico();

    gerenciadorDeEventos = gerenciadorDeEventos->getGerenciadorDeEventos();

    pEstado = pEstado->getGerenciadorDeEstado();

    if(pEstado == nullptr)
    {
        std::cout<<"nao foi possivel criar o gEstado";
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
    while (gerenciadorGrafico->verificaJanelaAberta()){

        gerenciadorDeEventos->executar();

        gerenciadorGrafico->limpaJanela();

        pEstado->executar();

        gerenciadorGrafico->mostraElementos();

        gerenciadorGrafico->resetarRelogio();
    }
    return;
}

/*------------------------------------------------------------------*/

Game::Principal::~Principal()
{

}

/*------------------------------------------------------------------*/

void Game::Principal::criarEstadoInicial()
{
    pEstado->addEstado(IDs::IDs::forest);
}
