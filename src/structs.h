#ifndef STRUCTS_H
#define STRUCTS_H

// Definição da struct personagem
typedef struct {
    char nome[50];
    int hp;
    int ataque;
    int defesa;
    int mana;
    int stamina;
    int defendendo;
} personagem;

// Definição da struct magia
typedef struct {
    int Raio;
    int bolaDeFogo;
} magia;

#endif
