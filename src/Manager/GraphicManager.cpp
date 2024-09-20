
#include "../../includes/Manager/GraphicManager.h"
#include <iostream>


namespace Game::Manager{

    GraphicManager* GraphicManager::m_graphicManager = nullptr;
    float GraphicManager::m_time = 0.0f;

    GraphicManager::GraphicManager():
    m_window(new sf::RenderWindow (sf::VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), "Son of Storm")),
    m_clock(), m_camera(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN))
    {
        if(m_window == nullptr)
        {
            std::cout<<"Manager::GraphicManager::not possible to create the window"<<std::endl;
            exit(1);
        }
    }

    GraphicManager::~GraphicManager()
    {
        if(m_window)
        {
            delete m_window;
            m_window = nullptr;
        }
        m_graphicManager = nullptr;
    }

    void GraphicManager::resetClock()
    {
        m_time = m_clock.getElapsedTime().asSeconds();
        m_clock.restart();
    }

    const float GraphicManager::getTime()
    {
        return m_time;
    }

    GraphicManager* GraphicManager::getGraphicManager()
    {
        if(m_graphicManager == nullptr)
            m_graphicManager = new GraphicManager();

        return m_graphicManager;
    }

    sf::RenderWindow* GraphicManager::getWindow()
    {
        return m_window;
    }

    void GraphicManager::clearWindow()
    {
        m_window->clear();
    }

    void GraphicManager::drawElement(sf::RectangleShape corpo)
    {
        m_window->draw(corpo);
    }

    void GraphicManager::showElements()
    {
        m_window->display();
    }

    void GraphicManager::closeWindow()
    {
        m_window->close();
    }

    const bool GraphicManager::checkIsOpenWindow()
    {
        if(m_window->isOpen())
            return true;

        return false;
    }

    sf::Texture GraphicManager::loadTexture(const char* caminhoTextura)
    {
        sf::Texture textura;

        if(!textura.loadFromFile(caminhoTextura)){
            std::cout<<"Manager::GraphicManager::not possible to load the texture"<<std::endl;
            exit(1);
        }
        return textura;
    }

    sf::Font GraphicManager::loadFont(const char* caminhoFonte){
        sf::Font fonte;
        if(!(fonte.loadFromFile(caminhoFonte)))
        {
            std::cout<<"ERROR::Game:Manager::GrphicManager::not possible to load the font"<<std::endl;
            exit(1);
        }
        return fonte;
    }

    void GraphicManager::updateCamera(sf::Vector2f position)
    {
        m_camera.update(sf::Vector2f(position));
        m_window->setView(m_camera.getCamera());
    }

    sf::View GraphicManager::getCamera()
    {
        return m_camera.getCamera();
    }

    const sf::Vector2f GraphicManager::getSizeWindow(){
        return sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN);
    }

    void GraphicManager::drawElement(sf::Text text)
    {
        m_window->draw(text);
    }

    void GraphicManager::resetWindow(){
        m_camera.reset(sf::Vector2f(WIDTH_SCREEN / 2.0f, HEIGHT_SCREEN / 2.0f));
        m_window->setView(m_camera.getCamera());
    }

    void GraphicManager::setSizeCamera(sf::Vector2f size)
    {
        m_camera.setSize(size);
    }
}