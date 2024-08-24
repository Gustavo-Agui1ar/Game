
#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/entidade/entidade.h"
#include "../includes/animador/Animation.h"
#include "../Weapon/Weapon.h"


#define GRAVIDADE 1200.0f

#define BARRA_VIDA_X 60.0f
#define BARRA_VIDA_Y 6.0f

namespace Game::Entidade::Character {
    class Character : public Entidade {

    protected:

        //atributos de animacao e visualizacao

        Animator::Animation m_animation;

        //metodos de inicializacao

        virtual void bootLifeBar() = 0;
        
        //metodos de atuallizacao da classe

        virtual void updateAnimation() = 0;
        virtual void updateLifeBar();

        //atributos relacionados a velocidade 

        sf::Vector2f m_speed;
        const float  m_maxSpeed;
        
        //atributos de locomocao
        
        bool m_moving;
        bool m_direction;
        float dt;

        //atributos de vida
        sf::RectangleShape m_lifeBar;
        const float m_maxLife;
        float m_life;
        
        //  atributos de controle de tempo

        const float m_animationTimeGetDamage;
        const float m_animationTimeDeath;
        float m_timeDeath;
        float m_timeDamage;
        
        // atributo relacionado a vida 
        
        bool m_dying;

        //atributos de ataque
        bool m_getDamage;
        bool m_attaking;

        //atributos reacionados aoo dano 

        Weapon::Weapon* m_weapon;
        float m_damage;

    public:

        //construtores e destrutores
        
        Character(const sf::Vector2f pos, const sf::Vector2f size, const float speed,IDs::IDs ID,const float animationTimeGetDamage, const float animationTimeDeath,const float damage);
        ~Character() override;

        //metodos setters da classe
        
        void setMaxSpeed(sf::Vector2f speed);
        void setMoving(bool moving);
        void setWeapon(Weapon::Weapon* weapon);
        void setWeaponDamage(float damage);
        void setAttacking(bool attacking);
        bool getAttacking();

        //metodos de locomocao

        void walk(bool direction);
        void stop();

        //metodos de atualizacao de atributos da classe

        virtual void updateTimeDamage();
        virtual void updatePosition();

        //metodos de ataque
        
        virtual void takeDamage(const float damage);

        //metodos de ataque

        void stopAttack();
        void attack();

        //metodos que salvam os atributos de um objeto desta classe

        nlohmann::ordered_json saveCharacter();
        nlohmann::ordered_json salvar() override = 0;

        //getters daa classe
        
        sf::Vector2f getSpeed();
        const bool getDie();
        const bool getDirection();

        //metodos de animacao e visualizacao
        
        void draw() override;
        bool checkInsideScreen();
    };
}
