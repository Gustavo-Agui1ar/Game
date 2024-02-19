
#include "../includes/entidade/Obstaculo/casa.h"

namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            Casa::Casa(const sf::Vector2f tam, const IDs::IDs ID, const sf::Vector2f pos):
            Entidade(tam, ID, pos)
            {

            }

            Casa::~Casa()
            {

            }

            void Casa::atualizar()
            {
                pGrafico->desenhaElemento(corpo);
            }

            void Casa::setTextura(const char* caminhoTextura)
            {
                textura = pGrafico->carregarTextura(caminhoTextura);

                corpo.setTexture(&textura);
            }

            nlohmann::ordered_json Casa::salvar()
            {
                nlohmann::ordered_json json = salvarEntidade();
                return json;
            }
            
            void Casa::colisao(Entidade* outraEntidade, sf::Vector2f ds)
            {

            }
        }
    }
}