#include "../includes/entidade/Player/Character.h"
#include <iostream>
#include <math.h>

namespace Game::Entidade::Character{



    /**
     * @brief destrutora da classe personagem.
     */
    Character::~Character() = default;

    /**
     * @brief costrutora da classe personagem.
     *
     * @param pos posicao do corpo nescessario para construtora de entidade.
     * @param tam tamanho do corpo nescessario para construtora de entidade.
     * @param ID  ID a ser enviado nescessario para de entidade.
     * @param vel velocidade de movimento do personagem.
     */
    Character::Character(const sf::Vector2f pos, const sf::Vector2f size, const float speed, const IDs::IDs ID, const float animationTimeGetDamage, const float animationTimeDeath, const float damage):
    Entidade(size,ID, pos),m_animation(&corpo),m_speed(sf::Vector2f(speed,0)) , m_maxSpeed(speed),
        m_moving(false),m_direction(false), dt(0.0f), m_maxLife(100.0f), m_life(100.0f), m_animationTimeGetDamage(animationTimeGetDamage),
        m_animationTimeDeath(animationTimeDeath), m_timeDeath(0.0f), m_timeDamage(0.0f), m_dying(false), m_getDamage(false), m_attaking(false)
    {
        m_damage = damage;
        m_weapon = nullptr;
    }

    /**
     * @brief metodo que muda o atributo booleano movendo para false.
     */
    void Character::stop()
    {
        m_moving = false;
    }

    /**
     * @brief metodo que altera o estado do atributo direcao e movendo.
     *
     * @param direction booleano que diz qual direcao o personagem esta olhando.
     */
    void Character::walk(bool direction)
    {
        m_direction = direction;
        m_moving = true;
    }

    /**
     * @brief metodo que move o personagem nas 4 direcoes esquerda direita cima e baixo.
     */
    void Character::updatePosition()
    {
        dt = m_pGrafic->getTempo();

        sf::Vector2f ds(0.f,0.f);
        
        if(m_moving && !m_dying && !m_getDamage){
            ds.x = m_speed.x * dt;

        if(m_direction)
            ds.x *= -1;
        }

        //gravity effect
        const float Vy = m_speed.y;
        m_speed.y = m_speed.y + GRAVIDADE * dt;
        ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;

        setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y ));

        m_speed.x = m_maxSpeed;

        updateTimeDamage();

        draw();
    }

    /**
     * @brief metodo de acesso a velocidade do personagem.
     * 
     * @return retorna a velocidade do personagem
    */
    sf::Vector2f Character::getSpeed()
    {
        return m_speed;
    }

    /**
     * @brief metodo que seta a velocidade do personagem(este metodo altera tanto a velocidade em x quanto em y).
     *
     * @param speed valor a ser inserido em velocidade.
    */
    void Character::setMaxSpeed(sf::Vector2f speed)
    {
        m_speed = speed;
    }
    
    /**
     * @brief metodo que altera o estado do boleano de ataque do personagem
    */
    void Character::attack()
    {
        m_attaking = true;
        m_moving = false;
    }


    /**
     * @brief metodo que altera o estado do boleano de ataque do personagem
    */
    void Character::stopAttack()
    {
        m_attaking = false;
        m_weapon->setPos(sf::Vector2f(-1000.0f, -1000.f));
    }

    /**
     * @brief metodo que atualiza a barra de vida do personagem
     * de acordo com sua posicao
    */
    void Character::updateLifeBar()
    {
        auto lifePosition(sf::Vector2f(pos.x + tam.x/2.0f - corpo.getSize().x/2.0f, pos.y - 20.0f));
        m_lifeBar.setPosition(lifePosition);
        m_lifeBar.setSize((sf::Vector2f((m_life/m_maxLife)* BARRA_VIDA_X, BARRA_VIDA_Y)));
    }
    
    /**
     * @brief metodo que mostra o corpo e a barra de vida na tela.
    */
    void Character::draw()
    {
        m_pGrafic->desenhaElemento(m_lifeBar);
        m_pGrafic->desenhaElemento(corpo);
        
    }

    /**
     * @brief metodo que  retorna o estado do 
     * boleano de morrer do personagem
    */
    const bool Character::getDie()
    {
        return m_dying;
    }
    
    /**
     * @brief metodo que  retorna o estado do 
     * boleano de morrer do personagem
    */
    const bool Character::getDirection()
    {
        return m_direction;
    }
    
    /**
     * @brief metodo que auxilia na tomada de dano.
     * 
     * @param dano valor a ser descontado da vida do jogador.
    */
    void Character::takeDamage(const float damage)
    {
        if(!m_getDamage)
        {
            m_getDamage = true;
            m_attaking = false;
            m_moving = false;
            m_life -= damage;
            if(m_life <= 0.0f)
            {
                m_dying = true;
                m_getDamage = false;
                m_life = 0.0f;
                
                if(m_weapon != nullptr)
                {
                    m_weapon->remover();
                }
            }
            m_timeDamage = 0.0f;
        }
    }

    /**
     * @brief metodo responsavel por atualiar o
     * estado de tomarDano do personagem
    */
    void Character::updateTimeDamage()
    {
        m_timeDamage += m_pGrafic->getTempo();

        if(m_getDamage && m_timeDamage > m_animationTimeGetDamage)
        {
            m_getDamage = false;
            m_timeDamage = 0.0f;
        }
        
    }

    /**
     * @brief metodo que seta a arma do personagem atribuindo a ela: dano e tamanho.
     * ( posicao  é  inicializada  no  construtor  do  objeto  arma )
    */
    void Character::setWeapon(Weapon::Weapon* weapon)
    {
        m_weapon = weapon;
        m_weapon->setDamage(m_damage);
        m_weapon->setTam(tam);
    }

    /**
     * @brief metodo que salva o estado de um objeto desta classe 
     * 
     * @return retorna um json contendo o estado atual de um objeto desta classe
    */
    nlohmann::ordered_json Character::saveCharacter()
    {
        nlohmann::ordered_json json = salvarEntidade();

        json["velocidade"] = {{"x", m_speed.x}, {"y", m_speed.y}};
        json["tempoMorrer"] = m_timeDeath;
        json["levandoDano"] = m_getDamage;
        json["tempoDano"] = m_timeDamage;
        json["morrendo"] = m_dying;
        json["atacando"] = m_attaking;
        json["movendo"] = m_moving;
        json["direcao"] = m_direction;
        json["dano"] = m_damage;
        json["vida"] = m_life;
        json["dt"] = dt;

        return json;
    }

    bool Character::checkInsideScreen()
    {
        sf::Vector2f screenCenter = m_pGrafic->getCamera().getCenter();

        if(sf::Vector2f screenSize = m_pGrafic->getTamJanela(); 
            pos.x < screenCenter.x - screenSize.x/2.0f || pos.x > screenCenter.x + screenSize.x/2.0f ||
            pos.y < screenCenter.y - screenSize.y/2.0f || pos.y > screenCenter.y + screenSize.y/2.0f  )
        {
            return false;
        }

        return true;
    }

    void Character::setWeaponDamage(float damage) {
        m_weapon->setDamage(damage);
    }

    void Character::setMoving(bool moving) {
        m_moving = moving;
    }

    void Character::setAttacking(bool attacking) {
        m_attaking = attacking;
    }
    
    bool Character::getAttacking() {
       return m_attaking;
    }
}

