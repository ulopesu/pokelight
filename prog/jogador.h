/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jogador.h
 * Author: 2016101881
 *
 * Created on 30 de Agosto de 2016, 13:36
 */
#include "pokemon.h"

#ifndef JOGADOR_H
#define JOGADOR_H

#include "administrador.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Nojog {
        int idgrupo;
        int idjogador;
        char *nome;
        int posicaox;
        int posicaoy;
        int destinox;
        int destinoy;
        struct Listapok *pokemons;
        struct Nojog *prox;
    } Nojog;

    typedef struct Listajog {
        struct Nojog *pri;
        struct Nojog *ult;
    } Listajog;

    
    Listajog *PegaListaJog(Jogo *jogo);
    Nojog *PegaJog(Listajog *l, int id);
    Listajog *CriaListaJog();
    void InserirJog(Listajog *s, int idg, int idj, char *nome);
    Listajog *LiberaListaJog(Listajog *s);
    Listajog *ExcluirJog(Listajog *s, int id);
    int IdJogExiste(int idj, Listajog *s);
    void InserirJogadores(Listajog *s, FILE *fpi, FILE *fpo);
    void EliminarJogadores(Listajog *s, FILE *fpi, FILE *fpo);
    void ExibirJogadores(Listajog *s, FILE *fpo);
    void MudarGrupoJog(int idj, int idg, Listajog *s);
    void MudarGrupoJogadores(Listajog *s, FILE *fpi, FILE *fpo);
    



#ifdef __cplusplus
}
#endif

#endif /* JOGADOR_H */

