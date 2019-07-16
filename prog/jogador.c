/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "pokemon.h"
#include "administrador.h"

void ExibirJogadores(Listajog *s, FILE *fpo) {
    Nojog* aux; /* variável auxiliar para salval o começo da lista */
    fprintf(fpo, "ID Jogador  ID Grupo  Nome do Jogador\n");
    for (aux = s->pri; s->pri != NULL; s->pri = s->pri->prox) {
        fprintf(fpo, "   %d\t\t%d\t%s\n", s->pri->idjogador, s->pri->idgrupo, s->pri->nome);
    }
    s->pri = aux;
}

int ContarJogadores(Listajog *s) {
    int cont = 0;
    Nojog* aux; /* variável auxiliar para salval o começo da lista */
    for (aux = s->pri; s->pri != NULL; s->pri = s->pri->prox) {
        cont++;
    }
    s->pri = aux;
    return cont;
}

Listajog *PegaListaJog(Jogo *jogo) {
    return jogo->jogadores;
}

Nojog *PegaJog(Listajog *l, int id) {
    Nojog *aux = l->pri, *aux2 = NULL;
    if (l != NULL) {
        for (aux = l->pri; l->pri != NULL; l->pri = l->pri->prox) {
            if (l->pri->idjogador == id) {
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

Listajog *CriaListaJog() {
    Listajog *s;
    s = (Listajog*) malloc(sizeof (Listajog));
    s->pri = NULL;
    s->ult = NULL;
    return s;
}

void InserirJog(Listajog *s, int idg, int idj, char *nome) {
    Nojog *novo;

    novo = (Nojog*) malloc(sizeof (Nojog));
    novo->idgrupo = idg;
    novo->idjogador = idj;
    novo->nome = strdup(nome);
    novo->posicaox = 0;
    novo->posicaoy = 0;
    novo->destinox = 0;
    novo->destinoy = 0;
    novo->pokemons = CriaListaPok();

    // ORGANIZAÇÃO DA LISTA.
    if (s->pri == NULL && s->ult == NULL) {
        novo->prox = NULL;
        s->pri = novo;
        s->ult = novo;
    } else {
        novo->prox = NULL;
        s->ult->prox = novo;
        s->ult = novo;
    }
}

Listajog *LiberaListaJog(Listajog *s) {
    Nojog *aux;
    if (s != NULL) {
        while (s->pri != NULL) {
            aux = s->pri->prox;
            s->pri->pokemons = LiberaListaPok(s->pri->pokemons);
            free(s->pri->nome);
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

Listajog *ExcluirJog(Listajog *s, int id) {
    Nojog *aux = NULL, *aux2 = s->pri;

    for (aux = s->pri; s->pri != NULL; aux2 = s->pri, s->pri = s->pri->prox) {
        // APAGANDO DE LISTA DE ÚNICO ELEMENTO.
        if (id == s->pri->idjogador && s->pri == s->ult && aux == s->pri) {
            s->pri->pokemons = LiberaListaPok(s->pri->pokemons);
            free(s->pri->nome);
            free(s->pri);
            s->pri = NULL;
            s->ult = NULL;
            return s;
        }// APAGANDO NO COMECO DA LISTA.
        else if (id == s->pri->idjogador && aux2 == s->pri) {
            aux = aux->prox;
            s->pri->pokemons = LiberaListaPok(s->pri->pokemons);
            free(s->pri->nome);
            free(s->pri);
            s->pri = aux;
            return s;
        }// APAGANDO NO MEIO DA LISTA.
        else if (id == s->pri->idjogador && s->pri != s->ult && s->pri != aux) {
            aux2->prox = s->pri->prox;
            s->pri->pokemons = LiberaListaPok(s->pri->pokemons);
            free(s->pri->nome);
            free(s->pri);
            s->pri = aux;
            return s;
        }// APAGANDO NO FINAL DA LISTA.
        else if (id == s->pri->idjogador && s->pri == s->ult && aux != s->pri) {
            aux2->prox = NULL;
            s->ult = aux2;
            s->pri->pokemons = LiberaListaPok(s->pri->pokemons);
            free(s->pri->nome);
            free(s->pri);
            s->pri = aux;
            return s;
        }
    }
    return s;
}

int IdJogExiste(int idj, Listajog *s) {
    Nojog *aux;

    if (s->pri == NULL) {
        return 0;
    } else {
        for (aux = s->pri; s->pri != NULL; s->pri = s->pri->prox) {
            if (s->pri->idjogador == idj) {
                s->pri = aux;
                return 1;
            }
        }
        s->pri = aux;
    }
    return 0;
}

void InserirJogadores(Listajog *s, FILE *fpi, FILE *fpo) {
    int qtd, cont1, idj, idg, verro1 = 1, verro2 = 1;
    char nome[100], lixo;
    fprintf(fpo, "Digite a quantidade de Jogadores que deseja inserir.\n");
    fscanf(fpi, "%d", &qtd);
    if (qtd != 0) {
        fprintf(fpo, "\nDigite todos os jogadores da seguinte forma:\nid do jogador, id do Grupo e o nome do jogador.\nExemplo: 1 3 Joao Maria");
        fprintf(fpo, "\nOs ids de grupos existentes sao: 1(Amarelo), 2(Azul) ou 3(Vermelho)");
        for (cont1 = 0; cont1 < qtd; cont1++) {
            fprintf(fpo, "\n");
            while (verro1 != 0) {
                fscanf(fpi, "%d", &idj);
                if (IdJogExiste(idj, s) == 0) {
                    verro1 = 0;
                    while (verro2 != 0) {
                        fscanf(fpi, "%d", &idg);
                        if (idg >= 1 && idg <= 3) {
                            verro2 = 0;
                            fscanf(fpi, "%[^\n]", nome);
                            InserirJog(s, idg, idj, nome);
                        } else {
                            fprintf(fpo, "\nO id de grupo digitado nao existe, digite novamente o id do grupo e o nome:\n");
                        }
                    }
                    verro2 = 1;
                } else {
                    fprintf(fpo, "\nO id de jogador digitado ja existe, digite tudo novamente:\n");
                }
            }
            verro1 = 1;
        }
        fprintf(fpo, "O(s) jogador(es) foram inseridos com sucesso");
    }
}

void EliminarJogadores(Listajog *s, FILE *fpi, FILE *fpo) {
    int qtd, verro1 = 1, cont1, idj, verro2 = 1, qtdj, opcao;
    while (verro2 != 0) {
        ExibirJogadores(s, fpo);
        qtdj = ContarJogadores(s);
        fprintf(fpo, "\nDigite a quantidade de Jogadores que deseja eliminar: ");
        fscanf(fpi, "%d", &qtd);
        if (qtd != 0 && qtd <= qtdj) {
            verro2 = 0;
            for (cont1 = 0; cont1 < qtd; cont1++) {
                fprintf(fpo, "\nDigite o ID do jogador que deseja excluir: ");
                while (verro1 != 0) {
                    fscanf(fpi, "%d", &idj);
                    if (IdJogExiste(idj, s)) {
                        verro1 = 0;
                        s = ExcluirJog(s, idj);
                    } else {
                        fprintf(fpo, "\nO ID de jogador digitado nao existe, digite outro: ");
                    }
                }
                verro1 = 1;
            }
            fprintf(fpo, "Jogador(es) excluido(s) com sucesso.\n");
        } else {
            fprintf(fpo, "\nQuantidade Invalida, existem apenas %d jogador(es).", qtdj);
            fprintf(fpo, "\nDigite:\n1) para tentar novamente ou 2) para sair.\n");
            fscanf(fpi, "%d", &opcao);
            if (opcao == 2) {
                verro2 = 0;
            }
        }
    }
}

void MudarGrupoJog(int idj, int idg, Listajog *s) {
    Nojog *j;
    j = PegaJog(s, idj);
    j->idgrupo = idg;
}

void MudarGrupoJogadores(Listajog *s, FILE *fpi, FILE *fpo) {
    int idj, idg, verro1 = 1, verro2 = 1;
    if (s != NULL) {
        ExibirJogadores(s, fpo);
        fprintf(fpo, "\nDigite o ID do jogador que deseja mudar de grupo");
        while (verro1 != 0) {
            fprintf(fpo, "\n");
            fscanf(fpi, "%d", &idj);
            if (IdJogExiste(idj, s)) {
                verro1 = 0;
                fprintf(fpo, "\nDigite o id do novo grupo");
                while (verro2 != 0) {
                    fprintf(fpo, "\n");
                    fscanf(fpi, "%d", &idg);
                    if (idg >= 1 && idg <= 3) {
                        verro2 = 0;
                        MudarGrupoJog(idj, idg, s);
                    } else {
                        fprintf(fpo, "\nO id de grupo digitado nao existe, digite 1(Amarelo), 2(Azul) ou 3(Vermelho).");
                    }
                }
            } else {
                fprintf(fpo, "\nID de jogador digitado nao existe, digite novamente.");
            }
        }
    } else {
        fprintf(fpo, "\nNao existem jogadores.");
    }
}


