
#include "../includes/estados/estado.h"

namespace  Game{

    namespace Estado{

        Estado::Estado(IDs::IDs ID):
        Ente(ID)
        {
            remover = false;
        }

        Estado::~Estado()
        {

        }

        void Estado::desenhar()
        {

        }

        void Estado::setRemover()
        {
            remover = true;
        }

        const bool Estado::getRemover()
        {
            return remover;
        }
        
    }
}