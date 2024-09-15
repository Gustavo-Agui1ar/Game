#include "../../includes/Entity/Ente.h"

namespace Game{

    Gerenciador::GerenciadorGrafico* Ente::m_graphic= Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

    Ente::Ente(const IDs::IDs ID):
    ID(ID)
    {
        
    }

    Ente::~Ente() = default;

    const IDs::IDs Ente::getID()
    {
        return ID;
    }

    nlohmann::ordered_json Ente::saveEnte()
    {
        nlohmann::ordered_json json;

        json["ID"] = getID();

        return json;
    }
}