
#include "../includes/menus/Button/TextEffect.h"

namespace Game::Menu::Button{
    
    TextEffect::TextEffect(const sf::Font font, const std::string textInfo, const unsigned int fontSize):
    Text(font,textInfo, fontSize), m_transparency(255), m_turnOff(true)
    {
        
    }

    TextEffect::~TextEffect() = default;

    void TextEffect::changeTransparency()
    {
        m_turnOff = m_turnOff ? false : true ;
    }

    const bool TextEffect::getTurnOff()
    {
        return m_turnOff;
    }

    void TextEffect::setTransparency(int transparency)
    {
        m_transparency = transparency;
        update();
    }

    const int TextEffect::getTransparency()
    {
        return m_transparency;
    }

    
    void TextEffect::reset()
    {
        m_transparency = 255;
        update();
    }

    void TextEffect::update()
    {
        m_colorTextBorder = sf::Color(0,0,0,(sf::Uint8)m_transparency);
        m_textColor = sf::Color(m_textColor.r, m_textColor.g, m_textColor.b,(sf::Uint8)m_transparency);
        m_text.setOutlineColor(m_colorTextBorder);
        m_text.setFillColor(m_textColor);
    }
}