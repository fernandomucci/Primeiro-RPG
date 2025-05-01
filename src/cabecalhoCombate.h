#ifndef COMBATE_H
#define COMBATE_H


//minhas bibliotecas

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

#include "structs.h"


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

//printf animado
void print_animated(const char* formato, ...) {
    char buffer[256];
    va_list args;
    va_start(args, formato);
    vsnprintf(buffer, sizeof(buffer), formato, args);
    va_end(args);

    for (int i = 0; buffer[i] != '\0'; i++) {
        putchar(buffer[i]);
        fflush(stdout);
        SLEEP(20);
    }
}



//funcoes relacionadas ao combate em si


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
   print_animated("\n======= STATUS =======\n");
   print_animated("%s - HP: %d | Mana: %d | Stamina: %d\n", j->nome, j->hp, j->mana, j->stamina);
   print_animated("%s - HP: %d | Mana: %d | Stamina: %d\n", i->nome, i->hp, i->mana, i->stamina);
   print_animated("=======================\n");
}


int CalculoDano(int* danoBase, int defesa, int defendendo)
{
    if(Esquiva())
    {
        *danoBase=0;
       print_animated("\n>>ESQUIVOU! DANO E ZERO.\n");
    }

    if (defendendo) {
        *danoBase/= 2;
       print_animated(">> Defendeu! Dano reduzido pela metade.\n");
    }

    int danoFinal = *danoBase - defesa;
    if (danoFinal < 0) danoFinal = 0;

    return danoFinal;

}

#endif

