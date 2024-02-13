
#pragma once

#include "../jogador/jogador.h"
#include "../inimigo/inimigo.h"
#include "../npcs/npc.h"
#include "../includes/entidade/entidade.h"
#include "../includes/animador/animacao.h"

#define CAMINHO_TEXTURA_PLATAFORMA_CAVERNA "..\\Game\\animations\\platform\\Platform_cave.png"
#define CAMINHO_TEXTURA_PLATAFORMA_FOREST "..\\Game\\animations\\platform\\Platform-forest.png"


namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            class Obstaculo: public Entidade{

            protected:

                //atributo a ser aplicado no corpo do obstaculo
                
                sf::Texture textura;

            public:

                //construtor e destrutor

                Obstaculo(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID, IDs::IDs IDtextura);
                ~Obstaculo();

                //metodo que analisa a colisao com outros objetos
                
                virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) = 0;
                void colisaoObstaculo(sf::Vector2f ds, Personagem::Personagem* pPersonagem);
                
                //metodo que atualiza o estado de um objeto desta classe 
                
                virtual void atualizar() = 0;

                //metodo que salva o estado  de um objeto desta classe

                virtual nlohmann::ordered_json salvar() = 0;
            };
        }
    }
}
