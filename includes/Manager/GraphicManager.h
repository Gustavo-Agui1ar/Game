
#pragma once

#define WIDTH_SCREEN 1700.f
#define HEIGHT_SCREEN  900.f

#include <SFML/Graphics.hpp>
#include "camera.h"

namespace Game::Manager{


    class GraphicManager{

    private:

        sf::RenderWindow* m_window;
        
        static float m_time;
        sf::Clock m_clock;
        
        Camera m_camera;

        static GraphicManager* m_graphicManager;
        GraphicManager();

    public:

        ~GraphicManager();
        
        static GraphicManager* getGraphicManager();

        sf::Texture loadTexture(const char* pathTexture);
        sf::Font loadFont(const char* pathFont);
        
        void drawElement(sf::RectangleShape body);
        void drawElement(sf::Text texto);
        const bool checkIsOpenWindow();
        void showElements();
        void resetWindow();
        void closeWindow();
        void clearWindow();
        
        void updateCamera(sf::Vector2f position);
        sf::View getCamera();
        void setSizeCamera(sf::Vector2f size);
        
        const float getTime();
        void resetClock();
        
        const sf::Vector2f getSizeWindow();
        sf::RenderWindow* getWindow();

    };
}
