
#pragma once

#include "image.h"
#include "json.hpp"
#include <map>

namespace Game::Animator{


    class Animation{

    private:

        //atributo com referencia ao corpo para evitar chamadas de metodos.
        
        sf::RectangleShape *m_body;
        
        //atributos relaciondos a imagem
        
        std::map<std::string, Image*> m_mapImage;
        std::string m_currentState;
        
        //atributos de tempo
        
        sf::Clock m_clock;

    public:
    
        //construtor e destrutor
        
        explicit Animation(sf::RectangleShape* body);
        ~Animation();

        //metodo de atualizacao de animacao

        void update(bool direction, std::string currentState);

        //metodo de adicionar a animacao

        void addAnimation(const char* texturePath, std::string const & animationName, const unsigned int qtdImage, const float swapTime, sf::Vector2f scale, sf::Vector2f origin);
        
        //seters referentes aos atributos da classe
        
        void setTotalTime(const float time);
        void setCurrentImg(std::string_view img);
        void setCurrentFrame(const unsigned int frame);

        //geters referentes aos atributos da classe
        
        float getTotalTime();
        unsigned int getCurrentFrame();
        std::string getCurrentImg() const;
        nlohmann::ordered_json saveAnimation(nlohmann::ordered_json json);
    };
}
