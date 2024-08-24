
#pragma once

#include "Enemy.h"

#define ESQUELETO_TEMPO_ANIMACAO_DE_MORTE 1.25f
#define TAM_ESQUELETO_X 30.0f
#define TAM_ESQUELETO_Y 60.0f
#define VEL_ESQUELETO 50.0f
#define ESQUELETO_TEMPO_LEVAR_DANO 0.6f
#define ESQUELETO_TEMPO_DE_ATAQUE 1.0f
#define DANO_ESQUELETO 10.0F

#define SOM_DE_DANO_ESQUELETO "Sounds/Skeleton-Sound-Effect.wav"


namespace Game::Entidade::Character::Enemy{
    class Skeleton : public Enemy{
        
    private:

        //metodos de inicializacao
        
        void bootAnimation() override;
        void bootSound() override;
        
        //metodos de atualizacao
        
        void updateAnimation() override;
        void updateAttack() override;

    public:

        //construtor e destrutor
        
        Skeleton(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon = nullptr);
        Skeleton(nlohmann::ordered_json atributos, Player::Player *player);
        ~Skeleton() override;
    };
}
