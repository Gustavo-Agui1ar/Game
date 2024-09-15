
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game{

    namespace Gerenciador{

         GerenciadorDeEstado* GerenciadorDeEstado::pEstado = nullptr;
         GerenciadorDeMusica* GerenciadorDeEstado::pMusica = GerenciadorDeMusica::getGerenciadorDeMusica();

         /**
          * @brief construtora da classe GerenciadoDeEstado
         */
         GerenciadorDeEstado::GerenciadorDeEstado():
         pilhaEstados()
         {

         }

        /**
         * @brief metodo de acesso a um objeto da classe GerenciadorDeEstado
         * 
         * @return retorna um ponteiro para um objeto da classe GerenciadorDeEstado
        */
        GerenciadorDeEstado* GerenciadorDeEstado::getGerenciadorDeEstado()
        {
            if(pEstado == nullptr)
                pEstado = new GerenciadorDeEstado();
            return pEstado;
        }

        /**
         * @brief destrutora da classe GerenciadorDeEstado
        */
        GerenciadorDeEstado::~GerenciadorDeEstado()
        {
            if(pMusica != nullptr)
                delete pMusica;
            
            pMusica = nullptr;

            while(!pilhaEstados.empty())
            {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if(pEstado){
                pEstado = nullptr;
            }
        }

        /**
         * @brief adiciona um estado a pilha de estados
         * 
         * @param ID identificador de qual estado deve ser criado
        */
        void GerenciadorDeEstado::addEstado(IDs::IDs ID)
        {
            State::State* estado = nullptr;

            if(ID == IDs::IDs::dawn_forest || ID == IDs::IDs::cave || ID == IDs::IDs::village)
            {
                estado = static_cast<State::State*>(new State::LevelState(ID));
            }
            else if(ID == IDs::IDs::main_menu ||
                    ID == IDs::IDs::pause_menu     ||
                    ID == IDs::IDs::option_menu     ||
                    ID == IDs::IDs::game_over_menu  ||
                    ID == IDs::IDs::load_menu  ||
                    ID == IDs::IDs::save_menu    ||
                    ID == IDs::IDs::select_fase_menu    ||
                    ID == IDs::IDs::bug_menu)
            {
                auto* mEstado = new State::MenuState(ID);
                estado = static_cast<State::State*>(mEstado);
            }
            else if(ID == IDs::IDs::dialogue_estate)
            {
                State::State* estadoAtual = getEstadoAtual();

                auto* eFase = static_cast<State::LevelState*>(estadoAtual);
                
                auto* mEstado = new State::DialogueState(ID);

                mEstado->setFase(eFase->getLevel());

                estado = static_cast<State::State*>(mEstado);
            }

            if(estado == nullptr)
            {
                std::cout << ":Gerenciador::GerenciadorEstado::estado nulo" << std::endl;
                exit(1);
            }
            if(!pilhaEstados.empty())
                desativarListener();
            
            pMusica->mudarMusica(ID);
            pilhaEstados.push(estado);
        }

        /**
         * @brief metodo responsavel por remover 1 estado da pilha de estados
        */
        void GerenciadorDeEstado::removerEstado()
        {
            if(pilhaEstados.top() != nullptr && !pilhaEstados.empty())
            {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if(!pilhaEstados.empty())
            {
               pMusica->mudarMusica(pilhaEstados.top()->getID());
               ativarListener();
            }
            else
            {
                Gerenciador::GerenciadorGrafico* m_pGrafic = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();
                m_pGrafic->fechaJanela();
            }
        }

        /**
         * @brief metodo que ativa o observador do estado
        */
        void GerenciadorDeEstado::ativarListener()
        {
            State::State* estadoAtual = getEstadoAtual();

            estadoAtual->changeEstateObserver(true);
        }

        /**
         * @brief metodo que desativa o observador do estado
        */
        void GerenciadorDeEstado::desativarListener()
        {
            State::State* estadoAtual = getEstadoAtual();

            estadoAtual->changeEstateObserver(false);
        }

        /**
         * @brief metodo de acesso ao estado no topo da pilha de estados
         * 
         * @return retorna o estado do topo da pilha de estados
        */
        State::State* GerenciadorDeEstado::getEstadoAtual()
        {
            if(!pilhaEstados.empty())
            {
                return pilhaEstados.top();
            }
            return nullptr;
        }

        /**
         * @brief metodo de acesso a um estado da pilha de estados
         * 
         * @param qtd quantidade de estados anteriores a ser percorrida ate o estado desejado
         * 
         * @return retorna o estado desejado da pilha de estados
        */
        State::State* GerenciadorDeEstado::getEstado(int qtd)
        {
            std::stack<State::State*> pilhaAux = pilhaEstados;

            int i = 0;

            while( i  < qtd && !pilhaAux.empty())
            {
                pilhaAux.pop();
                i++;
            }

            if(!pilhaAux.empty())
                return pilhaAux.top();
            
            return nullptr;
        }

        /**
         * @brief metodo que executa o estado do topo da pilha
        */
        void GerenciadorDeEstado::executar()
        {
            if(!pilhaEstados.empty())
            {
                State::State* estado = pilhaEstados.top();
                estado->execute();
            }
        }

        /**
         * @brief remove um ou mais estados da pilha de estados
         * 
         * @param quantidade quantidades a ser removida de estados
        */
        void GerenciadorDeEstado::removerEstado(const int quantidade)
        {
            int i = 0;
            while(!pilhaEstados.empty() && i < quantidade)
            {
                State::State* estado = pilhaEstados.top();
                if(estado != nullptr){
                    delete(estado);
                    estado = nullptr; 
                }
                pilhaEstados.pop();
                i++;
            }
            if(!pilhaEstados.empty())
            {
                pMusica->mudarMusica(pilhaEstados.top()->getID());
                ativarListener();
            } 
            else 
            {
                GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fechaJanela();
            }
        }
    }
}
