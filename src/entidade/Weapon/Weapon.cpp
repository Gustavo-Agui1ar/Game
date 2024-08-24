
#include "../includes/entidade/Weapon/Weapon.h"
#include "../includes/entidade/Enemy/Enemy.h"

namespace Game::Entidade::Weapon{

    /**
     * @brief construtora da classe arma
     * 
     * @param ID variavel de indentificacao da classe arma alemde nescessario para costrutora de ente
     * 
    */
    Weapon::Weapon(IDs::IDs ID):
    Entidade(sf::Vector2f(-1000.0f, -1000.0f),ID)
    {
        m_damage = 0.0f;
    }

    /**
     * @brief construtora da classe arma
     * 
     * @param atributos variavel que contem todas as informacoes dos atributos da classe jogador
     * 
    */
    Weapon::Weapon(nlohmann::ordered_json atributos):
    Entidade(sf::Vector2f(-1000.0f, -1000.0f), (atributos["ID"].template get<IDs::IDs>()))
    {
        try{
            m_damage = atributos["dano"].template get<float>();
            setPos(sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>()));
            setTam(sf::Vector2f(atributos["tam"]["x"].template get<float>(), atributos["tam"]["y"].template get<float>()));
        
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            podeRemover = true;
        }
    }


    /**
     * @brief destrutora da classe arma
    */
    Weapon::~Weapon() = default;

    /**
     * @brief metodo que define o valor do 
     * atributo dano da classe arma
    */
    void Weapon::setDamage(const float damage)
    {
        m_damage = damage;
    }

    /**
     * @brief metodo que retorna o atributo dano de arma.
    */
    const float Weapon::getDamage()
    {
        return m_damage;
    }

    /**
     * @brief metodo que trata da colisao da arma
     * com outtras entidades dependendo de 
     * seu id.
     * 
     * @param outraEntidade entidade a verificar colisao
     * @param ds distancia entre os centros de arma e outra entidade. 
    */
    void Weapon::colisao(Entidade* outraEntidade, sf::Vector2f ds)
    {
        if(ID == IDs::IDs::armaDoJogador && (outraEntidade->getID() == IDs::IDs::red_slime ||
        outraEntidade->getID() == IDs::IDs::esqueleto))
        {      
            auto *inimigo = static_cast<Character::Enemy::Enemy*>(outraEntidade);
            if(!inimigo->getDie())
            {
                inimigo->takeDamage(m_damage);
            }
        }
    }

    /**
     * @brief metodo que serve para definir  a  nao  vizualizacao  da arma  por se tratar apenas de uma  hitbox
    */
    void Weapon::draw()
    {
        //hitbox
    }

    /**
     * @brief metodo de atualizacao 
    */
    void Weapon::update()
    {
        //empty update
    }

    /**
     * @brief metodo que salva as informacoes de um objeto da classe arma
     * 
     * @return retorna um json contendo todasas informacoes do estado de um objeto arma
    */
    nlohmann::ordered_json Weapon::salvar()
    {
        nlohmann::ordered_json json = salvarEntidade();
        json["dano"] = m_damage;

        return json;
    }
    
    /**
     * @brief metodo que salva as informacoes de um objeto da classe arma
     * 
     * @return retorna um json contendo todasas informacoes do estado de um objeto arma
    */
    nlohmann::ordered_json Weapon::salvarArma()
    {
        nlohmann::ordered_json json = salvarEntidade();
        json["dano"] = m_damage;

        return json;
    }
}
