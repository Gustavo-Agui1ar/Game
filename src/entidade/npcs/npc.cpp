
#include "../includes/entidade/npcs/npc.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game{

    namespace Entidade{

        namespace Character{ 
            
            namespace Npc{

                Gerenciador::GerenciadorDeEstado* Npc::pEstado = Gerenciador::GerenciadorDeEstado::getGerenciadorDeEstado();
                
                Npc::Npc(sf::Vector2f pos, const IDs::IDs IDpersonagem , const char* caminhoDialogo):
                Character(pos,sf::Vector2f(TAM_NPC_GENERICO_X, TAM_NPC_GENERICO_Y), 0.0f, IDs::IDs::npc, 0.0f, 0.0f, 0.0f), caminhoDialogo(caminhoDialogo),IDpersonagem(IDpersonagem)
                {
                    inicializarAnimacao();
                    switch(IDpersonagem)
                    {
                        case(IDs::IDs::barman):
                            this->caminhoDialogo = "../Game/falas/barman.txt";
                        break;
                        
                        case(IDs::IDs::mulher):
                            this->caminhoDialogo = "../Game/falas/mulher.txt";
                        break;
                        
                        case(IDs::IDs::jovem):
                            this->caminhoDialogo = "../Game/falas/jovem.txt";
                         break;
                        
                        case(IDs::IDs::velho):
                            this->caminhoDialogo = "../Game/falas/velho.txt";
                         break;
                        
                        default:   
                            break;
                    }

                }
                Npc::~Npc() = default;
            
                void Npc::inicializarAnimacao()
                {
                    const auto origem = sf::Vector2f(tam.x/2.5,tam.y/2.2);

                    switch(IDpersonagem)
                    {
                        case(IDs::IDs::barman):
                            m_animation.addAnimation("../Game/animations/Npc/bearded-idle.png","PARADO",5,0.6,sf::Vector2f{6,2},origem);
                        break;
                        
                        case(IDs::IDs::mulher):
                            m_animation.addAnimation("../Game/animations/Npc/woman-idle.png","PARADO",7,0.5,sf::Vector2f{5,2},origem);
                        break;
                        
                        case(IDs::IDs::jovem):
                            m_animation.addAnimation("../Game/animations/Npc/hat-man-idle.png","PARADO",4,0.5,sf::Vector2f{6,2},origem);
                        break;
                        
                        case(IDs::IDs::velho):
                            m_animation.addAnimation("../Game/animations/Npc/oldman-idle.png","PARADO",3,1.5,sf::Vector2f{6,2},origem);
                        break;
                        
                        default:   
                            break;
                    }
                }

                void Npc::updateAnimation()
                {
                    m_animation.update(m_direction, "PARADO");
                }
                
                void Npc::updatePosition()
                {
                    dt = m_pGrafic->getTempo();
                    sf::Vector2f ds(0.f,0.f);

                    //efeito da gravidade
                
                    const float Vy = m_speed.y;
                    m_speed.y = m_speed.y + GRAVIDADE * dt;
                    ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;

                    setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y ));
                }

                nlohmann::ordered_json Npc::salvar()
                {
                    nlohmann::ordered_json json = saveCharacter();

                    json["dialogo"] = caminhoDialogo;
                    
                    return json;
                }
                
                const char* Npc::getCaminhoDialogo()
                {
                    return caminhoDialogo;
                }

                void Npc::draw()
                {
                    m_pGrafic->desenhaElemento(corpo);
                }

                void Npc::update()
                {
                    updatePosition();
                    updateAnimation();
                    draw();
                }

                void Npc::iniciarDialogo()
                {
                    auto* eFase = static_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                    Fase::Fase* fase = eFase->getFase();
                    
                    sf::Vector2f posDirecao = fase->getJogador()->getPos();

                    m_direction = pos.x - posDirecao.x > 0 ? true : false;

                    updateAnimation();

                    pEstado->addEstado(IDs::IDs::estado_dialogo);

                    Estado::Estado* estado = pEstado->getEstadoAtual();
                    auto* eDialogo = static_cast<Estado::EstadoDialogo*>(estado);

                    eDialogo->setDialogo(caminhoDialogo);
                }

                void Npc::colisao(Entidade* outraEntidade, sf::Vector2f ds)
                {

                }

            }
        }
    }
}