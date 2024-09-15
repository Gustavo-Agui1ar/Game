
#pragma once 

#include "menu.h"
#include "../Levels/Level.h"

namespace Game::Menu{
    class MenuPausa : public Menu{

    private:

        //atributo relacionado ao fundo

        sf::RectangleShape painel;

    protected:

        //atributos relacionados ao fundo

        Level::Level* fase;
        sf::RectangleShape fundoEscuro;
        
        //atributo e metodo de atualizacao do botao
        
        void atualizarBotoes();
        float posBotaoY;
        
    public:

        //construtores e destrutor

        explicit MenuPausa(Level::Level* fase = nullptr);
        MenuPausa(const IDs::IDs ID, const std::string titulo, Level::Level* fase = nullptr);
        ~MenuPausa() override;

        //metodo criador de botoes

        void criarBotoes() override;
        
        //metodo de modificacao do atributo fase

        void setFase(Level::Level* fase);
        
        //metodo de acesso ao atributo fase

        Level::Level* getFase();

        //metodo de atualizacao de um objeto desta classe

        void executar() override;

    };
}