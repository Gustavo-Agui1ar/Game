#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Game {

    namespace Gerenciador {

        class Camera {
            private:

                //atributos de visualizacao 
              
                sf::Vector2f tamJanela;
                sf::View camera;

            public:

                //construtor e destrutor
               
                Camera(const sf::Vector2f tamJanela);
                ~Camera();

                //metodo acessador do atributo camera
                
                sf::View getCamera();

                //metodos de atualizacao da camera
              
                void resetar(const sf::Vector2f posCenter);
                void atualizar(const sf::Vector2f pos);
        };

    }

}
