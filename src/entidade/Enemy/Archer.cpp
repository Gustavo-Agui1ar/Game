
#include "../includes/entidade/Enemy/Archer.h"

#define RAIO_DE_VISAO_X 200.0f
#define RAIO_DE_VISAO_Y 200.0f

namespace Game::Entidade::Character::Enemy{



    
    /**
     * @brief default constructor Archer class 
     * 
     * @param pos inicial position by the archer.
     * @param player pointer to player.
     * @param weapon weapon used by the archer.
     * 
    */
    Archer::Archer(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon):
    Enemy(pos, sf::Vector2f(TAM_ARQUEIRO_X, TAM_ARQUEIRO_Y), VEL_ARQUEIRO, player, ARQUEIRO_TEMPO_DE_ATAQUE,
    IDs::IDs::arqueiro, ARQUEIRO_TEMPO_LEVAR_DANO, ARQUEIRO_TEMPO_ANIMACAO_DE_MORTE,DANO_ARQUEIRO, weapon)
    {
        bootAnimation();
        bootSound();
    }

    /**
     * @brief constructor Archer class 
     * 
     * @param atributos json contendo as informacoes da classe
     * @param player pointer to player
    */
    Archer::Archer(nlohmann::ordered_json atributos, Player::Player* player):
    Enemy(pos, sf::Vector2f(TAM_ARQUEIRO_X,TAM_ARQUEIRO_Y), VEL_ARQUEIRO, player, ARQUEIRO_TEMPO_DE_ATAQUE,
    IDs::IDs::arqueiro, ARQUEIRO_TEMPO_LEVAR_DANO, ARQUEIRO_TEMPO_ANIMACAO_DE_MORTE, DANO_ARQUEIRO,  nullptr)
    {
        try
        {
            auto currentPos = sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>());

            setPos(currentPos);
            m_timeDeath = atributos["tempoMorrer"].template get<float>();
            m_getDamage = atributos["levandoDano"].template get<bool>();
            m_timeDamage = atributos["tempoDano"].template get<float>();
            m_dying = atributos["morrendo"].template get<bool>();
            m_attaking = atributos["atacando"].template get<bool>();
            m_moving = atributos["movendo"].template get<bool>();
            m_direction = atributos["direcao"].template get<bool>();
            m_damage = atributos["dano"].template get<float>();
            m_life = atributos["vida"].template get<float>();
            dt = atributos["dt"].template get<float>();
            m_timeAttack = atributos["tempoAtaque"].template get<float>();
            m_timeMove = atributos["tempoMover"].template get<float>();
            m_move = atributos["mover"].template get<short>();
            
            bootAnimation();

            m_animation.setCurrentImg(atributos["imagemAtual"].template get<std::string>());
            m_animation.setTotalTime(atributos["tempoTotal"].template get<float>());
            m_animation.setCurrentFrame(atributos["quadroAtual"].template get<unsigned int>());
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            podeRemover = true;
        }
        
    }
    
    /**
     * @brief destrutora da classe esqueleto
    */
    Archer::~Archer() = default;

        /**
     * @brief metodo que adiciona os sprites do inimigo esqueoeto para que este possa ser utilizado pela animacao
    */
    void Archer::bootAnimation()
    {
        const auto origin = sf::Vector2f(tam.x/2.5,tam.y/2.2);
        m_animation.addAnimation("../Game/animations/enemy/Skeleton_Archer/Idle.png","PARADO",7,0.16,sf::Vector2f{6,2},origin);
        m_animation.addAnimation("../Game/animations/enemy/Skeleton_Archer/Walk.png","ANDAR",8,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/enemy/Skeleton_Archer/Shot_1.png","ATACA",15,0.1,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/enemy/Skeleton_Archer/Hurt.png","TOMADANO",2,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/enemy/Skeleton_Archer/Dead.png","MORRE",5,0.25,sf::Vector2f{6,2}, origin);
    }

    /**
     * @brief metodo que define qual sprite sera chamado e atualizado no momento da chamada do metodo.
    */
        void Archer::updateAnimation()
        {
            if(m_dying){
                m_animation.update(m_direction, "MORRE");
                m_timeDeath += m_pGrafic->getTempo();
                if(m_timeDeath > m_animationTimeDeath)
                {
                    m_player->increaseRage(m_weapon->getDamage());
                    podeRemover = true;
                    m_timeDeath = 0.0f;
                    if(m_weapon != nullptr)
                    {
                        m_weapon->remover();
                    }
                }
            }
            else if(m_getDamage)
                m_animation.update(m_direction,"TOMADANO");
            else if(m_attaking)
                m_animation.update(m_direction,"ATACA");
            else if(m_moving)
                m_animation.update(m_direction,"ANDAR");
            else
                m_animation.update(m_direction,"PARADO");
        }
    
    /**
     * @brief metodo que atualiza a parte relacionada ao ataque do arqueiro
    */
    void Archer::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_pGrafic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                auto *bullet = dynamic_cast<Weapon::Bullet*>(m_weapon);
                bullet->setPos(sf::Vector2f(pos.x + tam.x ,pos.y +  tam.y / 3.0f));
                bullet->setCollision(false);
                bullet->setSpeed(sf::Vector2f(VEL_ARQUEIRO, 0.0f));
                bullet->setDirection(m_direction);
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
        }
    }

    /**
     * @brief metodo que inicializa os efeitos sonoros do esqueleto
    */
    void Archer::bootSound()
    {
        if(!m_DamageBufferSound.loadFromFile(SOM_DE_DANO_ARQUEIRO))
        {
            std::cout<< "Esqueleto: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundDamage.setBuffer(m_DamageBufferSound);
        m_soundDamage.setVolume(40.0f);
    }

    void Archer::moveEnemy()
    {
        if(!m_attaking && !m_dying && !m_getDamage)
        {
            auto enemyPos = corpo.getPosition();
            auto playerPos = m_player->getCorpo().getPosition();

            const float x = fabs(enemyPos.x - playerPos.x);
            const float y = fabs(enemyPos.y - playerPos.y);

            if(x <= RAIO_DE_VISAO_X && y <= RAIO_DE_VISAO_Y){
                    escape(playerPos,enemyPos);
            }
            else if(x <= RAIO_DE_VISAO_X * 5 && y <= RAIO_DE_VISAO_Y)
            {
                m_direction = (playerPos.x - enemyPos.x > 0.0f) ? false : true ;
                stop();
                
                auto *bullet = dynamic_cast<Weapon::Bullet*>(m_weapon);

                if(bullet->getCollision())
                { 
                    m_timeAttack += m_pGrafic->getTempo();
                    
                    if(m_timeAttack > m_AnimationTimeAttack)
                    {
                        m_attaking = true;
                        m_timeAttack = 0.0f;
                    }
                }
            }
            else
            {
                randomMove();
                m_timeAttack = 0.0f;
            }
        }
        else
        {
            m_timeMove = 0.0f;
        }
    }

    /**
     * @brief metodo que faz o inimigo fugir do jogador atualizando a movimentacao do inimigo de acordo com a pos do jogador.
     *
     * @param playerPos posicao atual do jogador
     * @param enemyPos posicao atual do inimigo
     */
    void Archer::escape(sf::Vector2f playerPos, sf::Vector2f enemyPos)
    {
        if(playerPos.x - enemyPos.x > 0.0f){
            walk(true);
        }else{
            walk(false);
        }
    }
}
