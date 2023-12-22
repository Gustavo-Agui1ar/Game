
#include "../includes/menus/card.h"

namespace Game{

    namespace Menu{

        Gerenciador::GerenciadorGrafico* Card::pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

        Card::Card(const sf::Vector2f pos, const std::string caminhoEntidades, const std::string caminhoImagem, const std::string caminhoFase):
        corpo(nullptr), textura(nullptr), caminhoEntidades(caminhoEntidades),caminhoImagem(caminhoImagem), caminhoFase(caminhoFase),
        cor(sf::Color(245, 170, 0)),selecionado(false), existe(false)
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
                if(!textura->loadFromFile("animations\\backgorund\\card\\card-vazio.png"))
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

        const std::string Card::getCaminhoEntidade()
        {
            return caminhoEntidades;
        }

        const std::string Card::getCaminhoImagem()
        {
            return caminhoImagem;
        }

        const std::string Card::getCaminhoFase()
        {
            return caminhoFase;
        }

        void Card::setColor(sf::Color cor)
        {
            this->cor = cor;
        }

        void Card::setSelecionado(const bool selecionado)
        {
            this->selecionado = selecionado;
            corpo->setOutlineColor(selecionado ? cor : sf::Color::Black);
            
        }

        const bool Card::getSelecionado()
        {
            return selecionado;
        }

        const bool Card::getExiste()
        {
            return existe;
        }

        void Card::deletarTextura(){
            if(textura){
                sf::Vector2u tamImgAnt = textura->getSize();
                if(!textura->loadFromFile("Game/animations/BacGorund/card/card-vazio.png")){
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

        void Card::desenhar()
        {
            pGrafico->desenhaElemento(*corpo);
        }
    }

}