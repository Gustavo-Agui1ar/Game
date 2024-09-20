
#pragma once

#include <SFML/Graphics.hpp>

namespace Game::BackGround{
    class Layer{

    private:

        const sf::Vector2f m_sizeWindow;
        const float m_speed;

        sf::RectangleShape m_backGroundAux;
        sf::RectangleShape m_backGround;
        
        sf::Texture m_texture;
        sf::IntRect m_scale;

        void changeTexture();

    public:

        Layer(const sf::Vector2f sizeWindow, sf::Texture texture,const float speed);
        ~Layer();

        void drawLayer(sf::RenderWindow* window);
        
        void update(const sf::Vector2f ds, const sf::Vector2f posCamera);

    };
}
