#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define LMAX 20
#define CMAX 20
#define TABMAX 20
#define NPEDRA 5

struct lista
{
    int Ppedra[LMAX][CMAX];
    int Probos[LMAX][CMAX];
    float posicao[LMAX][CMAX];
}A;

struct lugar
{
    int N1;
    int N2;
}Lr,Lh,Lp; /* R ==robo , H == humano, P==pedra, L ==lugar */

void valinit(int nivel);
void tabuleiro(int nivel);
void mover(char tecla);

int main(void)
{
    int NIVEL=1,sair=0,morto=0,NIVELUP =0,n1,n2;
    char TECLA;
    int tecla;
    printf("linha 31\n");
    valinit(NIVEL);
    
    while( morto == 0 )/*|| sair ==0 ) || (NIVELUP == 0)) */
    {
        tabuleiro(NIVEL);
        printf(" Digite Uma tecla\n Digite 'S' pra sair \n "); /* menu aqui */
        TECLA = getchar();
        printf("\e[H\e[2J");
        mover(TECLA);
    }
    return 0;
}

void valinit(int nivel)
{
    srand(time(NULL));
    int n3,n4;

    Lh.N1 =rand()%LMAX; /* Posicoes aleatorias */
    Lh.N2 =rand()%CMAX;
    A.posicao[Lh.N1][Lh.N2] = 1; /* Comeca na posicao [0][0] */

    for(n4=0;n4<nivel;n4++)    
    {
        while(n3!=-1) //infinito
        {
            Lr.N1 =rand()%LMAX; /* Posicoes aleatorias */
            Lr.N2 =rand()%CMAX;
            if((Lh.N1 != Lr.N1) && (Lh.N2 != Lr.N2))
            {
                A.Probos[Lr.N1][Lr.N2]=1;
                break;
            }
        }
    }
    for(n4=0;n4<(NPEDRA);n4++)
    {
        while(n3!=-1) //infinito
        {
            Lp.N1 =rand()%LMAX; /* Posicoes aleatorias */
            Lp.N2 =rand()%CMAX;

            if(((Lp.N1 != Lh.N1)&&(Lp.N1 != Lr.N1)) && ((Lp.N2 != Lh.N2)&&(Lp.N2 != Lr.N2)))
            {
                A.Ppedra[Lp.N1][Lp.N2] = 1;
                break;
            }
        }
    }
}           

void tabuleiro(int nivel)
{
    int n1,n2;

    printf("\n  ");
    for(n1=0;n1<TABMAX;n1++) /*  borda de cima */
        printf("- ");
    printf("\n");

    for(n1=0;n1<CMAX;n1++)
    {
        printf("| ");      /*  borda esquerda */
        for(n2=0;n2<LMAX;n2++)/* mapa */
        {
            if(A.posicao[n1][n2] == 1)
                printf(" H");
            else if(A.Ppedra[n1][n2] == 1)
                printf(" @");
            else if(A.Probos[n1][n2] == 1)
                printf(" +");
            else
                printf("  ");
        }
        printf("|\n");/* borda direita */
    }
    printf("  ");
    for(n1=0;n1<TABMAX;n1++)
        printf("- ");
    printf("\n Nivel: %d",nivel);

}

void mover(char tecla)
{
    printf(" ----------- %c %s ------------- \n",tecla);
    printf(" ------------------ \n");

    if((tecla == 'd')) //&& (Lh.N2<CMAX))
    {
        printf("116\n");
        Lh.N2++;
    }   
    if((tecla == 'w')) //&& (Lh.N1<0))
    {
        printf("121\n");
        Lh.N1++;
    }
    if((tecla == 'a')) //&& (Lh.N2<0))
    {
        printf("126\n"); 
        Lh.N2--;
    }
    if((tecla == 's')) //&& (Lh.N1<LMAX))
    {
        printf("131\n");
        Lh.N1--;
    }
}
