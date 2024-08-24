#include "../includes/entidade/entidade.h"

namespace Game::Entidade{


    /**
     * @brief costrutora da classe entidade
     *
     * @param pos posicao do corpo.
     * @param tam tamanho do corpo.
     * @param ID identificacao do objeto da classe.
     */
    Entidade::Entidade(const sf::Vector2f tam,const IDs::IDs ID, const sf::Vector2f pos):
    Ente(ID)
    {
        corpo = sf::RectangleShape(tam);
        corpo.setPosition(pos);
        this->tam = tam;
        this->pos = pos;
        podeRemover = false;
    }

    /**
     * @brief metodo de acesso a posicao do corpo.
     * 
     * @return retorna a posicaop do corpo de entidade
     */
    sf::Vector2f Entidade::getPos()
    {
        return pos;
    }

    /**
     * @brief metodo de acesso ao tamanho do corpo.
     * 
     * @return retorna o tamanho do corpo de entidade
     */
    sf::Vector2f Entidade::getTam()
    {
        return tam;
    }

    /**
     * @brief metodo que modifica posicao do corpo.
     *
     * @param pos valor a ser atribuido como posicao vdo corpo.
     */

    void Entidade::setPos(sf::Vector2f pos)
    {
        corpo.setPosition(pos);
        this->pos = pos;
    }

    /**
     * @brief metodo que desenha a entidade na tela.
     */
    void Entidade::draw()
    {
        m_pGrafic->desenhaElemento(corpo);
    }

    /**
     * @brief  metodo qde acesso ao atributo remover
     * 
     * @return retorna o estado do boleano remover 
    */
    const bool Entidade::getRemover()
    {
        return podeRemover;
    }

    /**
     * @brief metodo  que  altera  o estado da 
     * variavel remover para verdadeiro
    */
    void Entidade::remover()
    {
        podeRemover = true;
    }

    /**
     * @brief metodo que define o tamanho 
     * do atributo tam de entidade
    */
    void Entidade::setTam(const sf::Vector2f tam){
        corpo.setSize(tam);
        this->tam = tam;
    }

    /**
     * @brief destrutora da classe entidade
    */
    Entidade::~Entidade() = default;

    /**
     * @brief metodo que salva o estado de um objeto desta classe
     * 
     * @return retorna um json contendo o estado atual de um objeto desta classe
    */
    nlohmann::ordered_json Entidade::salvarEntidade()
    {
        nlohmann::ordered_json json = salvarEnte();

        json["tam"] = {{"x", getTam().x}, {"y", getTam().y}};
        json["pos"] = {{"x", getPos().x}, {"y", getPos().y}};
        json["remover"] = getRemover();

        return json;
    }
}


