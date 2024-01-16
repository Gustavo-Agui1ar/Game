
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
            
            static GerenciadorDeColisao* pColisao;
            GerenciadorDeColisao();
     
        public:

            //construtor e destrutor
           
            static GerenciadorDeColisao* getGerenciadorDeColisao();
            ~GerenciadorDeColisao();

            void setListaPersonagem(Lista::ListaEntidade* personagem);
            void setListaObstaculo( Lista::ListaEntidade* obstaculo);
            void limparListas();
            //metodos de analise de colisao
          
            const sf::Vector2f calculaColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2);
            Entidade::Entidade* procurarEntidade(sf::Vector2f posPersonagem, sf::Vector2f raioDeDistancia, IDs::IDs objProcurado);
            void executar();
        };
    }
}
