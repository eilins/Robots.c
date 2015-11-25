#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABMAX 10 /*mapa*/
#define TABPOS 100 /* mapa - posicoes*/
#define MODP TABMAX /*limite de xy-ij no mapa*/

typedef struct
{
    int tabela[TABMAX][TABMAX];
    int nivel;
}dados;

dados ini(void);            /*comeco de uma partida*/
void imprimetab(void);      /*representacao do tabuleiro*/
void imprimemenu(void);     /*criar menu de opcoes para usuario*/

dados d;

int main(void)
{
    int vez=-1;
    srand(time(NULL));

    ini();
    do
    {
        imprimetab();
        vez=vez*-1;
        if(vez==1)
            vezhumano();
        /* if(vez==-1)
         *           vezpc();*/ 

    }
    while(vez==5);

    return EXIT_SUCCESS;
}

void imprimetab(void)
{
    int i,j;
    printf("\e[H\e[2J");
    printf("\n-");
    for(i=0;i<TABMAX;i++) /*  borda de cima */
        printf(" -");
    printf(" -");

    for(i=0;i<TABMAX;i++)
    {
        printf("\n| ");      /*  borda esquerda */
        for(j=0;j<TABMAX;j++)/* mapa */
        {
            switch(d.tabela[i][j])
            {
                case 0:/* vazio */
                    printf("  ");
                    break;
                case 1:/* pedra */
                    printf("& ");
                    break;
                case 2:/* HEROI */
                    printf("H ");
                    break;
                case 3:/* robos */
                    printf("# ");
            }
        }
        printf("|");/* borda direita */
    }
    printf("\n-");/*  borda de baixo */
    for(i=0;i<TABMAX;i++)
        printf(" -");
    printf(" -\n");
    imprimemenu();
    return;
}

void imprimemenu(void)
{
    printf("\n[w] cima\n[a] esquerda\n[s] baixo\n[d] direita\n(q) teleporte\n[e] sair do jogo?\n?");
    return;
}
