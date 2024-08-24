
#pragma once 

#include "menuPrincipal.h"
#include "../gerenciador/gerenciadorArquivo.h"
#include "../fases/fase.h"

namespace Game::Menu {
    class MenuCarregar : public MenuPrincipal {

    private:

        Gerenciador::GerenciadorArquivo gerenciadorArquivo;

        //atributos relacionados aos cards de carregamento

        std::list<Card*> listaCards;
        std::list<Card*>::iterator itCards;

        //atributo do fundo

        Fase::Fase* fase;
        sf::RectangleShape fundoEscuro;

        //metodo de inicializacao

        void inicializarCards();

    public:
        
        //construtor e destrutor

        explicit MenuCarregar(Fase::Fase* fase = nullptr);
        ~MenuCarregar() override;

        //metodo de verificao de botoes

        void selecionaEsquerda() override;
        void selecionaDireita() override;
        
        void deletarArquivos();
        Card* getCardSelecionado()const;
        
        //metodos criadores de botoes

        void criarBotaoBug();
        void criarBotoes() override;
        
        //metodos de atualizacao e visualizacao

        void desenharCards();
        void executar() override;
    };
}