
#include "../includes/menus/menuSalvar.h"

namespace Game{

    namespace Menu{
        
        /**
         * @brief construtora da classe MenuSalvar 
         * 
         * @param fase fase a ser desenhada como fundo 
        */
        MenuSalvar::MenuSalvar(Level::Level* fase):
        MenuPausa(IDs::IDs::save_menu, "SALVAR JOGADA", fase),gArquivo()
        {
            atualizarPosicaoFundo();
            fundoEscuro.setPosition(0.0f, 0.0f);
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});

            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
            fundoEscuro.setPosition(posFundoEscuro);
            titulo.setPosition(sf::Vector2f(posFundo.x - titulo.getSize().x / 2.1f, posFundo.y - tamJanela.y / 2.0f ));
            
            inicializarCards();
        }

        /**
         * @brief destrutora da classe MenuSalvar
        */
        MenuSalvar::~MenuSalvar()
        {
            for(auto* card : listaCards)
            {
                if(card)
                    delete(card);
            }

            listaCards.clear();
            fase = nullptr;
        }

        /**
         * @brief metodo que inicializa os cards de salvamento
        */
        void MenuSalvar::inicializarCards()
        {
            float espacamento = (tamJanela.x/5.0f)/5.0f;

            for(int i = 0 ; i < 4 ; i++)
            {
                sf::Vector2f pos(sf::Vector2f( posFundo.x - tamJanela.x / 2.0f + (tamJanela.x / 5.0f) * i + (espacamento) * (i + 1), posFundo.y - tamJanela.y / 2.0f + 180.0f));

                std::string caminhoEntidades = "saves/SalvarEntidades/salvar" + std::to_string(i + 1) + ".json";
                std::string caminhoFase = "saves/SalvarFase/salvar" + std::to_string(i + 1) + ".json";
                std::string caminhoImagem = "saves/SalvarImagem/salvar" + std::to_string(i + 1) + ".png";

                Card* card = new Card(pos, caminhoEntidades, caminhoImagem, caminhoFase);
                card->setColor(sf::Color{238,173,45});
                listaCards.push_back(card);
            } 

            itCard = listaCards.begin();
            (*itCard)->setSelecionado(true);
        }


        /**
         * @brief metodo que salva as infomacoes e estados dos objetos da fase atual no card selecionado
        */
        void MenuSalvar::salvar()
        {
            nlohmann::ordered_json jsonEntidades = fase->SaveEntity();
            nlohmann::ordered_json jsonFase = fase->SaveLevel();
            
            const std::string caminhoImagem = (*itCard)->getCaminhoImagem();
            const std::string caminhoEntidade = (*itCard)->getCaminhoEntidade();
            const std::string caminhoFase = (*itCard)->getCaminhoFase();

            gArquivo.removeFile(caminhoEntidade.c_str());
            gArquivo.removeFile(caminhoFase.c_str());

            gArquivo.writeContent(caminhoEntidade.c_str(), jsonEntidades);
            gArquivo.writeContent(caminhoFase.c_str(), jsonFase);

            fase->draw();

            sf::RenderWindow* window = m_graphic->getWindow();

            sf::Texture textura;

            textura.create(window->getSize().x, window->getSize().y);
            textura.update(*(static_cast<sf::Window*>(window)));

            sf::Image imagem = textura.copyToImage();

            imagem.saveToFile(caminhoImagem);
        }

        /**
         * @brief metodo que seleciona o card anterior da lista de cards caso este esteja no inicio voltasse ao final da lista
        */
        void MenuSalvar::selecionaEsquerda()
        {
            std::cout << "i"<< std::endl;
            (*itCard)->setSelecionado(false);

            if(itCard == listaCards.begin())
                itCard = listaCards.end();
            itCard--;
            (*itCard)->setSelecionado(true);
        }

        /**
         * @brief metodo que seleciona o proximo card da lista de cards caso este esteja no final voltasse ao inicio da lista
        */
        void MenuSalvar::selecionaDireita()
        {
            (*itCard)->setSelecionado(false);

            itCard++;
            if(itCard == listaCards.end())
                itCard = listaCards.begin();
            
            (*itCard)->setSelecionado(true);
        }

        /**
         * @brief metodo que cria os botoes da classe MenuSalvar
        */
        void MenuSalvar::criarBotoes()
        {   
            addBotao( "Salvar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::save_button , sf::Color{238,173,45});
            addBotao( "Voltar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::back_button, sf::Color{238,173,45});

            posBotaoY = 0.8f;
            atualizarBotoes();

            inicialiarIterador();
        }

        /**
         * @brief metodo que desenha os cards do menu na tela
        */
        void MenuSalvar::desenharCards()
        {
            for(std::list<Card*>::iterator it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;
                card->draw();
            }
        }
        
        /**
         * @brief metodo que desenha todos os elementos graficos do menu na tela
        */
        void MenuSalvar::executar()
        {
            fase->draw();

            m_graphic->drawElement(fundoEscuro);

            m_graphic->drawElement(titulo.getInfoText());

            draw();

            desenharCards();
        }
    }
}