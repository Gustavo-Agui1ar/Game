
#pragma once

#include "Enemy.h"

#define SLIME_TEMPO_ANIMACAO_DE_MORTE 0.5F
#define SLIME_TEMPO_DE_TOMAR_DANO 0.6F
#define SLIME_TEMPO_DE_ATAQUE 0.8F
#define VEL_SLIME 50.0f
#define TAM_SLIME_X 30.0f
#define TAM_SLIME_Y 60.0f
#define DANO_SLIME 5.0F

#define SOM_DE_DANO_SLIME "Sounds/Slime-Sound-Effect.wav"

namespace Game::Entidade::Character::Enemy{
    class Slime : public Enemy{
    private:

        //metodos de inicializacao da classe
        
        void bootAnimation() override;
        void bootSound() override;
        
        //metodos de atualizacao da classe

        void updateAnimation() override;
        void updateAttack() override;

    public:

        //construtor e destrutor
        Slime(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon = nullptr);
        Slime(nlohmann::ordered_json atributos, Player::Player *player);
        ~Slime() override;
    };
}

