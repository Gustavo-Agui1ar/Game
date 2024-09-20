
#pragma once 

#include <iostream>
#include "../Entity/IDs.h"
#include <SFML/Audio.hpp>
#include <map>

namespace Game::Manager{
    class MusicManager {

    private:
        
        std::map<IDs::IDs, sf::Music*> m_musicMap;
        
        IDs::IDs m_IDcurrentMusic;
        
        float m_geralVolume;
        float m_soundEffectVolume;

        void addMusic(const IDs::IDs ID, const char* pathMusic);
        
        static MusicManager* m_musicManager;
        
        MusicManager();

    public:

        ~MusicManager();

        static MusicManager* getMusicManager();
        
        void changeMusic(const IDs::IDs IDmusic);
        
        void unPause();
        void pause();
        void stop();

        void setGeralVolume(const float geralVolume);
        void setVolume(IDs::IDs ID, const float volume);
        void setSoundEffectVolume(const float soundEffectVolume);
    
        const float getGeralVolume();
        const float getVolume(IDs::IDs ID);
        const float getSoundEffectVolume();
    };
}
