
#pragma once

#include "botao.h"
#include "textoEfeito.h"

#define FONTE "Game/animations/botton/MonsterOfFantasy.ttf"
#define TEMPO_TROCA  0.025f

namespace Game{

    namespace Menu{

        namespace Botao{

            class BotaoTexto : public Botao{
                
            protected:

                //atributos de botao selecionado
               
                sf::Color corSelecionado;
                bool  botaoSelecionado;
                
                //atributo de informacao do botao
               
                TextoEfeito texto;

                //metodo de acesso ao tamanho do texto
              
                const sf::Vector2f getTamTexto();

            public:

                //construtor e destrutor
              
                BotaoTexto(const std::string infoTexto, const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID, const sf::Color corSelecionado);
                ~BotaoTexto();
                
                //metodos de atualizacao dos atributos da classe
               
                void atualizarPosicaoDaCaixa(const sf::Vector2f pos);
                void atualizarAnimacao();

                //metodo modificador do atributo selecionado
             
                void setSelecionado(bool selecionado);
                
                //metodode acesso ao atributo selecionado
               
                const bool getSelecionado();
                
                //metodo responsavel pela visualizacao do botao
              
                void desenhar();

            };
        }
    }

}