
#pragma once 

#include "State.h"
#include "../Levels/Level.h"
#include "../menus/menu.h"


namespace Game{

    namespace Manager{

        class StateManager;
    }

    namespace State{

        class MenuState : public State{

            private:

                static Manager::StateManager* m_stateManager;

                Menu::Menu* m_menu;
                
               void makeMenu();

            public:

                explicit MenuState(const IDs::IDs ID);
                ~MenuState() override;

                void changeEstateObserver(const bool ativo) override;
                
                void makeMainMenu();
                void makePauseMenu(Level::Level* fase);
                void makeSaveMenu(Level::Level* fase);
                void makeLoadMenu(Level::Level* fase);
                void makeBugMenu(Level::Level* fase);
                void makeSelectFaseMenu(Level::Level* fase);
                void makeOptionMenu(Level::Level* fase);
                void makeGameOverMenu(Level::Level* fase);

                Menu::Menu* getMenu();
                Level::Level* getFase();

                void execute() override;
        };

    }

}