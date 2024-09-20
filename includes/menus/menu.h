
#pragma once

#include "../Entity/Ente.h"
#include "../menus/botao/botao.h"
#include "../menus/botao/botaoTexto.h"
#include "../BackGround/BackGround.h"
#include "card.h"
#include <list>

#define TAM_BOTAO_X 300.0f
#define TAM_BOTAO_Y 50.0f

namespace Game{

    namespace Observer{

        class ObserverMenu;
    }

    namespace Menu{

        class Menu : public Ente{

        protected:

            //atributos relacionado aos botoes do menu

            std::list<Botao::BotaoTexto*> listaDeBotao;
            std::list<Botao::BotaoTexto*>::iterator it;
            Botao::Texto titulo;

            const sf::Vector2f tamJanela;
            const sf::Vector2f tamBotao;

            sf::Vector2f posFundo;

            Observer::ObserverMenu* listenerMenu;
            bool mouseSelecionado;
            
            //metodo de atualiazcao da classe

            void  atualizarPosicaoFundo();
           
            virtual void criarFundo();
            virtual void criarBotoes() = 0;
           
            //metodo de inicializacao da classe

            void inicialiarIterador();

        public:

            //construtor e destrutor

            Menu(const IDs::IDs ID, const sf::Vector2f tamBotao, const std::string titulo, const unsigned int tamFonte);
            ~Menu() override;

            //metodo de adicao de um objeto botao

            void addBotao(const std::string infoTexto, const sf::Vector2f pos , const IDs::IDs ID, const  sf::Color corSelecionado);

            //metodo que altera o estado do observer da classe

            void mudarEstadoListener(const bool ativo);
           
            //metodo de verificacao do botao
            
            void selecionaParaCima();
            void selecionaParaBaixo();
            virtual void selecionaEsquerda();
            virtual void selecionaDireita();

            //getters da classe

            const IDs::IDs getIDBotaoSelecionado();
            const bool getMouseSelecionado();
           
            //metodo que verifica eventos d o mouse

            void eventoMouse(const sf::Vector2f posMouse);
           
            //metodos de atualizacao e visualizacao

            virtual void executar() = 0;
            void draw() override;  
        };
    }
}

