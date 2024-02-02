

#pragma once

#include "fase.h"
#include "../includes/entidade/npcs/npc.h"

namespace Game{

    namespace Fase{

        class Forest : public Fase{

        public:

            //contrutores e destrutor
          
            Forest(nlohmann::ordered_json entidades);
            Forest();
            ~Forest();
           
            //metodos de criacao de mapa da fase
          
            void criarFundo();
            void criarMapa();
           
            //metodo que cria uma plataforma
          
            void criarPlataforma(const sf::Vector2f pos);

            void criarNpc(sf::Vector2i pos);
            
            //metodo que recupera o estado salvo da fase
           
            void recuperarJogada(nlohmann::ordered_json entidades);

        };
    }

}

