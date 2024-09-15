
#include "../includes/Entity/npcs/npc.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game::Entity::Character::Npc{

    Gerenciador::GerenciadorDeEstado* Npc::m_pEstate = Gerenciador::GerenciadorDeEstado::getGerenciadorDeEstado();
    
    Npc::Npc(sf::Vector2f pos, const IDs::IDs IDcharacter , const char* pathDialogue):
    Character(pos,sf::Vector2f(NPC_SIZE_X, NPC_SIZE_Y), 0.0f, IDs::IDs::npc, 0.0f, 0.0f, 0.0f), m_pathDialogue(pathDialogue), m_IDcharacter(IDcharacter)
    {
        bootAnimation();
        switch(IDcharacter)
        {
            case IDs::IDs::barman:
                m_pathDialogue = "../Game/falas/barman.txt";
            break;
            case IDs::IDs::woman:
                m_pathDialogue = "../Game/falas/mulher.txt";
            break;
            case IDs::IDs::man:
                m_pathDialogue = "../Game/falas/jovem.txt";
                break;
            case IDs::IDs::old_man:
                m_pathDialogue = "../Game/falas/velho.txt";
                break;
            default:   
                break;
        }

    }
    Npc::~Npc() = default;

    void Npc::bootAnimation()
    {
        const auto origin = sf::Vector2f(m_size.x/2.5,m_size.y/2.2);

        switch(m_IDcharacter)
        {
            case IDs::IDs::barman:
                m_animation.addAnimation("../Game/animations/Characters/Npc/bearded-idle.png","PARADO",5,0.6,sf::Vector2f{6,2},origin);
            break;
            case IDs::IDs::woman:
                m_animation.addAnimation("../Game/animations/Characters/Npc/woman-idle.png","PARADO",7,0.5,sf::Vector2f{5,2},origin);
            break;
            case IDs::IDs::man:
                m_animation.addAnimation("../Game/animations/Characters/Npc/hat-man-idle.png","PARADO",4,0.5,sf::Vector2f{6,2},origin);
            break;
            case IDs::IDs::old_man:
                m_animation.addAnimation("../Game/animations/Characters/Npc/oldman-idle.png","PARADO",3,1.5,sf::Vector2f{6,2},origin);
            break;
            default:   
                break;
        }
    }

    void Npc::updateAnimation()
    {
        m_animation.update(m_direction, "PARADO");
    }
    
    void Npc::updatePosition()
    {
        dt = m_graphic->getTempo();
        sf::Vector2f ds(0.f,0.f);

        //efeito da gravidade

        const float Vy = m_speed.y;
        m_speed.y = m_speed.y + GRAVITY * dt;
        ds.y = Vy * dt + (GRAVITY * dt * dt) / 2.0f;

        setPosition(sf::Vector2f(m_position.x + ds.x, m_position.y + ds.y ));
    }

    nlohmann::ordered_json Npc::save()
    {
        nlohmann::ordered_json json = saveCharacter();

        json["dialogo"] = m_pathDialogue;
        
        return json;
    }
    
    const char* Npc::getPathDialogue()
    {
        return m_pathDialogue;
    }

    void Npc::draw()
    {
        m_graphic->desenhaElemento(m_body);
    }

    void Npc::update()
    {
        updatePosition();
        updateAnimation();
        draw();
    }

    void Npc::startDialogue()
    {
        auto* levelState = static_cast<State::LevelState*>(m_pEstate->getEstadoAtual());
        Level::Level* fase = levelState->getLevel();
        
        sf::Vector2f posDirecao = fase->getPlayer()->getPosition();

        m_direction = m_position.x - posDirecao.x > 0 ? true : false;

        updateAnimation();

        m_pEstate->addEstado(IDs::IDs::dialogue_estate);

        State::State* estado = m_pEstate->getEstadoAtual();
        auto* eDialogo = static_cast<State::DialogueState*>(estado);

        eDialogo->setDialogue(m_pathDialogue);
    }

    void Npc::collision(Entity* outraEntidade, sf::Vector2f ds)
    {
        //collision with player
    }
}