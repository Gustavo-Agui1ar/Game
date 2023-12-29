
#pragma once

#include "../gerenciador/gerenciadorDeColisao.h"

#include "../listeners/listenerFase.h"

#include "../Obstaculo/Plataforma.h"

#include "../lista/listaEntidade.h"

#include "../inimigo/esqueleto.h"

#include "../jogador/jogador.h"

#include "../inimigo/slime.h"

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
            
            void mudarEstadoListener(const bool ativo);

            nlohmann::ordered_json salvarFase();
            nlohmann::ordered_json salvarEntidades();

            //metodos de criacao de entidades
            void criarInimigo(const sf::Vector2f pos, const char letra);
            virtual void criarPlataforma(const sf::Vector2f pos) = 0;
            void criarPlataformaInvisivel(const sf::Vector2f pos);
            void criarEntidade(char letra, const sf::Vector2i pos);
            void criarEntidade(IDs::IDs ID, nlohmann::ordered_json entidade , nlohmann::ordered_json arma = nullptr, bool ehPersonagem = true);
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
