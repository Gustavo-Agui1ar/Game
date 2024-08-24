
#include "../includes/estados/estado.h"

namespace  Game{

    namespace Estado{
        
        /**
         * @brief construtora da classe Estado 
         * 
         * @param ID identificacao do estado
        */
        Estado::Estado(IDs::IDs ID):
        Ente(ID)
        {
            remover = false;
        }

        /**
         * @brief destrutora da classe Estado
        */
        Estado::~Estado()
        {

        }

        /**
         * @brief metodo responsavel por mostrar o estado
        */
        void Estado::draw()
        {

        }

        /**
         * @brief metodo queratualiza o estado do atributo remover para verdadeiro
        */
        void Estado::setRemover()
        {
            remover = true;
        }

        /**
         * @brief metodo de acesso ao atributo remover
         * 
         * @return retorna o estado do boelano remover
        */
        const bool Estado::getRemover()
        {
            return remover;
        }
        
    }
}