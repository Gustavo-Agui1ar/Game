
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

        
    }
}