
#include "../../includes/BackGround/BackGround.h"

/**
 *   fundos com possiveis chances de serem utilizados.
 * 
 *   #define CAMADA_1_2 "../Game/animations/backgorund/level-2/camada-1.png"
 *   #define CAMADA_2_2 "../Game/animations/backgorund/level-2/camada-2.png"
 *   #define CAMADA_3_2 "../Game/animations/backgorund/level-2/camada-3.png"
 *   #define CAMADA_4_2 "../Game/animations/backgorund/level-2/camada-4.png"
 *   #define CAMADA_5_2 "../Game/animations/backgorund/level-2/camada-5.png"
 *   #define CAMADA_6_2 "../Game/animations/backgorund/level-2/camada-6.png"
 *   #define CAMADA_7_2 "../Game/animations/backgorund/level-2/camada-7.png"
 *   #define CAMADA_8_2 "../Game/animations/backgorund/level-2/camada-8.png"

 *   #define CAMADA_1_3 "../Game/animations/backgorund/level-3/camada-1.png"
 *   #define CAMADA_2_3 "../Game/animations/backgorund/level-3/camada-2.png"
 *   #define CAMADA_3_3 "../Game/animations/backgorund/level-3/camada-3.png"
 *   #define CAMADA_4_3 "../Game/animations/backgorund/level-3/camada-4.png"
 *   #define CAMADA_5_3 "../Game/animations/backgorund/level-3/camada-5.png"

 *   #define CAMADA_1_4 "../Game/animations/backgorund/level-4/camada-1.png"
 *   #define CAMADA_2_4 "../Game/animations/backgorund/level-4/camada-2.png"
 *   #define CAMADA_3_4 "../Game/animations/backgorund/level-4/camada-3.png"
 *   #define CAMADA_4_4 "../Game/animations/backgorund/level-4/camada-4.png"
 *   #define CAMADA_5_4 "../Game/animations/backgorund/level-4/camada-5.png"
*/

namespace Game::BackGround{

    BackGround::BackGround(IDs::IDs ID):
    Ente(ID),m_posCamera(m_graphic->getCamera().getCenter())
    {

    }

    BackGround::~BackGround()
    {
        for(auto* layer : m_layers)
        {
            delete layer;
            layer = nullptr;
        }
        m_layers.clear();
    }

    void BackGround::execute()
    {
        sf::Vector2f currentPosCamera = m_graphic->getCamera().getCenter();
        sf::Vector2f ds =  currentPosCamera - m_posCamera;
        m_posCamera = currentPosCamera;

        if(ds.x != 0.0f)
        {
            ds.x *= 0.5;
            for(auto* layer : m_layers){
                layer->update(ds,currentPosCamera);
            }
        }
        draw();
    }

    void BackGround::draw()
    {
        for(auto* layer : m_layers)
            layer->drawLayer(m_graphic->getWindow());
    }

    void BackGround::addLayer(const char* caminhoTextura, const float vel)
    {
        auto* layer = new Layer((sf::Vector2f)m_graphic->getWindow()->getSize(),m_graphic->loadTexture(caminhoTextura),vel);
        if(layer == nullptr)
            std::cout<<"BackGround::BackGround: error to add a new layer"<<std::endl;
        m_layers.push_back(layer);
    }
}
