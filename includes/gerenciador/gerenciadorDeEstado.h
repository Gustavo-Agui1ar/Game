
#pragma once

#include "../States/LevelState.h"
#include "../States/MenuState.h"
#include "../States/DialogueState.h"
#include "gerenciadorDeMusica.h"
#include <stack>


namespace Game::Gerenciador{
    class GerenciadorDeEstado{

    private:

        //pilha de stados
        
        std::stack<State::State*> pilhaEstados;
        
        //construtora

        GerenciadorDeEstado();

        //ponteiros de outros gerenciadores
        
        static GerenciadorDeEstado* pEstado;
        static GerenciadorDeMusica* pMusica;

    public:
        
        //destrutora

        ~GerenciadorDeEstado();
        
        //metodo de acesso a classe
        
        static GerenciadorDeEstado* getGerenciadorDeEstado();
        
        //metodos de adivacao e desativacao de um observer
        
        void desativarListener();
        void ativarListener();

        //metodo que atualiza o estado dwe um objeto desta classe

        void executar();
        
        void addEstado(const IDs::IDs ID);
        void removerEstado();
        
        State::State* getEstadoAtual();
        State::State* getEstado(int qtd);
        void removerEstado(const int quantidade);

    };

}
