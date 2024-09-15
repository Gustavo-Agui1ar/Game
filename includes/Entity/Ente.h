
#pragma once

#include "IDs.h"
#include <fstream>
#include "../json.hpp"
#include "../gerenciador/gerenciadorGrafico.h"

namespace Game{

    class Ente{

    protected:

        static Gerenciador::GerenciadorGrafico* m_graphic;
        
        const IDs::IDs ID;

    public:

        explicit Ente(const IDs::IDs ID);
        virtual ~Ente();

        const IDs::IDs getID();

        nlohmann::ordered_json saveEnte();
        
        virtual void draw() = 0;
    };

}
