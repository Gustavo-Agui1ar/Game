
#include "../includes/arma/arma.h"
#include "../includes/inimigo/inimigo.h"

namespace Game{

    namespace Entidade{

        namespace Item{


                /**
                 * construtora da classe arma
                 * 
                 * parametros:
                 * 
                 * ID: variavel de indentificacao da classe arma alemde nescessario para costrutora de ente
                 * 
                */

                Arma::Arma(IDs::IDs ID):
                Entidade(sf::Vector2f(-1000.0f, -1000.0f),ID)
                {
                    dano = 0.0f;
                }

                /**
                 * destrutora da classe arma
                */

                Arma::~Arma()
                {

                }

                /**
                 * metodo que define o valor do 
                 * atributo dano da classe arma
                */

                void Arma::setDano(const float dano)
                {
                    this->dano = dano;
                }

                /**
                 * metodo que retorna o atributo dano de arma.
                */

                const float Arma::getDano()
                {
                    return dano;
                }

                /**
                 * metodo que trata da colisao da arma
                 * com outtras entidades dependendo de 
                 * seu id.
                 * 
                 * parametros:
                 * 
                 * outraEntidade: entidade a verificar colisao
                 * ds: distancia entre os centros de arma e outra entidade. 
                */

                void Arma::colisao(Entidade* outraEntidade, sf::Vector2f ds)
                {
                    if(ID == IDs::IDs::armaDoJogador)
                    {
                        if(outraEntidade->getID() == IDs::IDs::red_slime ||
                           outraEntidade->getID() == IDs::IDs::esqueleto)
                        {
                            Personagem::Inimigo::Inimigo* inimigo = static_cast<Personagem::Inimigo::Inimigo*>(outraEntidade);
                            if(!inimigo->getMorrer())
                            {
                                inimigo->tomarDano(dano);
                            }
                        }
                    }
                }

                /**
                 * metod que serve para definir  a 
                 * nao  vizualizacao  da arma  por 
                 * se tratar apenas de uma  hitbox
                */

                void Arma::desenhar()
                {

                }

                /**
                 * metodo de atualizacao definido para respeitar o virtual de entidade 
                 * porem  executado  de jeitos   diferentes   por  inimigo  e  jogador
                */

                void Arma::atualizar()
                {

                }

        }
    }
}
