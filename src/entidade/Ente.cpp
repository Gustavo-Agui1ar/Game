#include "../../includes/entidade/Ente.h"

namespace Game{

        //inicializa o ponteiro estatico de ente.
        Gerenciador::GerenciadorGrafico* Ente::pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

        /**
         * construtora da classe ente
         * 
         * parametros:
         * 
         * ID: id a ser colocado no atributo id de ente
        */

        Ente::Ente(const IDs::IDs ID):
        ID(ID){}

        /**
         * destrutora da classe ente
        */

        Ente::~Ente(){

        }

        /**
         * metodo que retorna o id de ente
        */

        const IDs::IDs Ente::getID()
        {
            return ID;
        }

}
