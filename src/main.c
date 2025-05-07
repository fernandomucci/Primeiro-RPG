#include "cabecalhoCombate.h"
#include "combate inimigo.h"
#include "combate jogadorG.h"
#include "combate jogadorM.h"
#include "structs.h"
#include "combate inimigo mago.h"


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");

   print_animated("\n RPG basico de turno");

    Mago jogadorM = {"Jogador", 75,30, 35, 125, 15, 0};
    personagem jogadorG = {"Jogador", 100, 35, 30, 125, 75, 0};
    personagem inimigo = {"inimigos", 200, 30, 25, 100, 70, 0};

    Mago* ptrMago = &jogadorM;
    personagem* ptrjogador = &jogadorG;
    personagem* ptrinimigo = &inimigo;    

    magiaBase tiposMagia = {70, 50};
    magiaBase* ptrmagia = &tiposMagia;

    MagiasMagos tiposMagiaM = {90, 70, 120, 160};
    MagiasMagos* ptrmagiaM = &tiposMagiaM;

    int personagem=0;
    int turno = 0;
    barra_progresso(3);

    printf("<------------------------>\nESCOLA SUA CLASSE\n[1] GUERREIRO\n[2]MAGO");
    scanf("%d",&personagem);
    if(personagem==1)
    {
        while (jogadorG.hp > 0 && inimigo.hp > 0) {
             if (turno % 2 == 0) {
                 CombateJogador(&jogadorG, &inimigo, ptrmagia);
                    } else {
                      CombateInimigo(&inimigo, &jogadorG, ptrmagia);
                    }
                     turno++;
         }
}else if(personagem==2)
{
    while (jogadorM.hp > 0 && inimigo.hp > 0) {
        if (turno % 2 == 0) {
            CombateJogadorM(&jogadorM, &inimigo, ptrmagiaM);
               } else {
                 CombateInimigoM(&inimigo, &jogadorM, ptrmagia);
               }
                turno++;
    }
}

    if (jogadorM.hp <= 0 || jogadorG.hp <=0)
       print_animated("\nVocê perdeu!\n");
    else
       print_animated("\nVocê venceu!\n");

}