
#include "../includes/menus/menuOpcao.h"
#include "../includes/Manager/FileManager.h"

namespace Game::Menu{

    
    MenuOpcao::MenuOpcao(Level::Level* fase):
    MenuPrincipal(IDs::IDs::option_menu, "Opcoes", 100),
    velBotaoVolume(VELOCIDADE_BOTAO_VOLUME), pMusica(Manager::MusicManager::getMusicManager()), fase(fase), mousePressed(false)
    {
        titulo.setTextColor(sf::Color{238,173,45});
        titulo.setPosition(sf::Vector2f(tamJanela.x / 2.0f - titulo.getSize().x / 2.0f, 25.0f));
        if(fase != nullptr)
        {
            atualizarPosicaoFundo();
            fundoEscuro.setSize(tamJanela);
            fundoEscuro.setPosition(0.0f, 0.0f);
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});
            auto posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
            fundoEscuro.setPosition(posFundoEscuro);
            titulo.setPosition(sf::Vector2f(posFundo.x - titulo.getSize().x / 2.1f, posFundo.y - tamJanela.y / 2.0f ));
        }

    }

    MenuOpcao::~MenuOpcao() = default;

    void MenuOpcao::addBotao(const std::string info, const sf::Vector2f pos, IDs::IDs ID, const sf::Color corSelecionado, const float posInicioFundo)
    {
        auto* botaoVolume = new Button::VolumeButton(info, tamBotao, pos, ID, corSelecionado, posInicioFundo);

        if(botaoVolume == nullptr)
        {
            std::cout <<"game:: erro ao criar botao de volume" << "\n";
            exit(1);
        }

        listaDeBotao.push_back(static_cast<Button::TextButton*>(botaoVolume));
    }

    void MenuOpcao::criarBotoes()
    {
        float posBotaoX = (tamJanela.x/4.0f - tamBotao.x/2.0f);
        float posBotaoV = tamJanela.x/2.0f - tamBotao.x/2.0f;

        if(fase != nullptr)
        {
            posBotaoX =  posFundo.x - tamBotao.x*2;
            posBotaoV = posFundo.x - tamBotao.x/2.0f;
        }

        addBotao("Volume Geral",sf::Vector2f(posBotaoX,tamJanela.y/4.0f + tamBotao.y * 1.5f), IDs::IDs::sound_geral_button, sf::Color{238,173,45}, posBotaoX +  1.5f*tamBotao.x + 20.0f);
        addBotao("Volume Jogo" , sf::Vector2f(posBotaoX+20.f, tamJanela.y/4.0f + tamBotao.y * 3.0f), IDs::IDs::sound_game_button, sf::Color{238,173,45}, posBotaoX + 1.5f*tamBotao.x + 20.0f);
        addBotao("Efeito Sonoro", sf::Vector2f(posBotaoX,tamJanela.y/4.0f + tamBotao.y * 4.5f), IDs::IDs::sound_effect_button, sf::Color{238,173,45}, posBotaoX +  1.5f*tamBotao.x + 20.0f);

        Menu::addBotao("Voltar", sf::Vector2f(posBotaoV, 550.0f), IDs::IDs::close_button, sf::Color{238,173,45});
        
        inicialiarIterador();
        
    }

    void MenuOpcao::alterarVolume(const bool aumentando)
    {
        if(getIDBotaoSelecionado() != IDs::IDs::close_button)
        {
            std::list<Button::TextButton*>::iterator itBotao;

            for(itBotao = listaDeBotao.begin() ; (*itBotao)->getID() != getIDBotaoSelecionado() ; itBotao++)
            {
                //empty
            }

            auto* botaoVolume = static_cast<Button::VolumeButton*>(*itBotao);

            short vol = aumentando ? 1 : -1;

            atualizarVolume(vol, botaoVolume);
        }
    }

    void MenuOpcao::atualizarVolume(const float volume, Button::VolumeButton* botao)
    {
        if(botao->getID() == IDs::IDs::sound_geral_button){
            
            for(auto aux = listaDeBotao.begin(); aux != listaDeBotao.end() ; aux++)
            {
                botao = static_cast<Button::VolumeButton*>(*aux);
                botao->changeVolume(volume);
               
            }
        } else {
            botao->changeVolume(volume);
        }
    }

    void MenuOpcao::selecionaDireita()
    {
        alterarVolume(true);
    }
    
    void MenuOpcao::selecionaEsquerda()
    {
        alterarVolume(false);
    }

    void MenuOpcao::executar()
    {
        if(fase != nullptr)
        {
            fase->draw();
            m_graphic->drawElement(fundoEscuro);
        }
        else
        {
            posFundo = sf::Vector2f(posFundo.x + m_graphic->getTime() * 80.0f, posFundo.y);
            m_graphic->updateCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
            fundo.execute();
            m_graphic->resetWindow();
        }
        draw();
        m_graphic->drawElement(titulo.getInfoText());
    }

    void MenuOpcao::eventoMouse(const sf::Vector2f posMouse){
        mouseSelecionado = false;
        sf::Vector2f posMouseJan = m_graphic->getWindow()->mapPixelToCoords((sf::Vector2i)posMouse);
        for(auto aux = listaDeBotao.begin(); aux != listaDeBotao.end(); aux++)
        {
            checkAndSelectButton(it, aux, (*aux)->getBox(), posMouseJan);

            auto ID = static_cast<int>((*aux)->getID());

            if(ID >= 37 && ID <= 39)
            {
                auto* button = static_cast<Button::VolumeButton*>(*aux);
                sf::RectangleShape volumeBody = button->getBackGroundBar();
                if(checkAndSelectButton(it, aux, button->getBackGroundBar(), posMouseJan))
                {
                    if(mousePressed && button->checkInsideLimits(posMouseJan)) {
                        if (button->getID() == IDs::IDs::sound_geral_button) {
                            for (auto& auxButton : listaDeBotao) {
                                auto* botao = static_cast<Button::VolumeButton*>(auxButton);
                                botao->changeVolume(posMouseJan);
                            }
                        } else 
                            button->changeVolume(posMouseJan);
                    }
                }
            }

        }
    }

    void MenuOpcao::changeMouseState(bool pressed) {
        mousePressed = pressed;
    }

    bool MenuOpcao::checkAndSelectButton(std::list<Button::TextButton*>::iterator& it, std::list<Button::TextButton*>::iterator& aux,sf::RectangleShape box, const sf::Vector2f& posMouseJan) {
        if (box.getGlobalBounds().contains(posMouseJan)) {
            (*it)->setSelected(false);
            it = aux;
            (*it)->setSelected(true);
            mouseSelecionado = true;
            return true;
        }
        return false;
    }
}