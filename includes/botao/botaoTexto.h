
#include "botao.h"
#include "textoEfeito.h"

#define FONTE "Game/animations/botton/menu.ttf"
#define TEMPO_TROCA  0.025f

namespace Game{

    namespace Menu{

        namespace Botao{

            class BotaoTexto : public Botao{
                
            private:

                bool  botaoSelecionado;
                sf::Color corSelecionado;
                TextoEfeito texto;

                 const sf::Vector2f getTamTexto();

            public:

                BotaoTexto(const std::string infoTexto, const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID, const sf::Color corSelecionado);
                ~BotaoTexto();

                void atualizarAnimacao();
                void atualizarPosicaoDaCaixa(const sf::Vector2f pos);
                void setSelecionado(bool selecionado);
                const bool getSelecionado();
                void desenhar();

            };
        }
    }

}