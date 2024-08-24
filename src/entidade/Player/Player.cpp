#include "../includes/listeners/listenerJogador.h"
#include "../includes/entidade/npcs/npc.h"
#include "../includes/entidade/Player/Player.h"
#include "../includes/gerenciador/gerenciadorDeColisao.h"
#include "../includes/entidade/Enemy/Skeleton.h"
#include "../includes/entidade/Enemy/Slime.h"
namespace Game::Entidade::Character::Player {
    /**
     * @brief destrutora da classe Player
     */
    Player::~Player() {
        if (m_observerPlayer!= nullptr)
            delete m_observerPlayer;
        if (m_lifeTube.getTexture())
            delete (m_lifeTube.getTexture());
        if (m_lifeBar.getTexture())
            delete (m_lifeBar.getTexture());
    }

    /**
     * @brief construtora da classe PLayer
     *
     * @param pos posicao do jogador
     * @param arma arma do jogador
     */
    Player::Player(const sf::Vector2f pos, Weapon::Weapon *weapon, Weapon::Bullet *bullet) : Character(pos, sf::Vector2f(SIZE_PLAYER_X, SIZE_PLAYER_Y), PLAYER_SPEED_X, IDs::IDs::jogador, PLAYER_TIME_GETDAMAGE, ANIMATION_DEATH_PLAYER, PLAYER_DAMAGE), m_dash(this), m_rage(this),
    m_stamina(this), m_fireball(this), m_onFloor(false), m_qtdJump(0), m_timeAnimationAttack(TIME_DAMAGE_PLAYER), m_timeAttack(0.0f), m_observerPlayer(new Listener::ListenerJogador(this)) {
        
        bootAnimation();
        bootLifeBar();
        bootSound();

        if (weapon != nullptr)
            setWeapon(weapon);

        if (bullet != nullptr)
            m_fireball.setBullet(bullet);
    }

    /**
     * @brief construtora da classe jogador
     *
     * @param atributos json contendo todas as informacoes da classe jogador
     */
    Player::Player(nlohmann::ordered_json atributos) : Character(pos, sf::Vector2f(SIZE_PLAYER_X, SIZE_PLAYER_Y), PLAYER_SPEED_X, IDs::IDs::jogador, PLAYER_TIME_GETDAMAGE, ANIMATION_DEATH_PLAYER, PLAYER_DAMAGE), 
    m_dash(this), m_rage(this), m_stamina(this), m_fireball(this), m_timeAnimationAttack(TIME_DAMAGE_PLAYER), m_timeAttack(0.0f), m_observerPlayer(new Listener::ListenerJogador(this))
    {
        try {
            auto currentPosition = sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>());
            auto currentSize = sf::Vector2f(atributos["tam"]["x"].template get<float>(), atributos["tam"]["y"].template get<float>());
            auto currentSpeed = sf::Vector2f(atributos["velocidade"]["x"].template get<float>(), atributos["velocidade"]["y"].template get<float>());

            setPos(currentPosition);
            setTam(currentSize);
            setMaxSpeed(currentSpeed);

            m_moving = atributos["movendo"].template get<bool>();
            m_direction = atributos["direcao"].template get<bool>();
            m_getDamage = atributos["levandoDano"].template get<bool>();
            m_attaking = atributos["atacando"].template get<bool>();
            m_dying = atributos["morrendo"].template get<bool>();
            m_life = atributos["vida"].template get<float>();
            m_timeDamage = atributos["tempoDano"].template get<float>();
            m_timeDeath = atributos["tempoMorrer"].template get<float>();
            dt = atributos["vida"].template get<float>();
            m_damage = atributos["dano"].template get<float>();
            m_stamina.setStamina(atributos["stamina"].template get<float>());
            m_onFloor = atributos["noChao"].template get<bool>();
            m_qtdJump = atributos["qtdPulo"].template get<int>();
           
            m_dash.setInDash(atributos["emDash"].template get<bool>());
            m_dash.setCanDash(atributos["podeDash"].template get<bool>());
            m_dash.setTimeDash(atributos["tempoDash"].template get<float>());
           
            m_rage.setRage(atributos["furia"].template get<float>());
            m_rage.setInRage(atributos["emFuria"].template get<bool>());
            m_rage.setStartingRage(atributos["entrandoEmFuria"].template get<bool>());
            
            m_fireball.setTrhowBullet(atributos["lancandoProjetil"].template get<bool>());
            m_fireball.setTimeTrhowBullet(atributos["tempoAtaqueProjetil"].template get<float>());

            bootAnimation();
            bootLifeBar();
            bootSound();

            m_animation.setCurrentImg(atributos["imagemAtual"].template get<std::string>());
            m_animation.setCurrentFrame(atributos["tempoTotal"].template get<unsigned int>());
            m_animation.setTotalTime(atributos["tempoTotal"].template get<float>());
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            podeRemover = true;
        }
    }

    /**
     * @brief metodo que inicializa a animacao  do jogador
     */
    void Player::bootAnimation() {
        const auto origemT = sf::Vector2f((tam.x / 2), (tam.y / 5));
        m_animation.addAnimation("animations/Player/Idle.png", "PARADO", 8, 0.2f, sf::Vector2f{2.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 3));
        m_animation.addAnimation("animations/Player/Jump.png", "PULO", 3, 0.16f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Player/Down.png", "CAINDO", 3, 0.12f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Player/Dash.png", "DASH", 4, 0.12f, sf::Vector2f{4.5f, 0.8f}, sf::Vector2f(origemT.x, origemT.y / 4));
        m_animation.addAnimation("animations/Player/Run.png", "CORRENDO", 8, 0.12f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Player/Attack.png", "ATACAR", 4, 0.15f, sf::Vector2f{3.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 2));
        m_animation.addAnimation("animations/Player/Dead.png", "MORRE", 12, 0.15f, sf::Vector2f{3.f, 1.5f}, sf::Vector2f(origemT.x - origemT.x / 2, origemT.y));
        m_animation.addAnimation("animations/Player/Hit.png", "TOMADANO", 3, 0.15f, sf::Vector2f{2.2f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 3));
        m_animation.addAnimation("animations/Player/Fireball.png", "LANCANDO_PROJETIL", 9, 0.1f, sf::Vector2f{3.5f, 1.12f}, sf::Vector2f(origemT.x, origemT.y / 5));
        m_animation.addAnimation("animations/Player/idle-fire.png", "PARADO-F", 8, 0.2f, sf::Vector2f{2.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 5));
        m_animation.addAnimation("animations/Player/Jump-fire.png", "PULO-F", 3, 0.16f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Player/Down-fire.png", "CAINDO-F", 3, 0.12f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Player/Dash-fire.png", "DASH-F", 4, 0.12f, sf::Vector2f{2.75f, 1.25f}, sf::Vector2f(origemT.x, origemT.y));
        m_animation.addAnimation("animations/Player/Run-fire.png", "CORRENDO-F", 8, 0.12f, sf::Vector2f{2.5f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 4));
        m_animation.addAnimation("animations/Player/attack-fire.png", "ATACAR-F", 4, 0.15f, sf::Vector2f{3.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 4));
        m_animation.addAnimation("animations/Player/Dead-fire.png", "MORRE-F", 11, 0.15f, sf::Vector2f{3.0f, 1.5f}, sf::Vector2f(origemT.x - origemT.x / 2, origemT.y));
        m_animation.addAnimation("animations/Player/Hit-fire.png", "TOMADANO-F", 4, 0.15f, sf::Vector2f{2.2f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 3));
        m_animation.addAnimation("animations/Player/Fireball-fire.png", "LANCANDO_PROJETIL-F", 9, 0.1f, sf::Vector2f{3.5f, 1.12f}, sf::Vector2f(origemT.x, origemT.y / 5));
        m_animation.addAnimation("animations/Player/Furia.png", "ENTRANDO_FURIA", 12, 0.1f, sf::Vector2f{3.0f, 1.12f}, sf::Vector2f(origemT.x, origemT.y / 5));
    }

    /**
     * @brief metodo  que atualiza a poiscao,aniimacao,
     * barra de vida e camera que seque o jogador
     */
    void Player::update() {
        
        updatePosition();
        updateWeapon();
        m_fireball.updateBullet();
        m_pGrafic->atualizarCamera(sf::Vector2f(getPos().x, ALTURA_TELA / 2.f));
        updateAnimation();
        updateLifeBar();
        m_stamina.updateStaminaBar();
        m_rage.updateRageBar();
        updateTimeDamage();
        m_dash.updateDash();
        draw();
    }

    /**
     * @brief metodo que muda o booleano que dita se o jogador pode pular ou nao
     */
    void Player::canJump() {
        m_onFloor = true;
        m_qtdJump = 0;
    }

    /**
     *@brief metodo que faz o pulo do jogador.
     */
    void Player::jump() {
        if (!m_attaking && !m_getDamage && (m_onFloor || m_qtdJump < QTD_JUMP)) {
            m_speed.y = -sqrt(2.0f * GRAVIDADE * JUMP_SIZE);
            m_onFloor = false;
            m_qtdJump++;
        }
    }

    /**
     * @brief metodo que atualiza a animacao do jogador de acordo com seu estado atual.
     */
    void Player::updateAnimation() {
        if (!m_rage.getInRage())
            selectAnimation("");
        else
            selectAnimation("-F");
    }

    void Player::selectAnimation(std::string complement) {
        if (m_dying) {
            m_animation.update(m_direction, "MORRE" + complement);
            m_timeDeath += m_pGrafic->getTempo();
            if (m_timeDeath > m_animationTimeDeath)
                podeRemover = true;
        }
        else if (m_rage.getStartingRage()) {
            m_animation.update(m_direction, "ENTRANDO_FURIA" + complement);
            m_rage.updateStartingRage();
        }
        else if (m_getDamage)
            m_animation.update(m_direction, "TOMADANO" + complement);
        else if (m_dash.getInDash())
            m_animation.update(m_direction, "DASH" + complement);
        else if (!m_onFloor && m_speed.y > 0.0f)
            m_animation.update(m_direction, "CAINDO" + complement);
        else if (!m_onFloor)
            m_animation.update(m_direction, "PULO" + complement);
        else if (m_moving)
            m_animation.update(m_direction, "CORRENDO" + complement);
        else if (m_attaking && m_fireball.getTrhowBullet())
            m_animation.update(m_direction, "LANCANDO_PROJETIL" + complement);
        else if (m_attaking)
            m_animation.update(m_direction, "ATACAR" + complement);
        else
            m_animation.update(m_direction, "PARADO" + complement);
    }

    /**
     * @brief metodo que define a colisao do personagem com outras entidades
     *
     * @param outraEntidade entidade a ser analizada a colisao com o jogador
     * @param ds distancia entre as duas entidades
     */
    void Player::colisao(Entidade *outraEntidade, sf::Vector2f ds) {
        IDs::IDs other_ID = outraEntidade->getID();
        if (other_ID == IDs::IDs::red_slime || other_ID == IDs::IDs::esqueleto) {
            auto *inimigo = static_cast<Enemy::Enemy *>(outraEntidade);
            inimigo->stop();
            inimigo->attack();
        }
        else if (other_ID == IDs::IDs::armaDoIimigo) {
            auto *m_weapon = static_cast<Weapon::Weapon *>(outraEntidade);

            if (m_rage.getInRage())
                takeDamage(m_weapon->getDamage() / 2.0f);
            else
                takeDamage(m_weapon->getDamage());
        }
        else if (other_ID == IDs::IDs::projetil_inimigo) {
            auto *bullet = dynamic_cast<Weapon::Bullet *>(outraEntidade);

            if (m_rage.getInRage())
                takeDamage(bullet->getDamage() / 2.0f);
            else
                takeDamage(bullet->getDamage());
            
            bullet->setCollision(true);
        }
    }

    /**
     * @brief metodo que inicializa e define a posicao da barra de vida do jogador
     * alem disso define a textura que a barra tera jutamente com o seu tamanho.
     */
    void Player::bootLifeBar() {
        auto lifeTube = sf::Vector2f(PLAYER_LIFE_BAR_X, PLAYER_LIFE_BAR_Y);
        m_lifeTube.setSize(lifeTube);
        m_lifeBar.setSize(lifeTube);
        auto *textureLife = new sf::Texture();
        auto *textureBar = new sf::Texture();
        textureLife->loadFromFile("animations/Life/VidaJogador.png");
        textureBar->loadFromFile("animations/Life/BarraVida.png");
        m_lifeBar.setTexture(textureLife);
        m_lifeTube.setTexture(textureBar);
    }
    
    /**
     * @brief  metodo que atualiza a posicao da barra de vida do jogador
     * assim como seu tamanho de acordo com o atributo vida do jogador.
     */
    void Player::updateLifeBar() {
        sf::Vector2f screenPosition = m_pGrafic->getCamera().getCenter();
        sf::Vector2f screenSize = m_pGrafic->getTamJanela();

        auto barPosition = sf::Vector2f(screenPosition.x - screenSize.x / 2.0f + 10.0f, 30.0f);
        m_lifeTube.setPosition(barPosition);
        m_lifeBar.setSize(sf::Vector2f((PLAYER_LIFE_BAR_X - 40.0f) * (m_life / m_maxLife), PLAYER_LIFE_BAR_Y - 13.0f));
        m_lifeBar.setPosition(sf::Vector2f(barPosition.x + 7.0f, barPosition.y + m_lifeTube.getSize().y / 2.0f - m_lifeBar.getSize().y / 2.0f));
    }

    /**
     * @brief metodo responsavel por desenhar a vida, stamina e o personagem na tela
     * com a ajuda do metodo desenhar elemento.
     */
    void Player::draw() {
        m_pGrafic->desenhaElemento(corpo);
        m_pGrafic->desenhaElemento(m_lifeTube);
        m_pGrafic->desenhaElemento(m_lifeBar);
        m_stamina.drawStaminaBar();
        m_rage.drawRageBar();
    }

    /**
     * @brief metodo  responsavel  por   atualizar   a  posicao
     * da arma do jogador dependendo de seu estado atual
     */
    void Player::updateWeapon() {
        if (m_attaking && !m_dying && !m_fireball.getTrhowBullet()) {
            m_timeAttack += m_pGrafic->getTempo();
            if (m_timeAttack > m_timeAnimationAttack) {
                m_weapon->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                m_timeAttack = 0.0f;
                m_attaking = false;
            }
            else if (m_timeAttack > (m_timeAnimationAttack / 3.0f) * 2) {
                sf::Vector2f weaponPosition = (m_direction ? sf::Vector2f(pos.x - m_weapon->getTam().x / 2.0f, pos.y) : sf::Vector2f(pos.x + m_weapon->getTam().x / 2.0f, pos.y));
                m_weapon->setPos(weaponPosition);
            }
            else if (m_timeAttack > m_timeAnimationAttack / 3.0f)
                m_soundAttack.play();
        }
    }

    void Player::trhowBullet() {
        m_fireball.trhowBullet();
    }

    /**
     * @brief metodo de acesso ao atributo noChao do jogador
     *
     * @return retorna o atributo noChao do jogador
     */
    bool Player::getOnFloor() const {
        return m_onFloor;
    }

    /**
     * @brief metodo que muda o estado do observador do jogador
     */
    void Player::changeObserverEstate(const bool ative) {
        m_observerPlayer->mudarEstado(ative);
    }

    /**
     * @brief metodo que salva o estado de um objeto da classe jogador
     *
     * @return retorna um json contendo as informacoes de um objeto jogador
     */
    nlohmann::ordered_json Player::salvar() {
        nlohmann::ordered_json json = saveCharacter();
        json["noChao"] = m_onFloor;
        json["qtdPulo"] = m_qtdJump;
        json["tempoAtaque"] = m_timeAttack;
        json = m_dash.saveDash(json);
        json = m_rage.saveRage(json);
        json = m_stamina.saveStamina(json);
        json = m_fireball.saveFireBall(json);
        json = m_animation.saveAnimation(json);

        return json;
    }

    /**
     * @brief metodo que inicializa os efeitos sonoros do jogador
     */
    void Player::bootSound() {
        if (!m_soundAttackBuffer.loadFromFile(PATH_SOUND_ATTACK)) {
            std::cout << "Player: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundAttack.setBuffer(m_soundAttackBuffer);
    }

    /**
     * @brief metodo que atualiza a posicao do jogador
     */
    void Player::updatePosition() {
        dt = m_pGrafic->getTempo();
        sf::Vector2f ds(0.f, 0.f);

        if (m_moving && !m_dying && !m_getDamage && !m_dash.getInDash()) {
            ds.x = m_speed.x * dt;
            if (m_direction)
                ds.x *= -1;
        }

        // efeito da gravidade
        if (!m_dash.getInDash()) {
            const float Vy = m_speed.y;
            m_speed.y = m_speed.y + GRAVIDADE * dt;
            ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;
        }

        setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y));

        m_speed.x = m_maxSpeed;
    }

    /**
     * @brief muda o estado dos atributos relacionados ao dash
     */
    void Player::stopDash() {
        m_dash.stopDash();
    }

    /**
     * @brief muda o estado dos atributos relacionados ao dash
     */
    void Player::doDash() {
        m_dash.doDash();
    }

    /**
     * @brief metodo que altera o atributo stamina
     *
     * @param qtdUso quantidade de stamina a ser consumida
     *
     * @return retorna um boleano dizendo se foi possivel consumir a quantidade de estamina recebida
     */
    bool Player::consumeStamina(float qtdUso) {
        return m_stamina.consumeStamina(qtdUso);
    }

    void Player::searchIteractions() {
        Gerenciador::GerenciadorDeColisao *pColisao = Gerenciador::GerenciadorDeColisao::getGerenciadorDeColisao();
        if (Entidade *ent = pColisao->procurarEntidade(getPos(), sf::Vector2f(100.0f, 100.0f), IDs::IDs::npc); ent != nullptr) {
            auto *npc = static_cast<Npc::Npc *>(ent);
            m_moving = m_getDamage = m_attaking = false;
            m_onFloor = true;
            updateAnimation();
            draw();
            npc->iniciarDialogo();
        }
    }

    void Player::setProjetil(Weapon::Bullet *bullet) {
        m_fireball.setBullet(bullet);
        m_fireball.setFireBallDamage(m_damage * 1.5f);
    }

    /**
     * @brief metodo que auxilia na tomada de m_damage.
     *
     * @param damage valor a ser descontado da vida do jogador.
     */
    void Player::takeDamage(const float damage) {
        if (!m_getDamage) {
            m_getDamage = true;
            m_attaking = m_moving = false;
            m_rage.setStartingRage(false);
            m_life -= damage;
            if (m_life <= 0.0f) {
                m_dying = true;
                m_getDamage = false;
                m_life = 0.0f;

                if (m_weapon != nullptr)
                    m_weapon->remover();
            }
            m_fireball.setTimeTrhowBullet(0.0f); 
            m_timeDamage = 0.0f;
            m_rage.increaseRage(damage / 2.0f);
        }
    }

    void Player::activeRage() {
        m_rage.startRage();
    }

    void Player::increaseRage(float qtdRage) {
        m_rage.increaseRage(qtdRage);
    }
}