
#pragma once 

#include "menu.h"
#include "../fundo/fundo.h"

#define CAMINHO_IMAGEM_FUNDO "../Game/animations/background/menu/menuPrincipal.png"

namespace Game::Menu{
    class MenuPrincipal : public Menu{

    protected:

        //atributo relacionado ao fundo

        Fundo::Fundo fundo;

    private:

        //metodo criador do fundo

        void criarFundo() override;

    public:

        //construtores e destrutor

        MenuPrincipal();
        MenuPrincipal(const IDs::IDs ID, std::string titulo, const unsigned int tamFonte);
        ~MenuPrincipal() override;

        //metodo criador de Botoes
        
        void criarBotoes() override;
        
        //metodo que atualiza o estado de um objeto desta classe 

        void executar() override;
        
    };

}