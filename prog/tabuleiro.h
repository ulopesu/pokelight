/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tabuleiro.h
 * Author: 2016101881
 *
 * Created on 27 de Setembro de 2016, 16:25
 */
#include "pokemon.h"

#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "administrador.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Campo {
        int vencontrados;
        int qtdj;
        struct Listapok *pokemons;
    }Campo;

    typedef struct Tabuleiro {
        Campo **campo;
        int x;
        int y;
    }Tabuleiro;
    

    void LimpaCampo(Tabuleiro *Tab);
    Campo** CriaCampo();
    Tabuleiro* CriaTabuleiro();
    void ImprimiCampo(Tabuleiro *Tab, FILE *fpo);
    Campo** LiberaCampo(Campo **campo);
    Tabuleiro* LiberaTabuleiro(Tabuleiro *Tab);
    void InserirPokemonsMapa(Tabuleiro *Tab, FILE *fpi, FILE *fpo);
    int TemPokemonMapa(Tabuleiro *Tab);
    void AtualizaCampo(Jogo *jogo);


#ifdef __cplusplus
}
#endif

#endif /* TABULEIRO_H */

