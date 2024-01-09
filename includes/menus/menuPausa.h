
#pragma once 

#include "menu.h"
#include "../fases/fase.h"

namespace Game{

    namespace Menu{

        class MenuPausa : public Menu{

        private:

            //atributo relacionado ao fundo

            sf::RectangleShape painel;

        protected:

            //atributos relacionados ao fundo

            Fase::Fase* fase;
            sf::RectangleShape fundoEscuro;
            
            //atributo e metodo de atualizacao do botao
            
            void atualizarBotoes();
            float posBotaoY;
            
        public:

            //construtores e destrutor

            MenuPausa(Fase::Fase* fase = nullptr);
            MenuPausa(const IDs::IDs ID, const std::string titulo, Fase::Fase* fase = nullptr);
            ~MenuPausa();

            //metodo criador de botoes

            virtual void criarBotoes();
            
            //metodo de modificacao do atributo fase

            void setFase(Fase::Fase* fase);
            
            //metodo de acesso ao atributo fase

            Fase::Fase* getFase();

            //metodo de atualizacao de um objeto desta classe

            virtual void executar();

        };
    }
}