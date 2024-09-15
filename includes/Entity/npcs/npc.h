
#pragma once

#include "../includes/Entity/Player/Character.h"

#define NPC_SIZE_X 15.f
#define NPC_SIZE_Y 30.f

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeEstado;
    }

    namespace Entity::Character::Npc{
        class Npc : public Character {
            
            protected:

                static Gerenciador::GerenciadorDeEstado* m_pEstate;
                const char* m_pathDialogue;

                const IDs::IDs m_IDcharacter;

                void bootLifeBar() override{/**/}
                void bootAnimation();

            public:
                
                Npc(sf::Vector2f pos, const IDs::IDs IDcharacter, const char* pathDialogue = nullptr);
                ~Npc() override;

                void updateAnimation() override;
                void updatePosition() override;

                nlohmann::ordered_json save() override;
                void startDialogue();
                const char* getPathDialogue();
                void collision(Entity* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
                void draw() override;
                void update() override;
        };
}
}