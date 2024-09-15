
#include "../includes/gerenciador/gerenciadorDeMusica.h"

namespace Game::Gerenciador{


    GerenciadorDeMusica* GerenciadorDeMusica::pMusica = nullptr;

    GerenciadorDeMusica::GerenciadorDeMusica():
    mapMusica(), volumeGeral(100.0f), volumeEfeitoSonoro(40.0f)
    {
        addMusica(IDs::IDs::dawn_forest, "sounds/musics/adventure-begins.ogg");
        addMusica(IDs::IDs::cave, "sounds/musics/Summer-Nights.ogg");
        addMusica(IDs::IDs::main_menu, "sounds/musics/main-theme.ogg");
        addMusica(IDs::IDs::pause_menu, "sounds/musics/Menu-Pause.ogg");
        addMusica(IDs::IDs::village, "sounds/musics/vila-tema.ogg");
        addMusica(IDs::IDs::game_over_menu, "sounds/musics/Game-Over.ogg");
        IDmusicaAtual = IDs::IDs::empty;
        setVolumeGeral(volumeGeral);
    }

    GerenciadorDeMusica::~GerenciadorDeMusica()
    {
        mapMusica[IDmusicaAtual]->stop();
        for(auto it = mapMusica.begin() ; it != mapMusica.end() ; it++)
        {
            if(it->second != nullptr)
                delete(it->second);
            it->second = nullptr;
        }

        mapMusica.clear();
    }

    GerenciadorDeMusica* GerenciadorDeMusica::getGerenciadorDeMusica()
    {
        if(pMusica == nullptr)
            pMusica = new GerenciadorDeMusica();
        return pMusica;
    }

    void GerenciadorDeMusica::addMusica(IDs::IDs ID, const char* caminhoMusica)
    {
        auto* musica = new sf::Music();

        if(!musica->openFromFile(caminhoMusica))
        {
            std::cout<<"GerenciadorDeMusica: erro ao carregar a musica ";
            exit(1);
        }
        musica->setLoop(true);
        mapMusica.insert(std::pair<IDs::IDs, sf::Music*>(ID, musica));
    }

    void GerenciadorDeMusica::mudarMusica(const IDs::IDs IDmusica)
    {
        setVolumeGeral(volumeGeral);
        if(IDmusica == IDs::IDs::village || IDmusica == IDs::IDs::cave || IDmusica == IDs::IDs::game_over_menu ) {
            if(IDmusicaAtual != IDs::IDs::empty)
                parar();
            mapMusica[IDmusica]->play();
            IDmusicaAtual = IDmusica;
        }

        switch (IDmusica)
        {
            case(IDs::IDs::main_menu):
            {
                if(IDmusicaAtual != IDs::IDs::empty && IDmusicaAtual != IDmusica)
                {
                    parar();
                }
                if(IDmusicaAtual != IDmusica)
                    mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;
            case(IDs::IDs::dawn_forest):
            {
                if(IDmusicaAtual != IDs::IDs::empty)
                    parar();
                mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;           
        case(IDs::IDs::dialogue_estate):
            {
                setVolume(IDmusicaAtual, volumeGeral * 0.4f);
            }
                break;
            case(IDs::IDs::pause_menu):
            {
                if(IDmusicaAtual != IDs::IDs::empty && IDmusica != IDmusicaAtual)
                    pausar();
                if(IDmusica != IDmusicaAtual)
                    mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;
            default:
            {
                //
            }
                break;
        }
    }

    void GerenciadorDeMusica::pausar()
    {
        mapMusica[IDmusicaAtual]->pause();
    }

    void GerenciadorDeMusica::despausar()
    {
        mapMusica[IDmusicaAtual]->play();
    
    }

    void GerenciadorDeMusica::parar()
    {
        mapMusica[IDmusicaAtual]->stop();
    }

    void GerenciadorDeMusica::setVolumeGeral(const float volumeGeral)
    {
        for(auto itMusica = mapMusica.begin() ; itMusica != mapMusica.end() ; itMusica++)
            itMusica->second->setVolume(volumeGeral);

        this->volumeGeral = volumeGeral;
        volumeEfeitoSonoro = volumeGeral;
    }

    void GerenciadorDeMusica::setVolume( IDs::IDs ID, const float volume)
    {
        mapMusica[ID]->setVolume(volume);
    }

    void GerenciadorDeMusica::setVolumeEfeitoSonoro(const float volumeEfeitoSonoro)
    {
        this->volumeEfeitoSonoro = volumeEfeitoSonoro;
    }

    const float GerenciadorDeMusica::getVolumeGeral()
    {
        return volumeGeral;
    }

    const float GerenciadorDeMusica::getVolume(IDs::IDs ID)
    {
        return mapMusica[ID]->getVolume();
    }

    const float GerenciadorDeMusica::getVolumeEfeitoSonoro()
    {
        return volumeEfeitoSonoro;
    }
}