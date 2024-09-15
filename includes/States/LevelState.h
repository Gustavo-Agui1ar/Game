
#pragma once 

#include "State.h"

#include "../gerenciador/gerenciadorGrafico.h"

#include "../Levels/level-1.h"
#include "../Levels/level-2.h"
#include "../Levels/vila.h"

namespace Game::State{
    class LevelState : public State{

    private:
        
        Level::Level* m_level;

    public:

        explicit LevelState(const IDs::IDs ID);
        ~LevelState() override;

        void makeLevel(nlohmann::ordered_json entidades, IDs::IDs IDfase);
        void makeLevel();
        
        void execute() override;

        Level::Level* getLevel();
        
        void changeEstateObserver(const bool ativo) override;

    };

}
