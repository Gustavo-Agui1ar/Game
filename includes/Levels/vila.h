
#pragma once

#include "Level.h"
#include "../includes/Entity/npcs/npc.h"
#include "../includes/Entity/Obstacle/House.h"

namespace Game::Level{


    class Vila : public Level{


    private:

        std::vector<sf::RectangleShape> objCenarios;

    public:

        Vila();
        ~Vila() override;

        void makeBackGround() override;
        void makeMap() override;
        void makePlatform(const sf::Vector2f pos) override;
        void criarNpc(sf::Vector2i pos, const IDs::IDs IDnpc);
        void criarCasaPequena(sf::Vector2i pos);
        void criarCasaMedia(sf::Vector2i pos);
        void criarCasaGrande(sf::Vector2i pos);
        void criarCaixotes(sf::Vector2i pos);
        void criarCarroca(sf::Vector2i pos);
        void criarPostes(sf::Vector2i pos);
        void desenharObjsCenario();

        void draw() override;
        void execute() override;
    };
}