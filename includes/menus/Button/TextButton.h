
#pragma once

#include "Button.h"
#include "TextEffect.h"

#define FONTE "Game/animations/botton/MonsterOfFantasy.ttf"
#define TEMPO_TROCA  0.025f

namespace Game::Menu::Button{
    class TextButton : public Button{
        
    protected:

        sf::Color m_colorSelected;
        bool  m_selectedButton;
        
        TextEffect m_text;

    public:

        TextButton(const std::string textInfo, const sf::Vector2f pos, const sf::Vector2f size, const IDs::IDs ID, const sf::Color selcectColor = sf::Color::White);
        ~TextButton() override;
        
        void updateBoxPosition(const sf::Vector2f pos);
        void updateAnimation() override;

        const sf::Vector2f getSizeText();
        
        void setSelected(bool selected);
        
        const bool getSelected();
        
        void draw() override;

    };
}