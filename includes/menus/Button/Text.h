
#pragma once 

#include <SFML/Graphics.hpp>

namespace Game::Menu::Button{
    class Text{

    protected:
        
        
        const sf::Font m_font;
        
        std::string m_textInfo;

        void boot();

        sf::Text m_text;

        unsigned int m_fontSize;
        sf::Vector2f m_size;
        sf::Vector2f m_position;

        sf::Color m_colorTextBorder;
        sf::Color m_textColor;

    public:

        Text(const sf::Font font, const std::string textInfo, const unsigned int fontSize = 50);
        ~Text();
        
        const std::string getText();
        const sf::Vector2f getPos();
        const sf::Vector2f getSize();
        const sf::Text getInfoText();
        
        void setFontSize(const unsigned int fontSize);
        void setTextColor(const sf::Color textColor);
        void setBorderSize(const float borderSize);
        void setSpacing(const float spacingSize);
        void setText(sf::String textInfo);
        void setPosition(const sf::Vector2f position);
        
    };
}