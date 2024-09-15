#pragma once

#include "../../../gerenciador/gerenciadorGrafico.h"
#include "../../Weapon/Bullet.h"
#include "json.hpp"

#define TIME_BULLET_PLAYER 0.9f

namespace Game::Entity::Character::Player {

    class Player;

    namespace Skils {
    
        class FireBall {

        private:

          Gerenciador::GerenciadorGrafico *m_graphic;
          Player* m_player;

          Weapon::Bullet* m_bullet;
          bool m_trhowBullet;
          const float m_timeAnimationBullet;
          float m_timeTrhowBullet;


        public:
            
          explicit FireBall(Player* player);
          ~FireBall();

          void updateBullet();
          void setBullet(Weapon::Bullet* bullet);
          void trhowBullet();
          void drawFireBall();

          bool getTrhowBullet();
          void setFireBallDamage(float damage);
          void setTimeTrhowBullet(float time);
          void setTrhowBullet(bool trhow);

          nlohmann::ordered_json saveFireBall(nlohmann::ordered_json json);
        };
    }
}