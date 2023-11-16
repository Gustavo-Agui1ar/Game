
#pragma once

#include "../entidade/Ente.h"
#include "../botao/botao.h"
#include "../botao/botaoTexto.h"
#include "../fundo/fundo.h"
#include <list>

#define TAM_BOTAO_X 300.0f
#define TAM_BOTAO_Y 50.0f

namespace Game{

    namespace Listener{

        class ListenerMenu;
    }

    namespace Menu{

        class Menu : public Ente{

        protected:

            Listener::ListenerMenu* listenerMenu;
            std::list<Botao::BotaoTexto*> listaDeBotao;
            std::list<Botao::BotaoTexto*>::iterator it;
            const sf::Vector2f tamJanela;
            const sf::Vector2f tamBotao;

            sf::Vector2f posFundo;

            Botao::Texto titulo;
            bool mouseSelecionado;

            void  atualizarPosicaoFundo();
            virtual void criarFundo();
            virtual void criarBotoes() = 0;
            void inicialiarIterador();

        public:

            Menu(const IDs::IDs ID, const sf::Vector2f tamBotao, const std::string titulo, const unsigned int tamFonte);
            virtual ~Menu();

            void addBotao(const std::string infoTexto, const sf::Vector2f pos , const IDs::IDs ID, const  sf::Color corSelecionado);
            void mudarEstadoListener();
            void selecionaParaCima();
            void selecionaParaBaixo();

            const IDs::IDs getIDBotaoSelecionado();
            void eventoMouse(const sf::Vector2f posMouse);
            const bool getMouseSelecionado();
            virtual void executar() = 0;
            void desenhar();  
        };
    }
}

