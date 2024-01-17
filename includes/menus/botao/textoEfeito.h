
#pragma once

#include "texto.h"

namespace Game{

    namespace Menu{

        namespace Botao{

            class TextoEfeito : public Texto{

            private:

                //atributos referentes ao efeito do botao
              
                int transparencia;
                bool apagando;

                //metodo de atualizacao dos atributos de efeito
                
                void atualizar();

            public:

                //construtor e destrutor
               
                TextoEfeito(const sf::Font fonte, const std::string infoTexto);
                ~TextoEfeito();

                //metodo que aplica o efeito inverso ao atual
              
                void mudarTransparencia();
                
                //getters da classe
              
                const bool getApagando();
                const int getTransparente();
              
                //setters da classe
              
                void setTransparente(int tansparente);

                //metodo que reinicia o efeito do botao
               
                void resetar();

            };
        }
    }
}