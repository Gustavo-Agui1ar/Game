
#pragma once

#include "../Entity/Ente.h"
#include "Layer.h"

namespace Game::BackGround{
    class BackGround : public Ente{

    private:

        sf::Vector2f m_posCamera;

        std::vector<Layer*> m_layers;

    public:

        explicit BackGround(IDs::IDs ID);
        ~BackGround() override;

        void draw() override;

        void addLayer(const char* pathTexture, const float speed);
        
        void execute();
    };
}
