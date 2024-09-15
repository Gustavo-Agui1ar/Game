
#pragma once

#include <SFML/Graphics.hpp>
#include "../gerenciador/gerenciadorGrafico.h"

namespace Game::Animator{


    class Image{

    private:

        Gerenciador::GerenciadorGrafico * m_pGrafic;
        
        const sf::Vector2f m_escale;
        const sf::Vector2f m_origin;
        sf::Texture m_texture;
        sf::IntRect m_size;

        const unsigned int m_totalFrameImg;
        unsigned int m_currentFrame;
        const float m_swapTime;
        float m_totalTime;

    public:

        Image(const char* pathTexture, const unsigned int totalFrameImg, const float swapTime, sf::Vector2f escale, sf::Vector2f origin);
        ~Image();

        void update(bool direction,const float dt);
        
        void setCurrentFrame(const unsigned int currentImg);
        void setTotalTime(const float time);
        void reset();
        
        const sf::IntRect  getSize() const;
        const sf::Texture* getTexture() const;
        const sf::Vector2f getEscale() const;
        const unsigned int getCurrentFrame();
        const sf::Vector2f getOrigin();
        const float getTotalTime();
    };

}
