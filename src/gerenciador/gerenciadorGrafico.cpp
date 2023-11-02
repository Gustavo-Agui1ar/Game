
#include "../../includes/gerenciador/gerenciadorGrafico.h"
#include <iostream>


namespace Game{

    namespace Gerenciador{

        //atributos estaticos da classe
        GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;
        float GerenciadorGrafico::tempo = 0.0f;

        /**
         * construtor da classe
        */

        GerenciadorGrafico::GerenciadorGrafico():
        window(new sf::RenderWindow (sf::VideoMode(LARGURA_TELA,ALTURA_TELA), "game")),camera(sf::Vector2f(LARGURA_TELA,ALTURA_TELA)),
        relogio()
        {
            if(window == nullptr)
            {
                std::cout<<"error";
                exit(1);
            }
        }

        /**
         * destrutora da classe 
         * desaçloca a  memoria 
         * relacionada a janela
        */

        GerenciadorGrafico::~GerenciadorGrafico()
        {
            if(window)
            {
                delete (window);
                window = nullptr;
            }
        }

        /**
         * metodo que reinicia o tempo em relogio
        */

        void GerenciadorGrafico::resetarRelogio()
        {
            tempo = relogio.getElapsedTime().asSeconds();
            relogio.restart();
        }

        /**
         * metodo que retorna o tempo em relogio
        */

        const float GerenciadorGrafico::getTempo()
        {
            return tempo;
        }

        /**
         * metodo acessador da classe
        */

        GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico()
        {
            if(pGrafico == nullptr)
                pGrafico = new GerenciadorGrafico();

            return pGrafico;
        }

        /**
         * metodo que retorna a janela
        */

        sf::RenderWindow* GerenciadorGrafico::getWindow()
        {
            return window;
        }

        /**
         * metodo que limpa a janela
        */

        void GerenciadorGrafico::limpaJanela()
        {
            window->clear(sf::Color::White);
        }

        /**
         * metodo que desenha algo na tela 
         * 
         * parametros:
         * 
         * corpo: item a ser desenhado
         * 
        */

        void GerenciadorGrafico::desenhaElemento(sf::RectangleShape corpo)
        {
            window->draw(corpo);
        }

        /**
         * metodo que mostra todos os elementos desenhados na tela
        */

        void GerenciadorGrafico::mostraElementos()
        {
            window->display();
        }

        /**
         * metodo que encerra a janela
        */

        void GerenciadorGrafico::fechaJanela()
        {
            window->close();
        }

        /**
         * metodo que verifica o funcionamento da janela
        */

        const bool GerenciadorGrafico::verificaJanelaAberta()
        {
            if(window->isOpen())
                return true;

            return false;
        }

        /**
         * metodo responsavel por carregar texturas
         * 
         * parametros:
         * 
         * caminhoTextura: textura a ser carregada
        */

        sf::Texture GerenciadorGrafico::carregarTextura(const char* caminhoTextura)
        {
            sf::Texture textura;

            if(!textura.loadFromFile(caminhoTextura)){
                std::cout<<"nao foi possivel carregar a textura";
                exit(1);
            }
            return textura;
        }

        /**
        * metodo que atualiza a posicao da camera
        */ 
           
        void GerenciadorGrafico::atualizarCamera(sf::Vector2f pos)
        {
           // camera.atualizar(pos);
            camera.atualizar(sf::Vector2f(pos.x,ALTURA_TELA/2));
            window->setView(camera.getCamera());
        }

        /**
         * metodo que retorna a camera
        */

        sf::View GerenciadorGrafico::getCamera()
        {
            return camera.getCamera();
        }

        /**
         * metodo que retorna o tamanho da janela
        */

        const sf::Vector2f GerenciadorGrafico::getTamJanela(){
            return (sf::Vector2f)window->getSize();
        }
    }
}




