#include "../includes/Entity/npcs/npc.h"
#include "../includes/Manager/StateManager.h"

namespace Game::Entity::Character::Npc{

    // Initialize the static member variable
    Manager::StateManager* Npc::m_stateManager = Manager::StateManager::getStateManager();
    
    /**
     * @brief Construct a new Npc object.
     * 
     * @param pos Initial position of the NPC.
     * @param IDcharacter ID of the character type.
     * @param pathDialogue Path to the dialogue file.
     */
    Npc::Npc(sf::Vector2f pos, const IDs::IDs IDcharacter, const char* pathDialogue):
    Character(pos, sf::Vector2f(NPC_SIZE_X, NPC_SIZE_Y), 0.0f, IDs::IDs::npc, 0.0f, 0.0f, 0.0f), m_pathDialogue(pathDialogue), m_IDcharacter(IDcharacter)
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

    /**
     * @brief Destroy the Npc object.
     */
    Npc::~Npc() = default;

    /**
     * @brief Initialize the animations for the NPC.
     */
    void Npc::bootAnimation()
    {
        const auto origin = sf::Vector2f(m_size.x / 2.5, m_size.y / 2.2);

        switch(m_IDcharacter)
        {
            case IDs::IDs::barman:
                m_animation.addAnimation("../Game/animations/Characters/Npc/bearded-idle.png", "PARADO", 5, 0.6, sf::Vector2f{6, 2}, origin);
                break;
            case IDs::IDs::woman:
                m_animation.addAnimation("../Game/animations/Characters/Npc/woman-idle.png", "PARADO", 7, 0.5, sf::Vector2f{5, 2}, origin);
                break;
            case IDs::IDs::man:
                m_animation.addAnimation("../Game/animations/Characters/Npc/hat-man-idle.png", "PARADO", 4, 0.5, sf::Vector2f{6, 2}, origin);
                break;
            case IDs::IDs::old_man:
                m_animation.addAnimation("../Game/animations/Characters/Npc/oldman-idle.png", "PARADO", 3, 1.5, sf::Vector2f{6, 2}, origin);
                break;
            default:   
                break;
        }
    }

    /**
     * @brief Update the animation state of the NPC.
     */
    void Npc::updateAnimation()
    {
        m_animation.update(m_direction, "PARADO");
    }
    
    /**
     * @brief Update the position of the NPC.
     */
    void Npc::updatePosition()
    {
        dt = m_graphic->getTime();
        sf::Vector2f ds(0.f, 0.f);

        // Apply gravity effect
        const float Vy = m_speed.y;
        m_speed.y = m_speed.y + GRAVITY * dt;
        ds.y = Vy * dt + (GRAVITY * dt * dt) / 2.0f;

        setPosition(sf::Vector2f(m_position.x + ds.x, m_position.y + ds.y));
    }

    /**
     * @brief Save the current state of the NPC to a JSON object.
     * 
     * @return nlohmann::ordered_json The JSON object with the saved NPC state.
     */
    nlohmann::ordered_json Npc::save()
    {
        nlohmann::ordered_json json = saveCharacter();
        json["dialogue"] = m_pathDialogue;
        return json;
    }
    
    /**
     * @brief Get the path to the dialogue file.
     * 
     * @return const char* The path to the dialogue file.
     */
    const char* Npc::getPathDialogue()
    {
        return m_pathDialogue;
    }

    /**
     * @brief Draw the NPC on the screen.
     */
    void Npc::draw()
    {
        m_graphic->drawElement(m_body);
    }

    /**
     * @brief Update the state of the NPC.
     */
    void Npc::update()
    {
        updatePosition();
        updateAnimation();
        draw();
    }

    /**
     * @brief Start a dialogue with the NPC.
     */
    void Npc::startDialogue()
    {
        auto* levelState = static_cast<State::LevelState*>(m_stateManager->getCurrentState());
        Level::Level* level = levelState->getLevel();
        
        sf::Vector2f directionPosition = level->getPlayer()->getPosition();

        m_direction = m_position.x - directionPosition.x > 0 ? true : false;

        updateAnimation();

        m_stateManager->addState(IDs::IDs::dialogue_estate);

        State::State* state = m_stateManager->getCurrentState();
        auto* dialogue = static_cast<State::DialogueState*>(state);

        dialogue->setDialogue(m_pathDialogue);
    }

    /**
     * @brief Handle collision with another entity.
     * 
     * @param otherEntity Pointer to the other entity.
     * @param ds Displacement vector.
     */
    void Npc::collision(Entity* otherEntity, sf::Vector2f ds)
    {
        // Handle collision with player
    }
}