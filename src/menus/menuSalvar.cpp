
#include "../includes/menus/menuSalvar.h"

namespace Game{

    namespace Menu{

        MenuSalvar::MenuSalvar(Fase::Fase* fase):
        MenuPausa(IDs::IDs::menu_salvar, "SALVAR JOGADA", fase),gArquivo()
        {
            atualizarPosicaoFundo();
            fundoEscuro.setPosition(0.0f, 0.0f);
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});

            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
            fundoEscuro.setPosition(posFundoEscuro);
            titulo.setPos(sf::Vector2f(posFundo.x - titulo.getTam().x / 2.1f, posFundo.y - tamJanela.y / 2.0f ));
            
            inicializarCards();
        }

        MenuSalvar::~MenuSalvar()
        {
            std::list<Card*>::iterator it;

            for(it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;

                if(card != nullptr)
                    delete(card);
                card = nullptr;
            }

            listaCards.clear();
            fase = nullptr;
        }

        void MenuSalvar::inicializarCards()
        {
            float espacamento = (tamJanela.x/5.0f)/5.0f;

            for(int i = 0 ; i < 4 ; i++)
            {
                sf::Vector2f pos(sf::Vector2f( posFundo.x - tamJanela.x / 2.0f + (tamJanela.x / 5.0f) * i + (espacamento) * (i + 1), posFundo.y - tamJanela.y / 2.0f + 180.0f));

                std::string caminhoEntidades = "Game/saves/SalvarEntidades/salvar" + std::to_string(i + 1) + ".txt";
                std::string caminhoFase = "Game/saves/SalvarFase/salvar" + std::to_string(i + 1) + ".txt";
                std::string caminhoImagem = "Game/saves/SalvarImagem/salvar" + std::to_string(i + 1) + ".png";

                Card* card = new Card(pos, caminhoEntidades, caminhoImagem, caminhoFase);
                card->setColor(sf::Color{238,173,45});
                listaCards.push_back(card);
            } 

            itCard = listaCards.begin();
            (*itCard)->setSelecionado(true);
        }


        void MenuSalvar::salvar()
        {
            nlohmann::ordered_json jsonEntidades = fase->salvarEntidades();
            nlohmann::ordered_json jsonFase = fase->salvarFase();
            
            const std::string caminhoImagem = (*itCard)->getCaminhoImagem();
            const std::string caminhoEntidade = (*itCard)->getCaminhoEntidade();
            const std::string caminhoFase = (*itCard)->getCaminhoFase();

            gArquivo.removeArquivo(caminhoEntidade.c_str());
            gArquivo.removeArquivo(caminhoFase.c_str());

            gArquivo.gravarConteudo(caminhoEntidade.c_str(), jsonEntidades);
            gArquivo.gravarConteudo(caminhoFase.c_str(), jsonFase);

            fase->desenhar();

            sf::RenderWindow* window = pGrafico->getWindow();

            sf::Texture textura;

            textura.create(window->getSize().x, window->getSize().y);
            textura.update(*(static_cast<sf::Window*>(window)));

            sf::Image imagem = textura.copyToImage();

            imagem.saveToFile(caminhoImagem);
        }

        void MenuSalvar::selecionaEsquerda()
        {
            (*itCard)->setSelecionado(false);

            if(itCard == listaCards.begin())
                itCard = listaCards.end();
            itCard--;
            (*itCard)->setSelecionado(true);
        }
        
        void MenuSalvar::selecionaDireita()
        {
            (*itCard)->setSelecionado(false);

            itCard++;
            if(itCard == listaCards.end())
                itCard = listaCards.begin();
            
            (*itCard)->setSelecionado(true);
        }

        void MenuSalvar::criarBotoes()
        {   
            addBotao( "Salvar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_salvar , sf::Color{238,173,45});
            addBotao( "Voltar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_voltar, sf::Color{238,173,45});

            posBotaoY = 0.8f;
            atualizarBotoes();

            inicialiarIterador();
        }

        void MenuSalvar::desenharCards()
        {
            for(std::list<Card*>::iterator it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;
                card->desenhar();
            }
        }
        
        void MenuSalvar::executar()
        {
            fase->desenhar();

            pGrafico->desenhaElemento(fundoEscuro);

            pGrafico->desenhaElemento(titulo.getTexto());

            desenhar();

            desenharCards();
        }
    }
}