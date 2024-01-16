
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
            if(pEstado != nullptr)
                delete(pEstado);
            
            pEstado = nullptr;

            if(pMusica != nullptr)
                delete(pMusica);
            
            pMusica = nullptr;

            while(!pilhaEstados.empty())
            {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if(pEstado){
                delete(pEstado);
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
            Estado::Estado* estado = nullptr;

            if(ID == IDs::IDs::forest || ID == IDs::IDs::caverna)
            {
                estado = static_cast<Estado::Estado*>(new Estado::EstadoFase(ID));
            }
            else if(ID == IDs::IDs::menu_principal ||
                    ID == IDs::IDs::menu_pause     ||
                    ID == IDs::IDs::menu_opcao     ||
                    ID == IDs::IDs::menu_gameOver  ||
                    ID == IDs::IDs::menu_carregar  ||
                    ID == IDs::IDs::menu_salvar    ||
                    ID == IDs::IDs::menu_bug)
            {
                Estado::EstadoMenu* mEstado = new Estado::EstadoMenu(ID);
                estado = static_cast<Estado::Estado*>(mEstado);
            }

            if(estado == nullptr)
            {
                std::cout << ":Gerenciador::GerenciadorEstado::estado nulo" << std::endl;
                exit(1);
            }
            if(!pilhaEstados.empty())
            {
                desativarListener();
            }
            
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
                Gerenciador::GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fechaJanela();
            }
        }

        /**
         * @brief metodo que ativa o observador do estado
        */
        void GerenciadorDeEstado::ativarListener()
        {
            Estado::Estado* estadoAtual = getEstadoAtual();

            estadoAtual->mudarEstadoListener(true);
        }

        /**
         * @brief metodo que desativa o observador do estado
        */
        void GerenciadorDeEstado::desativarListener()
        {
            Estado::Estado* estadoAtual = getEstadoAtual();

            estadoAtual->mudarEstadoListener(false);
        }

        /**
         * @brief metodo de acesso ao estado no topo da pilha de estados
         * 
         * @return retorna o estado do topo da pilha de estados
        */
        Estado::Estado* GerenciadorDeEstado::getEstadoAtual()
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
        Estado::Estado* GerenciadorDeEstado::getEstado(int qtd)
        {
            std::stack<Estado::Estado*> pilhaAux = pilhaEstados;

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
                Estado::Estado* estado = pilhaEstados.top();
                estado->executar();
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
                Estado::Estado* estado = pilhaEstados.top();
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
