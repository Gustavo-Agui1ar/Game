
#include "../includes/menus/Button/TextButton.h"

namespace Game::Menu::Button{
       
    TextButton::TextButton(const std::string textInfo, const sf::Vector2f pos, const sf::Vector2f size, const IDs::IDs ID, const sf::Color colorSelected):
    Button(size,pos,ID,TEMPO_TROCA),m_colorSelected(colorSelected), m_selectedButton(false), m_text(m_graphic->loadFont("../Game/animations/botton/menu.ttf"), textInfo)
    {
        updateBoxPosition(pos);
    }
    
    TextButton::~TextButton() = default;

    const sf::Vector2f TextButton::getSizeText()
    {
        return sf::Vector2f(m_text.getInfoText().getGlobalBounds().width, m_text.getInfoText().getGlobalBounds().height);
    }

    void TextButton::draw()
    {
        updateAnimation();
        m_graphic->drawElement(m_text.getInfoText());
    }

    void TextButton::updateAnimation()
    {
        if(m_selectedButton) 
        {
            m_timeElapsed += m_graphic->getTime();
            if(m_timeElapsed > m_timeToChange)
            {
                int transparency = m_text.getTransparency();
                transparency += m_text.getTurnOff() ? -5 : 5;
                
                if (transparency >= 255 || transparency <= 0) {
                    transparency = (transparency >= 255) ? 255 : 0;
                    m_text.changeTransparency();
                }

                m_text.setTransparency(transparency);
                m_timeElapsed = 0.0f;
            }
        }
    }

    void TextButton::updateBoxPosition(const sf::Vector2f pos)
    {
        m_position = pos;
        m_box.setPosition(pos);
        sf::Vector2f textSize = m_text.getSize();
        auto textPosition = sf::Vector2f(
            pos.x + m_size.x / 2.0f - textSize.x / 2.05f,
            pos.y + m_size.y / 2.0f - textSize.y * 1.2f
        );
        m_text.setPosition(textPosition);

    }

    void TextButton::setSelected(bool selected)
    {
        m_text.setTextColor(selected ? m_colorSelected : sf::Color::White);
        m_selectedButton = selected;
        m_text.reset();
    }

    const bool TextButton::getSelected()
    {
        return m_selectedButton;
    }
}