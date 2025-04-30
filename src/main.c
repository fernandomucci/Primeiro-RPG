#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif
#define usleep(x) Sleep(x/1000)


typedef struct {
    char nome[50];
    int hp;
    int ataque;
    int defesa;
    int mana;
    int stamina;
    int defendendo;
} personagem;


typedef struct {
    int Raio;
    int bolaDeFogo;
} magia;




// Barra de progresso
void barra_progresso(int segundos) {
    printf("Carregando");
    for (int i = 0; i < segundos; i++) {
        printf(".");
        fflush(stdout);
        SLEEP(500);
    }
    printf("\n");
}

// Efeito de dano
void efeito_dano(int dano) {
    int blocos = dano / 10;
    if (blocos > 10) blocos = 10;

    printf("Dano: [");
    for (int i = 0; i < blocos; i++) {
        printf("#");
        fflush(stdout);
        usleep(100000);
    }
    printf("]\n");
}

/*//printfs animados
void print_animated(const char* texto) {
    while (*texto) {
        putchar(*texto);
        fflush(stdout);
        SLEEP(20);  
        texto++;
    }
}*/




int Dados()
{
    return (rand()%20+1);

}

int Esquiva()
{
    return (Dados() <=5);
}

void CriticoJogador(int* danoBase)
{
    if(Dados()<=3)
    {
    *danoBase *= 2;
    printf("\n>> CRiTICO!\n");
    }
}

void CriticoInimigo(int* danoBase)
{
    if(Dados()<=2)
    {
    *danoBase *= 2;
    printf(">> CRÍTICO!\n");
    }
}


void mostrarStatus(personagem* j,personagem* i)
{
    printf("\n======= STATUS =======\n");
    printf("%s - HP: %d | Mana: %d | Stamina: %d\n", j->nome, j->hp, j->mana, j->stamina);
    printf("%s - HP: %d | Mana: %d | Stamina: %d\n", i->nome, i->hp, i->mana, i->stamina);
    printf("\n=======================\n");
}


int CalculoDano(int* danoBase, int defesa, int defendendo)
{
    if(Esquiva())
    {
        *danoBase=0;
        printf("\n>>ESQUIVOU! DANO E ZERO.\n");
    }

    if (defendendo) {
        *danoBase/= 2;
        printf(">> Defendeu! Dano reduzido pela metade.\n");
    }

    int danoFinal = *danoBase - defesa;
    if (danoFinal < 0) danoFinal = 0;

    return danoFinal;

}

void CombateJogador(personagem* atacante, personagem* defensor, magia* tipo) {
    atacante->defendendo = 0;

    printf("\nTURNO DE %s", atacante->nome);

   mostrarStatus(atacante,defensor);


    int escolhaAtaque, escolhaMagia;
    int danoBase =0;
    int acertou=0;
    
   

    printf("\n[1] Usar Magia\n[2] Atacar com Espada\n[3] Defender\nEscolha: ");
    scanf("%d", &escolhaAtaque);

    if (escolhaAtaque == 1) {
        printf("\nQual magia? Raio [1] (35 mana, 50 dano) ou Bola de Fogo [2] (25 mana, 30 dano): ");
        scanf("%d", &escolhaMagia);


        // Raio
        if (escolhaMagia == 1 && atacante->mana >= 35) {
            atacante->mana -= 35;

                if(Dados()<=16)
                {
                    danoBase = tipo->Raio;
                   CriticoJogador(&danoBase);
                    acertou++;
                    printf("\nVocê lançou Raio!");
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
                    printf("\nVocê lançou Bola de Fogo!");
                }
                    else{printf("\n ERROU ATAQUE");}
        } else {
            printf("Mana insuficiente ou opção inválida!\n");
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
        printf("\nVocê atacou com espada!");

        }
             else {printf("\n ERROU O ATAQUE");} 


    // defesa
    } else if (escolhaAtaque == 3) {
        
        if(Dados()<=15)
        {
            atacante->defendendo = 1;
            printf("\n%s está se defendendo!\n", atacante->nome);
        }
            
    } else {
        printf("\n ERROU A DEFESA \n");
    }

    if (defensor->defendendo) {
        danoBase /= 2;
        printf("\n%s defendeu! Dano reduzido pela metade.\n", defensor->nome);
    }


    if (acertou) {
       
        int danoFinal = CalculoDano(&danoBase, defensor->defesa,defensor->defendendo);
        defensor->hp -= danoFinal;

        efeito_dano(danoFinal);

        printf("\nDano base: %d | Bloqueado pela defesa: %d | Dano final: %d\n", danoBase, defensor->defesa, danoFinal);
    }




    //status final do personagem

    mostrarStatus(atacante,defensor);
}


void CombateInimigo(personagem* atacante, personagem* defensor, magia* tipo) {
    atacante->defendendo = 0;

    printf("\n TURNO INIMIGO!!!");


    

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

                 printf("\n%s lançou Raio!", atacante->nome);
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
                printf("\n%s lançou Bola de Fogo!", atacante->nome);
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
            printf("\n%s atacou com espada!", atacante->nome);
        }
        else{printf("\n INIMIGO ERROU ATAQUE");}
    } 
    
    // defesa inimigo
    else if (escolha == 3 || (atacante->stamina < 15 && danoBase==0)) {

        if(Dados()<=13)
        {
        atacante->defendendo = 1;
        printf("\n%s está se defendendo!\n", atacante->nome);
        }
        else{printf("\n INIMIGO ERROU A DEFESA");}
    }

    if (acertou) {
        if (defensor->defendendo) {
            danoBase /= 2;
            printf("\n%s defendeu! Dano reduzido pela metade.\n", defensor->nome);
        }

        int danoFinal = CalculoDano(&danoBase, defensor->defesa,defensor->defendendo);
        defensor->hp -= danoFinal;

        efeito_dano(danoFinal);

        printf("\nDano base: %d | Bloqueado pela defesa: %d | Dano final: %d\n", danoBase, defensor->defesa, danoFinal);
    

        
    }

    mostrarStatus(atacante,defensor);
}


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese_Brazil");

    printf("\n RPG basico de turno");

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
        printf("\nVocê perdeu!\n");
    else
        printf("\nVocê venceu!\n");

}