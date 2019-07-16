/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"
#include "jogador.h"

Nopok *PegaPok(Listapok *l, int idp) {
    Nopok *aux = l->pri, *aux2 = NULL;
    if (l != NULL) {
        for (aux = l->pri; l->pri != NULL; l->pri = l->pri->prox) {
            if (l->pri->idpokemon == idp) {
                aux2 = l->pri;
                l->pri = aux;
                return aux2;
            }
        }
        l->pri = aux;
        return aux2;
    } else {
        return NULL;
    }
}

Listapok *PegaListaPok(Nojog *j) {
    return j->pokemons;
}

int IdPokExiste(int idp, Listapok *s) {
    Nopok *aux;

    if (s->pri == NULL) {
        return 0;
    } else {
        for (aux = s->pri; s->pri != NULL; s->pri = s->pri->prox) {
            if (s->pri->idpokemon == idp) {
                s->pri = aux;
                return 1;
            }
        }
        s->pri = aux;
    }
    return 0;
}

Listapok *CriaListaPok() {
    Listapok *s;
    s = (Listapok*) malloc(sizeof (Listapok));
    s->pri = NULL;
    s->ult = NULL;
    return s;
}

void InserirPok(Listapok *s, int id, int qtd, int evo) {
    Nopok *novo;

    novo = (Nopok*) malloc(sizeof (Nopok));
    novo->idpokemon = id;
    novo->qtd = qtd;
    novo->evo = evo;

    // INSERIR NA LISTA VAZIA
    if (s->pri == NULL && s->ult == NULL) {
        novo->prox = NULL;
        s->pri = novo;
        s->ult = novo;
    }// INSERIR EM LISTA NÃO VAZIA.  
    else {
        novo->prox = NULL;
        s->ult->prox = novo;
        s->ult = novo;
    }
}

Listapok *LiberaListaPok(Listapok *s) {
    Nopok *aux;
    if (s != NULL) {
        while (s->pri != NULL) {
            aux = s->pri->prox;
            free(s->pri);
            s->pri = aux;
            if (aux == NULL) {
                s->ult = NULL;
            }
        }
        free(s);
    }
    return NULL;
}

Listapok *ExcluirPok(Listapok *s, int id) {
    Nopok *aux = NULL, *aux2 = s->pri;

    for (aux = s->pri; s->pri != NULL; aux2 = s->pri, s->pri = s->pri->prox) {
        // APAGANDO DE LISTA DE ÚNICO ELEMENTO.
        if (id == s->pri->idpokemon && s->pri == s->ult && aux == s->pri) {
            free(s->pri);
            s->pri = NULL;
            s->ult = NULL;
            return s;
        }// APAGANDO NO COMECO DA LISTA.
        else if (id == s->pri->idpokemon && aux2 == s->pri) {
            aux = aux->prox;
            free(s->pri);
            s->pri = aux;
            return s;
        }// APAGANDO NO MEIO DA LISTA.
        else if (id == s->pri->idpokemon && s->pri != s->ult && s->pri != aux) {
            aux2->prox = s->pri->prox;
            free(s->pri);
            s->pri = aux;
            return s;
        }// APAGANDO NO FINAL DA LISTA.
        else if (id == s->pri->idpokemon && s->pri == s->ult && aux != s->pri) {
            aux2->prox = NULL;
            s->ult = aux2;
            free(s->pri);
            s->pri = aux;
            return s;
        }
    }
    return s;
}

void InserirPokemonCampo(Listapok *s, int idp, int qtd) {
    Nopok *p;
    if (IdPokExiste(idp, s)) {
        p = PegaPok(s, idp);
        p->qtd = p->qtd + qtd;
    } else {
        InserirPok(s, idp, qtd, 0);
    }
}

int TemPokemonLista(Listapok *s) {
    if (s != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int GeraNovoID(int id) {
    float f;
    int aux = 1;

    f = id;
    while ((f = f / 10) > 1) {
        aux = aux * 10;
    }
    aux = aux * 10;
    id = id + aux;
    return id;
}

void EvoluirPokemons(Listajog *jog) {
    Listapok *pokemons;
    Nojog *auxjog;
    Nopok *auxpok;
    int id;

    for (auxjog = jog->pri; jog->pri != NULL; jog->pri = jog->pri->prox) {
        pokemons = jog->pri->pokemons;
        for (auxpok = pokemons->pri; pokemons->pri != NULL; pokemons->pri = pokemons->pri->prox) {
            id = pokemons->pri->idpokemon;
            if (pokemons->pri->qtd >= 3) {
                InserirPok(pokemons, GeraNovoID(id), 1, 1);
                auxpok = pokemons->pri->prox;
                jog->pri->pokemons = ExcluirPok(pokemons, pokemons->pri->idpokemon);
            }
        }
        pokemons->pri = auxpok;
    }
    jog->pri = auxjog;
}