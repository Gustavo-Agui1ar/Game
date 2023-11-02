
#pragma once

#include <SFML/Graphics.hpp>
#include "../lista/listaEntidade.h"
#include <cmath>

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeColisao{
        private:

            //atributo lista de entidades a serem analizadas 
            Lista::ListaEntidade* listaPersonagem;
            Lista::ListaEntidade* listaObstaculo;

        public:

            //construtor e destrutor
            GerenciadorDeColisao( Lista::ListaEntidade* personagem, Lista::ListaEntidade* obstaculo);
            ~GerenciadorDeColisao();

            //metodos de analise de colisao
            const sf::Vector2f calculaColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2);
            void executar();
        };
    }
}
