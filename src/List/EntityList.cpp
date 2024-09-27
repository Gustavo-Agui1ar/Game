#include "../includes/List/EntityList.h"
#include <iostream>


namespace Game::List{

        EntityList::EntityList():
        m_entityList()
        {

        }

        EntityList::~EntityList() {
            m_entityList.clearList();
        }

        void EntityList::add(Entity::Entity* entity) {
            m_entityList.add(entity);
        }
        
        void EntityList::add(Entity::Entity* entity, int pos)  {
            m_entityList.add(entity, pos);
        }
        
        void EntityList::remove(Entity::Entity* entity) {
            m_entityList.remove(entity);
        }

        void EntityList::remove(int pos) {
            m_entityList.remove(pos);
        }
        
        const int EntityList::getSize() {
            return m_entityList.getSize();
        }

        Entity::Entity* EntityList::operator[](int pos) {
            return m_entityList.operator[](pos);
        }

        void EntityList::clearList() {
            m_entityList.clearList();
        }

        void EntityList::execute() {   
            for(auto it = m_entityList.begin(); it != m_entityList.end(); it++) {
                if((*it)->getRemove()) {
                    m_entityList.remove(*it);
                    delete (*it);
                } 
                else 
                    (*it)->update();
            }
        }

        void EntityList::drawEntitys() {
            for(auto it = m_entityList.begin(); it != m_entityList.end(); it++)
                (*it)->draw();
        }
}