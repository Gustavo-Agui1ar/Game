#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Game::Manager {
    class Camera {
        private:

            sf::Vector2f m_sizeWindow;
            sf::View m_camera;

        public:

            explicit Camera(const sf::Vector2f m_sizeWindow);
            ~Camera();

            sf::View getCamera();
            void setSize(sf::Vector2f tam);

            void reset(const sf::Vector2f posCenter);
            void update(const sf::Vector2f pos);
    };
}
