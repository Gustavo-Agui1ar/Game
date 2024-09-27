
#include "../includes/menus/Button/TalkBalloon.h"

namespace Game::Menu::Button{

    TalkBalloon::TalkBalloon(std::string infoTexto, std::string infoNome, const float tempoDeTroca):
    m_graphicManager(Manager::GraphicManager::getGraphicManager()),m_talk(tempoDeTroca, m_graphicManager->loadFont( "../Game/animations/botton/menu.ttf"), infoTexto),
    m_name(m_graphicManager->loadFont( "../Game/animations/botton/menu.ttf"), infoNome),m_dialogueBox(), m_nameBox()
    {
        bootDialogueBox();
    }

    TalkBalloon::~TalkBalloon() = default;

    void TalkBalloon::bootDialogueBox()
    {

        sf::Vector2f sizeWindow = m_graphicManager->getSizeWindow();
        sf::Vector2f positionWindow = m_graphicManager->getCamera().getCenter();

        m_dialogueBox.setSize(sf::Vector2f(sizeWindow.x, sizeWindow.y/4.0f)); 
        m_dialogueBox.setPosition(positionWindow.x - sizeWindow.x/2.0f, positionWindow.y - sizeWindow.y/2.0f);
        m_dialogueBox.setFillColor(sf::Color{0, 0, 0, 230});
        m_dialogueBox.setOutlineThickness(5.0f);
        m_dialogueBox.setOutlineColor(sf::Color{200,200,200});

        m_nameBox.setSize(sf::Vector2f(m_name.getSize().x + 50.f, TAM_NOME_Y));
        m_nameBox.setPosition(positionWindow.x - sizeWindow.x/2.0f + 5.0f, (positionWindow.y - sizeWindow.y/2.0f) + m_dialogueBox.getSize().y + 5.0f);
        m_nameBox.setFillColor(sf::Color{0, 0, 0, 230});
        m_nameBox.setOutlineThickness(5.0f);
        m_nameBox.setOutlineColor(sf::Color{200,200,200});

        m_talk.setFontSize(35);
        m_name.setFontSize(30);
        
        bootName();
        bootText();
    }

    void TalkBalloon::bootName()
    {
        sf::Vector2f nameSize = m_name.getSize();
        sf::Vector2f position = m_nameBox.getPosition();
        sf::Vector2f size = m_nameBox.getSize();
        auto posNome = sf::Vector2f(
            position.x + size.x / 2.0f - nameSize.x / 2.f,
            position.y + size.y / 2.0f - nameSize.y
        );
        m_name.setPosition(posNome);
    }
    
    void TalkBalloon::bootText()
    {
        sf::Vector2f position = m_dialogueBox.getPosition();
        sf::Vector2f size = m_dialogueBox.getSize();
        auto posTexto = sf::Vector2f(position.x + size.x / 10.f , position.y + size.y / 5.f);
        m_talk.setPosition(posTexto);
    }
    
    void TalkBalloon::updateName()
    {
        m_nameBox.setSize(sf::Vector2f(m_name.getSize().x + 50.f, TAM_NOME_Y));
        sf::Vector2f nameSize = m_name.getSize();
        sf::Vector2f position = m_nameBox.getPosition();
        sf::Vector2f size = m_nameBox.getSize();
        auto namePosition = sf::Vector2f(
            position.x + size.x / 2.0f - nameSize.x / 2.f,
            position.y + size.y / 2.0f - nameSize.y
        );
        m_name.setPosition(namePosition);
    }
    
    void TalkBalloon::updateText()
    {
        sf::Vector2f Position = m_dialogueBox.getPosition();
        sf::Vector2f size = m_dialogueBox.getSize();
        auto textPosition = sf::Vector2f(
            Position.x + size.x / 10.f ,
            Position.y + size.y / 5.f 
        );
        m_talk.setPosition(textPosition);
    }

    void TalkBalloon::setNameDirection(bool left)
    {
        updateName();
        sf::Vector2f windowSize = m_graphicManager->getSizeWindow();
        sf::Vector2f windowCenterPosition = m_graphicManager->getCamera().getCenter();
        float posX = left ? windowCenterPosition.x - windowSize.x / 2.f + 5.f : windowCenterPosition.x + windowSize.x / 2.f - m_nameBox.getSize().x;
        float posY = (windowCenterPosition.y - windowSize.y/2.0f) + m_dialogueBox.getSize().y + 5.0f;
        m_nameBox.setPosition(posX, posY);
        updateName();
    }

    void TalkBalloon::setText(std::string text)
    {
        m_talk.setCompleteText(text);
    }
    
    std::string TalkBalloon::getText()
    {
        return m_talk.getCompleteText();
    }

    void TalkBalloon::setName(std::string name)
    {
        m_name.setText(name);
    }
    
    std::string TalkBalloon::getName()
    {
        return m_name.getText();
    }

    const float TalkBalloon::getTimeToChange()
    {
        return m_talk.getTimeToChange();
    }

    void TalkBalloon::update()
    {
        m_talk.update();

        float talkRightEdge = m_talk.getPos().x + m_talk.getSize().x;
        float boxDialogueRightEdge = m_dialogueBox.getPosition().x + m_dialogueBox.getSize().x - m_dialogueBox.getSize().x / 10.f;

        if (talkRightEdge >= boxDialogueRightEdge) {
            draw();
        }
    }

    void TalkBalloon::draw()
    {
        m_graphicManager->drawElement(m_dialogueBox);
        m_graphicManager->drawElement(m_nameBox);
        m_graphicManager->drawElement(m_name.getInfoText());
        m_graphicManager->drawElement(m_talk.getInfoText());
    }

    void TalkBalloon::skipDialogue()
    {
        m_talk.showCompleteText();
    }

    const bool TalkBalloon::getEndText()
    {
        return m_talk.getEndText();
    }
}