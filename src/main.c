#include "cabecalhoCombate.h"
#include "combate inimigo.h"
#include "combate jogador.h"
#include "structs.h"


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese_Brazil");

   print_animated("\n RPG basico de turno");

    personagem jogador = {"piruGrosso", 100, 35, 30, 125, 75, 0};
    personagem inimigo = {"inimigos", 200, 30, 25, 100, 70, 0};

    personagem* ptrjogador = &jogador;
    personagem* ptrinimigo = &inimigo;    

    magia tiposMagia = {70, 50};
    magia* ptrmagia = &tiposMagia;

    int turno = 0;
    barra_progresso(3);

    while (jogador.hp > 0 && inimigo.hp > 0) {
        if (turno % 2 == 0) {
            CombateJogador(&jogador, &inimigo, ptrmagia);
        } else {
            CombateInimigo(&inimigo, &jogador, ptrmagia);
        }
        turno++;
    }

    if (jogador.hp <= 0)
       print_animated("\nVocê perdeu!\n");
    else
       print_animated("\nVocê venceu!\n");

}