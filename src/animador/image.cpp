
#include "../../includes/animador/image.h"

namespace Game::Animator{

    

    /**
     * @brief costrutora da classe imagem
     * 
     * @param caminhoTextura: onde esta a textura
     * 
     * @param totalDeQuadrosImagem:quantidade de sprites da imagem.
     * 
     * @param tempoDeTroca: tempo total entre cada troca de sprite.
     * 
     * @param escala: escala da imagem.
     * 
    */
    Image::Image(const char* pathTexture, const unsigned int totalFrameImg, const float swapTime, sf::Vector2f escale, sf::Vector2f origin ):
    m_pGrafic(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),  m_escale(escale), m_origin(origin),  m_texture(m_pGrafic->carregarTextura(pathTexture)),
    m_totalFrameImg(totalFrameImg),m_currentFrame(0),m_swapTime(swapTime),m_totalTime(0)
    {
        m_size.width = static_cast<int>(m_texture.getSize().x/ (float) totalFrameImg);
        m_size.height = m_texture.getSize().y;
    }

    /**
     * @brief destrutora da classe imagem.
    */
    Image::~Image() = default;

    /**
     * @brief metodo que atualiza a imagem
     * 
     * @param direcao atributo que mostra a direcao do jogador.
     *
     * @param dt tempo decorrido com esta imagem.
     * 
     * @return metodo sem retorno (void)
    */
    void Image::update(bool direction, const float dt)
    {
        m_totalTime += dt;
        if(m_totalTime >= m_swapTime)
        {
            m_totalTime -= m_swapTime;
            m_currentFrame = (m_currentFrame + 1)%m_totalFrameImg;
        }

        if(direction)
        {
            m_size.left = (m_currentFrame + 1) * abs(m_size.width);
            m_size.width = -abs(m_size.width);
        }
        else
        {
            m_size.left = m_currentFrame * abs(m_size.width);
            m_size.width = abs(m_size.width);
        }
    }

    /**
     *  @brief metodo que reinicia aq imagem 
     *  zerando o tempo e a imagem atual.
    */
    void Image::reset()
    {
        m_totalTime = 0.0f;
        m_currentFrame = 0;
    }

    /**
     * @brief metodo que retorna o tamnha da imagem.
    */
    const sf::IntRect  Image::getSize() const
    {
        return m_size;
    }

    /**
     * @brief metodo que retorna a textura da imagem.
     * 
     * @return retorna a textura da imagem
    */
    const sf::Texture* Image::getTexture() const
    {
        return &m_texture;
    }

    /**
     * @brief metodo que retorna a escala da imagem. 
     *
     * @return retorna a escala da imagem
    */
    const sf::Vector2f Image::getEscale() const
    {
        return m_escale;
    }
    
    /**
     * @brief metodo que modifica o atributo quadroAtual
     * 
     * @param imgAtual valor a ser atribuido em estadoAtual
     * 
    */
    void Image::setCurrentFrame(const unsigned int imgAtual)
    {
        m_currentFrame = imgAtual;
    }

    /**
     * @brief metodo que modifica o atributo tempoTotal
     * 
     * @param tempo valor a ser atribuido em tempototal
     * 
    */
    void Image::setTotalTime(const float time)
    {
        m_totalTime = time;
    }

    /**
     * @brief metodo que retorna o atributo tempoTotal
     * 
     * @return retorna o valor em tempototal
     * 
    */
    const float Image::getTotalTime()
    {
        return m_totalTime;
    }
    
    /**
     * @brief metodo que retorna o atributo quadroAtual
     * 
     * @return retorna o valor em quadroAtual
     * 
    */
    const unsigned int Image::getCurrentFrame()
    {
        return m_currentFrame;    
    }

    /**
     * @brief metodo que retorna o atributo origem
     * 
     * @return retorna o valor em origem
     * 
    */
    const sf::Vector2f Image::getOrigin(){
        return m_origin;
    }
}
