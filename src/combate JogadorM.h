#include "structs.h"
#include "cabecalhoCombate.h"

void CombateJogadorM(Mago* atacante, personagem* defensor, MagiasMagos* tipo) {
    atacante->defendendo = 0;
    

    print_animated("\nTURNO DE %s", atacante->nome);

    mostrarStatusM(defensor,atacante);
 
 
     int escolhaAtaque, escolhaMagia;
     int danoBase =0;
     int acertou=0;
     
    
 
    print_animated("\n[1] Usar Magia\n[2] Atacar com Espada\n[3] Defender\nEscolha: ");
     scanf("%d", &escolhaAtaque);

     if(escolhaAtaque==1)
     {
        print_animated("\nQual magia? Raio [1] (35 mana, 90 dano)\nBola de Fogo [2] (25 mana, 70 dano)\n[3]Gravidade(80 mana, 120)\n[4]Buraco Negro(100 mana, 160): ");
        scanf("%d", &escolhaMagia);

            if(escolhaMagia==1 && atacante->mana>=35)
            {
                atacante->mana-=35;

                if(Dados()<=16)
                {
                    danoBase = tipo->raio;
                   CriticoJogador(&danoBase);
                    acertou++;
                   print_animated("\nVocê lançou Raio!");
                }
                    else{printf("\n ERROU ATAQUE");}
            }else if(escolhaMagia==2 && atacante->mana>=25)
            {
                atacante->mana-=25;

                if(Dados()<=16)
                {
                    danoBase = tipo->bolaDeFogo;
                    CriticoJogador(&danoBase);
                    acertou++;
                    print_animated("\n você lançou Bola de fogo!");

                }else {printf("\n ERROU ATAQUE");}
            }else if(escolhaMagia==3 && atacante->mana>=80)
            {
                    atacante->mana-=80;

                    if(Dados()<=16)
                    {
                        danoBase = tipo->gravidade;
                        CriticoJogador(&danoBase);
                        acertou++;
                        print_animated("\n você lançou Gravidade");
                    }
                        else {printf("\n ERROU O ATAQUE");}

            }else if(escolhaMagia==4 && atacante->mana>=100)
            {
                atacante->mana-=100;

                if(Dados()<=16)
                {
                    danoBase = tipo->buracoNegro;
                    CriticoJogador(&danoBase);
                    acertou++;
                    print_animated("\n você lançou Buraco Negro");
                }
                        else{printf("\n ERROU ATAQUE");}

            }else{ 

             print_animated("Mana insuficiente ou opção inválida!\n");
            return;
                 }

        } else if (escolhaAtaque == 2 && atacante->stamina >= 15) {
            atacante->stamina -= 15;
    
    
             if(Dados()<=16)
            { 
               
                danoBase = atacante->ataque;
               CriticoJogador(&danoBase);
                acertou++;
           print_animated("\nVocê atacou com espada!");
    
            }
                 else {printf("\n ERROU O ATAQUE");} 

     }
else if (escolhaAtaque == 3) {
        
        if(Dados()<=15)
        {
            atacante->defendendo = 1;
           print_animated("\n%s está se defendendo!\n", atacante->nome);
        }
            
    } else {
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

    mostrarStatusM(defensor,atacante);

} 
