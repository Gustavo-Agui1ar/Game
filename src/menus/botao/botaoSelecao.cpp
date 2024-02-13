
#include "../includes/menus/botao/botaoSelecao.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
            BotaoSelecao::BotaoSelecao(const std::string infoTexto, const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID, const sf::Color corSelecionado, IDs::IDs IDFase):
            BotaoTexto(infoTexto, pos,  tam, ID, corSelecionado ), IDFase(IDFase)
            {
                sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                sf::Vector2f posicaoCaixa(posJanela.x - TAM_V_FASE_X/2.f, posJanela.y - TAM_V_FASE_Y/2.f);
                
                atualizarPosicaoDaCaixa(sf::Vector2f(posJanela.x - caixa.getSize().x/2.f, posicaoCaixa.y - 80.f));          

                visualizacaoFase.setSize(sf::Vector2f(TAM_V_FASE_X, TAM_V_FASE_Y));
                visualizacaoFase.setPosition(posicaoCaixa);
            }

            BotaoSelecao::~BotaoSelecao()
            {

            }

            const IDs::IDs BotaoSelecao::getIDFase()
            {
                return IDFase;
            }

            void BotaoSelecao::setImagemFase(const char* caminhoImagem)
            {
                texture = pGrafico->carregarTextura(caminhoImagem);

                visualizacaoFase.setTexture(&texture);                
            }

            void BotaoSelecao::desenhar()
            {
                pGrafico->desenhaElemento(texto.getTexto());
                pGrafico->desenhaElemento(visualizacaoFase);
            }
        }
    }
}