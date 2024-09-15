
#include "../includes/menus/botao/balaoDeFala.h"

namespace Game::Menu::Botao{

            BalaoDeFala::BalaoDeFala(std::string infoTexto, std::string infoNome, const float tempoDeTroca):
            pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),fala(tempoDeTroca, pGrafico->carregarFonte( "../Game/animations/botton/menu.ttf"), infoTexto),
            nome(pGrafico->carregarFonte( "../Game/animations/botton/menu.ttf"), infoNome),caixaDialogo(), caixaNome()
            {
                inicializarCaixaDeDialogo();
            }

            BalaoDeFala::~BalaoDeFala() = default;

            void BalaoDeFala::inicializarCaixaDeDialogo()
            {
        
                sf::Vector2f tamJanela = pGrafico->getTamJanela();
                sf::Vector2f posJanela = pGrafico->getCamera().getCenter();

                caixaDialogo.setSize(sf::Vector2f(tamJanela.x, tamJanela.y/4.0f)); 
                caixaDialogo.setPosition(posJanela.x - tamJanela.x/2.0f, posJanela.y - tamJanela.y/2.0f);
                caixaDialogo.setFillColor(sf::Color{0, 0, 0, 230});
                caixaDialogo.setOutlineThickness(5.0f);
                caixaDialogo.setOutlineColor(sf::Color{200,200,200});

                caixaNome.setSize(sf::Vector2f(nome.getTam().x + 50.f, TAM_NOME_Y));
                caixaNome.setPosition(posJanela.x - tamJanela.x/2.0f + 5.0f, (posJanela.y - tamJanela.y/2.0f) + caixaDialogo.getSize().y + 5.0f);
                caixaNome.setFillColor(sf::Color{0, 0, 0, 230});
                caixaNome.setOutlineThickness(5.0f);
                caixaNome.setOutlineColor(sf::Color{200,200,200});

                fala.setTamFonte(35);
                nome.setTamFonte(30);
                
                inicializarNome();
                inicializarTexto();
            }

            void BalaoDeFala::inicializarNome()
            {
                sf::Vector2f tamNome = nome.getTam();
                sf::Vector2f pos = caixaNome.getPosition();
                sf::Vector2f tam = caixaNome.getSize();
                auto posNome = sf::Vector2f(
                    pos.x + tam.x / 2.0f - tamNome.x / 2.f,
                    pos.y + tam.y / 2.0f - tamNome.y
                );
                nome.setPos(posNome);
            }
            
            void BalaoDeFala::inicializarTexto()
            {
                sf::Vector2f pos = caixaDialogo.getPosition();
                sf::Vector2f tam = caixaDialogo.getSize();
                auto posTexto = sf::Vector2f(pos.x + tam.x / 10.f , pos.y + tam.y / 5.f);
                fala.setPos(posTexto);
            }
           
            void BalaoDeFala::atualizarNome()
            {
                caixaNome.setSize(sf::Vector2f(nome.getTam().x + 50.f, TAM_NOME_Y));
                sf::Vector2f tamNome = nome.getTam();
                sf::Vector2f pos = caixaNome.getPosition();
                sf::Vector2f tam = caixaNome.getSize();
                auto posNome = sf::Vector2f(
                    pos.x + tam.x / 2.0f - tamNome.x / 2.f,
                    pos.y + tam.y / 2.0f - tamNome.y
                );
                nome.setPos(posNome);
            }
            
            void BalaoDeFala::atualizarTexto()
            {
                sf::Vector2f pos = caixaDialogo.getPosition();
                sf::Vector2f tam = caixaDialogo.getSize();
                auto posTexto = sf::Vector2f(
                    pos.x + tam.x / 10.f ,
                    pos.y + tam.y / 5.f 
                );
                fala.setPos(posTexto);
            }

            void BalaoDeFala::setDirecaoNome(bool esquerda)
            {
                sf::Vector2f tamJanela = pGrafico->getTamJanela();
                sf::Vector2f posJanela = pGrafico->getCamera().getCenter();

                float posX = esquerda ? posJanela.x - tamJanela.x / 2.f + 5.f : posJanela.x + tamJanela.x / 2.f - caixaNome.getSize().x - 5.f;

                caixaNome.setPosition(posX, (posJanela.y - tamJanela.y/2.0f) + caixaDialogo.getSize().y + 5.0f);
                atualizarNome();
            }

            void BalaoDeFala::setTexto(std::string texto)
            {
                fala.setTexto(texto);
            }
            
            std::string BalaoDeFala::getTexto()
            {
                return fala.getFalaCompleta();
            }

            void BalaoDeFala::setNome(std::string nome)
            {
                this->nome.setString(nome);
            }
            
            std::string BalaoDeFala::getNome()
            {
                return nome.getString();
            }

            const float BalaoDeFala::getTempoTroca()
            {
                return fala.getTempoTroca();
            }

            void BalaoDeFala::atualizar()
            {
                fala.atualizar();

                if(fala.getPos().x + fala.getTam().x >= 
                   caixaDialogo.getPosition().x + caixaDialogo.getSize().x -  caixaDialogo.getSize().x / 10.f)

                draw();
            }

            void BalaoDeFala::draw()
            {
                pGrafico->desenhaElemento(caixaDialogo);
                pGrafico->desenhaElemento(caixaNome);
                pGrafico->desenhaElemento(nome.getTexto());
                pGrafico->desenhaElemento(fala.getTexto());
            }

            void BalaoDeFala::pularDialogo()
            {
                fala.mostrarFalaInteira();
            }

            const bool BalaoDeFala::getFimTexto()
            {
                return fala.getFimTexto();
            }
}