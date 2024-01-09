
#pragma once

#define LARGURA_TELA 1700.f
#define ALTURA_TELA  900.f

#include <SFML/Graphics.hpp>
#include "camera.h"

namespace Game{

    namespace Gerenciador{

        class GerenciadorGrafico{

        private:

            //atributo de visualizacao
        
            sf::RenderWindow *window;
            
            //atributos relacionados ao tempo
         
            static float tempo;
            sf::Clock relogio;
            
            //atributo de camera
            
            Camera camera;

            //metodos de acesso a classe
            static GerenciadorGrafico *pGrafico;
            GerenciadorGrafico();

        public:

            //destrutora da classe
         
            ~GerenciadorGrafico();
           
            //metodo acessador da classe
     
            static GerenciadorGrafico* getGerenciadorGrafico();

            //metodo que carrega textura e fonte
      
            sf::Texture carregarTextura(const char* caminhoTextura);
            sf::Font carregarFonte(const char* caminhoFonte);
           
           //metodos de visualiazacao
       
            void desenhaElemento(sf::RectangleShape corpo);
            void desenhaElemento(sf::Text texto);
            const bool verificaJanelaAberta();
            void mostraElementos();
            void resetarJanela();
            void fechaJanela();
            void limpaJanela();
           
            //metodos de acesso e de atualizacao da camera 
       
            void atualizarCamera(sf::Vector2f pos);
            sf::View getCamera();
           
            //metodos relacionados ao tempo
        
            const float getTempo();
            void resetarRelogio();
           
            //metodo de acesso ao atributo window
         
            const sf::Vector2f getTamJanela();
            sf::RenderWindow* getWindow();

        };
    }
}
