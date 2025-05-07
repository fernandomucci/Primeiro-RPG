#include "structs.h"
#include "cabecalhoCombate.h"


void CombateInimigo(personagem* atacante, personagem* defensor, magiaBase* tipo) {
    atacante->defendendo = 0;

   print_animated("\n TURNO INIMIGO!!!\n2");


    

    int escolha = rand() % 3 + 1;
    int danoBase = 0,acertou=0;

    if (escolha == 1) {
        int magiaEscolhida = (rand() % 2) + 1;

        // Raio inimigo 
        if (magiaEscolhida == 1 && atacante->mana >= 35) {
            atacante->mana -= 35;

            if(Dados()<=13)
            {
                 danoBase = tipo->Raio;
                 CriticoInimigo(&danoBase);
                 acertou++;

                print_animated("\n%s lançou Raio!", atacante->nome);
            }
                else{printf("\n INIMIGO ERROU ATAQUE");}
        }

        // Bola de fogo inimigo
        else if (magiaEscolhida == 2 && atacante->mana >= 25) {
            atacante->mana -= 25;

            if(Dados()<=13)
            {
                danoBase = tipo->bolaDeFogo;
                CriticoInimigo(&danoBase);
                acertou++;
               print_animated("\n%s lançou Bola de Fogo!", atacante->nome);
            }
            else{printf("\n INIMIGO ERROU ATAQUE");}

        } else {
            escolha = 2; // se não tiver mana, vai pra espada
        }
    }
       
    //ataque espada inimigo
    if (escolha == 2  && atacante->stamina >= 15 && danoBase==0) {
        atacante->stamina -= 15;
        if(Dados()<=13)
        {
            danoBase = atacante->ataque;
            CriticoInimigo(&danoBase);
            acertou++;
           print_animated("\n%s atacou com espada!", atacante->nome);
        }
        else{printf("\n INIMIGO ERROU ATAQUE");}
    } 
    
    // defesa inimigo
    else if (escolha == 3 || (atacante->stamina < 15 && danoBase==0)) {

        if(Dados()<=9)
        {
        atacante->defendendo = 1;
       print_animated("\n%s está se defendendo!\n", atacante->nome);
        }
        else{printf("\n INIMIGO ERROU A DEFESA");}
    }

    if (acertou) {
        if (defensor->defendendo) {
            danoBase /= 2;
           print_animated("\n%s defendeu! Dano reduzido pela metade.\n", defensor->nome);
        }

        int danoFinal = CalculoDano(&danoBase, defensor->defesa,defensor->defendendo);
        defensor->hp -= danoFinal;

        

       print_animated("\nDano base: %d | Bloqueado pela defesa: %d | Dano final: %d\n", danoBase, defensor->defesa, danoFinal);
    

        
    }

    mostrarStatus(atacante,defensor);
}