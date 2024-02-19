
#pragma once

#include "fase.h"
#include "../includes/entidade/npcs/npc.h"
#include "../includes/entidade/Obstaculo/casa.h"

namespace Game{

    namespace Fase{

        class Vila : public Fase{


            private:

                std::vector<sf::RectangleShape> objCenarios;

            public:

                Vila();
                ~Vila();

                void criarFundo();
                void criarMapa();
                void criarPlataforma(const sf::Vector2f pos);
                void criarNpc(sf::Vector2i pos, const IDs::IDs IDnpc);
                void criarCasaPequena(sf::Vector2i pos);
                void criarCasaMedia(sf::Vector2i pos);
                void criarCasaGrande(sf::Vector2i pos);
                void criarCaixotes(sf::Vector2i pos);
                void criarCarroca(sf::Vector2i pos);
                void criarPostes(sf::Vector2i pos);
                void desenharObjsCenario();

                void desenhar();
                void executar();
        };
    }
}