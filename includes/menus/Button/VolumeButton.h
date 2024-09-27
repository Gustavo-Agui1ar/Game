
#pragma once 

#include "TextButton.h"
#include "../includes/Manager/MusicManager.h"

#define VOLUME_SIZE_BAR_X 450.0f
#define VOLUME_SIZE_BAR_Y 30.0f

#define BUTTON_SIZE_VOLUME_X 50.0f
#define BUTTON_SIZE_VOLUME_Y 30.0f

namespace Game::Menu::Button{
    class VolumeButton : public TextButton{

    
    private:

        sf::RectangleShape m_backGroundVolume;
        sf::RectangleShape m_volumeBody;

        Manager::MusicManager* m_musicManager;

        const float m_beginVolumeBar;
        const float m_endVolumeBar;
        const float m_parametrization;


        void updateVolume();

    public:

        VolumeButton(const std::string info, sf::Vector2f size, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color selectedColor, const float beginBackGroundVolume);
        ~VolumeButton() override;
        void draw() override;
        bool checkInsideLimits(const sf::Vector2f pos);
        void changeVolume(const float volume);
        void changeVolume(sf::Vector2f volume);
        sf::RectangleShape getVolumeBody();
        sf::RectangleShape getBackGroundBar();
        const float getBeginVolumeBar();
    };
}