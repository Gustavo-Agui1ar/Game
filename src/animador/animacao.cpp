
#include "../../includes/animador/animacao.h"

namespace Game{

    namespace Animador{

        /**
         * construtora da classe animacao
         * 
         * @param corpo referencia ao corpo a ser aplicado a imagem.
        */
        Animacao::Animacao(sf::RectangleShape* corpo):relogio()
        {
            estadoAtual = "";
            this->corpo = corpo;
        }

        /**
         * destrutora da classe animacao realiza a destrucao
         * de todas as imagems armazenadas no hashMap.  
        */
        Animacao::~Animacao()
        {
           std::map<std::string, Imagem*>::iterator it = mapImagem.begin();
            while(it != mapImagem.end()){
                if(it->second){
                    delete(it->second);
                    it->second = nullptr;
                }
                it++;
            }
            mapImagem.clear();
        }

        /**
         * metodo que atualiza a imagem a ser desenhada 
         * 
         * @param direcao direcao do personagem(define a direcao da imagem)
         * @param estadoatual define qual imagem sera atualizada/chamada.
         * 
         *@return metodo sem retorno (void)
        */
        void Animacao::atualizar(bool direcao, std::string estadoAtual)
        {
            if(this->estadoAtual != estadoAtual)
            {
                if(this->estadoAtual != "")
                    mapImagem[this->estadoAtual]->resetar();
            }
            this->estadoAtual = estadoAtual;
            
            float dt = relogio.getElapsedTime().asSeconds();
            relogio.restart();

            Imagem* img = mapImagem[this->estadoAtual];
           
            sf::Vector2f escala = img->getEscala();

            img->atualizar(direcao,dt);
            corpo->setTextureRect(img->getTamanho());
            corpo->setTexture(img->getTextura());
            corpo->setOrigin(img->getOrigem());
            corpo->setScale(escala.x,escala.y);

        }

        /**
         * @brief metodo que adiciona uma imagem no hashMap de imagens
         * 
         * @param caminhoTextura onde a textura esta
         *
         * @param nomeDaAnimacao nome a ser usado de key no hashMap
         * 
         * @param qtdImagem numero de sprites da imagem
         * 
         * @param tempoDeTroca tempo total entre cada troca de sprites
         * 
         * @param escala escala da imagem.
         * 
         * @return metodo sem retorno (void)
        */
        void Animacao::addAnimacao(const char* caminhoTextura, std::string nomeDaAnimacao, const unsigned int qtdImagem, const float tempoTroca,sf::Vector2f escala, sf::Vector2f origem)
        {
            Imagem* img = new Imagem(caminhoTextura,qtdImagem,tempoTroca,escala, origem);
            mapImagem.insert(std::pair<std::string, Imagem*>(nomeDaAnimacao,img));
        }

        /**
         * @brief Metodo responsavel por atribuir a string img ao atributo estadoAtual.
         * 
         * @param img string a ser armazenada no estado atual
         * 
         * @return metodo sem retorno (void) 
        */
        void Animacao::setImgAtual(std::string img)
        {
            estadoAtual = img;
        }
        
        /**
         * @brief metodo responsavel por atribuir o inteiro quadro ao quadroAtual da imagem
         * 
         * @param quadro inteiro a ser armazenado no quadroAtual da imagem
         * 
         * @return metodo sem retorno (void) 
        */  
        void Animacao::setQuadroAtual(const unsigned int quadro)
        {
            mapImagem[estadoAtual]->setQuadroAtual(quadro);
        }
        
        /**
         * @brief metodo responsavel por atribuir o const float tempo ao tempo de imagem 
         * 
         * @param tempo float a ser armazenado no tempo da imagem
         * 
         * @return metodo sem retorno (void) 
        */
        void Animacao::setTempoTotal(const float tempo)
        {
            mapImagem[estadoAtual]->setTempoTotal(tempo);
        }

        /**
         * @brief metodo que retorna o estado do atributo tempo da imagem
         *  
         * @return retorn o tempo da imagemAtual
        */
        const float Animacao::getTempoTotal()
        {
            return mapImagem[estadoAtual]->getTempoTotal();
        }

         /**
         * @brief metodo que retorna o estado do atributo quadroAtual da imagem
         * 
         * @return retorna o quadroAtual atributo do objeto imagem
        */
        const unsigned int Animacao::getQuadroAtual()
        {
            return mapImagem[estadoAtual]->getQuadroAtual();
        }
        
        /**
         * @brief metodo que retorna o estado do atributo estadoAtual
         * 
         * @return retorna o estadoAtual do animador
        */
        const std::string Animacao::getIMagemAtual()
        {
            return this->estadoAtual;
        }
    }
}
