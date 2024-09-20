#include "../includes/List/EntityList.h"
#include <iostream>


namespace Game::List{

        EntityList::EntityList():
        m_entityList()
        {

        }

        EntityList::~EntityList()
        {
            m_entityList.clearList();
        }

        void EntityList::add(Entity::Entity* entity)
        {
            m_entityList.add(entity);
        }
        
        void EntityList::add(Entity::Entity* entity, int pos)
        {
            m_entityList.add(entity, pos);
        }
        
        void EntityList::remove(Entity::Entity* entity)
        {
            m_entityList.remove(entity);
        }

        void EntityList::remove(int pos)
        {
            m_entityList.remove(pos);
        }
        
        const int EntityList::getSize(){
            return m_entityList.getSize();
        }

        Entity::Entity* EntityList::operator[](int pos)
        {
            return m_entityList.operator[](pos);
        }

        void EntityList::clearList()
        {
            m_entityList.clearList();
        }

        void EntityList::execute()
        {
            int size = m_entityList.getSize();
            Entity::Entity* entity = nullptr;
            for(int i = size - 1; i >= 0; i--)
            {
                entity = m_entityList.operator[](i);
                if(entity->getRemove())
                {
                    m_entityList.remove(i);
                    delete entity;
                    entity = nullptr;
                } 
                else 
                {
                    entity->update();
                }
            }
        }

        void EntityList::drawEntitys()
        {
            int size = m_entityList.getSize();
            Entity::Entity* entity = nullptr;
            for(int i = size - 1 ; i >= 0 ; i--)
            {
                entity = m_entityList.operator[](i);
                entity->draw();
            }
        }

}