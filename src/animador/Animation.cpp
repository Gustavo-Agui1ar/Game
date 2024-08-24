
#include "../../includes/animador/Animation.h"

namespace Game::Animator{


    /**
     * construtora da classe animacao
     * 
     * @param body referencia ao corpo a ser aplicado a imagem.
    */
    Animation::Animation(sf::RectangleShape* body): m_clock()
    {
        m_currentState = "";
        m_body = body;
    }

    /**
     * destrutora da classe animacao realiza a destrucao
     * de todas as imagems armazenadas no hashMap.  
    */
    Animation::~Animation()
    {
        auto it = m_mapImage.begin();
        while(it != m_mapImage.end()){
            if(it->second){
                delete(it->second);
                it->second = nullptr;
            }
            it++;
        }
        m_mapImage.clear();
    }

    /**
     * metodo que atualiza a imagem a ser desenhada 
     * 
     * @param direction direcao do personagem(define a direcao da imagem)
     * @param currentState define qual imagem sera atualizada/chamada.
     * 
     *@return metodo sem retorno (void)
    */
    void Animation::update(bool direction, std::string currentState)
    {
        if(m_currentState != currentState && (m_currentState != ""))
            m_mapImage[m_currentState]->reset();

        m_currentState = currentState;
        
        float dt = m_clock.getElapsedTime().asSeconds();
        m_clock.restart();

        Image* img = m_mapImage[m_currentState];
        
        sf::Vector2f scale = img->getEscale();

        img->update(direction,dt);
        m_body->setTextureRect(img->getSize());
        m_body->setTexture(img->getTexture());
        m_body->setOrigin(img->getOrigin());
        m_body->setScale(scale.x,scale.y);

    }

    /**
     * @brief metodo que adiciona uma imagem no hashMap de imagens
     * 
     * @param texturePath onde a textura esta
     *
     * @param animationName nome a ser usado de key no hashMap
     * 
     * @param qtdImage numero de sprites da imagem
     * 
     * @param swapTime tempo total entre cada troca de sprites
     * 
     * @param scale escala da imagem.
     * 
     * @param origin origem da imagem.
     * 
     * @return metodo sem retorno (void)
    */
    void Animation::addAnimation(const char* texturePath, std::string const & animationName, const unsigned int qtdImage, const float swapTime,sf::Vector2f scale, sf::Vector2f origin)
    {
        auto *img = new Image(texturePath, qtdImage, swapTime,scale, origin);
        m_mapImage.try_emplace(animationName, img);
    }

    /**
     * @brief Metodo responsavel por atribuir a string img ao atributo estadoAtual.
     * 
     * @param img string a ser armazenada no estado atual
     * 
     * @return metodo sem retorno (void) 
    */
    void Animation::setCurrentImg(std::string_view img)
    {
        m_currentState = img;
    }
    
    /**
     * @brief metodo responsavel por atribuir o inteiro quadro ao quadroAtual da imagem
     * 
     * @param frame inteiro a ser armazenado no quadroAtual da imagem
     * 
     * @return metodo sem retorno (void) 
    */  
    void Animation::setCurrentFrame(const unsigned int frame)
    {
        m_mapImage[m_currentState]->setCurrentFrame(frame);
    }
    
    /**
     * @brief metodo responsavel por atribuir o const float tempo ao tempo de imagem 
     * 
     * @param time float a ser armazenado no tempo da imagem
     * 
     * @return metodo sem retorno (void) 
    */
    void Animation::setTotalTime(const float time)
    {
        m_mapImage[m_currentState]->setTotalTime(time);
    }

    /**
     * @brief metodo que retorna o estado do atributo tempo da imagem
     *  
     * @return retorn o tempo da imagemAtual
    */
    float Animation::getTotalTime()
    {
        return m_mapImage[m_currentState]->getTotalTime();
    }

        /**
     * @brief metodo que retorna o estado do atributo quadroAtual da imagem
     * 
     * @return retorna o quadroAtual atributo do objeto imagem
    */
    unsigned int Animation::getCurrentFrame()
    {
        return m_mapImage[m_currentState]->getCurrentFrame();
    }
    
    /**
     * @brief metodo que retorna o estado do atributo estadoAtual
     * 
     * @return retorna o estadoAtual do animador
    */
    std::string Animation::getCurrentImg() const
    {
        return m_currentState;
    }

    nlohmann::ordered_json Animation::saveAnimation(nlohmann::ordered_json json) {
        json["imagemAtual"] = getCurrentImg();
        json["tempoTotal"] =  getTotalTime();
        json["quadroAtual"] = getCurrentFrame();
        return json;
    }
}
