
#include "../includes/entidade/Obstaculo/Obstaculo.h"

namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            /**
             * @brief metodo contrutor da classe Obstaculo
             *
             * @param pos atributo nescessario para a contrutora de Entidade;
             * @param tam atributo nescessario para a contrutora de Entidade;
             * @param ID  recebido das filhas de OBstaculo(plataforma,caixa e etc).
             * @param IDtextura indica a textura a ser carregada no obstaculo
             */
            Obstaculo::Obstaculo(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID, IDs::IDs IDtextura):
            Entidade(tam, ID, pos)
            {
                Gerenciador::GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                
                switch(IDtextura)
                {
                    case(IDs::IDs::caverna):
                         textura = pGrafico->carregarTextura(CAMINHO_TEXTURA_PLATAFORMA_CAVERNA);
                         corpo.setTexture(&textura);
                         corpo.setFillColor(sf::Color{100,100,100});
                         break;
                    case(IDs::IDs::floresta_do_amanhecer):
                        textura = pGrafico->carregarTextura(CAMINHO_TEXTURA_PLATAFORMA_FOREST);
                        corpo.setTexture(&textura);
                        break;
                    case(IDs::IDs::vila):
                        textura = pGrafico->carregarTextura(CAMINHO_TEXTURA_PLATAFORMA_VILA);
                        corpo.setTexture(&textura);
                        corpo.setFillColor(sf::Color{170,170,170});
                        break;
                    case(IDs::IDs::plataforma_invisivel):
                        corpo.setFillColor(sf::Color::Transparent);
                    default:
                        break;
                }

            
            }
            /**
             * @brief destrutora da classe.
             */
            Obstaculo::~Obstaculo()
            {
                
            }

            /**
             * @brief metodo que ajusta a posicao entre personagem e plataforma
             * levando em conta sua posicao em relacao a plataforma.
             *
             * @param ds distancia entre os centros de  OBstaculo e personagem.
             * @param pPresonagem personagem a ser ajustado a posicao.
             */
            void Obstaculo::colisaoObstaculo(sf::Vector2f ds, Character::Character* pCharacter)
            {
                sf::Vector2f posOutro = pCharacter->getPos();
                sf::Vector2f velFinal = pCharacter->getSpeed();
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

                            if(pCharacter->getID() == IDs::IDs::jogador)
                            {
                                auto* pJogador = static_cast<Character::Player::Player*>(pCharacter);
                                pJogador->canJump();
                            }
                        }
                        else
                        {
                            posOutro.y -= ds.y;
                        }
                        velFinal.y = 0.0f;
                    }
                }
                pCharacter->setPos(posOutro);
                pCharacter->setMaxSpeed(velFinal);
            }
        }

    }
}
