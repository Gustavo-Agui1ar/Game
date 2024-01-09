
#pragma once 

#include <iostream>
#include "../entidade/IDs.h"
#include <SFML/Audio.hpp>
#include <map>

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeMusica {

            private:

                //mapa de musicas a serem todcadas
                
                std::map<IDs::IDs, sf::Music*> mapMusica;
                
                //atributo para se saber em qual musica o map tocou por ultimo
                
                IDs::IDs IDmusicaAtual;
               
                //atributo de volume da musica
                
                float volumeGeral;

                //metodo que adiciona uma musica 

                void addMusica(const IDs::IDs ID, const char* caminhoMusica);
               
                //ponteiro da classe( padrao singleton)
                static GerenciadorDeMusica* pMusica;
               
                //construtora

                GerenciadorDeMusica();

            public:

                //destrutora

                ~GerenciadorDeMusica();

                //metodo de acesso a classe
                               
                static GerenciadorDeMusica* getGerenciadorDeMusica();
                
                // metodo que altera a musica atual
                
                void mudarMusica(const IDs::IDs IDmusica);
               
               //metodos de modificacao da musica atual

                void despausar();
                void pausar();
                void parar();

                //metodos acessadores e modificadores do volume
                void setVolume(const float volumeGeral);
                const float getVolumeGeral();
        };
    }
}
