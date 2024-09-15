
#pragma once

#include "../Entity/Ente.h"


namespace Game::State{
    class State : public Ente{


    private:
        
        bool m_remove;

    public:
        
        explicit State(const IDs::IDs ID);
        ~State() override;

        virtual void execute() = 0;
        void draw() override;

        virtual void changeEstateObserver(const bool ativo) = 0;
        
        const bool getRemove();

        void setRemove();

    };

}
