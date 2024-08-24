
#pragma once

#include "fase.h"
#include "../includes/entidade/npcs/npc.h"
#include "../includes/entidade/Obstaculo/casa.h"

namespace Game::Fase{


    class Vila : public Fase{


    private:

        std::vector<sf::RectangleShape> objCenarios;

    public:

        Vila();
        ~Vila() override;

        void criarFundo() override;
        void criarMapa() override;
        void criarPlataforma(const sf::Vector2f pos) override;
        void criarNpc(sf::Vector2i pos, const IDs::IDs IDnpc);
        void criarCasaPequena(sf::Vector2i pos);
        void criarCasaMedia(sf::Vector2i pos);
        void criarCasaGrande(sf::Vector2i pos);
        void criarCaixotes(sf::Vector2i pos);
        void criarCarroca(sf::Vector2i pos);
        void criarPostes(sf::Vector2i pos);
        void desenharObjsCenario();

        void draw() override;
        void executar() override;
    };
}