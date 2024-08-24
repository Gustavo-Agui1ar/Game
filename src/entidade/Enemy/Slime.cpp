
#include "../includes/entidade/Enemy/Slime.h"

namespace Game::Entidade::Character::Enemy{




    /**
     * @brief contrutora da classe slime 
     * 
     * 
     * @param pos posicao onde o corpo do slime tera sua posicao inicial.
     * @param player ponteiro para jogador que sera preciso para a movimentacao do slime.
     * 
    */
    Slime::Slime(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon):
    Enemy(pos,  sf::Vector2f(TAM_SLIME_X, TAM_SLIME_Y), VEL_SLIME, player, SLIME_TEMPO_DE_ATAQUE, IDs::IDs::red_slime, 
    SLIME_TEMPO_DE_TOMAR_DANO, SLIME_TEMPO_ANIMACAO_DE_MORTE, DANO_SLIME, weapon)
    { 
        bootAnimation();
        bootSound();
    }
    
    /**
     * @brief construtora da classe Slime
     * 
     * @param atributos json contendo todas as informcoes da classe
     * @param player ponteiro para o jogador
    */
    Slime::Slime(nlohmann::ordered_json atributos, Player::Player *player):
    Enemy(pos,  sf::Vector2f(TAM_SLIME_X, TAM_SLIME_Y), VEL_SLIME, player, SLIME_TEMPO_DE_ATAQUE, IDs::IDs::red_slime, 
    SLIME_TEMPO_DE_TOMAR_DANO, SLIME_TEMPO_ANIMACAO_DE_MORTE, DANO_SLIME, nullptr)
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
     * @brief destrutora da classe slime
    */
    Slime::~Slime() = default;

    /**
     * @brief metodo que adiciona os sprites do 
     * inimigo slime para que este possa ser utilizado pela animacao
    */
    void Slime::bootAnimation()
    {
        const auto origin = sf::Vector2f(tam.x/2.5,tam.y/2.2);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Red_Slime\\Idle.png","PARADO",8,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Red_Slime\\Walk.png","ANDAR",8,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Red_Slime\\Attack_3.png","ATACA",5,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Red_Slime\\Dead.png","MORRE",3,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("..\\Game\\animations\\enemy\\Red_Slime\\Hurt.png","TOMADANO",6,0.1,sf::Vector2f{6,2}, origin);
        
    }

    /**
     * @brief metodo que definem qual sprite sera 
     * chamado e atualizado no momento da
     * chamada do metodo.
    */
    void Slime::updateAnimation()
    {
            if(m_dying && !podeRemover){
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
     * @brief metodo que atualiza a parte 
     * relacionada ao ataque do slime
    */
    void Slime::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_pGrafic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                m_player->increaseRage(m_weapon->getDamage());
                m_weapon->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
            else if(m_timeAttack > m_AnimationTimeAttack/2.0f)
            {
                auto weaponPos = (m_direction ? sf::Vector2f(pos.x - m_weapon->getTam().x/2.0f,pos.y) : sf::Vector2f(pos.x + m_weapon->getTam().x/2.0f,pos.y));
                m_weapon->setPos(weaponPos);
            }
        }
        
    }

    /**
     * @brief metodo que inicializa os efeitos sonoros da classe
    */
    void Slime::bootSound()
    {
        if(!m_DamageBufferSound.loadFromFile(SOM_DE_DANO_SLIME))
        {
            std::cout<< "Slime: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundDamage.setBuffer(m_DamageBufferSound);
        m_soundDamage.setVolume(40.0f);
    }
}

