
#include "../includes/menus/Button/SelectionButton.h"

namespace Game::Menu::Button{
            
    SelectionButton::SelectionButton(const std::string infoText, const sf::Vector2f pos, const sf::Vector2f size, const IDs::IDs ID, const sf::Color colorSelected, IDs::IDs IDlevel):
    TextButton(infoText, pos,  size, ID, colorSelected ), m_IDLevel(IDlevel)
    {
        sf::Vector2f windowCenterPosition = m_graphic->getCamera().getCenter();
        sf::Vector2f boxPosition(windowCenterPosition.x - SIZE_LEVEL_X/2.f, windowCenterPosition.y - SIZE_LEVEL_y/2.f);
        
        updateBoxPosition(sf::Vector2f(windowCenterPosition.x - m_box.getSize().x/2.f, boxPosition.y - 80.f));          

        m_levelView.setSize(sf::Vector2f(SIZE_LEVEL_X, SIZE_LEVEL_y));
        m_levelView.setPosition(boxPosition);
    }

    SelectionButton::~SelectionButton() = default;

    const IDs::IDs SelectionButton::getIDLevel()
    {
        return m_IDLevel;
    }

    void SelectionButton::setImagemLevel(const char* pathImage)
    {
        m_textureLevel = m_graphic->loadTexture(pathImage);

        m_levelView.setTexture(&m_textureLevel);                
    }

    void SelectionButton::draw()
    {
        m_graphic->drawElement(m_text.getInfoText());
        m_graphic->drawElement(m_levelView);
    }
}
