
#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

            //poteiro estatico da classe
            GerenciadorDeEventos* GerenciadorDeEventos::pEventos = nullptr;
            Lista::ListaListener* GerenciadorDeEventos::listaListener = nullptr;

            /**
             * @brief construtora da classe gerenciadorDeEventos 
            */
            GerenciadorDeEventos::GerenciadorDeEventos():
            pGrafico(pGrafico->getGerenciadorGrafico()),
            pEstado(pEstado->getGerenciadorDeEstado())
            {
                listaListener = new Lista::ListaListener();
            }

            /**
             * @brief destrutora da classe
            */
            GerenciadorDeEventos::~GerenciadorDeEventos()
            {
                if(pEventos != nullptr)
                    delete(pEventos);
                pEventos = nullptr;
            }

            /**
             * @brief metodo acessador da classe
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
             * @brief metodo responsavel pela verificacao de eventos caso acontecer algum evento é acionado o tratamento do mesmo aos observers
            */
            void GerenciadorDeEventos::executar()
            {
                sf::Event evento;

                while(pGrafico->getWindow()->pollEvent(evento))
                {
                    if(evento.type != sf::Event::LostFocus)
                    {
                        if(evento.type == sf::Event::KeyPressed)
                        listaListener->tratarTeclaPressionada(evento.key.code);
                        else if(evento.type == sf::Event::KeyReleased)
                        listaListener->tratarTeclaSolta(evento.key.code);
                        else if(evento.type == sf::Event::MouseMoved)
                            listaListener->notificarMovimentoMouse(evento.mouseMove);
                        else if(evento.type == sf::Event::MouseButtonReleased)
                            listaListener->notificarBotaoMouseSolta(evento.mouseButton.button);
                        else if(evento.type == sf::Event::Closed)
                            pGrafico->fechaJanela();
                    }
                    else{
                        if(pEstado->getEstadoAtual()->getID() == IDs::IDs::floresta_do_amanhecer)
                            pEstado->addEstado(IDs::IDs::menu_pause);
                    }
                }
            }

            /**
             * @brief adiciona um observer a lista
             * 
             * @param listener observer a ser adicionado
            */
            void GerenciadorDeEventos::addListener(Listener::Listener* listener)
            {
                listaListener->addListener(listener);
            }

            /**
             * @brief remove um observer da lista 
            */
            void GerenciadorDeEventos::removerListener(Listener::Listener* listener)
            {
                listaListener->removerListener(listener);
            }
    }
}



