
#pragma once 

#include "menu.h"
#include "../fundo/fundo.h"

#define CAMINHO_IMAGEM_FUNDO "C:/Users/gusta/OneDrive/Documentos/Faculdade/1-Periodo/projetos a parte/Game/animations/backgorund/menu/menuPrincipal.png"

namespace Game{

    namespace Menu{
        
        class MenuPrincipal : public Menu{

        protected:

            //atributo relacionado ao fundo

            Fundo::Fundo fundo;

        private:

            //metodo criador do fundo

            void criarFundo();

        public:

            //construtores e destrutor

            MenuPrincipal();
            MenuPrincipal(const IDs::IDs ID, std::string titulo, const unsigned int tamFonte);
            virtual ~MenuPrincipal();

            //metodo criador de Botoes
            
            virtual void criarBotoes();
            
            //metodo que atualiza o estado de um objeto desta classe 

            virtual void executar();
            
        };

    }
}