
#pragma once

#include "../gerenciador/gerenciadorDeEstado.h"
#include "../gerenciador/gerenciadorGrafico.h"
#include "../lista/listaListener.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeEventos{


        private:

            //atributo grafico
            GerenciadorGrafico *pGrafico;
            GerenciadorDeEstado* pEstado;
            static Lista::ListaListener* listaListener;


            //ponteiro responsavel por 'distribuir' o mesmo objeto a outras classes (padrao singlenton)
            static GerenciadorDeEventos *pEventos;

            //construtora
            GerenciadorDeEventos();

        public:

            //destrutora
            ~GerenciadorDeEventos();
            
            //metodo de acesso a classe
            static GerenciadorDeEventos* getGerenciadorDeEventos();

            void removerListener(Listener::Listener* listener);
            void addListener(Listener::Listener* listener);
            
            //metodo de verificacao de eventos
            void executar();
        };
    }
}
