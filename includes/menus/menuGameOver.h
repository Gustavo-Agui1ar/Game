
#pragma once 

#include "menuPausa.h"

namespace Game {

    namespace Menu{

        class MenuGameOver : public MenuPausa{
        
        public:

            //construtor e destrutor

            MenuGameOver(Fase::Fase* fase);
            ~MenuGameOver();

            //metodo que cria botoes

            void criarBotoes();
        };
    }
}