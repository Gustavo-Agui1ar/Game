
#include "../includes/menus/menuCarregar.h"

namespace Game{

    namespace Menu{
        
        /**
         * @brief contrutora da classe MenuCarregar
         * 
         * @param fase fase a ser desenhada como fundo
        */
        MenuCarregar::MenuCarregar(Level::Level* fase):
        MenuPrincipal(IDs::IDs::load_menu, "CARREGAR JOGO", 100),gerenciadorArquivo(),fase(fase)
        {
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

            inicializarCards();
        }

        /**
         * @brief destrutora da classe MenuCarregar
        */
        MenuCarregar::~MenuCarregar()
        {
            for(auto* card : listaCards)
            {
                if(card)
                    delete card;
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
                auto pos(sf::Vector2f((tamJanela.x/5.0f) * i + espacamento * (i + 1),180.0f));

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
                gerenciadorArquivo.removeFile(card->getCaminhoEntidade().c_str());
                gerenciadorArquivo.removeFile(card->getCaminhoFase().c_str());
                gerenciadorArquivo.removeFile(card->getCaminhoImagem().c_str());
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
         * @brief cria os botoes do menuCarregar
        */
        void MenuCarregar::criarBotoes()
        {
            const float posBotaoX = tamJanela.x/2.0f - tamBotao.x/2.0f;
            addBotao( "Carregar", sf::Vector2f(posBotaoX,tamJanela.y/2.0f + tamBotao.y * 1.5f), IDs::IDs::load_button , sf::Color{238,173,45});
            addBotao( "Remover", sf::Vector2f(posBotaoX,tamJanela.y/2.0f +  tamBotao.y * 3.0f), IDs::IDs::remove_button, sf::Color{238,173,45});
            addBotao( "Voltar", sf::Vector2f(posBotaoX,tamJanela.y/2.0f +  tamBotao.y * 4.5f), IDs::IDs::back_button, sf::Color{238,173,45});
            inicialiarIterador();

            if(fase != nullptr)
            {
                float posBotaoY = 0.8;
                int i = 1;
                for(auto* button : listaDeBotao)
                {
                    button->updateBoxPosition(sf::Vector2f(posFundo.x - tamBotao.x / 2.0f, posFundo.y / posBotaoY + (tamBotao.y + 20.f) * i)); 
                    i++;     
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

            desenharCards();
        }

        /**
         * @brief metodo que desenha os cards do menuCarregar
        */
        void MenuCarregar::desenharCards()
        {
            for(auto* card : listaCards)
                card->draw();
        }
    }
}