
#include "../includes/menus/menuPrincipal.h"

namespace Game{

    namespace Menu{

        MenuPrincipal::MenuPrincipal():
        Menu(IDs::IDs::menu_principal,sf::Vector2f(TAM_BOTAO_X, TAM_BOTAO_Y),"SON OF THE STORM",150),
        fundo(IDs::IDs::fundo_menu)
        {
            titulo.setPos(sf::Vector2f(tamJanela.x/2.0f - titulo.getTam().x/2.0f, 25.0f));
            titulo.setCorTexto(sf::Color(238,173,45));
            criarFundo();
            criarBotoes();
        }

        MenuPrincipal::~MenuPrincipal()
        {

        }

        void MenuPrincipal::criarBotoes()
        {
            const float posBotaoX = tamJanela.x/2.0f - TAM_BOTAO_X/2.0f;
            addBotao("Novo Jogo",sf::Vector2f(posBotaoX, tamJanela.y/2.0f),IDs::IDs::botao_novoJogo,sf::Color{238,173,45});
            addBotao("Carregar Jogo",sf::Vector2f(posBotaoX, tamJanela.y/2.0f + tamBotao.y *1.5f),IDs::IDs::botao_carregar_jogo,sf::Color{238,173,45});
            addBotao("Opcoes",sf::Vector2f(posBotaoX, tamJanela.y/2.0f + tamBotao.y *3.0f),IDs::IDs::botao_opcao,sf::Color{238,173,45});
            addBotao("sair",sf::Vector2f(posBotaoX, tamJanela.y/2.0f + tamBotao.y *4.5f),IDs::IDs::botao_sair,sf::Color{238,173,45});
            inicialiarIterador();
        
        }

        void MenuPrincipal::criarFundo()
        {
            fundo.addCamada(CAMINHO_IMAGEM_FUNDO, 0.0f);
        }

        void MenuPrincipal::executar()
        {
            posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
            pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
            fundo.executar();
            pGrafico->resetarJanela();
          
            desenhar();
            pGrafico->desenhaElemento(titulo.getTexto());
        }
    }
}