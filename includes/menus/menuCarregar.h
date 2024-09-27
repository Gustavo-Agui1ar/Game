
#pragma once 

#include "menuPrincipal.h"
#include "../Manager/FileManager.h"
#include "../Levels/Level.h"

namespace Game::Menu {
    class MenuCarregar : public MenuPrincipal {

    private:

        Manager::FileManager gerenciadorArquivo;

        //atributos relacionados aos cards de carregamento

        std::list<Card*> listaCards;
        std::list<Card*>::iterator itCards;

        //atributo do fundo

        Level::Level* fase;
        sf::RectangleShape fundoEscuro;

        //metodo de inicializacao

        void inicializarCards();

    public:
        
        //construtor e destrutor

        explicit MenuCarregar(Level::Level* fase = nullptr);
        ~MenuCarregar() override;

        //metodo de verificao de botoes

        void selecionaEsquerda() override;
        void selecionaDireita() override;
        
        void deletarArquivos();
        Card* getCardSelecionado()const;
        
        //metodos criadores de botoes

        void criarBotoes() override;
        
        //metodos de atualizacao e visualizacao

        void desenharCards();
        void executar() override;
    };
}