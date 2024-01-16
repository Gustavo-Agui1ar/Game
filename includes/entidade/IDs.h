
#pragma once

namespace IDs{

        enum class IDs{

            vazio = 0,
           
            //personagens 
            jogador ,
            esqueleto,
            red_slime ,
            plataforma ,
            plataforma_invisivel,
            
            //IDs fases
            caverna,
            forest = 7,
            
            //IDs das armas
            armaDoJogador,
            armaDoIimigo,

            //botoes dos menus
            fundo_menu ,
            botao_novoJogo, 
            botao_carregar_jogo, 
            botao_opcao, 
            botao_sair , 
            botao_voltar, 
            
            //menu para solucionar bug em evento
            menu_bug,

            //botoes dos menus
            botao_salvar , 
            botao_salvar_jogo , 
            botao_carregar , 
            botao_remover ,
            botao_reniciar_jogo,
            botao_volume_efeito_sonoro,
            botao_volume_do_jogo,
            botao_volume_geral,

            //IDs menus

            menu_principal ,
            menu_pause ,
            menu_gameOver ,
            menu_carregar ,
            menu_opcao ,
            menu_salvar 
        };
}
