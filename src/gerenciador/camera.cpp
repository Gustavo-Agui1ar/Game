#include "../../includes/gerenciador/camera.h"

#include "../../includes/gerenciador/gerenciadorGrafico.h"

namespace Game {

    namespace Gerenciador {

            /**
             * construtor da classe camera
             * 
             * parametros:
             * 
             * tamJanela: tamanho que a camera deve assumir
            */

            Camera::Camera(const sf::Vector2f tamJanela):
            tamJanela(tamJanela),camera(sf::Vector2f(tamJanela.x / 2.0f, tamJanela.y / 2.0f), tamJanela)
            {

            }

            /**
             *destrutor da classe 
            */

            Camera::~Camera()
            {

            }

            /**
             *metodo que retorna a camera 
            */

            sf::View Camera::getCamera(){
                return camera;
            }

            /**
             * metodo que atualiza a posicao da camera
            */

            void Camera::resetar(const sf::Vector2f posCenter){
                camera.setCenter(posCenter);
            }

            /**
             * metodo que atualiza a posicao da camera
            */
           
            void Camera::atualizar(const sf::Vector2f pos){
                camera.setCenter(pos);
            }
    }

}
