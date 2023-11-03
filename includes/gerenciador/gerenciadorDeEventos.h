
#pragma once

#include "../gerenciador/gerenciadorDeEstado.h"
#include "../gerenciador/gerenciadorGrafico.h"
#include <iostream>

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeEventos{


        private:

            //atributo grafico
            GerenciadorGrafico *pGrafico;
            GerenciadorDeEstado* pEstado;

            //ponteiro responsavel por 'distribuir' a classe 
            static GerenciadorDeEventos *pEventos;

            //construtora
            GerenciadorDeEventos();

        public:

            //destrutora
            ~GerenciadorDeEventos();
            
            //metodo de acesso a classe
            static GerenciadorDeEventos* getGerenciadorDeEventos();
            
            //metodos de tratamentoo de eventos
            void verificaTeclaPresionada(sf::Keyboard::Key tecla);
            void verificaTeclaSolta(sf::Keyboard::Key tecla);
            
            //metodo de verificacao de eventos
            void executar();
        };
    }
}
