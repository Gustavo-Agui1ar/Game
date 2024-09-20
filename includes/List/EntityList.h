
#pragma once

#include  "../List/List.h"
#include  "../Entity/Entity.h"


namespace Game::List{
    class EntityList {

    private:

        List<Entity::Entity> m_entityList;
    public:

        EntityList();
        ~EntityList();
    
        void add(Entity::Entity* entity, int pos);
        void add(Entity::Entity* entity);
        
        void remove(Entity::Entity* entity);
        void remove(int pos);
        
        Entity::Entity* operator[](int pos);
        const int getSize();
        
        void clearList();
        
        void drawEntitys();
        void execute();

    };
}