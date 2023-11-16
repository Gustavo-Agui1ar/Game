/*
#pragma once 

#include "menu.h"
#include "../fases/fase.h"

namespace Game{

    namespace Menu{

        class MenuPausa : public Menu{

        private:

            sf::RectangleShape painel;

        protected:

            Fase::Fase* fase;
            sf::RectangleShape fundoEscuro;
            float posBotaoY;

            void atualizarBotoes();
            
        public:

            MenuPausa(Fase::Fase* fase = nullptr);
            MenuPausa(const IDs::IDs ID, const std::string titulo, Fase::Fase* fase = nullptr);
            ~MenuPausa();

            virtual void criarBotoes();
            void setFase(Fase::Fase* fase);
            Fase::Fase* getFase();
            virtual void executar();

        };
    }
}*/