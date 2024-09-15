#include "../includes/listeners/listenerJogador.h"
#include "../includes/Entity/npcs/npc.h"
#include "../includes/Entity/Player/Player.h"
#include "../includes/gerenciador/gerenciadorDeColisao.h"
#include "../includes/Entity/Enemy/Skeleton.h"
#include "../includes/Entity/Enemy/Slime.h"
namespace Game::Entity::Character::Player {
 
    Player::~Player() {
        if (m_observerPlayer!= nullptr)
            delete m_observerPlayer;
        if (m_lifeTube.getTexture())
            delete (m_lifeTube.getTexture());
        if (m_lifeBar.getTexture())
            delete (m_lifeBar.getTexture());
    }

    Player::Player(const sf::Vector2f pos, Weapon::Weapon *weapon, Weapon::Bullet *bullet) : Character(pos, sf::Vector2f(SIZE_PLAYER_X, SIZE_PLAYER_Y), PLAYER_SPEED_X, IDs::IDs::player, PLAYER_TIME_GETDAMAGE, ANIMATION_DEATH_PLAYER, PLAYER_DAMAGE), m_dash(this), m_rage(this),
    m_stamina(this), m_fireball(this), m_onFloor(false), m_qtdJump(0), m_timeAnimationAttack(TIME_DAMAGE_PLAYER), m_timeAttack(0.0f), m_observerPlayer(new Listener::ListenerJogador(this)) {
        
        bootAnimation();
        bootLifeBar();
        bootSound();

        if (weapon != nullptr)
            setWeapon(weapon);

        if (bullet != nullptr)
            m_fireball.setBullet(bullet);
    }

    Player::Player(nlohmann::ordered_json atributos) : Character(m_position, sf::Vector2f(SIZE_PLAYER_X, SIZE_PLAYER_Y), PLAYER_SPEED_X, IDs::IDs::player, PLAYER_TIME_GETDAMAGE, ANIMATION_DEATH_PLAYER, PLAYER_DAMAGE), 
    m_dash(this), m_rage(this), m_stamina(this), m_fireball(this), m_timeAnimationAttack(TIME_DAMAGE_PLAYER), m_timeAttack(0.0f), m_observerPlayer(new Listener::ListenerJogador(this))
    {
        try {
            auto currentPosition = sf::Vector2f(atributos["position"]["x"].template get<float>(), atributos["position"]["y"].template get<float>());
            auto currentSize = sf::Vector2f(atributos["size"]["x"].template get<float>(), atributos["size"]["y"].template get<float>());
            auto currentSpeed = sf::Vector2f(atributos["speed"]["x"].template get<float>(), atributos["speed"]["y"].template get<float>());

            setPosition(currentPosition);
            setSize(currentSize);
            setMaxSpeed(currentSpeed);

            m_moving = atributos["moving"].template get<bool>();
            m_direction = atributos["direction"].template get<bool>();
            m_getDamage = atributos["InDamage"].template get<bool>();
            m_attaking = atributos["attacking"].template get<bool>();
            m_dying = atributos["dying"].template get<bool>();
            m_life = atributos["life"].template get<float>();
            m_timeDamage = atributos["timeDamage"].template get<float>();
            m_timeDeath = atributos["deathTime"].template get<float>();
            dt = atributos["life"].template get<float>();
            m_damage = atributos["damage"].template get<float>();
            m_stamina.setStamina(atributos["stamina"].template get<float>());
            m_onFloor = atributos["onFloor"].template get<bool>();
            m_qtdJump = atributos["qtdJump"].template get<int>();
           
            m_dash.setInDash(atributos["inDash"].template get<bool>());
            m_dash.setCanDash(atributos["canDash"].template get<bool>());
            m_dash.setTimeDash(atributos["timeDash"].template get<float>());
           
            m_rage.setRage(atributos["rage"].template get<float>());
            m_rage.setInRage(atributos["inRage"].template get<bool>());
            m_rage.setStartingRage(atributos["startingRage"].template get<bool>());
            
            m_fireball.setTrhowBullet(atributos["trhowBullet"].template get<bool>());
            m_fireball.setTimeTrhowBullet(atributos["timeTrhowBullet"].template get<float>());

            bootAnimation();
            bootLifeBar();
            bootSound();

            m_animation.setCurrentImg(atributos["currentImg"].template get<std::string>());
            m_animation.setCurrentFrame(atributos["currentFrame"].template get<unsigned int>());
            m_animation.setTotalTime(atributos["totalTime"].template get<float>());
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            m_canRemove = true;
        }
    }

    void Player::bootAnimation() {
        const auto origemT = sf::Vector2f((m_size.x / 2), (m_size.y / 5));
        m_animation.addAnimation("animations/Characters/Player/Idle.png", "IDLE", 8, 0.2f, sf::Vector2f{2.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 3));
        m_animation.addAnimation("animations/Characters/Player/Jump.png", "JUMP", 3, 0.16f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Characters/Player/Down.png", "DOWN", 3, 0.12f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Characters/Player/Dash.png", "DASH", 4, 0.12f, sf::Vector2f{4.5f, 0.8f}, sf::Vector2f(origemT.x, origemT.y / 4));
        m_animation.addAnimation("animations/Characters/Player/Run.png", "RUN", 8, 0.12f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Characters/Player/Attack.png", "ATTACK", 4, 0.15f, sf::Vector2f{3.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 2));
        m_animation.addAnimation("animations/Characters/Player/Dead.png", "DEAD", 12, 0.15f, sf::Vector2f{3.f, 1.5f}, sf::Vector2f(origemT.x - origemT.x / 2, origemT.y));
        m_animation.addAnimation("animations/Characters/Player/Hit.png", "HIT", 3, 0.15f, sf::Vector2f{2.2f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 3));
        m_animation.addAnimation("animations/Characters/Player/Fireball.png", "FIREBALL", 9, 0.1f, sf::Vector2f{3.5f, 1.12f}, sf::Vector2f(origemT.x, origemT.y / 5));
        m_animation.addAnimation("animations/Characters/Player/idle-fire.png", "IDLE-F", 8, 0.2f, sf::Vector2f{2.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 5));
        m_animation.addAnimation("animations/Characters/Player/Jump-fire.png", "JUMP-F", 3, 0.16f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Characters/Player/Down-fire.png", "DOWN-F", 3, 0.12f, sf::Vector2f{2.5f, 1.25f}, origemT);
        m_animation.addAnimation("animations/Characters/Player/Dash-fire.png", "DASH-F", 4, 0.12f, sf::Vector2f{2.75f, 1.25f}, sf::Vector2f(origemT.x, origemT.y));
        m_animation.addAnimation("animations/Characters/Player/Run-fire.png", "RUN-F", 8, 0.12f, sf::Vector2f{2.5f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 4));
        m_animation.addAnimation("animations/Characters/Player/attack-fire.png", "ATTACK-F", 4, 0.15f, sf::Vector2f{3.0f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 4));
        m_animation.addAnimation("animations/Characters/Player/Dead-fire.png", "DEAD-F", 11, 0.15f, sf::Vector2f{3.0f, 1.5f}, sf::Vector2f(origemT.x - origemT.x / 2, origemT.y));
        m_animation.addAnimation("animations/Characters/Player/Hit-fire.png", "HIT-F", 4, 0.15f, sf::Vector2f{2.2f, 1.1f}, sf::Vector2f(origemT.x, origemT.y / 3));
        m_animation.addAnimation("animations/Characters/Player/Fireball-fire.png", "FIREBALL-F", 9, 0.1f, sf::Vector2f{3.5f, 1.12f}, sf::Vector2f(origemT.x, origemT.y / 5));
        m_animation.addAnimation("animations/Characters/Player/Furia.png", "RAGE", 12, 0.1f, sf::Vector2f{3.0f, 1.12f}, sf::Vector2f(origemT.x, origemT.y / 5));
    }

    void Player::update() {
        
        updatePosition();
        updateWeapon();
        m_fireball.updateBullet();
        m_graphic->atualizarCamera(sf::Vector2f(getPosition().x, ALTURA_TELA / 2.f));
        updateAnimation();
        updateLifeBar();
        m_stamina.updateStaminaBar();
        m_rage.updateRageBar();
        updateTimeDamage();
        m_dash.updateDash();
        draw();
    }

    void Player::canJump() {
        m_onFloor = true;
        m_qtdJump = 0;
    }
    
    void Player::jump() {
        if (!m_attaking && !m_getDamage && (m_onFloor || m_qtdJump < QTD_JUMP)) {
            m_speed.y = -sqrt(2.0f * GRAVITY * JUMP_SIZE);
            m_onFloor = false;
            m_qtdJump++;
        }
    }

    void Player::updateAnimation() {
        if (!m_rage.getInRage())
            selectAnimation("");
        else
            selectAnimation("-F");
    }

    void Player::selectAnimation(std::string complement) {
        if (m_dying) {
            m_animation.update(m_direction, "DEAD" + complement);
            m_timeDeath += m_graphic->getTempo();
            if (m_timeDeath > m_animationTimeDeath)
                m_canRemove = true;
        }
        else if (m_rage.getStartingRage()) {
            m_animation.update(m_direction, "RAGE" + complement);
            m_rage.updateStartingRage();
        }
        else if (m_getDamage)
            m_animation.update(m_direction, "HIT" + complement);
        else if (m_dash.getInDash())
            m_animation.update(m_direction, "DASH" + complement);
        else if (!m_onFloor && m_speed.y > 0.0f)
            m_animation.update(m_direction, "DOWN" + complement);
        else if (!m_onFloor)
            m_animation.update(m_direction, "JUMP" + complement);
        else if (m_moving)
            m_animation.update(m_direction, "RUN" + complement);
        else if (m_attaking && m_fireball.getTrhowBullet())
            m_animation.update(m_direction, "FIREBALL" + complement);
        else if (m_attaking)
            m_animation.update(m_direction, "ATTACK" + complement);
        else
            m_animation.update(m_direction, "IDLE" + complement);
    }

    void Player::collision(Entity *outraEntidade, sf::Vector2f ds) {
        IDs::IDs other_ID = outraEntidade->getID();
        if (other_ID == IDs::IDs::red_slime || other_ID == IDs::IDs::skeleton) {
            auto *inimigo = static_cast<Enemy::Enemy *>(outraEntidade);
            inimigo->stop();
            inimigo->attack();
        }
        else if (other_ID == IDs::IDs::enemy_weapon) {
            auto *m_weapon = static_cast<Weapon::Weapon *>(outraEntidade);

            if (m_rage.getInRage())
                takeDamage(m_weapon->getDamage() / 2.0f);
            else
                takeDamage(m_weapon->getDamage());
        }
        else if (other_ID == IDs::IDs::enemy_bullet) {
            auto *bullet = dynamic_cast<Weapon::Bullet *>(outraEntidade);

            if (m_rage.getInRage())
                takeDamage(bullet->getDamage() / 2.0f);
            else
                takeDamage(bullet->getDamage());
            
            bullet->setCollision(true);
        }
    }

    void Player::bootLifeBar() {
        auto lifeTube = sf::Vector2f(PLAYER_LIFE_BAR_X, PLAYER_LIFE_BAR_Y);
        m_lifeTube.setSize(lifeTube);
        m_lifeBar.setSize(lifeTube);
        auto *textureLife = new sf::Texture();
        auto *textureBar = new sf::Texture();
        textureLife->loadFromFile("animations/Characters/Life/VidaJogador.png");
        textureBar->loadFromFile("animations/Characters/Life/BarraVida.png");
        m_lifeBar.setTexture(textureLife);
        m_lifeTube.setTexture(textureBar);
    }
  
    void Player::updateLifeBar() {
        sf::Vector2f screenPosition = m_graphic->getCamera().getCenter();
        sf::Vector2f screenSize = m_graphic->getTamJanela();

        auto barPosition = sf::Vector2f(screenPosition.x - screenSize.x / 2.0f + 10.0f, 30.0f);
        m_lifeTube.setPosition(barPosition);
        m_lifeBar.setSize(sf::Vector2f((PLAYER_LIFE_BAR_X - 40.0f) * (m_life / m_maxLife), PLAYER_LIFE_BAR_Y - 13.0f));
        m_lifeBar.setPosition(sf::Vector2f(barPosition.x + 7.0f, barPosition.y + m_lifeTube.getSize().y / 2.0f - m_lifeBar.getSize().y / 2.0f));
    }

    void Player::draw() {
        m_graphic->desenhaElemento(m_body);
        m_graphic->desenhaElemento(m_lifeTube);
        m_graphic->desenhaElemento(m_lifeBar);
        m_stamina.drawStaminaBar();
        m_rage.drawRageBar();
    }

    void Player::updateWeapon() {
        if (m_attaking && !m_dying && !m_fireball.getTrhowBullet()) {
            m_timeAttack += m_graphic->getTempo();
            if (m_timeAttack > m_timeAnimationAttack) {
                m_weapon->setPosition(sf::Vector2f(-1000.0f, -1000.0f));
                m_timeAttack = 0.0f;
                m_attaking = false;
            }
            else if (m_timeAttack > (m_timeAnimationAttack / 3.0f) * 2) {
                sf::Vector2f weaponPosition = (m_direction ? sf::Vector2f(m_position.x - m_weapon->getSize().x / 2.0f, m_position.y) : sf::Vector2f(m_position.x + m_weapon->getSize().x / 2.0f, m_position.y));
                m_weapon->setPosition(weaponPosition);
            }
            else if (m_timeAttack > m_timeAnimationAttack / 3.0f)
                m_soundAttack.play();
        }
    }

    void Player::trhowBullet() {
        m_fireball.trhowBullet();
    }

    bool Player::getOnFloor() const {
        return m_onFloor;
    }

    void Player::changeObserverState(const bool ative) {
        m_observerPlayer->mudarEstado(ative);
    }

    nlohmann::ordered_json Player::save() {
        nlohmann::ordered_json json = saveCharacter();
        json["onFloor"] = m_onFloor;
        json["qtdJump"] = m_qtdJump;
        json["timeAttack"] = m_timeAttack;
        json = m_dash.saveDash(json);
        json = m_rage.saveRage(json);
        json = m_stamina.saveStamina(json);
        json = m_fireball.saveFireBall(json);
        json = m_animation.saveAnimation(json);

        return json;
    }

    void Player::bootSound() {
        if (!m_soundAttackBuffer.loadFromFile(PATH_SOUND_ATTACK)) {
            std::cout << "Player: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundAttack.setBuffer(m_soundAttackBuffer);
    }

    void Player::updatePosition() {
        dt = m_graphic->getTempo();
        sf::Vector2f ds(0.f, 0.f);

        if (m_moving && !m_dying && !m_getDamage && !m_dash.getInDash()) {
            ds.x = m_speed.x * dt;
            if (m_direction)
                ds.x *= -1;
        }

        if (!m_dash.getInDash()) {
            const float Vy = m_speed.y;
            m_speed.y = m_speed.y + GRAVITY * dt;
            ds.y = Vy * dt + (GRAVITY * dt * dt) / 2.0f;
        }

        setPosition(sf::Vector2f(m_position.x + ds.x, m_position.y + ds.y));

        m_speed.x = m_maxSpeed;
    }

    void Player::stopDash() {
        m_dash.stopDash();
    }

    void Player::doDash() {
        m_dash.doDash();
    }

    bool Player::consumeStamina(float qtdUso) {
        return m_stamina.consumeStamina(qtdUso);
    }

    void Player::searchIteractions() {
        Gerenciador::GerenciadorDeColisao *pColisao = Gerenciador::GerenciadorDeColisao::getGerenciadorDeColisao();
        if (Entity *ent = pColisao->procurarEntidade(getPosition(), sf::Vector2f(100.0f, 100.0f), IDs::IDs::npc); ent != nullptr) {
            auto *npc = static_cast<Npc::Npc *>(ent);
            m_moving = m_getDamage = m_attaking = false;
            m_onFloor = true;
            updateAnimation();
            draw();
            npc->startDialogue();
        }
    }

    void Player::setBullet(Weapon::Bullet *bullet) {
        m_fireball.setBullet(bullet);
        m_fireball.setFireBallDamage(m_damage * 1.5f);
    }

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
                    m_weapon->remove();
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