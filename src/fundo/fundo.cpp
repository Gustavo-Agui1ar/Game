
#include "../../includes/fundo/fundo.h"

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

namespace Game{

    namespace Fundo{

        /**
         * @brief construtora da classe fundo
         * 
         * @param ID identificacao da fase(nescessario para a construtora de Ente)
        */
        Fundo::Fundo(IDs::IDs ID):
        Ente(ID),posCameraAnterior(m_graphic->getCamera().getCenter())
        {

        }

        /**
         *  @brief destrutora da classe Fundo
         *  
         * realiza a destrucao das camadas utilizadas no fundo
        */
        Fundo::~Fundo()
        {
            for(int i = 0 ; i < camadas.size() ; i++)
            {
                Camada* camada = camadas.at(i);

                if(camada)
                {
                    delete(camada);
                    camada = nullptr;
                }
            }
            camadas.clear();
        }

        /**
         * @brief metodo  que aplica o fundo na janela
         * o fundo atualizando todas as camadas
         * existentes do fundo
        */
        void Fundo::executar()
        {
            sf::Vector2f posCamera = m_graphic->getCamera().getCenter();
            sf::Vector2f ds =  posCamera - posCameraAnterior;
            posCameraAnterior = posCamera;

            if(ds.x != 0.0f)
            {
                ds.x *= 0.5;
                for(int i = 0 ; i < camadas.size() ; i++){
                    camadas.at(i)->atualizar(ds,posCamera);
                }
            }
            draw();
        }

        /**
         * @brief metodo que percorre a array de camadas
         * desenhando as camadas na janela. 
        */
        void Fundo::draw()
        {
            for(int i = 0 ; i < camadas.size() ; i++){
                Camada* camada = camadas.at(i);
                camada->desenharCamada(m_graphic->getWindow());
            }
        }

        /**
         * @brief metodo que adiciona uma camada a array de camadas.
         * 
         * @param caminhoTextura char que contem o caminho ate a textura
         * @param vel velociadade com que a camada se movimentara
        */
        void Fundo::addCamada(const char* caminhoTextura, const float vel)
        {
            Camada* camada = new Camada((sf::Vector2f)m_graphic->getWindow()->getSize(),m_graphic->carregarTextura(caminhoTextura),vel);
            if(camada == nullptr)
                std::cout<<"Fundo::Fundo: erro ao adicionar camada de fundo";
            camadas.push_back(camada);
        }
    }

}
