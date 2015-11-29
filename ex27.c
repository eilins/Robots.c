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
void teleport(char tecla);
void moverrobo(char tecla);

int main(void)
{
    int NIVEL=1,sair=0,morto=0,NIVELUP =0,n1,n2;
    char TECLA;
    int tecla;
    valinit(NIVEL);
    
    while( morto == 0 )/*|| sair ==0 ) || (NIVELUP == 0)) */
    {
        tabuleiro(NIVEL);
        printf("\nDigite Uma tecla\nDigite 'x' pra sair\nDigite 'w' para mover para cima\nDigite 'a' para mover para esquerda\nDigite 's' para mover para baixo\nDigite 'd' para mover para direita\nDigite 't' para teletransportar\n"); /* menu aqui */
        TECLA = getchar();
        getchar();
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

    printf("\nJOGO ROBOTS!\n");
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
                printf(" I");
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
    int n1,n2;

    printf(" ----------- %c ------------- \n",tecla);

    if((tecla == 'd')) //&& (Lh.N2<CMAX))
    {
        for(n1=0;n1<LMAX;n1++)
        {
            for(n2=0;n2<CMAX;n2++)
            {
                if(A.posicao[n1][n2] == 1)
                {
                    A.posicao[n1][n2] = 0;
                   // printf("%d %d\n", n1, n2-1);
                    A.posicao[n1][(n2+1)] = 1;
                   // printf("&&& A.posicao[%d][%d] = %d '1'\n", n1, n2+1, A.posicao[n1][n2+1]);
                    break;
                }
            }
        }    
    }   
    if((tecla == 'w')) //&& (Lh.N1<0))
    {
        for(n1=0;n1<LMAX;n1++)
        {
            for(n2=0;n2<CMAX;n2++)
            {
                if(A.posicao[n1][n2] == 1)
                {
                    A.posicao[n1][n2] = 0;
                    A.posicao[(n1-1)][n2] = 1;
                    break;
                }
            }
        }     
    }
    if((tecla == 'a')) //&& (Lh.N2<0))
    {
        for(n1=0;n1<LMAX;n1++)
        {
            for(n2=0;n2<CMAX;n2++)
            {
                if(A.posicao[n1][n2] == 1)
                {
                    A.posicao[n1][n2] = 0;
                    printf("%d %d\n", n1, n2+1);
                    A.posicao[n1][(n2-1)] = 1;
                    break;
                }
            }
       }
    }
    if((tecla == 's')) //&& (Lh.N1<LMAX))
    {
    int enable=0;

        for(n1=0;n1<LMAX;n1++)
        {
            for(n2=0;n2<CMAX;n2++)
            {
                if(A.posicao[n1][n2] == 1 && enable == 0)
                {
                    A.posicao[n1][n2] = 0;
                    printf("\nem s: %d", n1);
                    A.posicao[n1+1][n2] = 1; /*nao pode ser -1 pq fica igual ao caso do 'w'.*/
                    enable=1;
                    break;
                }
            }
        }    
    }
    if(tecla == 't')
    {
    int tn1, tn2;
        
        for(n1=0;n1<LMAX;n1++)
        {
            for(n2=0;n2<CMAX;n2++)
            {
                if(A.posicao[n1][n2] == 1)
                {
                    tn1=rand()%LMAX;
                    tn2=rand()%CMAX;
                    A.posicao[tn1][tn2]=1;
                    A.posicao[n1][n2]=0;
                }
            }
        }
    }
}

void teleporte(char tecla)
{   
    int n1,n2,comando, comandoinvalido, sair, d;
    char TECLA;
    srand(time(NULL));

     //   Lh.N1=rand()%LMAX;
     //   Lh.N2=rand()%CMAX;
    
    switch(comando)
    {
        case 'x':
            printf("\n Voce tem certeza que deseja sair do jogo? (S - sim / N - nao)\n: ");
        do
        {
            do
            {
                sair=getchar();
            }while(sair=='\n');

            if (sair!='S' && sair!='N')
            {
                printf("\nComando invalido!\n: ");
                comandoinvalido=1;
            }
            else
            {
                comandoinvalido=0;
                if(sair=='S')
                    exit(1);
                if(sair=='N')
                    return d;
            } 
        }
        while(comandoinvalido);
    }
    return d;
}

void moverrobo(char tecla)
{

    if(Lr.N1>Lh.N1 && Lr.N2>Lh.N2)
    {
        Lr.N1--;
        Lr.N2--;
    }
   
    if(Lr.N1<Lh.N1 && Lr.N2>Lh.N2)
    {
        Lr.N1++;
        Lr.N2--;
    }
    if(Lr.N1<Lh.N1 && Lr.N2<Lh.N2)
    {
        Lr.N1++;
        Lr.N2++;
    }
    if(Lr.N1>Lh.N1 && Lr.N2<Lh.N2)
    {
        Lr.N1--;
        Lr.N2++;
    }
    if(Lr.N1==Lh.N1 && Lr.N2>Lh.N2)
    {
        Lr.N2--;
    }
    if(Lr.N1==Lh.N1 && Lr.N2<Lh.N2)
    {
        Lr.N2++;
    }
    if(Lr.N1>Lh.N1 && Lr.N2==Lh.N2)
    {
        Lr.N1--;
    }
    if(Lr.N1<Lh.N1 && Lr.N2==Lh.N2)
    {
        Lr.N1++;
    }
}

