
#pragma once

#include "../gerenciador/gerenciadorGrafico.h"
#include "../jogador/jogador.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeEventos{


        private:

            //atributo grafico
            GerenciadorGrafico *pGrafico;
            
            //atributo de verificacao de eventod do jogador
            Entidade::Personagem::Jogador::Jogador *jogador;

            //ponteiro responsavel por 'distribuir' a classe 
            static GerenciadorDeEventos *pEventos;

            //construtora
            GerenciadorDeEventos();

        public:

            //destrutora
            ~GerenciadorDeEventos();
            
            //metodo de acesso a classe
            static GerenciadorDeEventos* getGerenciadorDeEventos();
            
            //metodo seter e geter de jogador
            void setJogador(Entidade::Personagem::Jogador::Jogador *jogador);
            Entidade::Personagem::Jogador::Jogador* getJogador();
            
            //metodos de tratamentoo de eventos
            void verificaTeclaPresionada(sf::Keyboard::Key tecla);
            void verificaTeclaSolta(sf::Keyboard::Key tecla);
            
            //metodo de verificacao de eventos
            void executar();
        };
    }
}
