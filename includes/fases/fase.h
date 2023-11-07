
#pragma once

#include "../gerenciador/gerenciadorDeColisao.h"

#include "../listeners/listenerFase.h"

#include "../Obstaculo/Plataforma.h"

#include "../lista/listaEntidade.h"

#include "../inimigo/esqueleto.h"

#include "../jogador/jogador.h"

#include "../inimigo/slime.h"

#include "../fundo/fundo.h"

#include <fstream>

namespace Game{

    namespace Fase{

        class Fase : public Ente{

        protected:
            
            Listener::ListenerFase* listenerFase;

            //listas de entidades
            Lista::ListaEntidade* listaPersonagens;
            Lista::ListaEntidade* listaObstaculos;
            Entidade::Personagem::Jogador::Jogador* jogador;

            //objeto responsavel pela verificacao da colisao entre entidades
            Gerenciador::GerenciadorDeColisao* pColisao;
            
            //objeto responsavel poer criar o fundo da fase
            Fundo::Fundo fundo;

        public:   

            //contrutor e destrutor
            Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo);
            virtual ~Fase();
            
            void mudarEstadoListener();

            //metodos de criacao de entidades
            void criarInimigo(const sf::Vector2f pos, const char letra);
            virtual void criarPlataforma(const sf::Vector2f pos) = 0;
            void criarEntidade(char letra, const sf::Vector2i pos);
            void criarJogador(const sf::Vector2f pos);
            
            //metodos criadores de mapas da fase
            virtual void criarFundo() = 0;
            virtual void criarMapa() = 0;
            
            //metodo que retorna o jogador da fase
            Entidade::Personagem::Jogador::Jogador* getJogador();
            
            //metodos de atualizacao e vizualizacao
            void executar();
            void desenhar();

        };
    }
}
