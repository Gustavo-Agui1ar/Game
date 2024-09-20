
#pragma once

#include "../includes/menus/botao/balaoDeFala.h"
#include <list>

namespace Game{

    namespace Observer{

        class ObserverDialogue;
    }

    namespace Manager{

        class DialogueManager{

        private:

            std::list<Menu::Botao::BalaoDeFala*> m_dialogues;
            std::list<Menu::Botao::BalaoDeFala*>::iterator m_currentDialogue;

            bool m_endLastTalk;
            bool m_nameLeft;

            Observer::ObserverDialogue* m_observerDialogue;

            void bootDialogues(std::vector<std::string> names, std::vector<std::string> talks);

        public:

            DialogueManager(std::vector<std::string> names, std::vector<std::string> talks);
            ~DialogueManager();

            void changeObserverState(const bool ative);

            void skipDialogue();
            void nextTalk();

            void update();
            void draw();

            const bool getEndLastTalk();
            const bool getEndCurrentTalk();

        };
    }
}