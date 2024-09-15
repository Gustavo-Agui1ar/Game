
#pragma once 

#include "../includes/gerenciador/gerenciadorGrafico.h"
#include "../gerenciador/gerenciadorDeEstados.h"
#include "../includes/Entity/Entity.h"
#include "House.h"

namespace Game::Entity::Obstacle{

  class Door : public Entity{
    private:
      Gerenciador::GerenciadorDeEstados* m_gerenciadorDeEstados;
      sf::Texture m_texture;
      House* m_house;
      bool m_open;
      bool m_locked;
      bool m_key;
    
    public:
      Door(sf::Vector2f position, sf::Vector2f size, IDs::IDs ID, IDs::IDs IDTexture, House* house);
      ~Door() override;
      
      void collision(Entity* otherEntity, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
      void update() override;
      nlohmann::ordered_json save() override;
      void open();

      void setKey(bool key);
      void setLocked(bool locked);
      void setOpen(bool open);

      bool getKey();
      bool getLocked();
      bool getOpen();

      
  };
}