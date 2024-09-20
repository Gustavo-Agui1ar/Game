
#include "../includes/menus/menuDeSelecao.h"

namespace Game{

    namespace Menu{

        MenuDeSelecao::MenuDeSelecao(Level::Level* fase):
        MenuPausa(IDs::IDs::select_fase_menu,"Menu de Selecao", fase), pArquivo(new Manager::FileManager()), listaDeSelecao()
        {
            sf::Vector2f posJanela = m_graphic->getCamera().getCenter();
            
            atualizarPosicaoFundo();
            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
            
            fundoEscuro.setPosition(posFundoEscuro);
            titulo.setPos(sf::Vector2f(posJanela.x - titulo.getTam().x/2.f, 40.f));

            criarBotoes();
        }

        MenuDeSelecao::~MenuDeSelecao()
        {

        }

        void MenuDeSelecao::criarBotoes()
        {
            addBotao("Jogar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::play_button, sf::Color{245, 170, 0});
            addBotao("Voltar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::back_button, sf::Color{245, 170, 0});
            
            inicializarBotoes();
           
            inicialiarIterador();

            criarBotoesDeSelecao();
        }

        void MenuDeSelecao::inicializarBotoes()
        {
            std::list<Botao::BotaoTexto*>::iterator itAux = listaDeBotao.begin();
            sf::Vector2f posJanela = m_graphic->getCamera().getCenter();
            int auxTam = 0;
            
            while (itAux != listaDeBotao.end())
            {
                Botao::BotaoTexto* botao = (*itAux);
                
                botao->atualizarPosicaoDaCaixa(sf::Vector2f(posJanela.x - tamBotao.x/2.f, 700.f + auxTam * 50.f));
                itAux++;
                auxTam++;
            }
            
        }

        void MenuDeSelecao::criarBotoesDeSelecao()
        {
            std::vector<std::string> faseNomes = pArquivo->readFileText("../Game/saves/fases.txt");
            auto itFases = faseNomes.begin();
            IDs::IDs IDFaseAux = IDs::IDs::cave;

            while(itFases != faseNomes.end())
            {
                Botao::BotaoSelecao* botao = nullptr;
                botao = new Botao::BotaoSelecao((*itFases),sf::Vector2f(0.f, 0.f), tamBotao,IDs::IDs::select_level_button, sf::Color{245,170,0} ,IDFaseAux); 
                if(botao == nullptr)
                {
                    std::cout<<"nao foi possive criar o botao de selecao de fase";
                    exit(1);
                }

                std::string caminhoFase("../Game/animations/" + (*itFases) + ".png");

                botao->setImagemFase( caminhoFase.c_str());

                int aux = static_cast<int>(IDFaseAux);
                aux++;
                IDFaseAux = static_cast<IDs::IDs>(aux);
                itFases++;

                listaDeSelecao.push_back(botao);
            }
            
            itSelecaoFase = listaDeSelecao.begin();
        }

        void MenuDeSelecao::selecionaEsquerda()
        {
            if(itSelecaoFase == listaDeSelecao.begin())
                itSelecaoFase = listaDeSelecao.end();
           
            itSelecaoFase--;
        }

        void MenuDeSelecao::selecionaDireita()
        {
            itSelecaoFase++;

            if(itSelecaoFase == listaDeSelecao.end())
                itSelecaoFase = listaDeSelecao.begin();
        }

        void MenuDeSelecao::executar()
        {
            fase->draw();

            m_graphic->drawElement(fundoEscuro);

            m_graphic->drawElement(titulo.getTexto());

            (*itSelecaoFase)->draw();

            draw();
        }

        const IDs::IDs MenuDeSelecao::getIDdeSelecao()
        {
            return (*itSelecaoFase)->getIDFase();
        }
    }
}