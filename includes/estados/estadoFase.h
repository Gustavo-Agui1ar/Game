
#pragma once 

#include "estado.h"

#include "../gerenciador/GerenciadorGrafico.h"

#include "../fases/level-1.h"
#include "../fases/level-2.h"
#include "../fases/vila.h"

namespace Game::Estado{
    class EstadoFase : public Estado{

    private:
        
        //atributo principal da classe
        
        Fase::Fase* fase;

    public:

        //construtor e destrutor
        
        explicit EstadoFase(const IDs::IDs ID);
        ~EstadoFase() override;

        //metodo responsavel por inicializar o atributo fase
        
        void criarFase(nlohmann::ordered_json entidades, IDs::IDs IDfase);
        void criarFase();
        
        //metodo responsavel pela visualizacao e atualizacao da classe
        
        void executar() override;

        //metodo de acesso ao atributo fase
        
        Fase::Fase* getFase();
        
        //metodo que altera o observador da classe
        
        void mudarEstadoListener(const bool ativo) override;

    };

}
