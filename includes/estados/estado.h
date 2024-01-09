
#pragma once

#include "../entidade/Ente.h"


namespace Game{

    namespace Estado{

        class Estado : public Ente{


        private:

            //aributo de controle de remocao
         
            bool remover;

        public:

            //construtor e destrutor
           
            Estado(const IDs::IDs ID);
            virtual ~Estado();

            //metodos responsaveis pela visualizacao e atualizacao da classe
           
            virtual void executar() = 0;
            virtual void desenhar();

            //metodo que altera oo estado do observador da classe
         
            virtual void mudarEstadoListener(const bool ativo) = 0;
            
            //metodo de acesso ao atributo remover
          
            const bool getRemover();

            //metodo modificacao ao atributo remover
          
            void setRemover();

        };

    }
}
