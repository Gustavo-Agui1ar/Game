
#include "../includes/Observer/Observer.h"

#include "../includes/Manager/EventManager.h"
#include "../includes/Manager/StateManager.h"

namespace Game::Observer{


    Manager::EventManager* Observer::m_eventManager = Manager::EventManager::getEventManager();
    Manager::StateManager* Observer::m_stateManager = Manager::StateManager::getStateManager();

    Observer::Observer():
    m_defaultKeys(),m_especialKeys() , m_active(true)
    {
        m_eventManager->addObserver(this);
        bootKeyboardComands();
    }

    Observer::~Observer()
    {
        removeObserver();
    }

    void Observer::bootKeyboardComands()
    {
        m_defaultKeys.try_emplace(sf::Keyboard::Num0, '0');
        m_defaultKeys.try_emplace(sf::Keyboard::Num1, '1');
        m_defaultKeys.try_emplace(sf::Keyboard::Num2, '2');
        m_defaultKeys.try_emplace(sf::Keyboard::Num3, '3');
        m_defaultKeys.try_emplace(sf::Keyboard::Num4, '4');
        m_defaultKeys.try_emplace(sf::Keyboard::Num5, '5');
        m_defaultKeys.try_emplace(sf::Keyboard::Num6, '6');
        m_defaultKeys.try_emplace(sf::Keyboard::Num7, '7');
        m_defaultKeys.try_emplace(sf::Keyboard::Num8, '8');
        m_defaultKeys.try_emplace(sf::Keyboard::Num9, '9');
        m_defaultKeys.try_emplace(sf::Keyboard::A, 'a');
        m_defaultKeys.try_emplace(sf::Keyboard::B, 'b');
        m_defaultKeys.try_emplace(sf::Keyboard::C, 'c');
        m_defaultKeys.try_emplace(sf::Keyboard::D, 'd');
        m_defaultKeys.try_emplace(sf::Keyboard::E, 'e');
        m_defaultKeys.try_emplace(sf::Keyboard::F, 'f');
        m_defaultKeys.try_emplace(sf::Keyboard::G, 'g');
        m_defaultKeys.try_emplace(sf::Keyboard::H, 'h');
        m_defaultKeys.try_emplace(sf::Keyboard::I, 'i');
        m_defaultKeys.try_emplace(sf::Keyboard::J, 'j');
        m_defaultKeys.try_emplace(sf::Keyboard::K, 'k');
        m_defaultKeys.try_emplace(sf::Keyboard::L, 'l');
        m_defaultKeys.try_emplace(sf::Keyboard::M, 'm');
        m_defaultKeys.try_emplace(sf::Keyboard::N, 'n');
        m_defaultKeys.try_emplace(sf::Keyboard::O, 'o');
        m_defaultKeys.try_emplace(sf::Keyboard::P, 'p');
        m_defaultKeys.try_emplace(sf::Keyboard::Q, 'q');
        m_defaultKeys.try_emplace(sf::Keyboard::R, 'r');
        m_defaultKeys.try_emplace(sf::Keyboard::S, 's');
        m_defaultKeys.try_emplace(sf::Keyboard::T, 't');
        m_defaultKeys.try_emplace(sf::Keyboard::U, 'u');
        m_defaultKeys.try_emplace(sf::Keyboard::V, 'v');
        m_defaultKeys.try_emplace(sf::Keyboard::X, 'x');
        m_defaultKeys.try_emplace(sf::Keyboard::W, 'w');
        m_defaultKeys.try_emplace(sf::Keyboard::Z, 'z');

        m_especialKeys.try_emplace(sf::Keyboard::Enter, "Enter");
        m_especialKeys.try_emplace(sf::Keyboard::BackSpace, "BackSpace");
        m_especialKeys.try_emplace(sf::Keyboard::Escape, "Escape");
        m_especialKeys.try_emplace(sf::Keyboard::Delete, "Delete");
        m_especialKeys.try_emplace(sf::Keyboard::Left, "Left");
        m_especialKeys.try_emplace(sf::Keyboard::Right, "Right");
        m_especialKeys.try_emplace(sf::Keyboard::Down, "Down");
        m_especialKeys.try_emplace(sf::Keyboard::Up, "Up");
        m_especialKeys.try_emplace(sf::Keyboard::LShift, "LShift");
    }

    void Observer::removeObserver()
    {
        m_eventManager->removeObserver(this);
    }

    void Observer::changeState(const bool active)
    {
        m_active = active;
    }

    const bool Observer::getActive()
    {
        return m_active;
    }

    void Observer::mouseMove(const sf::Vector2f posMouse)
    {
        //nothing to do
    }

    void Observer::mouseButtonRelease(const sf::Mouse::Button botaoMouse)
    {
        //nothing to do
    }

}