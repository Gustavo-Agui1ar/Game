
#include "../../includes/gerenciador/gerenciadorDeEventos.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

            //poteiro estatico da classe
            GerenciadorDeEventos* GerenciadorDeEventos::pEventos = nullptr;


            /**
             *construtora da classe gerenciadorDeEventos 
            */

            GerenciadorDeEventos::GerenciadorDeEventos():
            pGrafico(pGrafico->getGerenciadorGrafico())
            {

            }

            /**
             * destrutora da classe
            */

            GerenciadorDeEventos::~GerenciadorDeEventos(){}

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
             * metodo que seta o jogador
             * 
             * parametros: 
             * 
             * jogador: jogador a ser setado
            */

            void GerenciadorDeEventos::setJogador(Entidade::Personagem::Jogador::Jogador *jogador)
            {
                this->jogador = jogador;
            }

            /**
             * metodo que retorna o jogador
            */

            Entidade::Personagem::Jogador::Jogador* GerenciadorDeEventos::getJogador()
            {
                return jogador;
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

            /**
             * metodo que trata eventos relacionados a teclass soltas
             * 
             * parametros:
             * 
             * tecla: tecla a ser analizada
            */

            void GerenciadorDeEventos::verificaTeclaSolta(sf::Keyboard::Key tecla)
            {
                if(tecla == sf::Keyboard::A || tecla == sf::Keyboard::D)
                {
                    jogador->parar();
                }   
                else if(tecla == sf::Keyboard::E)
                {
                jogador->pararAtaque();
                }
                    
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



