/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "administrador.h"
#include "jogador.h"
#include "pokemon.h"
#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Jogo *CriaJogo() {
    Jogo * jogo;

    jogo = (Jogo*) malloc(sizeof (Jogo));

    jogo->jogadores = CriaListaJog();

    jogo->Tab = CriaTabuleiro();

    return jogo;
}

void PreparaJogo(Jogo *jogo, FILE *fpi, FILE *fpo) {
    int comando1, verro1 = 1, comando2, verro2 = 1;

    jogo->Amarelo.idgrupo = 1;
    jogo->Azul.idgrupo = 2;
    jogo->Vermelho.idgrupo = 3;

    fprintf(fpo, "\n\n\tBEM VINDO AO 'MENU ADMINISTRADOR'");
    fprintf(fpo, "\nE NECESSARIO CONFIGURAR O JOGO ANTES DE COMECAR");
    fprintf(fpo, "\n\nDigite:");

    while (verro1 != 0) {
        fprintf(fpo, "\n1) Para Inserir Jogadores.\n2) Eliminar Jogadores.\n3) Mudar Grupo de Jogador.\n4) Inserir Pokemons no Mapa.\n");
        fscanf(fpi, "%d", &comando1);
        
        if (comando1 == 1) {
            InserirJogadores(PegaListaJog(jogo), fpi, fpo);
            verro1 = 0;
        } else if (comando1 == 2) {
            EliminarJogadores(PegaListaJog(jogo), fpi, fpo);
            verro1 = 0;
        } else if (comando1 == 3) {
            MudarGrupoJogadores(PegaListaJog(jogo), fpi, fpo);
            verro1 = 0;
        } else if (comando1 == 4) {
            InserirPokemonsMapa(jogo->Tab, fpi, fpo);
            verro1 = 0;
        } else {
            fprintf(fpo, "\n!COMANDO INVALIDO!, digite novamente:");
        }

        while (verro1 == 0 && verro2 != 0) {
            fprintf(fpo, "\n\nDeseja executar mais algum comando do 'MENU ADMINISTRADOR'? Digite:\n1) Sim.\n2) Nao.\n");
            fscanf(fpi, "%d", &comando2);
            if (comando2 == 1) {
                verro1 = 1;
                fprintf(fpo, "\nDigite:");
            } else if (comando2 == 2) {
                verro2 = 0;
            } else {
                fprintf(fpo, "\n!COMANDO INVALIDO!");
            }
        }
    }
}

Jogo *LiberaJogo(Jogo *jogo) {
    jogo->Tab = LiberaTabuleiro(jogo->Tab);
    jogo->jogadores = LiberaListaJog(jogo->jogadores);
    free(jogo);
    return NULL;
}

void RealizaJogadas(Jogo *jogo, FILE *fpi, FILE *fpo) {
    int verro1 = 1, x, y, cont1, cont2;
    char sx[6], sy[6];
    Nojog *aux, *jogador;
    char jogada[6];

    jogador = jogo->jogadores->pri;

    for (aux = jogador; jogador != NULL; jogador = jogador->prox) {
        while (verro1 != 0) {
            if (jogador->posicaox == jogador->destinox && jogador->posicaoy == jogador->destinoy) {
                fprintf(fpo, "Digite uma jogada para o Jogador %d - %s.\n", jogador->idjogador, jogador->nome);
                fprintf(fpo, "Sua posicao atual em (coluna,linha) eh: (%d,%d)\n", jogador->posicaox, jogador->posicaoy);
                fscanf(fpi, "%s", jogada);


                if (jogada[0] <= '9' && jogada[0] >= '0') {
                    for (cont1 = 0; jogada[cont1] != ',' && jogada[cont1] != ' ' && jogada[cont1] != '\0'; cont1++) {
                        sx[cont1] = jogada[cont1];
                    }
                    sx[cont1] = '\0';
                    cont1++;
                    for (cont2 = 0; jogada[cont1] != '\0' && jogada[cont1] != ' '; cont1++, cont2++) {
                        sy[cont2] = jogada[cont1];
                    }
                    sy[cont2] = '\0';

                    x = atoi(sx);
                    y = atoi(sy);

                    if (x <= 19 && x >= 0 && y <= 9 && y >= 0) {
                        jogador->destinox = x;
                        jogador->destinoy = y;
                        verro1 = 0;
                    } else {
                        fprintf(fpo, "POSICAO FORA DO TABULEIRO\n");
                    }
                } else {
                    if (strcmp(jogada, "up") == 0 || strcmp(jogada, "UP") == 0) {
                        if (jogador->posicaoy != 0) {
                            jogador->destinoy--;
                            verro1 = 0;
                        } else {
                            fprintf(fpo, "POSICAO FORA DO TABULEIRO\n");
                        }
                    } else if (strcmp(jogada, "down") == 0 || strcmp(jogada, "DOWN") == 0) {
                        if (jogador->posicaoy != 9) {
                            jogador->destinoy++;
                            verro1 = 0;
                        } else {
                            fprintf(fpo, "POSICAO FORA DO TABULEIRO\n");
                        }
                    } else if (strcmp(jogada, "right") == 0 || strcmp(jogada, "RIGHT") == 0) {
                        if (jogador->posicaox != 19) {
                            jogador->destinox++;
                            verro1 = 0;
                        } else {
                            fprintf(fpo, "POSICAO FORA DO TABULEIRO\n");
                        }
                    } else if (strcmp(jogada, "left") == 0 || strcmp(jogada, "LEFT") == 0) {
                        if (jogador->posicaox != 0) {
                            jogador->destinox--;
                            verro1 = 0;
                        } else {
                            fprintf(fpo, "POSICAO FORA DO TABULEIRO\n");
                        }
                    } else {
                        fprintf(fpo, "COMANDO INVALIDO\n");
                    }
                }
            } else {
                verro1 = 0;
            }
        }
        verro1 = 1;
    }
    jogador = aux;
}

void ExecutaJogada(Jogo *jogo, FILE *fpo) {
    int cont1, cont2;
    Nojog *auxjog, *jogador;
    Listapok *encontrados;
    Nopok *auxpok, *auxpok2;
    jogador = jogo->jogadores->pri;

    for (auxjog = jogador; jogador != NULL; jogador = jogador->prox) {
        if (jogador->posicaox != jogador->destinox) {
            if (jogador->posicaox < jogador->destinox) {
                jogador->posicaox++;
            } else {
                jogador->posicaox--;
            }
        } else if (jogador->posicaoy != jogador->destinoy) {
            if (jogador->posicaoy < jogador->destinoy) {
                jogador->posicaoy++;
            } else {
                jogador->posicaoy--;
            }
        }

        encontrados = jogo->Tab->campo[jogador->posicaox][jogador->posicaoy].pokemons;
        jogo->Tab->campo[jogador->posicaox][jogador->posicaoy].vencontrados = 1;

        if (encontrados != NULL) {
            fprintf(fpo, "O jogador %s encontrou este(s) pokemon(s):\n", jogador->nome);
            for (auxpok = encontrados->pri; encontrados->pri != NULL; encontrados->pri = encontrados->pri->prox) {
                fprintf(fpo, "ID do pokemon: %d. Quantidade: %d.\n", encontrados->pri->idpokemon, encontrados->pri->qtd);
                if (IdPokExiste(encontrados->pri->idpokemon, jogador->pokemons)) {
                    auxpok2 = PegaPok(jogador->pokemons, encontrados->pri->idpokemon);
                    auxpok2->qtd = auxpok2->qtd + encontrados->pri->qtd;
                } else {
                    InserirPok(jogador->pokemons, encontrados->pri->idpokemon, encontrados->pri->qtd, 0);
                }
            }
            encontrados->pri = auxpok;
        }
    }
    jogador = auxjog;

    for (cont1 = 0; cont1 < jogo->Tab->y; cont1++) {
        for (cont2 = 0; cont2 < jogo->Tab->x; cont2++) {
            if (jogo->Tab->campo[cont2][cont1].vencontrados == 1) {
                jogo->Tab->campo[cont2][cont1].pokemons = LiberaListaPok(jogo->Tab->campo[cont2][cont1].pokemons);
                jogo->Tab->campo[cont2][cont1].vencontrados = 0;
            }
        }
    }
}

void IniciaJogo(Jogo *jogo, FILE *fpi, FILE *fpo) {

    fprintf(fpo, "\n\nSe-prepare(m) jogador(es), pois agora o jogo vai comecar. O objetivo de voces e encontrar todos os pokemons do mapa, o jogo acaba assim que todos os pokemons forem encontrados. GOOD LUCK!!!\n\n\n");

    ExibirJogadores(jogo->jogadores, fpo);

    fprintf(fpo, "\nE hora de realizar as jogadas, e elas podem ser realizadas de duas formas.\n1) Digite uma posicao (coluna,linha) a qual deseja mover o jogador.\nExemplo: 1,5\n2) Digite um comando unico para se mover (UP,DOWN,LEFT,RIGHT).\nExemplos: DOWN\n\n");


    AtualizaCampo(jogo);
    ExecutaJogada(jogo, fpo);
    ImprimiCampo(jogo->Tab, fpo);

    while (TemPokemonMapa(jogo->Tab) == 1) {
        RealizaJogadas(jogo, fpi, fpo);
        ExecutaJogada(jogo, fpo);
        AtualizaCampo(jogo);
        ImprimiCampo(jogo->Tab, fpo);
    }
    EvoluirPokemons(jogo->jogadores);

    fprintf(fpo, "\n\nParabens todos os pokemons foram encontrados. O jogo acabou!!!\n");
}
