
#include "../includes/menus/menuCarregar.h"

namespace Game{

    namespace Menu{
        
        /**
         * @brief contrutora da classe MenuCarregar
         * 
         * @param fase fase a ser desenhada como fundo
        */
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

        /**
         * @brief destrutora da classe MenuCarregar
        */
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

        /**
         * @brief inicializa os cards de carregamento
        */
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

        /**
         * @brief metodo que seleciona o card anterior da lista de cards caso este esteja no inicio voltasse ao final da lista
        */
        void MenuCarregar::selecionaEsquerda()
        {
            (*itCards)->setSelecionado(false);

            if(itCards == listaCards.begin())
                itCards = listaCards.end();
            
            itCards--;

            (*itCards)->setSelecionado(true);
        }

        /**
         * @brief metodo que seleciona o proximo card da lista de cards caso este esteja no final voltasse ao inicio da lista
        */
        void MenuCarregar::selecionaDireita()
        {
            (*itCards)->setSelecionado(false);

            itCards++;
            if(itCards == listaCards.end())
                itCards = listaCards.begin();
            
            (*itCards)->setSelecionado(true);
        }
        
        /**
         * @brief metodo que deleta as informacoes do card selecionado
        */
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
        
        /**
         * @brief metodo de acesso ao card selecionado
         * 
         * @return retorna um card com as informcoes do card selecionado
        */
        Card* MenuCarregar::getCardSelecionado()const
        {
            const std::string entidade = (*itCards)->getCaminhoEntidade(); 
            const std::string imagem = (*itCards)->getCaminhoImagem(); 
            const std::string fase = (*itCards)->getCaminhoFase(); 

            return new Card(sf::Vector2f(0,0), entidade, imagem, fase);
        }

        /**
         * @brief metodo de correcao do evento de entrar em menus 
        */
        void MenuCarregar::criarBotaoBug()
        {
            addBotao("Voltar", sf::Vector2f(tamJanela.x / 2.0f - tamBotao.x / 2.0f, tamJanela.y - tamJanela.y / 12.0f), IDs::IDs::botao_voltar, sf::Color{0, 255, 0});
            inicialiarIterador();
        }
        
        /**
         * @brief cria os botoes do menuCarregar
        */
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

        /**
         * @brief metodo que desenha os elementos graficos do menuCarregar
        */
        void MenuCarregar::executar()
        {
            if(fase != nullptr)
            {
                fase->draw();
                m_pGrafic->desenhaElemento(fundoEscuro);
            }
            else
            {
                posFundo = sf::Vector2f(posFundo.x + m_pGrafic->getTempo() * 80.0f, posFundo.y);
                m_pGrafic->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
                fundo.executar();
                m_pGrafic->resetarJanela();
            }
            draw();

            m_pGrafic->desenhaElemento(titulo.getTexto());

            desenharCards();
        }

        /**
         * @brief metodo que desenha os cards do menuCarregar
        */
        void MenuCarregar::desenharCards()
        {
            for(std::list<Card*>::iterator it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;
                card->draw();
            }
        }
    }
}