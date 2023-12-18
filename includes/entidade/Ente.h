
#pragma once

#include "IDs.h"
#include <fstream>
#include "../json.hpp"
#include "../gerenciador/gerenciadorGrafico.h"

namespace Game{

    class Ente{

    protected:

        //atributo usado por suas filhas
        static Gerenciador::GerenciadorGrafico* pGrafico;
        
        //atributo de identificacao da filha
        const IDs::IDs ID;

    public:

        //construtor e destrutor
        Ente(const IDs::IDs ID);
        ~Ente();

        //metodo de acesso a id
        const IDs::IDs getID();

        nlohmann::ordered_json salvarEnte();

        
        //metodo usado por suas filhas para vizualizacao
        virtual void desenhar() = 0;
    };

}
