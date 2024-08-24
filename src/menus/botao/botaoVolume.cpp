
#include "../includes/menus/botao/botaoVolume.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
         BotaoVolume::BotaoVolume(const std::string info, sf::Vector2f tam, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color corSelecionado, const float posInicioFundo):
         BotaoTexto(info, pos, tam, ID, corSelecionado), fundoVolume(sf::Vector2f(TAMANHO_BARRA_VOLUME_X, TAMANHO_BARRA_VOLUME_Y)),
         corpoVolume(sf::Vector2f(TAMANHO_BOTAO_VOLUME_X, TAMANHO_BOTAO_VOLUME_Y)), pMusica(pMusica->getGerenciadorDeMusica()), posInicioFundo(posInicioFundo),
         parametrizacao((TAMANHO_BARRA_VOLUME_X - TAMANHO_BOTAO_VOLUME_X) / 100.0f), posInicioBarra(posInicioFundo),
         posFimBarra(posInicioFundo + TAMANHO_BARRA_VOLUME_X)
         {
            fundoVolume.setFillColor(sf::Color::Black);
            fundoVolume.setPosition(sf::Vector2f(posInicioFundo, getPos().y + getTamTexto().y - 15.0f));

            corpoVolume.setFillColor(sf::Color{238,173,45});

            float volume = 0.0f;

            switch(ID)
            {
                case(IDs::IDs::botao_volume_geral):
                {
                    volume = pMusica->getVolumeGeral();
                    corpoVolume.setPosition(sf::Vector2f(posInicioFundo + volume * parametrizacao, getPos().y + getTamTexto().y - 15.0f));
                }
                break;
                
                case(IDs::IDs::botao_volume_do_jogo):
                {
                    volume = pMusica->getVolume(IDs::IDs::floresta_do_amanhecer);
                    corpoVolume.setPosition(sf::Vector2f(posInicioFundo + volume * parametrizacao, getPos().y + getTamTexto().y - 15.0f));
                }
                break;
                
                case(IDs::IDs::botao_volume_efeito_sonoro):
                {
                    volume = pMusica->getVolumeEfeitoSonoro();
                    corpoVolume.setPosition(sf::Vector2f(posInicioFundo + volume * parametrizacao, getPos().y + getTamTexto().y - 15.0f));
                }
                break;

                default:
                    break;
            }

         }

         BotaoVolume::~BotaoVolume()
         {
            
         }

         void BotaoVolume::alterarVolume(const float volume)
         {
            sf::Vector2f posVolume = corpoVolume.getPosition();

            posVolume.x += volume;

            if(posVolume.x + TAMANHO_BOTAO_VOLUME_X > posFimBarra)
            {
                posVolume.x =  posFimBarra - TAMANHO_BOTAO_VOLUME_X;
            }
            else if(posVolume.x < posInicioBarra)
            {
                posVolume.x = posInicioBarra;
            }

            corpoVolume.setPosition(posVolume);
            atualizarVolume();
         }

         void BotaoVolume::atualizarVolume()
         {
            const float vol = ((corpoVolume.getPosition().x - posFimBarra + TAMANHO_BOTAO_VOLUME_X) / parametrizacao) + 100.0f;

            switch(ID)
            {
                case(IDs::IDs::botao_volume_do_jogo):
                {
                    pMusica->setVolume(IDs::IDs::floresta_do_amanhecer, vol);
                }
                break;
                
                case(IDs::IDs::botao_volume_efeito_sonoro):
                {
                    pMusica->setVolumeEfeitoSonoro(vol);
                }
                break;
                
                case(IDs::IDs::botao_volume_geral):
                {
                    pMusica->setVolumeGeral(vol);
                }
                break;

                default:
                    break;
            }
         }

         void BotaoVolume::draw()
         {
            atualizarAnimacao();

            m_pGrafic->desenhaElemento(fundoVolume);
            m_pGrafic->desenhaElemento(corpoVolume);
            m_pGrafic->desenhaElemento(texto.getTexto());
         }

        }
    }
}