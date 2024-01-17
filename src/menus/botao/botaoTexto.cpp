
#include "../includes/menus/botao/botaoTexto.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
            /**
             * @brief construtora da classe BotaoTexto
             * 
             * @param infoTexto informacao do botao (texto)
             * @param pos posicao do botao
             * @param tam tamanho do botao
             * @param id identificacao do botao
             * @param corSelecionado cor do botao ao ser selecionado
            */
            BotaoTexto::BotaoTexto(const std::string infoTexto, const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID, const sf::Color corSelecionado):
            Botao(tam,pos,ID,TEMPO_TROCA),corSelecionado(corSelecionado),texto(pGrafico->carregarFonte("../Game/animations/botton/menu.ttf"), infoTexto)
            {
                botaoSelecionado = false;

                sf::Vector2f tamTexto = this->texto.getTam();
                sf::Vector2f posTexto = sf::Vector2f(
                    pos.x + tam.x / 2.0f - tamTexto.x / 2.05f,
                    pos.y + tam.y / 2.0f - tamTexto.y * 1.2f
                );
                this->texto.setPos(posTexto);
            }
            
            /**
             * @brief destrutora da classe BotaoTexto
            */
            BotaoTexto::~BotaoTexto()
            {

            }

            /**
             * @brief metodo de acesso ao atributo tamanho do texto
             * 
             * @return retorna um retangulo que determina o tamanho do texto
            */
            const sf::Vector2f BotaoTexto::getTamTexto()
            {
                return sf::Vector2f(texto.getTexto().getGlobalBounds().width, texto.getTexto().getGlobalBounds().height);
            }
            
            /**
             * @brief metodo responsavel por mostrar o botao na tela
            */
            void BotaoTexto::desenhar()
            {
                atualizarAnimacao();
                //pGrafico->desenhaElemento(caixa);
                pGrafico->desenhaElemento(texto.getTexto());
            }

            /**
             * @brief metodo responsavel por atualizar a animacao do botao
            */
            void BotaoTexto::atualizarAnimacao()
            {
                tempo += pGrafico->getTempo();
                
                if(botaoSelecionado) 
                {
                    if(tempo > tempoTroca)
                    {
                        int transparente = texto.getTransparente();
                        if(texto.getApagando())
                        {
                            transparente += 5;
                            if(transparente > 255)
                            {
                                transparente= 255;
                                texto.mudarTransparencia();
                            }
                        }
                        else
                        {
                            transparente -= 5;
                            if(transparente < 0)
                            {
                                transparente = 0;
                                texto.mudarTransparencia();
                            }
                        }
                        texto.setTransparente(transparente);
                        tempo = 0.0f;
                    }
                }
                else
                {
                    tempo = 0.0f;
                }
            }
            
            /**
             * @brief metodo que atualiaza a posicao do botao
             * 
             * @param pos posicao a ser definida no botao 
            */
            void BotaoTexto::atualizarPosicaoDaCaixa(const sf::Vector2f pos)
            {
                this->pos = pos;
                caixa.setPosition(pos);
                 sf::Vector2f tamTexto = texto.getTam();
                sf::Vector2f posTexto = sf::Vector2f(
                    pos.x + tam.x / 2.0f - tamTexto.x / 2.05f,
                    pos.y + tam.y / 2.0f - tamTexto.y * 1.2f
                );
                texto.setPos(posTexto);

            }

            /**
             * @brief metodo que altera o atributo botaoSelecionado
             * 
             * @param selecionado boleano a ser atribuido em botaoSelecionado
            */
            void BotaoTexto::setSelecionado(bool selecionado)
            {
                texto.setCorTexto(selecionado ? corSelecionado : sf::Color::White);
                botaoSelecionado = selecionado;
                texto.resetar();
            }

            /**
             * @brief metodo de acesso ao atributo botaoSelecionado
             * 
             * @return rretorna um boleano com o valor do atributo botaoSelecionado
            */
            const bool BotaoTexto::getSelecionado()
            {
                return botaoSelecionado;
            }
        }
    }
}