
#pragma once

#include "menuPausa.h"
#include "../gerenciador/gerenciadorArquivo.h"

namespace Game::Menu{


    class MenuSalvar : public MenuPausa{

    private:
        
        Gerenciador::GerenciadorArquivo gArquivo;
        
        //atributos relacionados aos cards 

        std::list<Card*> listaCards;
        std::list<Card*>::iterator itCard;

        //metodo de inicializacao

        void inicializarCards();
        
    public:

        //construtor e destrutor

        explicit MenuSalvar(Level::Level* fase);
        ~MenuSalvar() override;

        //metodo criador de botoes

        void criarBotoes() override;

        //metodo ue salva as informacoes do atributo fase da classe MenuPausa

        void salvar();

        //metodo de verificacao de eventos card

        void selecionaEsquerda() override;
        void selecionaDireita() override;

        //metodos de atualizacao e visualizacao

        void desenharCards();
        void executar() override;

    };
}