
#include "../../includes/Obstaculo/Plataforma.h"


namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            /**
             * @brief contrutora da classe plataforma
             *
             * @param pos atributo nescessario da construtora de Entidade.
             * @param tam atributo nescessario da construtora de Entidade.
             * @param ID identificacao da plataforma
             */
            Plataforma::Plataforma(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs IDplataforma, IDs::IDs IDtextura):
            Obstaculo(pos,tam,IDplataforma, IDtextura)
            {

            }

            /**
             * @brief contrutora da classe plataforma
             *
             * @param atributos json contendo todas as informacoes do objeto
             * @param IDplataforma identificacao da plataforma
             * @param IDtextura identificacao da textura
             */
            Plataforma::Plataforma(nlohmann::ordered_json atributos,IDs::IDs IDplataforma, IDs::IDs IDtextura):
            Obstaculo(sf::Vector2f(atributos["pos"]["x"].get<float>(), atributos["pos"]["y"].get<float>()),
            sf::Vector2f(atributos["tam"]["x"].get<float>(), atributos["tam"]["y"].get<float>()), 
            IDplataforma, IDtextura)
            {

            }

            /**
             * @brief destrutora da classe.
             */
            Plataforma::~Plataforma(){
            }

            /**
             * @brief metodo que verifica a colisao de personagens com as plataformas
             *
             * @param outraEntidade entidade a ser a analizada na colisao.
             *
             * @param ds distancia entre as duas entidades
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
             * @brief metodo que desenha a plataforma na janela.
            */
            void Plataforma::atualizar()
            {
                desenhar();
            }

            /**
             * @brief metodo que salva o estado atual de um objeto desta classe
             * 
             * @return retorna um json contendo as informacoes do objeto
            */
            nlohmann::ordered_json Plataforma::salvar()
            {
                nlohmann::ordered_json json = salvarEntidade();

                return json;
            }
        }
    }
}
