
#include "../includes/Manager/MusicManager.h"

namespace Game::Manager{


    MusicManager* MusicManager::m_musicManager = nullptr;

    MusicManager::MusicManager():
    m_musicMap(), m_geralVolume(100.0f), m_gameVolume(100.0f),m_soundEffectVolume(100.0f)
    {
        addMusic(IDs::IDs::dawn_forest, "sounds/musics/adventure-begins.ogg");
        addMusic(IDs::IDs::cave, "sounds/musics/Summer-Nights.ogg");
        addMusic(IDs::IDs::main_menu, "sounds/musics/main-theme.ogg");
        addMusic(IDs::IDs::pause_menu, "sounds/musics/Menu-Pause.ogg");
        addMusic(IDs::IDs::village, "sounds/musics/vila-tema.ogg");
        addMusic(IDs::IDs::game_over_menu, "sounds/musics/Game-Over.ogg");
        m_IDcurrentMusic = IDs::IDs::empty;
        setGeralVolume(m_geralVolume);
    }

    MusicManager::~MusicManager()
    {
        m_musicMap[m_IDcurrentMusic]->stop();
        for(auto it = m_musicMap.begin() ; it != m_musicMap.end() ; it++)
        {
            if(it->second != nullptr)
                delete(it->second);
            it->second = nullptr;
        }

        m_musicMap.clear();
    }

    MusicManager* MusicManager::getMusicManager()
    {
        if(m_musicManager == nullptr)
            m_musicManager = new MusicManager();
        return m_musicManager;
    }

    void MusicManager::addMusic(IDs::IDs ID, const char* caminhoMusica)
    {
        auto* musica = new sf::Music();

        if(!musica->openFromFile(caminhoMusica))
        {
            std::cout<<"MusicManager: erro ao carregar a musica ";
            exit(1);
        }
        musica->setLoop(true);
        m_musicMap.insert(std::pair<IDs::IDs, sf::Music*>(ID, musica));
    }

    void MusicManager::changeMusic(const IDs::IDs IDmusic)
    {
        if(IDmusic == IDs::IDs::village || IDmusic == IDs::IDs::cave || IDmusic == IDs::IDs::game_over_menu ) {
            if(m_IDcurrentMusic != IDs::IDs::empty)
                stop();
            m_musicMap[IDmusic]->play();
            m_IDcurrentMusic = IDmusic;
        }

        switch (IDmusic)
        {
            case IDs::IDs::main_menu:
            {
                if(m_IDcurrentMusic != IDs::IDs::empty && m_IDcurrentMusic != IDmusic)
                {
                    stop();
                }
                if(m_IDcurrentMusic != IDmusic)
                    m_musicMap[IDmusic]->play();
                m_IDcurrentMusic = IDmusic;
            }
            break;
            case IDs::IDs::dawn_forest:
            {
                if(m_IDcurrentMusic != IDs::IDs::empty)
                    stop();
                m_musicMap[IDmusic]->play();
                m_IDcurrentMusic = IDmusic;
            }
            break;           
            case IDs::IDs::dialogue_estate:
            {
                setVolume(m_geralVolume * 0.4f);
            }
            break;
            case IDs::IDs::pause_menu:
            {
                if(m_IDcurrentMusic != IDs::IDs::empty && IDmusic != m_IDcurrentMusic)
                    stop();
                if(IDmusic != m_IDcurrentMusic)
                    m_musicMap[IDmusic]->play();
                m_IDcurrentMusic = IDmusic;
            }
            break;
            default:
            {
                //
            }
            break;
        }
    }

    void MusicManager::pause()
    {
        m_musicMap[m_IDcurrentMusic]->pause();
    }

    void MusicManager::unPause()
    {
        m_musicMap[m_IDcurrentMusic]->play();
    
    }

    void MusicManager::stop()
    {
        m_musicMap[m_IDcurrentMusic]->stop();
    }

    void MusicManager::setGeralVolume(const float geralVolume)
    {
        m_geralVolume = geralVolume;

        for(auto itMusic = m_musicMap.begin(); itMusic != m_musicMap.end(); itMusic++)
            itMusic->second->setVolume(m_geralVolume);
    }

    void MusicManager::setVolume(const float volume) {
        m_gameVolume = volume;
        for (auto it = m_musicMap.begin(); it != m_musicMap.end(); ++it) 
            if((it->first == IDs::IDs::village || it->first == IDs::IDs::cave || it->first == IDs::IDs::game_over_menu))
                it->second->setVolume(m_gameVolume);
        
    }

    void MusicManager::setSoundEffectVolume(const float soundEffectVolume)  
    {
       m_soundEffectVolume = soundEffectVolume;
    }

    const float MusicManager::getGeralVolume()
    {
        return m_geralVolume;
    }

    const float MusicManager::getVolume()
    {
        return m_gameVolume;
    }

    const float MusicManager::getSoundEffectVolume()
    {
        return m_soundEffectVolume;
    }
}