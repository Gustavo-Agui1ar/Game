
#pragma once

#include <SFML/Graphics.hpp>
#include "../Player/Character.h"
#include "../Player/Player.h"
#include <iostream>

namespace Game::Entidade::Character::Enemy{
    class Enemy : public Character{

    protected:

        Player::Player *m_player;

        //atributos de ataque
        
        const float m_AnimationTimeAttack;
        float m_timeAttack;
        
        //atributos de movimento
    
        float m_timeMove;
        short m_move;


        //atributos de efeito sonoro da classe

        sf::SoundBuffer m_DamageBufferSound;
        sf::Sound m_soundDamage;

        //metodo que inicializa aos atriibutos de efeito sonoro

        virtual void bootSound(){
            //
        };

        //metodos de animacao
        
        virtual void bootAnimation() = 0;
        void updateAnimation() override;

        //metodos de movimento
    
        virtual void moveEnemy();

        //metodos de ataque
        
        virtual void updateAttack();
        void updateTimeDamage() override;

        //metodo responsavel por salvar o estado de um objeto desta classe

        nlohmann::ordered_json salvar() override;
        
        //metodos de vida
        
        void bootLifeBar() override;

    public:

        //construtor e destrutor
        
        Enemy(sf::Vector2f pos, sf::Vector2f size, const float speed, Player::Player *player,const float animationTimeAttack, IDs::IDs ID, const float animationTimeGetDamage, const float animationTimeDeath, float damage, Weapon::Weapon* weapon);
        ~Enemy() override;

        //metodos de movimento
        
        void chasePlayer(sf::Vector2f playerPos, sf::Vector2f enemyPos);
        void randomMove();
        
        //metodo de colisao
        
        void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
        
        // metodos de atualizar inimigo
        
        void update() override;
    };

}
