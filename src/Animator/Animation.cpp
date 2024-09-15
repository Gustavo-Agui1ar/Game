#include "../../includes/Animator/Animation.h"

namespace Game::Animator{

    /**
     * @brief Construct a new Animation object.
     * 
     * @param body Pointer to the rectangle shape that will be animated.
     */
    Animation::Animation(sf::RectangleShape* body): m_clock()
    {
        m_currentState = "";
        m_body = body;
    }

    /**
     * @brief Destroy the Animation object and free allocated resources.
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
     * @brief Update the animation state.
     * 
     * @param direction The direction of the animation.
     * @param currentState The current state of the animation.
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

        img->update(direction, dt);
        m_body->setTextureRect(img->getSize());
        m_body->setTexture(img->getTexture());
        m_body->setOrigin(img->getOrigin());
        m_body->setScale(scale.x, scale.y);
    }

    /**
     * @brief Add a new animation to the animation map.
     * 
     * @param texturePath Path to the texture file.
     * @param animationName Name of the animation.
     * @param qtdImage Number of images in the animation.
     * @param swapTime Time between frames.
     * @param scale Scale of the animation.
     * @param origin Origin of the animation.
     */
    void Animation::addAnimation(const char* texturePath, std::string const & animationName, const unsigned int qtdImage, const float swapTime, sf::Vector2f scale, sf::Vector2f origin)
    {
        auto *img = new Image(texturePath, qtdImage, swapTime, scale, origin);
        m_mapImage.try_emplace(animationName, img);
    }

    /**
     * @brief Set the current image of the animation.
     * 
     * @param img Name of the current image.
     */
    void Animation::setCurrentImg(std::string_view img)
    {
        m_currentState = img;
    }
    
    /**
     * @brief Set the current frame of the animation.
     * 
     * @param frame The frame number to set.
     */
    void Animation::setCurrentFrame(const unsigned int frame)
    {
        m_mapImage[m_currentState]->setCurrentFrame(frame);
    }
    
    /**
     * @brief Set the total time of the animation.
     * 
     * @param time The total time to set.
     */
    void Animation::setTotalTime(const float time)
    {
        m_mapImage[m_currentState]->setTotalTime(time);
    }

    /**
     * @brief Get the total time of the animation.
     * 
     * @return float The total time of the animation.
     */
    float Animation::getTotalTime()
    {
        return m_mapImage[m_currentState]->getTotalTime();
    }

    /**
     * @brief Get the current frame of the animation.
     * 
     * @return unsigned int The current frame of the animation.
     */
    unsigned int Animation::getCurrentFrame()
    {
        return m_mapImage[m_currentState]->getCurrentFrame();
    }
    
    /**
     * @brief Get the current image of the animation.
     * 
     * @return std::string The current image of the animation.
     */
    std::string Animation::getCurrentImg() const
    {
        return m_currentState;
    }

    /**
     * @brief Save the current state of the animation to a JSON object.
     * 
     * @param json The JSON object to save the animation state to.
     * @return nlohmann::ordered_json The JSON object with the saved animation state.
     */
    nlohmann::ordered_json Animation::saveAnimation(nlohmann::ordered_json json) {
        json["currentImg"] = getCurrentImg();
        json["totalTime"] = getTotalTime();
        json["currentFrame"] = getCurrentFrame();
        return json;
    }
}