
#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

            //poteiro estatico da classe
            GerenciadorDeEventos* GerenciadorDeEventos::pEventos = nullptr;
            Lista::ListaListener* GerenciadorDeEventos::listaListener = nullptr;

            /**
             *construtora da classe gerenciadorDeEventos 
            */

            GerenciadorDeEventos::GerenciadorDeEventos():
            pGrafico(pGrafico->getGerenciadorGrafico()),
            pEstado(pEstado->getGerenciadorDeEstado())
            {
                listaListener = new Lista::ListaListener();
            }

            /**
             * destrutora da classe
            */

            GerenciadorDeEventos::~GerenciadorDeEventos()
            {
                if(pEventos != nullptr)
                    delete(pEventos);
                pEventos = nullptr;
            }

            /**
             * metodo acessador da classe
            */

            GerenciadorDeEventos* GerenciadorDeEventos::getGerenciadorDeEventos()
            {
                if(pEventos == nullptr)
                {
                    pEventos =  new GerenciadorDeEventos();
                }
                return pEventos;
            }

            /**
             * metod responsavel pela verificacao de eventos 
            */

            void GerenciadorDeEventos::executar()
            {
                sf::Event evento;

                while(pGrafico->getWindow()->pollEvent(evento))
                {
                    if(evento.type == sf::Event::KeyPressed)
                       listaListener->tratarTeclaPressionada(evento.key.code);
                    else if(evento.type == sf::Event::KeyReleased)
                       listaListener->tratarTeclaSolta(evento.key.code);
                    else if(evento.type == sf::Event::Closed)
                        pGrafico->fechaJanela();
                }
            }

            void GerenciadorDeEventos::addListener(Listener::Listener* listener)
            {
                listaListener->addListener(listener);
            }

            void GerenciadorDeEventos::removerListener(Listener::Listener* listener)
            {
                listaListener->removerListener(listener);
            }
    }
}



