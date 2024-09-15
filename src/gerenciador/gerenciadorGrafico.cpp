
#include "../../includes/gerenciador/gerenciadorGrafico.h"
#include <iostream>


namespace Game{

    namespace Gerenciador{

        GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;
        float GerenciadorGrafico::tempo = 0.0f;

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
                delete window;
                window = nullptr;
            }
            pGrafico = nullptr;
        }

        void GerenciadorGrafico::resetarRelogio()
        {
            tempo = relogio.getElapsedTime().asSeconds();
            relogio.restart();
        }

        const float GerenciadorGrafico::getTempo()
        {
            return tempo;
        }

        GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico()
        {
            if(pGrafico == nullptr)
                pGrafico = new GerenciadorGrafico();

            return pGrafico;
        }

        sf::RenderWindow* GerenciadorGrafico::getWindow()
        {
            return window;
        }

        void GerenciadorGrafico::limpaJanela()
        {
            window->clear();
        }

        void GerenciadorGrafico::desenhaElemento(sf::RectangleShape corpo)
        {
            window->draw(corpo);
        }

        void GerenciadorGrafico::mostraElementos()
        {
            window->display();
        }

        void GerenciadorGrafico::fechaJanela()
        {
            window->close();
        }

        const bool GerenciadorGrafico::verificaJanelaAberta()
        {
            if(window->isOpen())
                return true;

            return false;
        }

        sf::Texture GerenciadorGrafico::carregarTextura(const char* caminhoTextura)
        {
            sf::Texture textura;

            if(!textura.loadFromFile(caminhoTextura)){
                std::cout<<"Gerenciador::GerenciadorGrafico: nao foi possivel carregar a textura";
                exit(1);
            }
            return textura;
        }

        sf::Font GerenciadorGrafico::carregarFonte(const char* caminhoFonte){
            sf::Font fonte;
            if(!(fonte.loadFromFile(caminhoFonte)))
            {
                throw("ERROR::Game::Gerenciador::GerenciadorGrafico::nao foi possivel encontrar o caminho da fonte");
            }
            return fonte;
        }

        void GerenciadorGrafico::atualizarCamera(sf::Vector2f pos)
        {
            camera.atualizar(sf::Vector2f(pos));
            window->setView(camera.getCamera());
        }

        sf::View GerenciadorGrafico::getCamera()
        {
            return camera.getCamera();
        }

        const sf::Vector2f GerenciadorGrafico::getTamJanela(){
            return sf::Vector2f(LARGURA_TELA, ALTURA_TELA);
        }

        void GerenciadorGrafico::desenhaElemento(sf::Text texto)
        {
            window->draw(texto);
        }

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