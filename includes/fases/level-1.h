
#pragma once

#include "fase.h"

namespace Game::Fase{
    class Caverna : public Fase{

    public:

        //construtor e destrutor
        explicit Caverna(nlohmann::ordered_json entidades);
        Caverna();
        ~Caverna() override;
        
        //metodos de criacao de mapas da fase
        void criarFundo() override;
        void criarMapa() override;

        //metoido que cria uma plataforma
        void criarPlataforma(const sf::Vector2f pos) override;
        
        void recuperarJogada(nlohmann::ordered_json entidades);
    };

}
