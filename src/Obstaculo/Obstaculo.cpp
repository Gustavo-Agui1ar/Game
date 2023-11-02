
#include "../../includes/Obstaculo/Obstaculo.h"

namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            /**
             * metodo contrutor da classe Obstaculo
             *
             * parametro:
             *
             * pos: atributo nescessario para a contrutora de Entidade;
             * tam: atributo nescessario para a contrutora de Entidade;
             * ID:  recebido das filhas de OBstaculo(plataforma,caixa e etc).
             *
             */

            Obstaculo::Obstaculo(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID):
            Entidade(tam, ID, pos)
            {
                Gerenciador::GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                
                if(ID == IDs::IDs::caverna)
                   textura = pGrafico->carregarTextura(CAMINHO_TEXTURA_PLATAFORMA_CAVERNA);
                else if(ID == IDs::IDs::forest)
                   textura = pGrafico->carregarTextura(CAMINHO_TEXTURA_PLATAFORMA_FOREST);

                corpo.setTexture(&textura);
            
            }
            /**
             * destrutora da classe.
             */

            Obstaculo::~Obstaculo()
            {
                
            }

            /**
             * metodo que ajusta a posicao entre personagem e plataforma
             * levando em conta sua posicao em relacao a plataforma.
             *
             * ds: distancia entre os centros de  OBstaculo e personagem.
             * pPresonagem: personagem a ser ajustado a posicao.
             */

            void Obstaculo::colisaoObstaculo(sf::Vector2f ds, Personagem::Personagem* pPersonagem)
            {
                sf::Vector2f posOutro = pPersonagem->getPos();
                sf::Vector2f velFinal = pPersonagem->getVelocidade();
                if(ds.x < 0.0f && ds.y < 0.0f){ //houve colisao
                    if(ds.x > ds.y)
                    {
                        if(posOutro.x < pos.x) //colis�o em x
                        {
                            posOutro.x += ds.x;
                        }
                        else
                        {
                            posOutro.x -= ds.x;
                        }
                        velFinal.x = 0.0f;
                    }
                    else
                    {
                        if(posOutro.y < pos.y) //colis�o em y
                        {
                            posOutro.y += ds.y;

                            if(pPersonagem->getID() == IDs::IDs::jogador)
                            {
                                Personagem::Jogador::Jogador* pJogador = static_cast<Personagem::Jogador::Jogador*>(pPersonagem);
                                pJogador->podePular();
                            }
                        }
                        else
                        {
                            posOutro.y -= ds.y;
                        }
                        velFinal.y = 0.0f;
                    }
                }
                pPersonagem->setPos(posOutro);
                pPersonagem->setVelMax(velFinal);
            }
        }

    }
}
