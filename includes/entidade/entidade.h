
#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.h"

namespace Game::Entidade{


    class Entidade : public Ente{

    protected:

        //atributos do corpo
    
        sf::RectangleShape corpo;
        sf::Vector2f pos;
        sf::Vector2f tam;

        //atributos de remocao
    
        bool podeRemover;

    public:

        //construtores/destrutor
        
        Entidade(const sf::Vector2f tam,const IDs::IDs ID, const sf::Vector2f pos = {0,0});
        ~Entidade() override;

        //metodos referentes ao corpo
        
        sf::RectangleShape getCorpo(){return corpo;}
        
        //metodo de modificacao do atributo corpo
        
        void setTam(const sf::Vector2f tam);
        
        //metodo de acesso ao atributo corpo
        
        sf::Vector2f getTam();

        //metodos responsaveis por salvar o estado atual de um objeto desta classe
    
        nlohmann::ordered_json salvarEntidade();
        virtual nlohmann::ordered_json salvar() = 0;

        //metodos modificacao do atributo pos
        
        void setPos(sf::Vector2f pos);

        //metodos de acesso ao atributo pos
    
        sf::Vector2f getPos();

        //metodos referentes a colisao
        
        virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) = 0;
        
        //metodos de remocao
        
        const bool getRemover();
        void remover();

        //metodos referentes a visulizacao 
        
        virtual void update() = 0;
        void draw() override;
    };
}


