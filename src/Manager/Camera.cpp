#include "../../includes/Manager/camera.h"

#include "../../includes/Manager/GraphicManager.h"

namespace Game::Manager {

    Camera::Camera(const sf::Vector2f sizeWindow):
    m_sizeWindow(sizeWindow), m_camera(sf::Vector2f(sizeWindow.x / 2.0f, sizeWindow.y / 2.0f), sizeWindow)
    {
    
    }

    Camera::~Camera() = default;

    sf::View Camera::getCamera(){
        return m_camera;
    }

    void Camera::reset(const sf::Vector2f posCenter){
        m_camera.setCenter(posCenter);
    }

    void Camera::update(const sf::Vector2f pos){
        m_camera.setCenter(pos);
    }

    void Camera::setSize(sf::Vector2f size)
    {
        m_camera.setSize(size);
    }
}
