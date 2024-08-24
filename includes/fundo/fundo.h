
#pragma once

#include "../entidade/Ente.h"
#include "camada.h"

namespace Game::Fundo{
    class Fundo : public Ente{

    private:

        //atributo de posicao da camera antetrior
        
        sf::Vector2f posCameraAnterior;

        //atributo que armazena todas as camadas que geram o fundo
        
        std::vector<Camada*> camadas;

    public:

        //construtor e destrutor
        
        explicit Fundo(IDs::IDs ID);
        ~Fundo() override;

        //metodo de vizualizacao
        
        void draw() override;

        //metodo de adicao de camada
        
        void addCamada(const char* caminhoTextura, const float vel);
        
        //metodo de satualizacao
        
        void executar();
    };
}
