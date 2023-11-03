#include "../includes/lista/listaEntidade.h"
#include <iostream>


namespace Game{

    namespace Lista{

        ListaEntidade::ListaEntidade():
        objListaEntidade()
        {

        }

        ListaEntidade::~ListaEntidade(){
            limparLista();
        }

        void ListaEntidade::addEntidade(Entidade::Entidade* entidade)
        {
            objListaEntidade.addElemento(entidade);
        }

        void ListaEntidade::addEntidade(Entidade::Entidade* entidade, int pos)
        {
            objListaEntidade.addElemento(entidade, pos);
        }

        void ListaEntidade::removerEntidade(Entidade::Entidade* entidade)
        {
            objListaEntidade.removerElemento(entidade);
        }
            
        void ListaEntidade::removerEntidade(int pos)
        {
            objListaEntidade.removerElemento(pos);
        }

        const int ListaEntidade::getTam(){
            return objListaEntidade.getTam();
        }

        Entidade::Entidade* ListaEntidade::operator[](int pos)
        {
            return objListaEntidade.operator[](pos);
        }

        void ListaEntidade::limparLista()
        {
            objListaEntidade.limparLista();
        }

        void ListaEntidade::executar()
        {
            //atualiza e desenha as entidades
            int tam = objListaEntidade.getTam();
            Entidade::Entidade* aux = nullptr;
            for(int i = tam - 1; i >= 0; i--){
                aux = objListaEntidade.operator[](i);
                if(aux->getRemover())
                {
                    objListaEntidade.removerElemento(aux);
                    delete(aux);
                    aux = nullptr;
                } 
                else 
                {
                    aux->atualizar();
                }
            }
        }

        void ListaEntidade::desenharEntidades()
        {
            //apenas desenha as Entidades
            int tam = objListaEntidade.getTam();
            Entidade::Entidade* aux = nullptr;
            for(int i = 0; i < tam; i++)
            {
                aux = objListaEntidade.operator[](i);
                aux->desenhar();
            }
        }

        /*ListaEntidade::ListaEntidade():
        pInicio(nullptr),pUltimo(nullptr),tam(0)
        {

        }

        ListaEntidade::~ListaEntidade(){
            limparLista();
        }

        void ListaEntidade::addEntidade(Entidade::Entidade* entidade)
        {
            if(entidade == nullptr)
            {
                std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
                exit(1);
            }
            
            ElementoEntidade* novoElemento = new ElementoEntidade();

            if(novoElemento == nullptr)
            {
                std::cout << "ERROR::Lista aux eh nullptr" << std::endl;
                exit(1);
            }
            
            novoElemento->setEntidade(entidade);
            
            if(pInicio == nullptr)
            {
                pInicio = novoElemento;
                pUltimo = novoElemento;
            } 
            
            else 
            {
                pUltimo->setProxEntidade(novoElemento);
                pUltimo = novoElemento;
            }
            tam++;
        }

        void ListaEntidade::addEntidade(Entidade::Entidade* entidade, int pos)
        {
            if(pos > (int)tam || pos < 0)
            {
                std::cout << "ERRO::Lista::posicao nao eh compativel com o tamanho da lista" << std::endl;
                exit(1);
            }
            
            if(entidade == nullptr)
            {
                std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
                exit(1);
            }
            
            ElementoEntidade* novoElemento = new ElementoEntidade();
            
            if(novoElemento == nullptr)
            {
                std::cout << "ERROR::Lista novoElemento eh nullptr" << std::endl;
                exit(1);
            }
            novoElemento->setEntidade(entidade);
            if(pInicio == nullptr){
                pInicio = novoElemento;
                pUltimo = novoElemento;
            } 
            else
            {
                ElementoEntidade* aux = pInicio;
                ElementoEntidade* aux2 = nullptr;
                
                for(int i = 0; i < pos; i++)
                {
                    aux2 = aux;
                    aux = aux->getProxEntidade();
                }
                
                if(aux2 == nullptr)
                {
                    novoElemento->setProxEntidade(aux);
                    pInicio = novoElemento;
                }
                
                else
                {
                    aux2->setProxEntidade(novoElemento);
                    novoElemento->setProxEntidade(aux);
                }
            }
            tam++;
        }

        void ListaEntidade::removerEntidade(Entidade::Entidade* entidade)
        {
            if(entidade == nullptr)
            {
                std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
                exit(1);
            }
            
            ElementoEntidade* aux = pInicio;
            ElementoEntidade* aux2 = nullptr;
            
            while (aux != nullptr && aux->getEntidade() != entidade)
            {
                aux2 = aux;
                aux = aux->getProxEntidade();
            }
            
            if(aux->getEntidade() == entidade)
            {
                if(aux == pInicio)
                {
                    pInicio = aux->getProxEntidade();
                }
                else if(aux == pUltimo)
                {
                    pUltimo = aux2;
                }
                else 
                {
                    aux2->setProxEntidade(aux->getProxEntidade());
                }
                
                delete(aux);
                aux = nullptr;
                aux2 = nullptr;
                
                tam--;
            }
        }
            
        void ListaEntidade::removerEntidade(int pos)
        {
            Entidade::Entidade* elemento = operator[](pos);
            return removerEntidade(elemento);
        }

        const int ListaEntidade::getTam()
        {
            return (int)tam;
        }

        Entidade::Entidade* ListaEntidade::operator[](int pos)
        {
            if(pos >= (int)tam || pos < 0)
            {
                std::cout << "ERROR::Lista pos eh maior que o tamanho da lista" << std::endl;
                exit(1);
            }
            ElementoEntidade* aux = pInicio;
            for(int i = 0; i < pos; i++)
            {
                aux = aux->getProxEntidade();
            }
            
            return aux->getEntidade();
        }

        void ListaEntidade::limparLista()
        {
            if(pInicio != nullptr)
            {
                ElementoEntidade* aux = pInicio;
                ElementoEntidade* aux2 = nullptr;
                unsigned int i = 0;
                while(aux != nullptr && i < tam)
                {
                    Entidade::Entidade* elemento = aux->getEntidade();
                    if(elemento != nullptr)
                    {
                        delete(elemento);
                        elemento = nullptr;
                    }
                    
                    aux2 = aux->getProxEntidade();
                    delete(aux);
                    aux = nullptr;
                    aux = aux2;
                    i++;
                }
            }
            pInicio = nullptr;
            pUltimo = nullptr;
            tam = 0;
        }

        void ListaEntidade::executar()
        {
            //atualiza e desenha as entidades
            int tam = getTam();
            Entidade::Entidade* aux = nullptr;
            
            for(int i = tam - 1; i >= 0; i--)
            {
                aux = operator[](i);
                if(aux->getRemover())
                {
                    removerEntidade(aux);
                    delete(aux);
                    aux = nullptr;
                } 
                else 
                {
                    aux->atualizar();
                }
            }
        }

        void ListaEntidade::desenharEntidades()
        {
            //apenas desenha as Entidades
            int tam = getTam();
            Entidade::Entidade* aux = nullptr;
            for(int i = 0; i < tam; i++)
            {
                aux = operator[](i);
                aux->desenhar();
            }
        }
*/
    }
}

