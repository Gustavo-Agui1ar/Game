

#pragma once

#include "fase.h"

namespace Game::Fase{
    class Forest : public Fase{

    public:

        //contrutores e destrutor
        
        explicit Forest(nlohmann::ordered_json entidades);
        Forest();
        ~Forest() override;
        
        //metodos de criacao de mapa da fase
        
        void criarFundo() override;
        void criarMapa() override;
        
        //metodo que cria uma plataforma
        
        void criarPlataforma(const sf::Vector2f pos) override;
        
        //metodo que recupera o estado salvo da fase
        
        void recuperarJogada(nlohmann::ordered_json entidades);

    };

}

