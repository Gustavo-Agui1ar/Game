
#include "../includes/gerenciador/gerenciadorDeMusica.h"

namespace Game{

    namespace Gerenciador{

        GerenciadorDeMusica* GerenciadorDeMusica::pMusica = nullptr;

        /**
         * @brief construtora da classe GerenciadordeMusica nela é inicializada as musicas a serem tocadas
        */
        GerenciadorDeMusica::GerenciadorDeMusica():
        mapMusica(),volumeGeral(100.0f)
        {
            addMusica(IDs::IDs::forest, "musics/adventure-begins.ogg");
            addMusica(IDs::IDs::menu_principal, "musics/main-theme.ogg");
            addMusica(IDs::IDs::menu_pause, "musics/Menu-Pause.ogg");
            addMusica(IDs::IDs::menu_gameOver, "musics/Game-Over.ogg");
            IDmusicaAtual = IDs::IDs::vazio;
        }


        /**
         * @brief destrutora da classe GerenciadorDeMusica
        */
        GerenciadorDeMusica::~GerenciadorDeMusica()
        {
            std::map<IDs::IDs,sf::Music*>::iterator it;

            for(it = mapMusica.begin() ; it != mapMusica.end() ; it++)
            {
                if(it->second != nullptr)
                    delete(it->second);
                it->second = nullptr;
            }

            mapMusica.clear();
        }

        /**
         * @brief metodo de acesso a classe GerenciadorDeMusica
         * 
         * @return retorna um ponteiro para classe GerenciadorDeMusica
        */
        GerenciadorDeMusica* GerenciadorDeMusica::getGerenciadorDeMusica()
        {
            if(pMusica == nullptr)
                pMusica = new GerenciadorDeMusica();
            return pMusica;
        }

        /**
         * @brief adiciona uma musica no map de musicas
         * 
         * @param ID identificador da musica
         * @param caminhoMusica caminho ate o arquivo da musica
        */
        void GerenciadorDeMusica::addMusica(IDs::IDs ID, const char* caminhoMusica)
        {
            sf::Music* musica = new sf::Music();

            if(!musica->openFromFile(caminhoMusica))
            {
                std::cout<<"GerenciadorDeMusica: erro ao carregar a musica ";
                exit(1);
            }
            musica->setLoop(true);
            mapMusica.insert(std::pair<IDs::IDs, sf::Music*>(ID, musica));
        }

        /**
         * @brief muda a musica a ser tocada no momento
         * 
         * @param IDMusica identificacao da musica a ser tocada
        */
        void GerenciadorDeMusica::mudarMusica(const IDs::IDs IDmusica)
        {
            switch (IDmusica)
            {
            case(IDs::IDs::menu_principal):
            {
                if(IDmusicaAtual != IDs::IDs::vazio && IDmusicaAtual != IDmusica)
                {
                    parar();
                }
                if(IDmusicaAtual != IDmusica)
                    mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;
            case(IDs::IDs::forest):
            {
                if(IDmusicaAtual != IDs::IDs::vazio)
                    parar();
                mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;
            case(IDs::IDs::menu_gameOver):
            {
                if(IDmusicaAtual != IDs::IDs::vazio)
                    parar();
                mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;

            case(IDs::IDs::menu_pause):
            {
                if(IDmusicaAtual != IDs::IDs::vazio && IDmusica != IDmusicaAtual)
                    pausar();
                if(IDmusica != IDmusicaAtual)
                    mapMusica[IDmusica]->play();
                IDmusicaAtual = IDmusica;
            }
                break;

            case(IDs::IDs::menu_carregar):
            {
               
            }
                break;

            case(IDs::IDs::menu_salvar):
            {
             
            }
                break;
            case(IDs::IDs::menu_bug):
            {
                
            }
                break;
            
            default:
            {
                if(IDmusicaAtual != IDs::IDs::vazio)
                    pausar();
                IDmusicaAtual =IDs::IDs::vazio;
            }
                break;
            }
        }

        /**
         * @brief pausa a musica sendo tocada no momento
        */
        void GerenciadorDeMusica::pausar()
        {
            mapMusica[IDmusicaAtual]->pause();
        }

        /**
         * @brief despausa a musica sento tocada no momento
        */
        void GerenciadorDeMusica::despausar()
        {
            mapMusica[IDmusicaAtual]->play();
        
        }

        /**
         * @brief para  a musica sendo tocada o momento 
        */
        void GerenciadorDeMusica::parar()
        {
            mapMusica[IDmusicaAtual]->stop();
        }

        /**
         * @brief atualiza o volume da musica sendo tocada no momento
         * 
         * @param volumeGeral volume a ser aplicado na musica
        */
        void GerenciadorDeMusica::setVolume(const float volumeGeral)
        {
            mapMusica[IDmusicaAtual]->setVolume(volumeGeral);
            this->volumeGeral = volumeGeral;
        }

        /**
         * @brief metodo de acesso ao volumeGeral
         * 
         * @return retorna o atributo volumeGeral
        */
        const float GerenciadorDeMusica::getVolumeGeral()
        {
            return volumeGeral;
        }
    }
}