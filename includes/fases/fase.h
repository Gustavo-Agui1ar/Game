
#pragma once

#include "../includes/gerenciador/gerenciadorDeColisao.h"

#include "../listeners/listenerFase.h"

#include "../includes/entidade/Obstaculo/Plataforma.h"

#include "../lista/listaEntidade.h"

#include "../includes/entidade/inimigo/esqueleto.h"

#include "../includes/entidade/inimigo/arqueiro.h"

#include "../includes/entidade/jogador/jogador.h"

#include "../includes/entidade/inimigo/slime.h"

#include "../fundo/fundo.h"

namespace Game{

    namespace Fase{

        class Fase : public Ente{

        protected:
            static Listener::ListenerFase* listenerFase;

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
            
            //metodo que altera o estado do observador da classe
          
            void mudarEstadoListener(const bool ativo);

            //metodo que salva o estado de um objeto desta classe
           
            nlohmann::ordered_json salvarFase();

            //metodo que salva o estado das entidades  da listaPersonagens e listaObstaculos
           
            nlohmann::ordered_json salvarEntidades();

            //metodos responaveis por criar as respectivas entidades 
         
            void criarEntidade(IDs::IDs ID, nlohmann::ordered_json entidade , nlohmann::ordered_json arma = nullptr, nlohmann::ordered_json arma2 = nullptr);
            void criarInimigo(const sf::Vector2f pos, const char letra);
            virtual void criarPlataforma(const sf::Vector2f pos) = 0;
            void criarEntidade(char letra, const sf::Vector2i pos);
            void criarPlataformaInvisivel(const sf::Vector2f pos);
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
