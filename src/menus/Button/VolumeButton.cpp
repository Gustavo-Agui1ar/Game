
#include "../includes/menus/Button/VolumeButton.h"

namespace Game::Menu::Button{
    
    VolumeButton::VolumeButton(const std::string info, sf::Vector2f size, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color corSelecionado, const float beginVolumeBarPosition):
    TextButton(info, pos, size, ID, corSelecionado), m_backGroundVolume(sf::Vector2f(VOLUME_SIZE_BAR_X, VOLUME_SIZE_BAR_Y)),
    m_volumeBody(sf::Vector2f(BUTTON_SIZE_VOLUME_X, BUTTON_SIZE_VOLUME_Y)), m_musicManager(Manager::MusicManager::getMusicManager()), m_beginVolumeBar(beginVolumeBarPosition),
    m_endVolumeBar(m_beginVolumeBar + VOLUME_SIZE_BAR_X), m_parametrization((VOLUME_SIZE_BAR_X - BUTTON_SIZE_VOLUME_X) / 100.0f)
    {
        m_backGroundVolume.setFillColor(sf::Color::Black);
        m_backGroundVolume.setPosition(sf::Vector2f(m_beginVolumeBar, getPos().y + getSizeText().y - 15.0f));

        m_volumeBody.setFillColor(sf::Color{238,173,45});

        float volume = 0.0f;

        switch(ID)
        {
            case IDs::IDs::sound_geral_button:
                volume = m_musicManager->getGeralVolume();
            break;
            
            case IDs::IDs::sound_game_button:
                volume = m_musicManager->getVolume();
            break;

            case IDs::IDs::sound_effect_button:
                volume = m_musicManager->getSoundEffectVolume();
            break;

            default:
                break;
        }
        m_volumeBody.setPosition(sf::Vector2f(m_beginVolumeBar + volume * m_parametrization, getPos().y + getSizeText().y - 15.0f));
    }

    VolumeButton::~VolumeButton() = default;

    void VolumeButton::changeVolume(const float volume)
    {
        sf::Vector2f posVolume = m_volumeBody.getPosition();
        posVolume.x += volume;

        if(posVolume.x + BUTTON_SIZE_VOLUME_X > m_endVolumeBar)
            posVolume.x =  m_endVolumeBar - BUTTON_SIZE_VOLUME_X;
        else if(posVolume.x < m_beginVolumeBar)
            posVolume.x = m_beginVolumeBar;

        m_volumeBody.setPosition(posVolume);
        updateVolume();
    }
   
    void VolumeButton::changeVolume(sf::Vector2f volume)
    {
        if(volume.x + BUTTON_SIZE_VOLUME_X > m_endVolumeBar)
            volume.x =  m_endVolumeBar - BUTTON_SIZE_VOLUME_X;
        else if(volume.x < m_beginVolumeBar)
            volume.x = m_beginVolumeBar;

        m_volumeBody.setPosition(volume.x, m_volumeBody.getPosition().y);
        updateVolume();
    }

    void VolumeButton::updateVolume()
    {
        const float vol = ((m_volumeBody.getPosition().x - m_endVolumeBar + BUTTON_SIZE_VOLUME_X) / m_parametrization) + 100.0f;

        switch(ID)
        {
            case IDs::IDs::sound_game_button:
                m_musicManager->setVolume(vol);
            break;
            
            case IDs::IDs::sound_effect_button:
                m_musicManager->setSoundEffectVolume(vol);
            break;
            
            case IDs::IDs::sound_geral_button:
                m_musicManager->setGeralVolume(vol);
            break;

            default:
                break;
        }
    }

    void VolumeButton::draw()
    {
        updateAnimation();

        m_graphic->drawElement(m_backGroundVolume);
        m_graphic->drawElement(m_volumeBody);
        m_graphic->drawElement(m_text.getInfoText());
    }

    sf::RectangleShape VolumeButton::getVolumeBody()
    {
        return m_volumeBody;
    }
    
    sf::RectangleShape VolumeButton::getBackGroundBar()
    {
        return m_backGroundVolume;
    }

    bool VolumeButton::checkInsideLimits(const sf::Vector2f pos){
        return (pos.x <= m_endVolumeBar && pos.x >= m_beginVolumeBar);
    }

    const float VolumeButton::getBeginVolumeBar()
    {
        return m_beginVolumeBar;
    }

}