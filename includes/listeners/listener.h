
#pragma once

#include "SFML/Graphics.hpp"
#include <map>

namespace Game{

    namespace Gerenciador
    {
        class GerenciadorDeEventos;
        class GerenciadorDeEstado;
    }

    namespace Listener{


        class Listener{

            protected:

                //ponteiro usado para o listener se adicionar a lista de pEvento 
                static Gerenciador::GerenciadorDeEventos* pEvento;

                //ponteiro usado para adicionar/remover estado nos eventos de listener
                static Gerenciador::GerenciadorDeEstado* pEstado;

                //mapeamento das teclas usadas nos eventos tratados pelos listener
                std::map<sf::Keyboard::Key, char> tecPadrao;
                std::map<sf::Keyboard::Key, std::string> tecEspecial;

            private:

                //atributo de ativacao do listener
                bool ativo;

                //metodo que mapeia as teclas
                void inicializarComandosteclado();

            public:

                //construtora e destrutora
                Listener();
                virtual ~Listener();

                //metodos de alteracao e verificacao de lestener ativo 
                const bool getAtivo();
                void mudarEstado();

                //metodo de remocao de listener da lista de pEvento
                void removerListener();
                
                //metodo de tratamento das teclas (implementdada nas filhas)
                virtual void teclaPressionada(const sf::Keyboard::Key tecla) = 0;
                virtual void teclaSolta(const sf::Keyboard::Key tecla) = 0;
                virtual void moveMouse(const sf::Vector2f posMouse);
                virtual void botaoMouseSolta(const sf::Mouse::Button botaoMouse);
        
        };

    }
}