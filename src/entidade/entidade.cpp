#include "../../includes/entidade/entidade.h"

namespace Game{

    namespace Entidade{

        /**
         * costrutora da classe entidade
         *
         * parametros:
         *
         * pos:   inicializa a posi��o do corpo.
         * tam:   inicializa o tamanho do corpo.
         * corpo: inicializa o corpo da entidade.
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
         * metodo que retorna a posicao do corpo da entidade.
         */

        sf::Vector2f Entidade::getPos()
        {
            return pos;
        }

        /**
         * metodo que retorna o tamanho do corpo da entidade.
         */

        sf::Vector2f Entidade::getTam()
        {
            return tam;
        }

        /**
         * metodo que seta a posi��o do corpo da entidade.
         *
         * parametros:
         *
         * pos: valor a ser atribuido a pos de entidade.
         */

        void Entidade::setPos(sf::Vector2f pos)
        {
            corpo.setPosition(pos);
            this->pos = pos;
        }

        /**
         * metodo que desenha o corpo da entidade na tela.
         */

        void Entidade::desenhar()
        {
            pGrafico->desenhaElemento(corpo);
        }

        /**
         * metodo que retorna o estado da variavel remover
        */

        const bool Entidade::getRemover()
        {
            return podeRemover;
        }

        /**
         * metodo  que  altera  o estado da 
         * variavel remover para verdadeiro
        */

        void Entidade::remover()
        {
            podeRemover = true;
        }

        /**
         * metodo que altera/define tamanho 
         * do  atributo  corpo  de entidade
        */

        void Entidade::setTam(const sf::Vector2f tam){
            corpo.setSize(tam);
            this->tam = tam;
        }

        /**
         * destrutora da classe entidade
        */

        Entidade::~Entidade()
        {

        }
    }
}


