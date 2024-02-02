
#include "../includes/entidade/npcs/npc.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game{

    namespace Entidade{

        namespace Personagem{ 
            
            namespace Npc{

                Gerenciador::GerenciadorDeEstado* Npc::pEstado = pEstado->getGerenciadorDeEstado();
                
                Npc::Npc(sf::Vector2f pos, const IDs::IDs ID, const char* caminhoDialogo):
                Personagem(pos,sf::Vector2f(TAM_NPC_GENERICO_X, TAM_NPC_GENERICO_Y), 0.0f, ID, 0.0f, 0.0f, 0.0f), caminhoDialogo(caminhoDialogo)
                {
                    inicializarAnimacao();
                }
                Npc::~Npc()
                {
            
                }
            
                void Npc::inicializarAnimacao()
                {
                    const sf::Vector2f origem = sf::Vector2f(tam.x/2.5,tam.y/2.2);
                    animacao.addAnimacao("../Game/animations/Npc/bearded-idle.png","PARADO",5,0.6,sf::Vector2f{6,2},origem);
                }

                void Npc::atualizarAnimacao()
                {
                    animacao.atualizar(direcao, "PARADO");
                }
                
                void Npc::atualizarPosicao()
                {
                    dt = pGrafico->getTempo();
                    sf::Vector2f ds(0.f,0.f);

                    //efeito da gravidade
                
                    const float Vy = velocidade.y;
                    velocidade.y = velocidade.y + GRAVIDADE * dt;
                    ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;

                    setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y ));
                }

                nlohmann::ordered_json Npc::salvar()
                {
                    nlohmann::ordered_json json = salvarPersonagem();

                    json["dialogo"] = caminhoDialogo;
                    
                    return json;
                }
                
                const char* Npc::getCaminhoDialogo()
                {
                    return caminhoDialogo;
                }

                void Npc::desenhar()
                {
                    pGrafico->desenhaElemento(corpo);
                }

                void Npc::atualizar()
                {
                    atualizarPosicao();
                    atualizarAnimacao();
                    desenhar();
                }

                void Npc::iniciarDialogo()
                {
                    pEstado->addEstado(IDs::IDs::estado_dialogo);

                    Estado::Estado* estado = pEstado->getEstadoAtual();
                    Estado::EstadoDialogo* eDialogo = static_cast<Estado::EstadoDialogo*>(estado);

                    eDialogo->setDialogo(caminhoDialogo);
                }

                void Npc::colisao(Entidade* outraEntidade, sf::Vector2f ds)
                {

                }

            }
        }
    }
}