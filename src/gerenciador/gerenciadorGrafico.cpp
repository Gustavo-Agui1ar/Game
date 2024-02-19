
#include "../../includes/gerenciador/gerenciadorGrafico.h"
#include <iostream>


namespace Game{

    namespace Gerenciador{

        //atributos estaticos da classe
        GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;
        float GerenciadorGrafico::tempo = 0.0f;

        /**
         * @brief construtor da classe
        */
        GerenciadorGrafico::GerenciadorGrafico():
        window(new sf::RenderWindow (sf::VideoMode(LARGURA_TELA,ALTURA_TELA), "game")),camera(sf::Vector2f(LARGURA_TELA,ALTURA_TELA)),
        relogio()
        {
            if(window == nullptr)
            {
                std::cout<<"Gerenciador::GerenciadorGrafico: erro ao criar janela";
                exit(1);
            }
        }

        /**
         * @brief destrutora da classe desaloca a memoria relacionada a janela
        */
        GerenciadorGrafico::~GerenciadorGrafico()
        {
            if(window)
            {
                delete (window);
                window = nullptr;
            }
            if(pGrafico != nullptr)
                delete(pGrafico);
                
            pGrafico = nullptr;
        }

        /**
         * @brief metodo que reinicia o tempo em relogio
        */
        void GerenciadorGrafico::resetarRelogio()
        {
            tempo = relogio.getElapsedTime().asSeconds();
            relogio.restart();
        }

        /**
         * @brief metodo de acesso ao relogio
         * 
         * @return retorna o tempo em segundos decorrido desde da ultima atualizacao
        */
        const float GerenciadorGrafico::getTempo()
        {
            return tempo;
        }

        /**
         * @brief metodo de acesso da classe
         * 
         * @return retorna um ponteiro para um objeto da classe
        */
        GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico()
        {
            if(pGrafico == nullptr)
                pGrafico = new GerenciadorGrafico();

            return pGrafico;
        }

        /**
         * @brief metodo qde acesso a janela
         * 
         * @return retorna um objeto janela 
        */
        sf::RenderWindow* GerenciadorGrafico::getWindow()
        {
            return window;
        }

        /**
         * @brief metodo que limpa a janela
        */
        void GerenciadorGrafico::limpaJanela()
        {
            window->clear();
        }

        /**
         * @brief metodo que desenha algo na tela 
         * 
         * @param corpo item a ser desenhado
        */
        void GerenciadorGrafico::desenhaElemento(sf::RectangleShape corpo)
        {
            window->draw(corpo);
        }

        /**
         * @brief metodo que mostra todos os elementos desenhados na tela
        */
        void GerenciadorGrafico::mostraElementos()
        {
            window->display();
        }

        /**
         * @brief metodo que encerra a janela
        */
        void GerenciadorGrafico::fechaJanela()
        {
            window->close();
        }

        /**
         * @brief metodo que verifica se a janela esta aberta
         * 
         * @return retorna um boleano indicando se a janela esta aberta
        */
        const bool GerenciadorGrafico::verificaJanelaAberta()
        {
            if(window->isOpen())
                return true;

            return false;
        }

        /**
         * @brief metodo responsavel por carregar texturas
         * 
         * @param caminhoTextura textura a ser carregada
         * 
         * @return retorna a textura carregada
        */
        sf::Texture GerenciadorGrafico::carregarTextura(const char* caminhoTextura)
        {
            sf::Texture textura;

            if(!textura.loadFromFile(caminhoTextura)){
                std::cout<<"Gerenciador::GerenciadorGrafico: nao foi possivel carregar a textura";
                exit(1);
            }
            return textura;
        }

        /**
         * @brief metodo responsavel por carregar uma fonte 
         * 
         * @param caminhoFonte caminho do arquivo da fonte
         * 
         * @return retorna a fonte carregada
        */
        sf::Font GerenciadorGrafico::carregarFonte(const char* caminhoFonte){
            sf::Font fonte;
            if(!(fonte.loadFromFile(caminhoFonte)))
            {
                throw("ERROR::Game::Gerenciador::GerenciadorGrafico::nao foi possivel encontrar o caminho da fonte");
            }
            return fonte;
        }

        /**
        * @brief metodo que atualiza a posicao da camera
        * 
        * @param pos posicao a ser atribuida a camera
        */ 
        void GerenciadorGrafico::atualizarCamera(sf::Vector2f pos)
        {
           // camera.atualizar(pos);
            camera.atualizar(sf::Vector2f(pos));
            window->setView(camera.getCamera());
        }

        /**
         * @brief metodo de acesso a camera
         * 
         * @return retorna a camera
        */
        sf::View GerenciadorGrafico::getCamera()
        {
            return camera.getCamera();
        }

        /**
         * @brief metodo que retorna o tamanho da janela
         * 
         * @return retorna um objeto vector2f contendo o tamanho da janela 
        */
        const sf::Vector2f GerenciadorGrafico::getTamJanela(){
            return sf::Vector2f(LARGURA_TELA, ALTURA_TELA);
        }

        /**
         * @brief desenha um elemento do tipo texto na janela 
         * 
         * @param texto texto a ser desenhado
        */
        void GerenciadorGrafico::desenhaElemento(sf::Text texto)
        {
            window->draw(texto);
        }

        /**
         * @brief reinicia o tamanho e posicao da camera
        */
        void GerenciadorGrafico::resetarJanela(){
            camera.resetar(sf::Vector2f(LARGURA_TELA / 2.0f, ALTURA_TELA / 2.0f));
            window->setView(camera.getCamera());
        }

        void GerenciadorGrafico::setTamCamera(sf::Vector2f tam)
        {
            camera.setTam(tam);
        }
    }
}




