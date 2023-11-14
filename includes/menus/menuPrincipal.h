
#pragma once 

#include "menu.h"
#include "../fundo/fundo.h"

#define CAMINHO_IMAGEM_FUNDO "C:/Users/gusta/OneDrive/Documentos/Faculdade/1-Periodo/projetos a parte/Game/animations/backgorund/menu/menuPrincipal.png"

namespace Game{

    namespace Menu{
        
        class MenuPrincipal : public Menu{

        protected:

            Fundo::Fundo fundo;

        private:

            void criarFundo();

        public:

            MenuPrincipal();
            virtual ~MenuPrincipal();

            virtual void criarBotoes();
            virtual void executar();
            
        };

    }
}