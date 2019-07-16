/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"
#include "pokemon.h"

Tabuleiro* CriaTabuleiro() {
    Tabuleiro *t;
    t = (Tabuleiro*) malloc(sizeof (Tabuleiro));
    t->x = 20;
    t->y = 10;
    t->campo = CriaCampo();
    return t;
}

Campo** CriaCampo() {
    Campo **campo;
    int i, x = 20, y = 10, cont1, cont2;

    campo = (Campo**) calloc(x, sizeof (Campo));

    for (i = 0; i < x; i++) {
        campo[i] = (Campo*) calloc(y, sizeof (Campo));
    }

    for (cont1 = 0; cont1 < x; cont1++) {
        for (cont2 = 0; cont2 < y; cont2++) {
            campo[cont1][cont2].pokemons = NULL;
        }
    }
    return campo;
}

Campo** LiberaCampo(Campo** campo) {
    int i, x = 20, y = 10, cont1, cont2;

    for (cont1 = 0; cont1 < x; cont1++) {
        for (cont2 = 0; cont2 < y; cont2++) {
            campo[cont1][cont2].pokemons = LiberaListaPok(campo[cont1][cont2].pokemons);
        }
    }
    for (i = 0; i < x; i++) {
        free(campo[i]);
    }
    free(campo);
    return NULL;
}

Tabuleiro* LiberaTabuleiro(Tabuleiro *Tab) {
    Tab->campo = LiberaCampo(Tab->campo);
    free(Tab);
    return NULL;
}

void LimpaCampo(Tabuleiro *Tab) {
    int cont1, cont2;

    for (cont1 = 0; cont1 < Tab->x; cont1++) {
        for (cont2 = 0; cont2 < Tab->y; cont2++) {
            Tab->campo[cont1][cont2].qtdj = 0;
        }
    }
}

void ImprimiCampo(Tabuleiro *Tab, FILE *fpo) {
    int cont1, cont2;

    fprintf(fpo, "\n  ");
    for (cont1 = 0; cont1 < Tab->x; cont1++) {
        fprintf(fpo, " %.2d", cont1);
    }
    for (cont1 = 0; cont1 < Tab->y; cont1++) {
        fprintf(fpo, "\n");
        fprintf(fpo, "%.2d|", cont1);
        for (cont2 = 0; cont2 < Tab->x; cont2++) {
            if (Tab->campo[cont2][cont1].qtdj == 0) {
                fprintf(fpo, "  |");
            } else {
                fprintf(fpo, "%.2d|", Tab->campo[cont2][cont1].qtdj);
            }
        }
    }
    fprintf(fpo, "\n  ");
}

void InserirPokemonsMapa(Tabuleiro *Tab, FILE *fpi, FILE *fpo) {
    int verro1 = 1, x, y, idp, qtd;

    fprintf(fpo, "\nDigite a posicao (coluna, linha) que deseja inserir seu pokemon.\nExemplo: 2 2.");
    while (verro1 != 0) {
        fprintf(fpo, "\n");
        fscanf(fpi, "%d %d", &x, &y);
        if (x < 20 && x >= 0 && y < 10 && y >= 0) {
            verro1 = 0;
            fprintf(fpo, "\nDigite o id do pokemon e a quantidade que deseja inserir\nExemplo: 1 3.\n");
            fscanf(fpi, "%d %d", &idp, &qtd);
            if (Tab->campo[x][y].pokemons == NULL) {
                Tab->campo[x][y].pokemons = CriaListaPok();
                InserirPokemonCampo(Tab->campo[x][y].pokemons, idp, qtd);
                fprintf(fpo, "\nPokemon(s) inserido(s) com sucesso.");
            } else {
                InserirPokemonCampo(Tab->campo[x][y].pokemons, idp, qtd);
                fprintf(fpo, "\nPokemon(s) inserido(s) com sucesso.");
            }
        } else {
            fprintf(fpo, "\nPOSICAO INVALIDA");
        }
    }
}

int TemPokemonMapa(Tabuleiro *Tab) {
    int cont1, cont2;

    for (cont1 = 0; cont1 < (Tab->y); cont1++) {
        for (cont2 = 0; cont2 < (Tab->x); cont2++) {
            if (TemPokemonLista(Tab->campo[cont2][cont1].pokemons)) {
                return 1;
            }
        }
    }
    return 0;
}

void AtualizaCampo(Jogo *jogo) {
    Nojog* jogador, *aux;

    LimpaCampo(jogo->Tab);
    jogador = jogo->jogadores->pri;

    for (aux = jogador; jogador != NULL; jogador = jogador->prox) {
        jogo->Tab->campo[jogador->posicaox][jogador->posicaoy].qtdj++;
    }
    jogador = aux;
}