
#pragma once

#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../npcs/npc.h"
#include "../includes/entidade/entidade.h"
#include "../includes/animador/Animation.h"

#define CAMINHO_TEXTURA_PLATAFORMA_CAVERNA "..\\Game\\animations\\platform\\Platform_cave.png"
#define CAMINHO_TEXTURA_PLATAFORMA_FOREST "..\\Game\\animations\\platform\\Platform-forest.png"
#define CAMINHO_TEXTURA_PLATAFORMA_VILA "..\\Game\\animations\\platform\\Platform-vila.png"


namespace Game::Entidade::Obstaculo{
    class Obstaculo: public Entidade{

    protected:

        //atributo a ser aplicado no corpo do obstaculo
        
        sf::Texture textura;

    public:

        //construtor e destrutor

        Obstaculo(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID, IDs::IDs IDtextura);
        ~Obstaculo() override;

        //metodo que analisa a colisao com outros objetos
        
        void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override = 0;
        void colisaoObstaculo(sf::Vector2f ds, Character::Character* pPersonagem);
        
        //metodo que atualiza o estado de um objeto desta classe 
        
        void update() override = 0;

        //metodo que salva o estado  de um objeto desta classe

        nlohmann::ordered_json salvar() override = 0;
    };
}
