
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

                static Gerenciador::GerenciadorDeEventos* pEvento;
                static Gerenciador::GerenciadorDeEstado* pEstado;

                std::map<sf::Keyboard::Key, char> tecPadrao;
                std::map<sf::Keyboard::Key, std::string> tecEspecial;

            private:

                bool ativo;
                void inicializarComandosteclado();

            public:

                Listener();
                virtual ~Listener();

                void mudarEstado();
                const bool getAtivo();
                void removerListener();
                
                virtual void teclaPressionada(const sf::Keyboard::Key tecla) = 0;
                virtual void teclaSolta(const sf::Keyboard::Key tecla) = 0;
        
        };

    }
}