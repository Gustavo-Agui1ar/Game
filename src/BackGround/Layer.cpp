
#include "../../includes/BackGround/Layer.h"
#include <math.h>

namespace Game::BackGround{

        Layer::Layer(const sf::Vector2f sizeWindow, sf::Texture texture,const float speed):
        m_sizeWindow(sizeWindow), m_speed(speed), m_texture(texture),m_scale(0,0,0,0)
        {
            m_scale.width  = (texture.getSize().x);
            m_scale.height = (texture.getSize().y);
            m_scale.left   = (texture.getSize().x);


            m_backGround.setSize(sizeWindow);
            m_backGround.setTexture(&m_texture);
            m_backGround.setPosition(0.0f,0.0f);

            m_backGroundAux.setSize(sizeWindow);
            m_backGroundAux.setTexture(&m_texture);
            m_backGroundAux.setPosition(sizeWindow.x,0.0f);
        }

        Layer::~Layer() = default;

        void Layer::changeTexture()
        {
            sf::RectangleShape auxChange = m_backGround;

            m_backGround = m_backGroundAux;
            m_backGroundAux = auxChange;
        }

        void Layer::drawLayer(sf::RenderWindow* window)
        {
            window->draw(m_backGround);

            if(m_speed != 0.0f){
                window->draw(m_backGroundAux);
            }
        }

        void Layer::update(const sf::Vector2f ds, const sf::Vector2f posCamera)
        {
            sf::Vector2f backGroundPosition = m_backGround.getPosition();
            sf::Vector2f backGroundAuxPosition = m_backGroundAux.getPosition();
            m_backGround.setPosition(sf::Vector2f(backGroundPosition.x, 0.0f));
            m_backGroundAux.setPosition(sf::Vector2f(backGroundAuxPosition.x, 0.0f));
            const float dx = ds.x * 0.5f;

            if(dx != 0.0f)
            {
                const float rightPosition = posCamera.x + m_sizeWindow.x / 2.0f;
                const float leftPosition =  posCamera.x - m_sizeWindow.x / 2.0f;

                if(m_speed != 0.0f)
                {
                    //aplicando o movimento contr�rio para as camadas
                    m_backGround.move(dx * -m_speed, 0.0f);
                    m_backGroundAux.move(dx * -m_speed, 0.0f);

                    if(ds.x > 0.0f) // camera movendo para a direita

                    {
                        if(backGroundPosition.x + m_sizeWindow.x < leftPosition)
                        {
                            changeTexture();
                            m_backGround.setPosition(leftPosition, backGroundPosition.y);
                            m_backGroundAux.setPosition(rightPosition, backGroundAuxPosition.y);
                        }

                    }
                    else // camera movendo para a esquerda
                    {
                        if(backGroundPosition.x > leftPosition)
                        {
                            changeTexture();
                            m_backGround.setPosition(leftPosition - m_sizeWindow.x, backGroundPosition.y);
                            m_backGroundAux.setPosition(leftPosition, backGroundAuxPosition.y);
                        }
                    }
                }
                //seta o m_backGround comecando na extremidade esquerda caso o m_backGround nao tenha movimento.
                else
                {
                    m_backGround.setPosition(leftPosition, backGroundPosition.y);
                }
            }

        }




}
