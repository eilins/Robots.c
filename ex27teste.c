#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABMAX 10 /*mapa*/
#define TABPOS 100 /* mapa - posicoes*/
#define POS TABMAX /*limite de xy-ij no mapa*/

/*prototipo*/
typedef struct
{
    int tabela[TABMAX][TABMAX];
    int nivel;
}dados;

dados ini(void);            /*comeco de uma partida*/
dados preenchezero(dados d);
void imprimetab(void);      /*representacao do tabuleiro*/
void imprimemenu(void);     /*criar menu de opcoes para usuario*/
dados preenchemundo(dados d, int nivel);

int main(void)
{
    int x=0, y; 
    int vez=-1;
    int nivel=5;
    srand(time(NULL));
    dados d;
    ini();
    do
    {
        vez=*-1;
        if(vez==1)
            /*chamada para imprimir a funcao*/
            vez=humanojoga();
        else if(vez==-1)
        {
            vez=computadorjoga();
            if(vez == 2)
            { 
                imprimetab();
            }
        }

    }
    while(vez==2);

    return EXIT_SUCCESS;
}

dados preenchezero(dados d)
{

    int x, y;

    for(x=0; x<MAXTAB; x++)
        for(y=0; y<MAXTAB; y++)
            d.tabela[x][y]=0
    return d;
}
void imprimetab(void)
{
    int x, y;
   
    printf("\n");
    for(x=0;x<MAXTAB;x++) /*  borda de cima */
        printf("- ");
    printf("\n");

    for(x=0;x<MAXTAB;x++)
    {
        printf("| ");      /*  borda esquerda */
        for(y=0;y<TABMAX;y++)/* mapa */
        {
            switch(d.tabela[x][y])
            {
                case 0:/* vazio */
                    printf(". ");
                    break;
                case 1:/* pedra */
                    printf("& ");
                    break;
                case 2:/* HEROI */
                    printf("H ");
                    break;
                case 3:/* robos */
                    printf("# ");
                    break;
            }
        }
        printf("|\n");/* borda direita */
    }
    for(x=0;x<MAXTAB;x++)
        printf("- ");
    printf("\n");
    imprimemenu();
    return;
}

void imprimemenu(void)
{
    printf("\n[w] cima\n[a] esquerda\n[s] baixo\n[d] direita\n(q) teleporte\n[e] sair do jogo?\n?");
    return;
}

dados preenchemundo(dados d, int nivel)
{
    int x;
    int i, j;
    int posicaolivre;

    do
    {
        i=rand()%10;
        j=rand()%10;
        posicaolivre=livreposicao(d, i, j);
        if(posicaolivre==1)
            d.tabela[i][j]=2;
    }
    while(!posicaolivre);
    for(x=0; x<(nivel*2); x++)
    {
        do
        {
            i=rand()%10;
            j=rand()%10;
            posicaolivre=livreposicao(d, i, j);
            if(posicaolivre==1)
                d.tabela[i][j]=3;
        }
        while(!posicaolivre);
    }
    return d;

}
