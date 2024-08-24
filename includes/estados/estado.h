
#pragma once

#include "../entidade/Ente.h"


namespace Game::Estado{
    class Estado : public Ente{


    private:

        //aributo de controle de remocao
        
        bool remover;

    public:

        //construtor e destrutor
        
        explicit Estado(const IDs::IDs ID);
        ~Estado() override;

        //metodos responsaveis pela visualizacao e atualizacao da classe
        
        virtual void executar() = 0;
        void draw() override;

        //metodo que altera oo estado do observador da classe
        
        virtual void mudarEstadoListener(const bool ativo) = 0;
        
        //metodo de acesso ao atributo remover
        
        const bool getRemover();

        //metodo modificacao ao atributo remover
        
        void setRemover();

    };

}
