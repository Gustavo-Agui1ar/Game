#pragma once

#include "Enemy.h"
#include "../includes/entidade/Weapon/Bullet.h"

#define ARQUEIRO_TEMPO_ANIMACAO_DE_MORTE 1.25f
#define TAM_ARQUEIRO_X 30.0f
#define TAM_ARQUEIRO_Y 60.0f
#define VEL_ARQUEIRO 250.0f
#define ARQUEIRO_TEMPO_LEVAR_DANO 0.6f
#define ARQUEIRO_TEMPO_DE_ATAQUE 1.5f
#define DANO_ARQUEIRO 10.0F

#define SOM_DE_DANO_ARQUEIRO "Sounds/Skeleton-Sound-Effect.wav"


namespace Game::Entidade::Character::Enemy{
    class Archer : public Enemy{
    
    private:

        //metodos de inicializacao
        
        void bootAnimation() override;
        void bootSound() override;
        
        //metodos de atualizacao

        void moveEnemy() override;
        void updateAnimation() override;
        void updateAttack() override;
        void escape(sf::Vector2f playerPos, sf::Vector2f enemyPos);
    
    public:

        //construtor e destrutor
        
        Archer(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon = nullptr);
        Archer(nlohmann::ordered_json atributos, Player::Player *player);
        ~Archer() override;
    };
}
