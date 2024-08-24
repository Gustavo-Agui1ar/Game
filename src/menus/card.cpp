
#include "../includes/menus/card.h"

namespace Game{

    namespace Menu{

        Gerenciador::GerenciadorGrafico* Card::pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

        /**
         * @brief construtora da classe Card
         * 
         * @param pos posicao do card
         * @param caminhoEntidades variavel a ser atrbuida em caminhoEntidades de card
         * @param caminhoImagem variavel a ser atrbuida em caminhoImagem de card
         * @param caminhoFase variavel a ser atrbuida em caminhoFase de card
        */
        Card::Card(const sf::Vector2f pos, const std::string caminhoEntidades, const std::string caminhoImagem, const std::string caminhoFase):
        corpo(nullptr), textura(nullptr),selecionado(false), cor(sf::Color(245, 170, 0)),  existe(false), caminhoEntidades(caminhoEntidades),
        caminhoImagem(caminhoImagem), caminhoFase(caminhoFase)
        {
            sf::Vector2f tamJanela = pGrafico->getTamJanela();
            corpo = new sf::RectangleShape(sf::Vector2f(tamJanela.x/5.0f, (tamJanela.x/5.0f) - 20.0f ));
            textura = new sf::Texture();
            std::ifstream arquivo(caminhoImagem);

            if(arquivo)
            {
                if(!textura->loadFromFile(caminhoImagem))
                {
                    std::cout<<"nao foi possivel carregar a textura do card";
                    exit(1);
                }
                existe = true;
            }
            else
            {
                if(!textura->loadFromFile("animations/backgorund/card/card-vazio.png"))
                {
                    std::cout<<"nao foi possivel carregar a textura do card";
                    exit(1);
                }
            }

            corpo->setTexture(textura);
            corpo->setPosition(pos);
            corpo->setOutlineThickness(5);
            corpo->setOutlineColor(sf::Color::Black);            

        }

        /**
         * @brief destrutora da classe card
        */
        Card::~Card()
        {
            if(textura != nullptr)
            {
                delete(textura);
                textura = nullptr;
            }
            if(corpo != nullptr)
            {
                delete(corpo);
                corpo = nullptr;
            }
        }

        /**
         * @brief metodo de acesso ao atributo position de card
         * 
         * @return retorna  a posicao do card
        */
        sf::Vector2f Card::getPos()
        {
            return corpo->getPosition();
        }

        /**
         * @brief metodo de acesso ao atributo caminhoEntidades
         * 
         * @return retorna  caminhoEntidades
        */
        const std::string Card::getCaminhoEntidade()
        {
            return caminhoEntidades;
        }

        /**
         * @brief metodo de acesso ao atributo caminhoImagem
         * 
         * @return retorna  caminhoImagem
        */
        const std::string Card::getCaminhoImagem()
        {
            return caminhoImagem;
        }

        /**
         * @brief metodo de acesso ao atributo caminhoFase
         * 
         * @return retorna  caminhoFase
        */
        const std::string Card::getCaminhoFase()
        {
            return caminhoFase;
        }

        /**
         * @brief metodo modificador do atributo cor 
         * 
         * @param cor cor a ser atribuida em cor do card
        */
        void Card::setColor(sf::Color cor)
        {
            this->cor = cor;
        }

        /**
         * @brief metodo que altera o estado do cboleano selecianado
         * 
         * @param selecionado boleano aser atribuido em selecionado
        */
        void Card::setSelecionado(const bool selecionado)
        {
            this->selecionado = selecionado;
            corpo->setOutlineColor(selecionado ? cor : sf::Color::Black);
            
        }

        /**
         * @brief metodo de acesso ao atributo selecionado
         * 
         * @return retornao boleano selecionado
        */
        const bool Card::getSelecionado()
        {
            return selecionado;
        }

        /**
         * @brief metodo de acesso ao atributo existe
         * 
         * @return retorna o boleano existe
        */
        const bool Card::getExiste()
        {
            return existe;
        }

        /**
         * @brief metodo que deleta as informacoes do card
        */
        void Card::deletarTextura(){
            if(textura){
                sf::Vector2u tamImgAnt = textura->getSize();
                if(!textura->loadFromFile("animations/backgorund/card/card-vazio.png")){
                    std::cout << "Card::nao foi possivel carregar textura" << std::endl;
                    exit(1);
                }
                corpo->setTexture(textura);
                sf::Vector2u tamImgAtual = textura->getSize();
                sf::Vector2f fator((float)tamImgAtual.x / (float)tamImgAnt.x, (float)tamImgAtual.y / (float)tamImgAnt.y);
                corpo->setTextureRect(sf::IntRect(0.0f, 0.0f, tamImgAnt.x * fator.x, tamImgAnt.y * fator.y));
                existe = false;
            }
        }

        /**
         *  @brief metodo que desenha o card na tela
        */
        void Card::draw()
        {
            pGrafico->desenhaElemento(*corpo);
        }
    }

}