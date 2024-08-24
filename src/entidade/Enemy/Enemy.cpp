
#include "../includes/entidade/Enemy/Enemy.h"
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <time.h>
#include <cmath>

#define VEL_INIMIGO_X 5.f
#define VEL_INIMIGO_Y 5.f

#define RAIO_DE_VISAO_X 200.0f
#define RAIO_DE_VISAO_Y 200.0f

namespace Game::Entidade::Character::Enemy{

    /**
     * @brief construtor da classe inimigo
     *
     * @param pos posicao do inimigo
     * @param tam tamanho do inimigo 
     * @param vel velocidade do inimigo
     * @param ID identificacao do inimigo
     * @param jogador ponteiro para um objeto da classe jogador.
     */
    Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size, const float speed, Player::Player *player,const float animationTimeAttack ,IDs::IDs ID, const float animationTimeGetDamage, const float animationTimeDeath, float damage, Weapon::Weapon* weapon):
    Character(pos,size,speed,ID, animationTimeGetDamage, animationTimeDeath, damage),m_AnimationTimeAttack(animationTimeAttack)
    {
        m_player = player;
        m_timeMove = 0.0f;
        m_timeAttack = 0.0f;

        srand(time(NULL));
        m_move = rand()%3;

        bootLifeBar();

        if(weapon != nullptr)
            setWeapon(weapon);
    }

    /**
     * @brief metodo que faz o inimigo perseguir o jogador atualizando a movimentacao do inimigo de acordo com a pos do jogador.
     *
     * @param posPlayer posicao atual do jogador
     * @param posEnemy posicao atual do inimigo
     */
    void Enemy::chasePlayer(sf::Vector2f posPlayer, sf::Vector2f posEnemy)
    {
        if(posPlayer.x - posEnemy.x > 0.0f)
            walk(false);
        else
            walk(true);
    }

    /**
     * @brief metodo que faz com que o inimigo ande euma direcao aleatoria
     * sendo as direcoes possiveis esquerda direita e parado.
     */
    void Enemy::randomMove()
    {
        if(m_timeMove > 1.5f){
            m_move = rand()%3;
            if(m_move == 0)
                walk(false);
            else if(m_move == 1)
                walk(true);
            else
                stop();
            m_timeMove = 0.0f;
        }
    }

    /**
     * @brief metodo que serve para atualizar  a movimentacao  do  inimigo
     * atualizando esta de acordo se o jogador esta ou nao no campo
     * campo de visao do inimigo(se  sim  ele  persegue  se nao ele
     * se move aleatoriamente).
     */
    void Enemy::update()
    {
        moveEnemy();

        m_timeMove += m_pGrafic->getTempo();

        updateAttack();

        updateLifeBar();

        updatePosition();

        updateAnimation();
    }

    /**
     * @brief metodo  que  atualiza  a  animacao  do  inimigo   de  acordo  com  o
     * que ele esta fazendo exemplo: movendo = true e paraEsquerda = true
     * a animacao resultante  e  o sprite  de andar  no sentido da esquerdajo
     */
    void Enemy::updateAnimation()
    {
        if(m_dying && podeRemover == false)
        {
            m_animation.update(m_direction, "MORRE");
            m_timeDeath += m_pGrafic->getTempo();
            if(m_timeDeath > m_animationTimeDeath)
            {
                remover();
                m_timeDeath = 0.0f;
                if(m_weapon != nullptr)
                {
                    m_weapon->remover();
                    m_weapon = nullptr;
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
     * @brief metodo que move o inimigo de acordo com os atributos 
     * atacando e posicao do jogador.
    */
    void Enemy::moveEnemy()
    {
        if(!m_attaking && !m_dying && !m_getDamage){

            sf::Vector2f posEnemy = corpo.getPosition();
            sf::Vector2f posPlayer = m_player->getCorpo().getPosition();

            if(fabs(posPlayer.x - posEnemy.x) <= RAIO_DE_VISAO_X && fabs(posPlayer.y - posEnemy.y) <= RAIO_DE_VISAO_Y)
                chasePlayer(posPlayer,posEnemy);
            else
                randomMove();
        } else
            m_timeMove = 0.0f;
    }

    /**
     * @brief metodo que verifica se o inimigo  esta atacando 
     * se estiver atualiza o tempo decorrido da animacao de ataque.
    */
    void Enemy::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_pGrafic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
        }
    }

    /**
     * @brief metodo que inicializa a barra de vida do inimigo
     * definido posicao, tamanho e textura a mesma.
    */
    void Enemy::bootLifeBar()
    {
        m_lifeBar.setSize((sf::Vector2f(BARRA_VIDA_X, BARRA_VIDA_Y)));
        auto* texture = new sf::Texture(); 
        texture->loadFromFile("../Game/animations/Life/LifeEnemy.png");
        m_lifeBar.setTexture(texture);
    }

    /**
     * @brief destrutora da classe desaloca a textura da barra de vida e retira o apontamento de arma
    */
    Enemy::~Enemy()
    {
        if(m_lifeBar.getTexture()){
            delete(m_lifeBar.getTexture());
        }
    }

    /**
     * @brief metodo que salva o estado de um objeto desta classe
     * 
     * @return retorna json contendo as infomacoes de um objeto desta classe 
    */
    nlohmann::ordered_json Enemy::salvar()
    {
        nlohmann::ordered_json json = saveCharacter();
        json["tempoAtaque"] = m_timeAttack;
        json["tempoMover"] = m_timeMove;
        json["mover"] = m_move;
        json = m_animation.saveAnimation(json);

        return json;
    }

    /**
     * @brief atualiza atributos relacionados a levar dano
    */
    void Enemy::updateTimeDamage()
    {
        if(m_getDamage)
        {
            if(m_timeDamage > m_animationTimeGetDamage)
            {
                m_getDamage = false;
                m_timeDamage = 0.0f;
            }
            if(m_timeDamage == 0.0f)
            {
                m_soundDamage.play();
            }
        }

        m_timeDamage += m_pGrafic->getTempo();
    }

    void Enemy::colisao(Entidade* outraEntidade, sf::Vector2f ds)
    {
        IDs::IDs IDent = outraEntidade->getID();

        if(IDent == IDs::IDs::projetil_jogador)
        {
            auto* projetil = dynamic_cast<Weapon::Bullet*>(outraEntidade);

            takeDamage(projetil->getDamage());
            projetil->setCollision(true);
        } 
    }
}