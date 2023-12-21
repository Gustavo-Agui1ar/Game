
#include "../includes/menus/menuCarregar.cpp"

namespace Game{

    namespace Menu{

        MenuCarregar::MenuCarregar():
        MenuPrincipal(IDs::IDs::menu_carregar, "CARREGAR JOGO", 100),gerenciadorArquivo()
        {
            inicializarCards();
        }

        MenuCarregar:: ~MenuCarregar()
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

            for(int i = 0 < 4 ; i++)
            {
                sf::Vector2f pos((tamJanela.5.0f) * i + espaco * (i + 1),180.0f);

                std::string caminhoEntidades = "Game/saves/SalvarEntidades/salvar" + std::to_string(i + 1) + ".txt";
                std::string caminhoFase = "Game/saves/SalvarFase/salvar" + std::to_string(i + 1) + ".txt";
                std::string caminhoImagem = "Game/saves/SalvarImagem/salvar" + std::to_string(i + 1) + ".png";

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
                gerenciadorArquivo.removeArquivo(card->getCaminhoEntidades().c_str());
                gerenciadorArquivo.removeArquivo(card->getCaminhoFase().c_str());
                gerenciadorArquivo.removeArquivo(card->getCaminhoImagem().c_str());
                card->deletarTextura();
            }
        }

        Card* MenuCarregar::getCardSelecionado()
        {
            return (*itCards);
        }

        void MenuCarregar::criarBotoes()
        {
            const float posBotaoX = tamJanela.x/2.0f - tamBotao.x/2.0f;
            addBotao( "Carregar", sf::Vector2f(posBotaoX,tamJanela.y/2.0f + tamJanela.y * 2.4f), IDs::IDs::botao_carregar , sf::Color{238,173,45});
            addBotao( "Remover", sf::Vector2f(posBotaoX,tamJanela.y/2.0f + tamJanela.y * 3.6f), IDs::IDs::botao_remover, sf::Color{238,173,45});
            addBotao( "Voltar", sf::Vector2f(posBotaoX,tamJanela.y/2.0f + tamJanela.y * 4.8f), IDs::IDs::botao_voltar, sf::Color{238,173,45});
            inicializarIterador();
        }

        void executar()
        {
            posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
            pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
            fundo.executar();
            pGrafico->resetarJanela();

            desenhar();

            pGrafico->desenharElemento(titulo.getTexto());

            for(std::list<Card*>::iterator it = listaCards.begin() ; it != listaCards.end() ; it++)
            {
                Card* card = *it;
                card->desenhar();
            }

        }
    }
}