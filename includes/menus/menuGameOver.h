
#pragma once 

#include "menuPausa.h"

namespace Game::Menu {
    class MenuGameOver : public MenuPausa{
    
    public:

        //construtor e destrutor

        explicit MenuGameOver(Level::Level* fase);
        ~MenuGameOver() override;

        //metodo que cria botoes

        void criarBotoes() override;
    };
}