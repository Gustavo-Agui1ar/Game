
#include "../includes/menus/Button/TextTalk.h"

namespace Game::Menu::Button{

    TextTalk::TextTalk(const float timeTochange, const sf::Font font, const std::string textInfo, const unsigned int fontSize):
    Text(font, "", fontSize),m_timeToChange(timeTochange),m_timeElapsed(0.0f), m_textEnd(false), m_graphicManager(Manager::GraphicManager::getGraphicManager()),
    m_completeText(textInfo)
    {
        bootIterator();
    }

    TextTalk::~TextTalk() = default;

    void TextTalk::increaseLetter()
    {
        if(!m_textEnd)
        {
            sf::String falaString(m_textInfo);
            falaString += (*m_letterIterator) == '_' ? sf::String("\n ") : sf::String(*m_letterIterator);

            setText(falaString);
            m_letterIterator++;
            if(m_letterIterator == m_completeText.end())
                m_textEnd = true;
        }
    }

    void TextTalk::bootIterator()
    {
        m_letterIterator = m_completeText.begin();
    }

    void TextTalk::showCompleteText()
    {
        m_textEnd = true;
        
        auto itF = m_completeText.begin();
        sf::String completeTalk("");
        
        while(itF != m_completeText.end())
        {
            completeTalk += (*itF) == '_' ? sf::String("\n ") : sf::String(*itF);
            itF++;
        }

        setText(completeTalk);
    }

    const bool TextTalk::getEndText()
    {
        return m_textEnd;
    }

    void TextTalk::update()
    {
        if(!m_textEnd)
        {
            m_timeElapsed += m_graphicManager->getTime();

            if(m_timeElapsed >= m_timeToChange)
            {
                increaseLetter();
                m_timeElapsed = 0.0f;
            }
        }
    }
    void TextTalk::setCompleteText(sf::String text)
    {
        m_completeText = text;
    }

    std::string TextTalk::getCompleteText()
    {
        return m_completeText;
    }

    const float TextTalk::getTimeToChange()
    {
        return m_timeToChange;
    }
}