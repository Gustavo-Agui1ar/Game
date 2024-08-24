
#pragma once

#include "../gerenciador/gerenciadorDeEstado.h"
#include "../gerenciador/gerenciadorGrafico.h"
#include "../lista/listaListener.h"
#include <iostream>

namespace Game::Gerenciador{
    class GerenciadorDeEventos{


    private:

        //atributo grafico
        
        GerenciadorGrafico *pGrafico;
        
        // ponteiro do gerenciador de estado
    
        GerenciadorDeEstado* pEstado;

        // lista de observers

        static Lista::ListaListener* listaListener;


        //ponteiro que aponta para a classe (padrao singlenton)
        
        static GerenciadorDeEventos *pEventos;

        //construtora
        
        GerenciadorDeEventos();

    public:

        //destrutora
    
        ~GerenciadorDeEventos();
        
        //metodo de acesso a classe
        
        static GerenciadorDeEventos* getGerenciadorDeEventos();

        //metodos de adicao e remocao de um observer

        void removerListener(Listener::Listener* listener);
        void addListener(Listener::Listener* listener);
        
        //metodo de verificacao de eventos
        
        void executar();
    };
}
