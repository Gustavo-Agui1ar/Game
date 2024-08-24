
#include "../includes/entidade/Weapon/Bullet.h"
#include "../includes/entidade/Enemy/Enemy.h"

namespace Game::Entidade::Weapon{

    Bullet::Bullet( IDs::IDs ID):
    Weapon(ID), m_direction(false), m_collision(true), m_speed(sf::Vector2f(0.0f, 0.0f)), m_animation(&corpo)
    {
        setPos(sf::Vector2f(-1000.0f, -1000.0f));
        inicializarAnimacao();
    }

    Bullet::Bullet( nlohmann::ordered_json atributos):
    Weapon(atributos["ID"].template get<IDs::IDs>()), m_animation(&corpo)
    {
        try{
            m_damage = atributos["dano"].template get<float>();
            setPos(sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>()));
            setTam(sf::Vector2f(atributos["tam"]["x"].template get<float>(), atributos["tam"]["y"].template get<float>()));
            m_direction = atributos["direcao"].template get<bool>();
            m_collision = atributos["colidiu"].template get<bool>();

            inicializarAnimacao();

            m_animation.setCurrentImg(atributos["imagemAtual"].template get<std::string>());
            m_animation.setCurrentFrame(atributos["tempoTotal"].template get<unsigned int>());
            m_animation.setTotalTime(atributos["tempoTotal"].template get<float>());

            setSpeed(sf::Vector2f(atributos["velocidade"]["x"].template get<float>(), atributos["velocidade"]["y"].template get<float>()));

        
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            podeRemover = true;
        }
    }

    Bullet::~Bullet() = default;

    void Bullet::inicializarAnimacao()
    {
        if(getID() == IDs::IDs::projetil_inimigo)
        {
            setTam(sf::Vector2f(TAMANHO_PROJETIL, TAMANHO_PROJETIL));
            m_animation.addAnimation("../Game/animations/enemy/Skeleton_Archer/Arrow.png", "ATACA", 1, 10.0f, sf::Vector2f(1.5f, 0.2f), sf::Vector2f(tam.x / 2.0f, tam.y / 2.0f));
        }
        else
        {
            setTam(sf::Vector2f(TAMANHO_PROJETIL_JOGADOR, TAMANHO_PROJETIL_JOGADOR));
            m_animation.addAnimation("../Game/animations/Player/Fire-ball.png", "ATACA", 4, 0.12f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(tam.x / 2.0f, tam.y / 2.0f));
        }
        m_animation.setCurrentImg("ATACA"); 
    }

    void Bullet::setSpeed(sf::Vector2f speed)
    {
        m_speed = speed;
    }

    void Bullet::setCollision(bool collision)
    {
        m_collision = collision;

        if(m_collision)
        {
            setPos(sf::Vector2f(-1000.0f, -1000.0f));
            setSpeed(sf::Vector2f(0.0f, 0.0f));
        }
    }

    const bool Bullet::getCollision()
    {
        return m_collision;
    }

    void Bullet::setDirection(bool direction)
    {
        m_direction = direction;
        m_speed = direction ? sf::Vector2f(m_speed.x * -1, m_speed.y) : m_speed;
    }

    void Bullet::verificarSaiuTela()
    {
        sf::Vector2f centroTela = m_pGrafic->getCamera().getCenter();
        sf::Vector2f tamJanela = m_pGrafic->getTamJanela();

        if(pos.x < centroTela.x - tamJanela.x/2.0f || pos.x > centroTela.x + tamJanela.x/2.0f ||
            pos.y < centroTela.y - tamJanela.y/2.0f || pos.y > centroTela.y + tamJanela.y/2.0f )
        {
            setCollision(true);
        }
    }

    void Bullet::atualizarPosicao()
    {
        const float dt = m_pGrafic->getTempo();
        sf::Vector2f posFinal(0.0f, pos.y);

        posFinal.x = pos.x + m_speed.x * dt;

        setPos(posFinal);
    }

    void Bullet::atualizarAnimacao()
    {
        m_animation.update(m_direction, "ATACA");
    }

    void Bullet::draw()
    {
        m_pGrafic->desenhaElemento(corpo);
    }

    nlohmann::ordered_json Bullet::salvar()
    {
        nlohmann::ordered_json json = salvarArma();

        json["direcao"] = m_direction;
        json["velocidade"] = {{"x", m_speed.x}, {"y", m_speed.y}};
        json["colidiu"] = m_collision;
        json["imagemAtual"] = m_animation.getCurrentImg();
        json["tempoTotal"] = m_animation.getTotalTime();
        json["quadroAtual"] = m_animation.getCurrentFrame();

        return json;
    }

    void Bullet::update()
    {
        if(!m_collision)
        {
            atualizarPosicao();
            atualizarAnimacao();
            verificarSaiuTela();

            m_pGrafic->desenhaElemento(corpo);
        }
    }

    /**
     * @brief metodo que trata da colisao da arma
     * com outtras entidades dependendo de 
     * seu id.
     * 
     * @param outraEntidade entidade a verificar colisao
     * @param ds distancia entre os centros de arma e outra entidade. 
    */
    void Bullet::colisao(Entidade* outraEntidade, sf::Vector2f ds)
    {
        auto other_ID = static_cast<int>(outraEntidade->getID());
        if(other_ID >= 2 && other_ID <= 4)
        {    
            auto* inimigo = static_cast<Character::Enemy::Enemy*>(outraEntidade);
            if(!inimigo->getDie())
            {
                inimigo->takeDamage(m_damage);
                setCollision(true);
            }
        
        }
    }
}