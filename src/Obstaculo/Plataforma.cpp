
#include "../../includes/Obstaculo/Plataforma.h"


namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            /**
             * contrutora da classe plataforma
             *
             * parametros:
             *
             * pos: atributo nescessario da construtora de Entidade.
             * tam: atributo nescessario da construtora de Entidade.
             *  ID: (ID::plataforma)constante por ser o "Rg" da classe.
             */

            Plataforma::Plataforma(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID):
            Obstaculo(pos,tam,ID)
            {

            }

            /**
             * destrutora da classe.
             */

            Plataforma::~Plataforma(){
            }

            /**
             * metodo que verifica a colis�o de personagens com as plataformas
             *
             * parametros:
             *
             * outraEntidade: entidade a ser a analizada na colisao.
             *
             * ds: distancia entre os centros das duas entidades
             * (centro da entidade com o centro da plataforma)
             * sendo tanto em x quanto em y.
             */

            void Plataforma::colisao(Entidade* outraEntidade, sf::Vector2f ds)
            {
                if(outraEntidade->getID() == IDs::IDs::jogador   ||
                   outraEntidade->getID() == IDs::IDs::esqueleto ||
                   outraEntidade->getID() == IDs::IDs::red_slime)
                {
                    colisaoObstaculo(ds, static_cast<Personagem::Personagem*>(outraEntidade));
                }
            }

            /**
             * metodo que desenha a plataforma na janela.
            */
           
            void Plataforma::atualizar()
            {
                desenhar();
            }

            nlohmann::ordered_json Plataforma::salvar()
            {
                nlohmann::ordered_json json = salvarEntidade();

                return json;
            }
        }
    }
}
