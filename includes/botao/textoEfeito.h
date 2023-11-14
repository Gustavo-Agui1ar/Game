
#pragma once

#include "texto.h"

namespace Game{

    namespace Menu{

        namespace Botao{

            class TextoEfeito : public Texto{

            private:

                int transparente;
                bool apagando;

                void atualizar();

            public:

                TextoEfeito(const sf::Font fonte, const std::string infoTexto);
                ~TextoEfeito();

                void mudarTransparencia();
                const bool getApagando();
                const int getTransparente();
                void setTransparente(int tansparente);
                void resetar();

            };
        }
    }
}