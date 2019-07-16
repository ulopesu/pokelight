/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pokémon.h
 * Author: 2016101881
 *
 * Created on 30 de Agosto de 2016, 13:37
 */

#ifndef POKEMON_H
#define POKEMON_H

#include "jogador.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Nopok {
        int evo;
        int idpokemon;
        int qtd;
        struct Nopok *prox;
    }Nopok;

    typedef struct Listapok {
        struct Nopok *pri;
        struct Nopok *ult;
    }Listapok;

    Nopok *PegaPok(Listapok *l, int idp);
    Listapok *PegaListaPok(Nojog *n);
    Listapok *CriaListaPok();
    void InserirPok(Listapok *s, int id, int qtd, int evo);
    Listapok *LiberaListaPok(Listapok *s);
    Listapok *ExcluirPok(Listapok *s, int id);
    int IdPokExiste(int idp, Listapok *s);
    void InserirPokemonCampo(Listapok *s, int idp, int qtd);
    int TemPokemonLista(Listapok *s);
    void EvoluirPokemons(Listajog *jog);
    int GeraNovoID(int id);


#ifdef __cplusplus
}
#endif

#endif /* POKÉMON_H */

