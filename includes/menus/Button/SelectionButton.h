

#pragma once

#include "TextButton.h"
#include <SFML/Graphics.hpp>

#define SIZE_LEVEL_X 800.f
#define SIZE_LEVEL_y 400.f

namespace Game::Menu::Button{
    class SelectionButton : public TextButton {

    private:

        sf::RectangleShape m_levelView;
        sf::Texture m_textureLevel;
        IDs::IDs m_IDLevel;

    public:

        SelectionButton(const std::string infoTexto, const sf::Vector2f pos, const sf::Vector2f size, const IDs::IDs ID, const sf::Color coloSelected, IDs::IDs IDlevel);
        ~SelectionButton() override;

        const IDs::IDs getIDLevel();
        void setImagemLevel(const char* pathImage);
        void draw() override; 

    };
}