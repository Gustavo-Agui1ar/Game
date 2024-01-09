
#include "../includes/arma/arma.h"
#include "../includes/inimigo/inimigo.h"

namespace Game{

    namespace Entidade{

        namespace Item{


                /**
                 * @brief construtora da classe arma
                 * 
                 * @param ID variavel de indentificacao da classe arma alemde nescessario para costrutora de ente
                 * 
                */
                Arma::Arma(IDs::IDs ID):
                Entidade(sf::Vector2f(-1000.0f, -1000.0f),ID)
                {
                    dano = 0.0f;
                }

                /**
                 * @brief construtora da classe arma
                 * 
                 * @param atributos variavel que contem todas as informacoes dos atributos da classe jogador
                 * 
                */
                Arma::Arma(nlohmann::ordered_json atributos):
                Entidade(sf::Vector2f(-1000.0f, -1000.0f), (atributos["ID"].template get<IDs::IDs>()))
                {
                    try{
                        dano = atributos["dano"].template get<float>();
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
                Arma::~Arma()
                {

                }

                /**
                 * @brief metodo que define o valor do 
                 * atributo dano da classe arma
                */
                void Arma::setDano(const float dano)
                {
                    this->dano = dano;
                }

                /**
                 * @brief metodo que retorna o atributo dano de arma.
                */
                const float Arma::getDano()
                {
                    return dano;
                }

                /**
                 * @brief metodo que trata da colisao da arma
                 * com outtras entidades dependendo de 
                 * seu id.
                 * 
                 * @param outraEntidade entidade a verificar colisao
                 * @param ds distancia entre os centros de arma e outra entidade. 
                */
                void Arma::colisao(Entidade* outraEntidade, sf::Vector2f ds)
                {
                    if(ID == IDs::IDs::armaDoJogador)
                    {
                        if(outraEntidade->getID() == IDs::IDs::red_slime ||
                           outraEntidade->getID() == IDs::IDs::esqueleto)
                        {
                            Personagem::Inimigo::Inimigo* inimigo = static_cast<Personagem::Inimigo::Inimigo*>(outraEntidade);
                            if(!inimigo->getMorrer())
                            {
                                inimigo->tomarDano(dano);
                            }
                        }
                    }
                }

                /**
                 * @brief metodo que serve para definir  a  nao  vizualizacao  da arma  por se tratar apenas de uma  hitbox
                */
                void Arma::desenhar()
                {

                }

                /**
                 * @brief metodo de atualizacao definido para respeitar o virtual de entidade 
                 * porem  executado  de jeitos   diferentes   por  inimigo  e  jogador
                */
                void Arma::atualizar()
                {

                }

                /**
                 * @brief metodo que salva as informacoes de um objeto da classe arma
                 * 
                 * @return retorna um json contendo todasas informacoes do estado de um objeto arma
                */
                nlohmann::ordered_json Arma::salvar()
                {
                    nlohmann::ordered_json json = salvarEntidade();
                    json["dano"] = dano;

                    return json;
                }

        }
    }
}
