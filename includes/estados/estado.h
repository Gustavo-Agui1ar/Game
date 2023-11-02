
#pragma once

#include "../entidade/Ente.h"

namespace Game{

    namespace Estado{

        class Estado : public Ente{


        private:

            bool remover;

        public:

            Estado(const IDs::IDs ID);
            virtual ~Estado();

            virtual void executar() = 0;
            virtual void desenhar();
            
            void setRemover(const bool remover = true);
            const bool getRemover()const;

        };

    }
}