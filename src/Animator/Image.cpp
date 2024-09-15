#include "../../includes/Animator/Image.h"

namespace Game::Animator{

    /**
     * @brief Construct a new Image object.
     * 
     * @param pathTexture Path to the texture file.
     * @param totalFrameImg Total number of frames in the image.
     * @param swapTime Time between frame swaps.
     * @param escale Scale of the image.
     * @param origin Origin of the image.
     */
    Image::Image(const char* pathTexture, const unsigned int totalFrameImg, const float swapTime, sf::Vector2f escale, sf::Vector2f origin):
    m_pGrafic(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()), m_escale(escale), m_origin(origin), m_texture(m_pGrafic->carregarTextura(pathTexture)),
    m_totalFrameImg(totalFrameImg), m_currentFrame(0), m_swapTime(swapTime), m_totalTime(0)
    {
        m_size.width = static_cast<int>(m_texture.getSize().x / (float) totalFrameImg);
        m_size.height = m_texture.getSize().y;
    }

    /**
     * @brief Destroy the Image object.
     */
    Image::~Image() = default;

    /**
     * @brief Update the image frame based on the elapsed time.
     * 
     * @param direction The direction of the animation.
     * @param dt The elapsed time since the last update.
     */
    void Image::update(bool direction, const float dt)
    {
        m_totalTime += dt;
        if(m_totalTime >= m_swapTime)
        {
            m_totalTime -= m_swapTime;
            m_currentFrame = (m_currentFrame + 1) % m_totalFrameImg;
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
     * @brief Reset the image animation to the first frame.
     */
    void Image::reset()
    {
        m_totalTime = 0.0f;
        m_currentFrame = 0;
    }

    /**
     * @brief Get the size of the current frame.
     * 
     * @return const sf::IntRect The size of the current frame.
     */
    const sf::IntRect Image::getSize() const
    {
        return m_size;
    }

    /**
     * @brief Get the texture of the image.
     * 
     * @return const sf::Texture* Pointer to the texture.
     */
    const sf::Texture* Image::getTexture() const
    {
        return &m_texture;
    }

    /**
     * @brief Get the scale of the image.
     * 
     * @return const sf::Vector2f The scale of the image.
     */
    const sf::Vector2f Image::getEscale() const
    {
        return m_escale;
    }

    /**
     * @brief Set the current frame of the image.
     * 
     * @param imgAtual The frame number to set.
     */
    void Image::setCurrentFrame(const unsigned int imgAtual)
    {
        m_currentFrame = imgAtual;
    }

    /**
     * @brief Set the total time of the animation.
     * 
     * @param time The total time to set.
     */
    void Image::setTotalTime(const float time)
    {
        m_totalTime = time;
    }

    /**
     * @brief Get the total time of the animation.
     * 
     * @return const float The total time of the animation.
     */
    const float Image::getTotalTime()
    {
        return m_totalTime;
    }
    
    /**
     * @brief Get the current frame of the animation.
     * 
     * @return const unsigned int The current frame of the animation.
     */
    const unsigned int Image::getCurrentFrame()
    {
        return m_currentFrame;    
    }

    /**
     * @brief Get the origin of the image.
     * 
     * @return const sf::Vector2f The origin of the image.
     */
    const sf::Vector2f Image::getOrigin()
    {
        return m_origin;
    }
}