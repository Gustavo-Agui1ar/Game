
#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

            //poteiro estatico da classe
            GerenciadorDeEventos* GerenciadorDeEventos::pEventos = nullptr;


            /**
             *construtora da classe gerenciadorDeEventos 
            */

            GerenciadorDeEventos::GerenciadorDeEventos():
            pGrafico(pGrafico->getGerenciadorGrafico()),
            pEstado(pEstado->getGerenciadorDeEstado())
            {

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
             * metodo que trata os eventos relacionados
             * a  presionacao  de  uma  tecla
             * 
             * parametros:
             * 
             * tecla: tecla a ser analizada
            */

            void GerenciadorDeEventos::verificaTeclaPresionada(sf::Keyboard::Key tecla)
            {
                if(pEstado->getEstadoAtual()->getID() == IDs::IDs::caverna ||
                   pEstado->getEstadoAtual()->getID() == IDs::IDs::forest){
                        Estado::EstadoFase* fase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                        Entidade::Personagem::Jogador::Jogador* jogador = fase->getPlayer();

                        if(jogador == nullptr)
                        {
                            std::cout<<"nao foi possivel recuperar o jogador";
                            exit(1);
                        }

                    if(tecla == sf::Keyboard::A){
                        jogador->andar(true);
                    }else if(tecla == sf::Keyboard::D){
                        jogador->andar(false);
                    }else if(tecla == sf::Keyboard::W){
                        jogador->pular();
                    }else if(tecla == sf::Keyboard::E){
                        jogador->atacar();
                    }else if(tecla == sf::Keyboard::Escape){
                        pGrafico->fechaJanela();
                    }
                }
            }

            /**
             * metodo que trata eventos relacionados a teclass soltas
             * 
             * parametros:
             * 
             * tecla: tecla a ser analizada
            */

            void GerenciadorDeEventos::verificaTeclaSolta(sf::Keyboard::Key tecla)
            {
                if(pEstado->getEstadoAtual()->getID() == IDs::IDs::caverna ||
                pEstado->getEstadoAtual()->getID() == IDs::IDs::forest)
                {
                    Estado::EstadoFase* fase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                    Entidade::Personagem::Jogador::Jogador* jogador = fase->getPlayer();

                    if(jogador == nullptr)
                    {
                        std::cout<<"nao foi possivel recuperar o jogador";
                        exit(1);
                    }

                    if(tecla == sf::Keyboard::A || tecla == sf::Keyboard::D)
                    {
                        jogador->parar();
                    }   
                    else if(tecla == sf::Keyboard::E)
                    {
                    jogador->pararAtaque();
                    }
                }
                if(tecla == sf::Keyboard::Q)
                    pEstado->removerEstado();
                else if(tecla == sf::Keyboard::P)
                    pEstado->addEstado(IDs::IDs::caverna);
                else if(tecla == sf::Keyboard::O)
                    pEstado->addEstado(IDs::IDs::forest);
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
                        verificaTeclaPresionada(evento.key.code);
                    else if(evento.type == sf::Event::KeyReleased)
                        verificaTeclaSolta(evento.key.code);
                    else if(evento.type == sf::Event::Closed)
                        pGrafico->fechaJanela();
                }
            }
    }
}



