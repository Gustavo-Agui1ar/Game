
#include "../../includes/gerenciador/gerenciadorDeColisao.h"


namespace Game{

    namespace Gerenciador{

        /**
         * @brief construtor da classe gerenciadorDeColisao
         * 
         * @param personagem lista de personagem a serem analizados
         * @param obstaculos lista de obstaculos a serem analizados
        */
        GerenciadorDeColisao::GerenciadorDeColisao(Lista::ListaEntidade* personagem, Lista::ListaEntidade* obstaculo):
        listaPersonagem(personagem), listaObstaculo(obstaculo)
        {

        }

        /**
         * @brief destrutora da  classe  gerenciadorDeColisao 
         * destroi as listas de personagem e obstaculo 
        */
        GerenciadorDeColisao::~GerenciadorDeColisao()
        {
             delete(listaObstaculo);
             delete(listaPersonagem);

             listaObstaculo = nullptr;
             listaPersonagem = nullptr;
        }

        /**
         * @brief metodo responsavel   por  calcular a  colisao entre duas entidades
         * 
         * @param ent1 entidades a ser analisada a colisao
         * @param ent2 entidades a ser analizada a colisao
         * 
         * @return retorna um vetor de 2 posicoes com a distancia entre os centros em x e em y se for negativo houve colisao
        */
        const sf::Vector2f GerenciadorDeColisao::calculaColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2)
        {

            sf::Vector2f pos1 = ent1->getPos();
            sf::Vector2f pos2 = ent2->getPos();

            sf::Vector2f tam1 = ent1->getTam();
            sf::Vector2f tam2 = ent2->getTam();

            sf::Vector2f distanciaEntreCentros(
                fabs((pos1.x + tam1.x/2.0f) - (pos2.x + tam2.x/2.0f)),
                fabs((pos1.y + tam1.y/2.0f) - (pos2.y + tam2.y/2.0f))
            );

            sf::Vector2f somaMetadeRetangulo(tam1.x/2.0f + tam2.x/2.0f, tam1.y/2.0f + tam2.y/2.0f);
            sf::Vector2f distanciaEntreCentrosDasEntidades(distanciaEntreCentros.x - somaMetadeRetangulo.x, distanciaEntreCentros.y - somaMetadeRetangulo.y);

            return distanciaEntreCentrosDasEntidades;
        }

        /**
         *  @brief metodo responsavel por verificar se houve colisao entre
         *  personagens e entre  personagens e obstaculos se houver
         *  entao chama-se o metodo do objeto de colisao que trata 
         *  a cosicao os dois objetos
        */
        void GerenciadorDeColisao::executar()
        {

            //personagem e personagem.
            for(int i = 0 ; i < listaPersonagem->getTam() - 1 ; i++)
            {
                Entidade::Entidade* ent1 = listaPersonagem->operator[](i);

                for(int j = i + 1 ; j < listaPersonagem->getTam() ; j++)
                {
                    Entidade::Entidade* ent2 = listaPersonagem->operator[](j);
                    sf::Vector2f ds = calculaColisao(ent1, ent2);

                    if(ds.x < 0.0f && ds.y < 0.0f)
                    {
                        ent1->colisao(ent2,ds);
                    }
                }
            }

            //personagem e obstaculo
             for(int i = 0 ; i < listaPersonagem->getTam(); i++)
            {
                Entidade::Entidade* ent1 = listaPersonagem->operator[](i);

                for(int j = 0 ; j < listaObstaculo->getTam() ; j++)
                {
                    Entidade::Entidade* ent2 = listaObstaculo->operator[](j);

                    sf::Vector2f ds = calculaColisao(ent1, ent2);

                    if(ds.x < 0.0f && ds.y < 0.0f)
                    {
                        ent2->colisao(ent1,ds);
                    }
                }
            }
        }
    }
}
