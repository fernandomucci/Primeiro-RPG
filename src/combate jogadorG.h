#include "structs.h"
#include "cabecalhoCombate.h"

void CombateJogador(personagem* atacante, personagem* defensor, magiaBase* tipo) {
    atacante->defendendo = 0;

   print_animated("\nTURNO DE %s", atacante->nome);

   mostrarStatus(atacante,defensor);


    int escolhaAtaque, escolhaMagia;
    int danoBase =0;
    int acertou=0;
    
   

   print_animated("\n[1] Usar Magia\n[2] Atacar com Espada\n[3] Defender\nEscolha: ");
    scanf("%d", &escolhaAtaque);

    if (escolhaAtaque == 1) {
       print_animated("\nQual magia? Raio [1] (35 mana, 50 dano) ou Bola de Fogo [2] (25 mana, 30 dano): ");
        scanf("%d", &escolhaMagia);


        // Raio
        if (escolhaMagia == 1 && atacante->mana >= 35) {
            atacante->mana -= 35;

                if(Dados()<=16)
                {
                    danoBase = tipo->Raio;
                   CriticoJogador(&danoBase);
                    acertou++;
                   print_animated("\nVocê lançou Raio!");
                }
                    else{printf("\n ERROU ATAQUE");}
        } 

        // Bola de fogo
        else if (escolhaMagia == 2 && atacante->mana >= 25) {
            atacante->mana -= 25;
                if(Dados()<=16)
                {
                    danoBase = tipo->bolaDeFogo;
                   CriticoJogador(&danoBase);
                    acertou++;
                   print_animated("\nVocê lançou Bola de Fogo!");
                }
                    else{printf("\n ERROU ATAQUE");}
        } else {
           print_animated("Mana insuficiente ou opção inválida!\n");
            return;
        }

    } 
    
    // espada
    else if (escolhaAtaque == 2 && atacante->stamina >= 15) {
        atacante->stamina -= 15;


         if(Dados()<=16)
        { 
           
            danoBase = atacante->ataque;
           CriticoJogador(&danoBase);
            acertou++;
       print_animated("\nVocê atacou com espada!");

        }
             else {printf("\n ERROU O ATAQUE");} 


    // defesa
    } else if (escolhaAtaque == 3) {
        
        if(Dados()<=15)
        {
            atacante->defendendo = 1;
           print_animated("\n%s está se defendendo!\n", atacante->nome);
        }
            
    } else if(escolhaAtaque==3 && Dados>=15){
       print_animated("\n ERROU A DEFESA \n");
    }

    if (defensor->defendendo) {
        danoBase /= 2;
       print_animated("\n%s defendeu! Dano reduzido pela metade.\n", defensor->nome);
    }


    if (acertou) {
       
        int danoFinal = CalculoDano(&danoBase, defensor->defesa,defensor->defendendo);
        defensor->hp -= danoFinal;

       

       print_animated("\nDano base: %d | Bloqueado pela defesa: %d | Dano final: %d\n", danoBase, defensor->defesa, danoFinal);
    }




    //status final do personagem

    mostrarStatus(atacante,defensor);
}
