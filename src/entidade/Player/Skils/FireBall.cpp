#include "../includes/entidade/Player/Skils/FireBall.h"
#include "../includes/entidade/Player/Player.h"

namespace Game::Entidade::Character::Player::Skils{
  
  FireBall::FireBall(Player* player) :  m_graphic(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),
  m_player(player), m_bullet(nullptr), m_trhowBullet(false), m_timeAnimationBullet(TIME_BULLET_PLAYER),
  m_timeTrhowBullet(0.0f) {

  }

  FireBall::~FireBall() {
    m_bullet = nullptr;
    m_player = nullptr;
  }

      
  void FireBall::updateBullet() {
    
    if (m_player->getAttacking() && !(m_player->getDie()) && m_trhowBullet) {
      
      m_timeTrhowBullet += m_graphic->getTempo();
      
      if (m_timeTrhowBullet > m_timeAnimationBullet) {
        m_player->setAttacking(false);
        m_trhowBullet = false;
        m_timeTrhowBullet = 0.0f;
      }
      
      else if (m_timeTrhowBullet > (m_timeAnimationBullet / 4) * 3) {
      
        float player_x = m_player->getDirection() ? (m_player->getPos().x - 29.0f) : (m_player->getPos().x + m_player->getTam().x + 15.0f);
        m_bullet->setPos(sf::Vector2f(player_x, (m_player->getPos().y + m_player->getTam().y / 3.0f) + 10.0f));
        m_bullet->setCollision(false);
        m_bullet->setSpeed(sf::Vector2f(350.0f, 0.0f));
        m_bullet->setDirection(m_player->getDirection());
      }
    }
  }

  void FireBall::setBullet(Weapon::Bullet* bullet) {
    m_bullet = bullet;
  }

  void FireBall::trhowBullet() {
    if (m_bullet->getCollision()) {
      m_player->stop();
      m_player->consumeStamina((MAX_STAMINA / 5) * 2);
      m_trhowBullet = true; 
      m_player->setAttacking(true);
    }
  }

  nlohmann::ordered_json FireBall::saveFireBall(nlohmann::ordered_json json) {
      json["lancandoProjetil"] = m_trhowBullet;
      json["tempoAtaqueProjetil"] = m_timeTrhowBullet;
      json["tempoAnimacaoAtaque"] = m_timeAnimationBullet;
      return json;
  }

  void FireBall::drawFireBall() {
      m_bullet->draw();
  }

  bool FireBall::getTrhowBullet() {
    return m_trhowBullet;
  }

  void FireBall::setFireBallDamage(float damage) {
    m_bullet->setDamage(damage);
  }

  void FireBall::setTimeTrhowBullet(float time) {
      m_timeTrhowBullet = time;
  }

  void FireBall::setTrhowBullet(bool trhow) {
    m_trhowBullet = trhow;
  }
}