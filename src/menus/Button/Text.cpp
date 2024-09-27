
#include "../includes/menus/Button/Text.h"

namespace Game::Menu::Button{

    
    Text::Text(const sf::Font font, const std::string textInfo, const unsigned int fontSize):
    m_font(font), m_textInfo(textInfo), m_text(), m_fontSize(fontSize), m_size(sf::Vector2f(0.0f,0.0f)),
    m_position(sf::Vector2f(0.0f,0.0f)), m_colorTextBorder(sf::Color::Black), m_textColor(sf::Color::White)
    {
        boot();
    }

    Text::~Text() = default;

    void Text::boot()
    {
        m_text.setString(m_textInfo);
        m_text.setCharacterSize(m_fontSize);
        m_text.setFont(m_font);
        m_text.setOutlineThickness(5.0f);
        m_text.setOutlineColor(m_colorTextBorder);
        m_text.setFillColor(m_textColor);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
    }

    void Text::setTextColor(const sf::Color textColor)
    {
        m_textColor = textColor;
        m_text.setFillColor(m_textColor);
    }

    void Text::setBorderSize(const float borderSize)
    {
        m_text.setOutlineThickness(borderSize);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width,m_text.getGlobalBounds().height);
    }

    void Text::setText(sf::String textInfo)
    {
        m_textInfo = textInfo;
        m_text.setString(m_textInfo);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width,m_text.getGlobalBounds().height);
    }

    void Text::setSpacing(const float tamEspaco)
    {
        m_text.setLetterSpacing(tamEspaco);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width,m_text.getGlobalBounds().height);
    }

    void Text::setFontSize(const unsigned int tamFonte)
    {
        m_text.setCharacterSize(tamFonte);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width,m_text.getGlobalBounds().height);
    }

    void Text::setPosition(const sf::Vector2f pos)
    {
        m_position = pos;
        m_text.setPosition(m_position);
    }

    const std::string Text::getText()
    {
        return m_text.getString();
    }

    const sf::Vector2f Text::getPos()
    {
        return m_text.getPosition();
    }

    const sf::Vector2f Text::getSize()
    {
        return m_size;
    }

    const sf::Text Text::getInfoText()
    {
        return m_text;
    }

}