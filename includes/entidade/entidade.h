
#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.h"

namespace Game{

    namespace Entidade{

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
            Entidade(const sf::Vector2f tam,const IDs::IDs, const sf::Vector2f pos = {0,0});
            virtual ~Entidade();

            //metodos referentes ao corpo
            sf::RectangleShape getCorpo(){return corpo;}
            void setTam(const sf::Vector2f tam);
            sf::Vector2f getTam();

            nlohmann::ordered_json salvarEntidade();
            virtual nlohmann::ordered_json salvar() = 0;

            //metodos referentes a posicao
            void setPos(sf::Vector2f pos);
            virtual void atualizar() = 0;
            sf::Vector2f getPos();

            //metodos referentes a colisao
            virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) = 0;
            
            //metodos de remocao
            const bool getRemover();
            void remover();

            //metodos referentes a visulizacao 
            virtual void desenhar();
        };
    }
}


