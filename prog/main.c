/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: 2016101881
 *
 * Created on 30 de Agosto de 2016, 13:32
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "administrador.h"
#include "jogador.h"
#include "pokemon.h"

/*
 *
 */

int main(int argc, char** argv) {
    char dirinp[200], dirout[200];
    char comando[10], verro1 = 1;
    char lixo;
    FILE *fileinp, *fileout;
    Jogo *jogo;

    jogo = CriaJogo();

    if (argc < 3) {
        printf("ERRO: Algum diretorio de arquivos nao foi informado!");
        return 1;
    }

    strcpy(dirinp, "../../../input/");
    strcpy(dirout, "../../../output/");

    strcat(dirinp, argv[1]);
    strcat(dirout, argv[2]);

    fileinp = fopen(dirinp, "r");
    fileout = fopen(dirout, "w");

    if (fileinp == NULL) {
        printf("\nNão foi possivel ler o arquivo de entrada\n");
        return 1;
    }

    while (verro1 != 0) {
        fprintf(fileout, "Digite a unidade de comando.\nExemplo: admin\n");
        fscanf(fileinp, "%s", comando);
        if (strcmp(comando, "admin") == 0 || strcmp(comando, "ADMIN") == 0 || strcmp(comando, "Admin") == 0) {
            PreparaJogo(jogo, fileinp, fileout);
            fprintf(fileout, "Digite 'sim' para acessar outra unidade de comando, ou digite 'nao', para encerrar o programa.\n");
            fscanf(fileinp, "%s", comando);
            if (strcmp(comando, "nao") == 0) {
                verro1 = 0;
            } else {
                fprintf(fileout, "\n");
            }
        } else if (strcmp(comando, "jogador") == 0 || strcmp(comando, "JOGADOR") == 0 || strcmp(comando, "Jogador") == 0) {
            IniciaJogo(jogo, fileinp, fileout);
            verro1 = 0;
        } else {
            fprintf(fileout, "\n!COMANDO INVALIDO!\n");
        }
    }

    fclose(fileinp);
    fclose(fileout);

    jogo = LiberaJogo(jogo);

    return (EXIT_SUCCESS);

}

