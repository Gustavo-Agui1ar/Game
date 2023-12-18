
#include "../includes/listeners/listener.h"

#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"

namespace Game{

    namespace Listener{

        Gerenciador::GerenciadorDeEventos* Listener::pEvento = Gerenciador::GerenciadorDeEventos::getGerenciadorDeEventos();
        Gerenciador::GerenciadorDeEstado* Listener::pEstado = Gerenciador::GerenciadorDeEstado::getGerenciadorDeEstado();

        Listener::Listener():
        ativo(true),tecPadrao(),tecEspecial()
        {
            pEvento->addListener(this);
            inicializarComandosteclado();
        }

        Listener::~Listener()
        {
            removerListener();
        }

        void Listener::inicializarComandosteclado()
        {
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num0, '0'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num1, '1'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num2, '2'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num3, '3'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num4, '4'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num5, '5'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num6, '6'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num7, '7'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num8, '8'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Num9, '9'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::A, 'a'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::B, 'b'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::C, 'c'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::D, 'd'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::E, 'e'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::F, 'f'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::G, 'g'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::H, 'h'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::I, 'i'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::J, 'j'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::K, 'k'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::L, 'l'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::M, 'm'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::N, 'n'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::O, 'o'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::P, 'p'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Q, 'q'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::R, 'r'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::S, 's'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::T, 't'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::U, 'u'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::V, 'v'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::X, 'x'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::W, 'w'));
            tecPadrao.insert(std::pair<sf::Keyboard::Key,char>(sf::Keyboard::Z, 'z'));

            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Enter, "Enter"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::BackSpace, "BackSpace"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Escape, "Escape"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Delete, "Delete"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Left, "Left"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Right, "Right"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Down, "Down"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::Up, "Up"));
            tecEspecial.insert(std::pair<sf::Keyboard::Key, std::string>(sf::Keyboard::LShift, "LShift"));
        }

        void Listener::removerListener()
        {
            pEvento->removerListener(this);
        }

        void Listener::mudarEstado(const bool ativo)
        {
            this->ativo = ativo;
        }

        const bool Listener::getAtivo()
        {
            return this->ativo;
        }

        void Listener::moveMouse(const sf::Vector2f posMouse)
        {
            
        }

        void Listener::botaoMouseSolta(const sf::Mouse::Button botaoMouse)
        {
            
        }
    }

}