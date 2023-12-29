
#include "../includes/menus/menuCarregar.h"

namespace Game{

    namespace Menu{

        MenuCarregar::MenuCarregar(Fase::Fase* fase):
        MenuPrincipal(IDs::IDs::menu_carregar, "CARREGAR JOGO", 100),gerenciadorArquivo(),fase(fase)
        {
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

            inicializarCards();
        }

        MenuCarregar::~MenuCarregar()
        {
            std::list<Card*>::iterator it;

            for(it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;
                if(card != nullptr)
                {
                    delete(card);
                    card = nullptr;
                }
            }

            listaCards.clear();
        
        }

        void MenuCarregar::inicializarCards()
        {
            float espacamento = (tamJanela.x/5.0f)/5.0f;

            for(int i = 0 ; i < 4 ; i++)
            {
                sf::Vector2f pos(sf::Vector2f((tamJanela.x/5.0f) * i + espacamento * (i + 1),180.0f));

                if(fase != nullptr)
                {
                    pos.x =  ( posFundo.x - tamJanela.x / 2.0f + (tamJanela.x / 5.0f) * i + (espacamento) * (i + 1));
                    pos.y =  (posFundo.y - tamJanela.y / 2.0f + 180.0f);
                }

                std::string caminhoEntidades = "saves/SalvarEntidades/salvar" + std::to_string(i + 1) + ".json";
                std::string caminhoFase = "saves/SalvarFase/salvar" + std::to_string(i + 1) + ".json";
                std::string caminhoImagem = "saves/SalvarImagem/salvar" + std::to_string(i + 1) + ".png";

                Card* card = new Card(pos, caminhoEntidades, caminhoImagem, caminhoFase);
                card->setColor(sf::Color{238,173,45});
                listaCards.push_back(card);
            } 

            itCards = listaCards.begin();
            (*itCards)->setSelecionado(true);
        }

        void MenuCarregar::selecionaEsquerda()
        {
            (*itCards)->setSelecionado(false);

            if(itCards == listaCards.begin())
                itCards = listaCards.end();
            
            itCards--;

            (*itCards)->setSelecionado(true);
        }

        void MenuCarregar::selecionaDireita()
        {
            (*itCards)->setSelecionado(false);

            itCards++;
            if(itCards == listaCards.end())
                itCards = listaCards.begin();
            
            (*itCards)->setSelecionado(true);
        }
        
        void MenuCarregar::deletarArquivos()
        {
            Card* card = (*itCards);

            if(card->getExiste())
            {
                gerenciadorArquivo.removeArquivo(card->getCaminhoEntidade().c_str());
                gerenciadorArquivo.removeArquivo(card->getCaminhoFase().c_str());
                gerenciadorArquivo.removeArquivo(card->getCaminhoImagem().c_str());
                card->deletarTextura();
            }
        }

        Card* MenuCarregar::getCardSelecionado()const
        {
            return new Card(sf::Vector2f(0,0),"saves/SalvarEntidades/salvar1.json", "saves/SalvarIMagem/salvar1.png", "saves/SalvarFase/salvar1.json");
        }

        void MenuCarregar::criarBotoes()
        {
            const float posBotaoX = tamJanela.x/2.0f - tamBotao.x/2.0f;
            addBotao( "Carregar", sf::Vector2f(posBotaoX,tamJanela.y/2.0f + tamBotao.y * 1.5f), IDs::IDs::botao_carregar , sf::Color{238,173,45});
            addBotao( "Remover", sf::Vector2f(posBotaoX,tamJanela.y/2.0f +  tamBotao.y * 3.0f), IDs::IDs::botao_remover, sf::Color{238,173,45});
            addBotao( "Voltar", sf::Vector2f(posBotaoX,tamJanela.y/2.0f +  tamBotao.y * 4.5f), IDs::IDs::botao_voltar, sf::Color{238,173,45});
            inicialiarIterador();

            if(fase != nullptr)
            {
                float posBotaoY = 0.8;
                std::list<Botao::BotaoTexto*>::iterator aux;
                int i = 1;
                for(aux = listaDeBotao.begin(); aux != listaDeBotao.end(); aux++, i++)
                {
                    Botao::BotaoTexto* botao = *aux;
                    botao->atualizarPosicaoDaCaixa(sf::Vector2f(posFundo.x - tamBotao.x / 2.0f, posFundo.y / posBotaoY + (tamBotao.y + 20.f) * i));       
                    botao = nullptr;
                }
            }
        }

        void MenuCarregar::executar()
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

            desenharCards();
        }

        void MenuCarregar::desenharCards()
        {
            for(std::list<Card*>::iterator it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;
                card->desenhar();
            }
        }
    }
}