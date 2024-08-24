
#include "../includes/entidade/Obstaculo/casa.h"

namespace Game::Entidade::Obstaculo{

    Casa::Casa(const sf::Vector2f tam, const IDs::IDs ID, const sf::Vector2f pos):
    Entidade(tam, ID, pos)
    {

    }

    Casa::~Casa() = default;

    void Casa::update()
    {
        m_pGrafic->desenhaElemento(corpo);
    }

    void Casa::setTextura(const char* caminhoTextura)
    {
        textura = m_pGrafic->carregarTextura(caminhoTextura);

        corpo.setTexture(&textura);
    }

    nlohmann::ordered_json Casa::salvar()
    {
        nlohmann::ordered_json json = salvarEntidade();
        return json;
    }
    
    void Casa::colisao(Entidade* outraEntidade, sf::Vector2f ds)
    {

    }
}