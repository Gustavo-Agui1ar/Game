
#include "../includes/entidade/Enemy/Skeleton.h"

namespace Game::Entidade::Character::Enemy{

    /**
     * @brief contrutora da classe slime 
     * 
     * @param pos posicao onde o corpo do esqueleto tera sua posicao inicial.
     * @param tam tamanho do corpo do esqueleto
     * @param vel velocidade com que o mesmo sera movimentado.
     * @param jogador ponteiro para jogador que sera preciso para a movimentacao do esqueleto.
     * 
    */
    Skeleton::Skeleton(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon):
    Enemy(pos, sf::Vector2f(TAM_ESQUELETO_X, TAM_ESQUELETO_Y), VEL_ESQUELETO, player, ESQUELETO_TEMPO_DE_ATAQUE,
    IDs::IDs::esqueleto, ESQUELETO_TEMPO_LEVAR_DANO, ESQUELETO_TEMPO_ANIMACAO_DE_MORTE,DANO_ESQUELETO, weapon)
    {
        bootAnimation();
        bootSound();
    }

    /**
     * @brief construtora da classe Skeleton 
     * 
     * @param atributos json contendo as informacoes da classe
     * @param jogador ponteiro do jogador
    */
    Skeleton::Skeleton(nlohmann::ordered_json atributos, Player::Player* player):
    Enemy(pos, sf::Vector2f(TAM_ESQUELETO_X,TAM_ESQUELETO_Y), VEL_ESQUELETO, player, ESQUELETO_TEMPO_DE_ATAQUE,
    IDs::IDs::esqueleto, ESQUELETO_TEMPO_LEVAR_DANO, ESQUELETO_TEMPO_ANIMACAO_DE_MORTE, DANO_ESQUELETO,  nullptr)
    {
        try
        {
            auto currentPosition = sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>());

            setPos(currentPosition);
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
    Skeleton::~Skeleton() = default;

        /**
     * @brief metodo que adiciona os sprites do inimigo esqueoeto para que este possa ser utilizado pela animacao
    */
    void Skeleton::bootAnimation()
    {
        const auto origin = sf::Vector2f(tam.x/2.5,tam.y/2.2);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Idle.png","PARADO",7,0.16,sf::Vector2f{6,2},origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Walk.png","ANDAR",7,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Attack_1.png","ATACA",4,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Hurt.png","TOMADANO",3,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Dead.png","MORRE",5,0.25,sf::Vector2f{6,2}, origin);
    }

    /**
     * @brief metodo que define qual sprite sera chamado e atualizado no momento da chamada do metodo.
    */
        void Skeleton::updateAnimation()
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
     * @brief metodo que atualiza a parte relacionada ao ataque do esqueleto
    */
    void Skeleton::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_pGrafic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                m_weapon->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
            else if(m_timeAttack > m_AnimationTimeAttack/2.0f)
            {
                sf::Vector2f weaponPosition = (m_direction ? sf::Vector2f(pos.x - m_weapon->getTam().x/2.0f,pos.y) : sf::Vector2f(pos.x + m_weapon->getTam().x/2.0f,pos.y));
                m_weapon->setPos(weaponPosition);
            }
        }
    }

    /**
     * @brief metodo que inicializa os efeitos sonoros do esqueleto
    */
    void Skeleton::bootSound()
    {
        if(!m_DamageBufferSound.loadFromFile(SOM_DE_DANO_ESQUELETO))
        {
            std::cout<< "Skeleton: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundDamage.setBuffer(m_DamageBufferSound);
        m_soundDamage.setVolume(40.0f);
    }
}
