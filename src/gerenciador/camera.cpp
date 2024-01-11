#include "../../includes/gerenciador/camera.h"

#include "../../includes/gerenciador/gerenciadorGrafico.h"

namespace Game {

    namespace Gerenciador {

            /**
             * @brief construtor da classe camera
             * 
             * @param tamJanela tamanho que a camera deve assumir
            */
            Camera::Camera(const sf::Vector2f tamJanela):
            tamJanela(tamJanela),camera(sf::Vector2f(tamJanela.x / 2.0f, tamJanela.y / 2.0f), tamJanela)
            {

            }

            /**
             *@brief destrutor da classe 
            */
            Camera::~Camera()
            {

            }

            /**
             * @brief metodo de acesso a camera
             * 
             * @return retorna a camera
            */
            sf::View Camera::getCamera(){
                return camera;
            }

            /**
             * @brief metodo que atualiza a posicao da camera
             * 
             * @param posCenter posicao a ser o foco da camera
            */
            void Camera::resetar(const sf::Vector2f posCenter){
                camera.setCenter(posCenter);
            }

            /**
             * @brief metodo que atualiza a posicao da camera
             * 
             * @param pos posicao a ser atribuida a camera
            */
            void Camera::atualizar(const sf::Vector2f pos){
                camera.setCenter(pos);
            }
    }

}
