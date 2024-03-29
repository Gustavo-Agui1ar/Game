
#include "../includes/menus/menuOpcao.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game{

    namespace Menu{
        

        MenuOpcao::MenuOpcao(Fase::Fase* fase):
        MenuPrincipal(IDs::IDs::menu_opcao, "Opcoes", 100),
        velBotaoVolume(VELOCIDADE_BOTAO_VOLUME), pMusica(pMusica->getGerenciadorDeMusica()), fase(fase)
        {
            titulo.setCorTexto(sf::Color{238,173,45});
            titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 25.0f));
            if(fase != nullptr)
            {
                atualizarPosicaoFundo();
                fundoEscuro.setSize(tamJanela);
                fundoEscuro.setPosition(0.0f, 0.0f);
                fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});
                sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
                fundoEscuro.setPosition(posFundoEscuro);
                titulo.setPos(sf::Vector2f(posFundo.x - titulo.getTam().x / 2.1f, posFundo.y - tamJanela.y / 2.0f ));
            }

        }

        MenuOpcao::~MenuOpcao()
        {

        }

        void MenuOpcao::addBotao(const std::string info, const sf::Vector2f pos, IDs::IDs ID, const sf::Color corSelecionado, const float posInicioFundo)
        {
            Botao::BotaoVolume* botaoVolume = new Botao::BotaoVolume(info, tamBotao, pos, ID, corSelecionado, posInicioFundo);

            if(botaoVolume == nullptr)
            {
                throw("game:: erro ao criar botao de volume");
            }

            listaDeBotao.push_back(static_cast<Botao::BotaoTexto*>(botaoVolume));
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

            addBotao("Volume Jogo" , sf::Vector2f(posBotaoX, tamJanela.y/4.0f + tamBotao.y * 1.5f), IDs::IDs::botao_volume_do_jogo, sf::Color{238,173,45}, posBotaoX + tamBotao.x + 20.0f);
            addBotao("Volume Geral",sf::Vector2f(posBotaoX,tamJanela.y/4.0f + tamBotao.y * 3.0f), IDs::IDs::botao_volume_geral, sf::Color{238,173,45}, posBotaoX + tamBotao.x + 20.0f);
            addBotao("Efeito Sonoro", sf::Vector2f(posBotaoX,tamJanela.y/4.0f + tamBotao.y * 4.5f), IDs::IDs::botao_volume_efeito_sonoro, sf::Color{238,173,45}, posBotaoX + tamBotao.x + 20.0f);

            Menu::addBotao("Voltar", sf::Vector2f(posBotaoV, 550.0f), IDs::IDs::botao_sair, sf::Color{238,173,45});
           
            inicialiarIterador();
            
        }

        void MenuOpcao::alterarVolume(const bool aumentando)
        {
            if(getIDBotaoSelecionado() != IDs::IDs::botao_sair)
            {
                std::list<Botao::BotaoTexto*>::iterator itBotao;

                for(itBotao = listaDeBotao.begin() ; (*itBotao)->getID() != getIDBotaoSelecionado() ; itBotao++){}

                Botao::BotaoVolume* botaoVolume = static_cast<Botao::BotaoVolume*>(*itBotao);

                short vol = 1;

                if(!aumentando)
                    vol = -1;

                atualizarVolume(vol, botaoVolume);
            }
        }

        void MenuOpcao::atualizarVolume(const float volume, Botao::BotaoVolume* botao)
        {
             if(botao->getID() == IDs::IDs::botao_volume_geral){
                std::list<Botao::BotaoTexto*>::iterator aux = listaDeBotao.begin();
                while (aux != listaDeBotao.end())
                {
                    botao = static_cast<Botao::BotaoVolume*>(*aux);
                    botao->alterarVolume(volume);
                    aux++;
                }
            } else {
                botao->alterarVolume(volume);
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
                fase->desenhar();
                pGrafico->desenhaElemento(fundoEscuro);
            }
            else
            {
                posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
                pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
                fundo.executar();
                pGrafico->resetarJanela();
            }
            desenhar();
            pGrafico->desenhaElemento(titulo.getTexto());
        }
    }
}