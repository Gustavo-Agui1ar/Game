
#pragma once

#include <SFML/Graphics.hpp>

namespace Game{

    namespace Fundo{

        class Camada{

        private:

            //atributo de locomocao do fundo
        
            const sf::Vector2f tamJanela;
            const float velocidade;

            //atributos do fundo da camada 
          
            sf::RectangleShape fundoAuxiliar;
            sf::RectangleShape fundo;
            
            //atributos da imageem do fundo
           
            sf::Texture textura;
            sf::IntRect escala;

            //metodo que faz a troca de fundos
         
            void trocarTextura();

        public:

            //construtor e destrutor
         
            Camada(const sf::Vector2f tamJanela, sf::Texture textura,const float velocidade);
            ~Camada();

            //metodo de vizualizacao
          
            void desenharCamada(sf::RenderWindow* window);
            
            //metodo de atualizacao da camada
         
            void atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual);

        };


    }
}
