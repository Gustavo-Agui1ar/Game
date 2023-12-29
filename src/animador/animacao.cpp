
#include "../../includes/animador/animacao.h"

namespace Game{

    namespace animador{

        /**
         * construtora da classe animacao
         * 
         * parametros:
         * 
         * corpo: referencia ao corpo a ser aplicado a imagem.
        */

        Animacao::Animacao(sf::RectangleShape* corpo):relogio()
        {
            estadoAtual = "";
            this->corpo = corpo;
        }

        /**
         * destrutora da classe animacao
         * realiza  a destrucao de todas 
         * as imagems armazenadas no hashMap.  
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
         * parametros:
         * 
         * direcao: direcao do personagem(define a direcao da imagem)
         * estadoatual: define qual imagem sera atualiza/chamada.
         * 
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
            corpo->setScale(escala.x,escala.y);

        }

        /**
         * metodo que adiciona uma imagem no hashMap de imagens
         * 
         * parametros:
         * 
         * caminhoTextura: onde a textura esta
         * nomeDaAnimacao: nome a ser usado de key no hashMap
         * qtdImagem: numero de sprites da imagem
         * tempoDeTroca: tempo total entre cada troca de sprites
         * escala: escala da imagem.
         * 
        */

        void Animacao::addAnimacao(const char* caminhoTextura, std::string nomeDaAnimacao, const unsigned int qtdImagem, const float tempoTroca,sf::Vector2f escala)
        {
            Imagem* img = new Imagem(caminhoTextura,qtdImagem,tempoTroca,escala);
            mapImagem.insert(std::pair<std::string, Imagem*>(nomeDaAnimacao,img));
        }

        void Animacao::setImgAtual(std::string img)
        {
            estadoAtual = img;
        }
            
        void Animacao::setQuadroAtual(const unsigned int quadro)
        {
            mapImagem[estadoAtual]->setQuadroAtual(quadro);
        }

        void Animacao::setTempoTotal(const float tempo)
        {
            mapImagem[estadoAtual]->setTempoTotal(tempo);
        }

        const float Animacao::getTempoTotal()
        {
            return mapImagem[estadoAtual]->getTempoTotal();
        }

        const unsigned int Animacao::getQuadroAtual()
        {
            return mapImagem[estadoAtual]->getQuadroAtual();
        }
        
        const std::string Animacao::getIMagemAtual()
        {
            return this->estadoAtual;
        }
    }
}
