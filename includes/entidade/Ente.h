
#pragma once

#include "IDs.h"
#include <fstream>
#include "../json.hpp"
#include "../gerenciador/gerenciadorGrafico.h"

namespace Game{

    class Ente{

    protected:

        //atributo usado por suas filhas
     
        static Gerenciador::GerenciadorGrafico* m_pGrafic;
        
        //atributo de identificacao da filha
       
        const IDs::IDs ID;

    public:

        //construtor e destrutor
       
        explicit Ente(const IDs::IDs ID);
        virtual ~Ente();

        //metodo de acesso a id
     
        const IDs::IDs getID();

        //metodo responsavel ppor salvar informacoes e estados da classe 
      
        nlohmann::ordered_json salvarEnte();
        
        //metodo usado por suas filhas para vizualizacao
        
        virtual void draw() = 0;
    };

}
