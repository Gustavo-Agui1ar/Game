
#pragma  once

#include "textoFala.h"

#define TAM_NOME_X 250.0f
#define TAM_NOME_Y 35.0f

namespace Game{

    namespace Menu{
        
        namespace Botao{

            class BalaoDeFala{
                
                private:
                    
                    Gerenciador::GerenciadorGrafico* pGrafico;
                    TextoFala fala;
                    Texto nome;
                    sf::RectangleShape caixaDialogo;
                    sf::RectangleShape caixaNome;
                
                    void inicializarCaixaDeDialogo();
                    void inicializarNome();
                    void inicializarTexto();
                
                public:

                    BalaoDeFala(std::string infoTexto, std::string infoNome, const float tempoDeTroca = 0.05f);
                    ~BalaoDeFala();

                    void setTexto(std::string texto);
                    std::string getTexto();

                    void setNome(std::string nome);
                    std::string getNome();

                    const float getTempoTroca();
                    const bool getFimTexto();

                    void setDirecaoNome(bool esquerda);

                    void pularDialogo();
                    
                    void atualizarNome();
                    void atualizarTexto();

                    void atualizar();
                    void desenhar();      
            };
        }
    }
}