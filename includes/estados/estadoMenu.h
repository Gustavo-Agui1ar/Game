
#pragma once 

#include "estado.h"
#include "../fases/fase.h"
#include "../menus/menu.h"


namespace Game{

    namespace Gerenciador{

        class GerenciadoDeEstado;
    }

    namespace Estado{

        class EstadoMenu : public Estado{

            private:

                static Gerenciador::GerenciadorDeEstado* pEstado;

                //atributo principal da classe
              
                Menu::Menu* menu;
                
                //metodo responsavel por inicializar o menu
         
               void criarMenu();

            public:

                //construtor e destrutor 
             
                explicit EstadoMenu(const IDs::IDs ID);
                ~EstadoMenu() override;

                //metodo que altera o estado do observador da classe
              
                void mudarEstadoListener(const bool ativo) override;
                
                //getters daa classe
             
                Menu::Menu* getMenu();
                Fase::Fase* getFase();

                //metodo responsavel pela atualizacao e visualizacao  da classe
              
                void executar() override;
        };

    }

}