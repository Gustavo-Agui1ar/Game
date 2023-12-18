
#pragma once 

#include "menuPausa.h"

namespace Game {

    namespace Menu{

        class MenuGameOver : public MenuPausa{
        
        public:

            MenuGameOver(Fase::Fase* fase);
            ~MenuGameOver();
            void criarBotoes();
        };
    }
}