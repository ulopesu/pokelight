/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   administrador.h
 * Author: 2016101881
 *
 * Created on 30 de Agosto de 2016, 13:36
 */
#include <stdlib.h>
#include <stdio.h>
#include "jogador.h"
#include "pokemon.h"
#include "tabuleiro.h"

#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Grupo {
        int idgrupo;
    } Grupo;

    typedef struct Jogo {
        struct Listajog *jogadores;
        Grupo Amarelo;
        Grupo Azul;
        Grupo Vermelho;
        struct Tabuleiro *Tab;
    } Jogo;


    Jogo *CriaJogo();
    void PreparaJogo(Jogo *jogo, FILE *fpi, FILE *fpo);
    Jogo *LiberaJogo(Jogo *j);
    void IniciaJogo(Jogo *j, FILE *fpi, FILE *fpo);
    void RealizaJogadas(Jogo *jogo, FILE *fpi, FILE *fpo);
    void ExecutaJogada(Jogo *jogo, FILE *fpo);


#ifdef __cplusplus
}
#endif

#endif /* ADMINISTRADOR_H */

