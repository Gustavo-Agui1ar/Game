
#include "../includes/menus/botao/textoFala.h"

namespace Game{

    namespace Menu{

        namespace Botao{

            TextoFala::TextoFala(const float tempoTroca, const sf::Font fonte, const std::string infoTexto, const unsigned int fonteTam):
            Texto(fonte, "", fonteTam),tempoDeTroca(tempoTroca),tempo(0.0f), fimTexto(false), pGrafico(pGrafico->getGerenciadorGrafico()),
            falaCompleta(infoTexto)
            {
                inicializarIterador();
            }

            TextoFala::~TextoFala()
            {
                
            }

            void TextoFala::incrementarFala()
            {
                if(!fimTexto)
                {
                    std::string texto = infoTexto;
                    std::string falaAtual = texto;
                    sf::String falaString(falaAtual);

                    if((*letraFala) == '_')
                    {
                        falaString += "\n ";
                    }
                    else
                        falaString += (*letraFala);

                    setString(falaString);
                    letraFala++;
                    if(letraFala == falaCompleta.end())
                    {
                        fimTexto = true;
                    }
                }
            }

            void TextoFala::inicializarIterador()
            {
                letraFala = falaCompleta.begin();
            }

            void TextoFala::mostrarFalaInteira()
            {
                fimTexto = true;
                
                std::string::iterator itF = falaCompleta.begin();
                sf::String fCompleto("");
                
                while(itF != falaCompleta.end())
                {
                    if((*itF) != '_')
                        fCompleto +=(*itF);
                    else 
                        fCompleto += "\n ";
                    itF++;
                }

                setString(fCompleto);
            }

            const bool TextoFala::getFimTexto()
            {
                return fimTexto;
            }

            void TextoFala::atualizar()
            {
                if(!fimTexto)
                {
                    tempo += pGrafico->getTempo();

                    if(tempo >= tempoDeTroca)
                    {
                        incrementarFala();
                        tempo = 0.0f;
                    }
                }
            }
            void TextoFala::setTexto(sf::String texto)
            {
                falaCompleta = texto;
            }

            std::string TextoFala::getFalaCompleta()
            {
                return falaCompleta;
            }

            const float TextoFala::getTempoTroca()
            {
                return tempoDeTroca;
            }

        }
    }
}