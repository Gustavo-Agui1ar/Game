#include "../../includes/entidade/Ente.h"

namespace Game{

        //inicializa o ponteiro estatico de ente.
        Gerenciador::GerenciadorGrafico* Ente::m_pGrafic = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

        /**
         * @brief construtora da classe ente
         * 
         * @param ID id a ser colocado no atributo id de ente
        */
        Ente::Ente(const IDs::IDs ID):
        ID(ID)
        {
            
        }

        /**
         * @brief destrutora da classe ente
        */
        Ente::~Ente() = default;

        /**
         * @brief metodo que retorna o id de ente
        */
        const IDs::IDs Ente::getID()
        {
            return ID;
        }

        /**
         * @brief metodo que salva o estado de um objeto desta classe
         * 
         * @return retorna um json contendo o estado atual de um objeto desta classe
        */
        nlohmann::ordered_json Ente::salvarEnte()
        {
            nlohmann::ordered_json json;

            json["ID"] = getID();

            return json;
        }

}
