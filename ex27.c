/*Ex27.c: Desenvolver o jogo Robots em linguagem C.
 * Autores: 
 * Flavio Henrique Duarte Santos Filhos
 * Vinicius Lins de Sa
 * Orientador: Ruben C. Benante
 * Disciplina: Informatica para Automacao e Controle*/

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
void moverrobo(void);

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
       // printf("\e[H\e[2J");
        mover(TECLA);
        moverrobo();
    }
    return 0;
}

void valinit(int nivel)
{
    srand(time(NULL));
    int n3=0,n4;

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
    int n1, n2;

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

/*char moverrobo(char tecla)
{
    int x, y, z, w;
    int Probos[LMAX][CMAX];

    for(z=0;z<TABMAX;z++)
    {
        for(w=0;w<TABMAX;w++)
        {
            if(Probos[z][w]==2)
            {
                for(x=0;x<TABMAX;x++)
                {
                    for(y=0;y<TABMAX;y++)
                    {
                        if(Probos[x][y]==3)
                        {
                            if((w-y)>0 && Probos[x+1][y]==0)
                            {
                                Probos[x+1][y]=3;
                                Probos[x][y]=0;
                            }
                            if((w-y)>0 && (Probos[x+1][y]==1 || Probos[x+1][y]==3))
                            {
                                Probos[x+1][y]=1;
                                Probos[x][y]=0;
                            }
                            if((w-y)<0 && Probos[x-1][y]==0)
                            {
                                Probos[x-1][y]=3;
                                Probos[x][y]=0;
                            }
                            if((w-y)<0 && Probos[x+1][y]==2)
                            {
                                return 2;
                            }
                            if((w-y)<0 && (Probos[x-1][y]==1 || Probos[x-1][y]==3))
                            {
                                Probos[x-1][y]=1;
                                Probos[x][y]=0;
                            }
                            if((w-y)>0 && Probos[x-1][y]==2)
                            {
                                return 2;
                            }
                            if((w-y)==0)
                            {
                                if((z-x)>0 && Probos[x][y-1]==0)
                                {
                                    Probos[x][y-1]=3;
                                    Probos[x][y]=0;
                                }
                                if((z-x)>0 && (Probos[x][y-1]==1 || Probos[x][y-1]==3))
                                {
                                    Probos[x][y-1]=1;
                                    Probos[x][y]=0;
                                }
                                if((z-x)>0 && Probos[x][y-1]==2)
                                {
                                    return 2;
                                }
                                if((z-x)<0 && Probos[x][y+1]==0)
                                {
                                    Probos[x][y+1]=3;
                                    Probos[x][y]=0;
                                }
                                if((z-x)<0 && (Probos[x][y+1]==1 || Probos[x][y+1]==3))
                                {
                                    Probos[x][y+1]=1;
                                    Probos[x][y]=0;
                                }
                                if((z-x)<0 && Probos[x][y+1]==2)
                                {
                                    return 2;
                                }
                                if((z-x)==0)
                                {
                                    return 2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
                     
    return -1;
}*/


void moverrobo(void)
{

    int h1, h2, r1, r2, posh1, posh2, posr1, posr2;

    for(h1=0;h1<LMAX;h1++)
    {
        for(h2=0;h2<LMAX;h2++)
        {
            if(A.posicao[h1][h2] == 1)
            {
                posh1=h1;
                posh2=h2;
            }
                
        }
     }

    printf("\nPOSICAO HUMANO %d %d\n", posh1, posh2);
    for(r1=0;r1<LMAX;r1++)
    {
        for(r2=0;r2<LMAX;r2++)
        {
            if(A.Probos[r1][r2] == 1)
            {
                posr1=r1;
                posr2=r2;
            }

        }
     }
    printf("\n POSICAO ROBO %d %d\n", posr1, posr2);

    if(posr1 < posh1 && posr2==posh2)
    {
        A.Probos[posr1][posr2] = 0;
        A.Probos[posr1+1][posr2] = 1;
    }
    else
        if(posr1 > posh1 && posr2==posh2 )
        {
            A.Probos[posr1][posr2] = 0;
            A.Probos[posr1-1][posr2] = 1;
        }   
        else
            if(posr1 < posh1 && posr2 < posh2)
            {
            A.Probos[posr1][posr2] = 0;
            A.Probos[posr1+1][posr2+1] = 1;
            }
            else
                if(posr1 < posh1 && posr2 > posh2)
                {
                A.Probos[posr1][posr2] = 0;
                A.Probos[posr1+1][posr2-1] = 1;
                }
                else
                    if(posr1 > posh1 && posr2 > posh2)
                    {
                        A.Probos[posr1][posr2] = 0;
                        A.Probos[posr1-1][posr2-1] = 1;
                    }
                    else
                    
                        if(posr1 > posh1 && posr2 < posh2)
                        {
                        A.Probos[posr1][posr2] = 0;
                        A.Probos[posr1-1][posr2+1] = 1;
                        }
                        else
                            if(posr1== posh1 && posr2 > posh2)
                            {
                                A.Probos[posr1][posr2] = 0;
                                A.Probos[posr1][posr2-1] = 1;
                            }
                            else
                                if(posr1 == posh1 && posr2 < posh2)
                                {
                                    A.Probos[posr1][posr2] = 0;
                                    A.Probos[posr1][posr2+1] = 1;
                                }
       
    /*if(Lr.N1>Lh.N1 && Lr.N2>Lh.N2)
    {
        for(r1=0;r1<LMAX;r1--)
        {
            for(r2=0;r2<CMAX;r2--)
            {
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1-1)][r2-1] = 1;
                }
            }
    
        }
    }   
    if(Lr.N1<Lh.N1 && Lr.N2>Lh.N2)
    { 
        for(r1=0;r1<LMAX;r1++)
        {
            for(r2=0;r2<CMAX;r2--)
            {
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1+1)][(r2-1)] = 1;
                }
            }
        }
    }

    if(Lr.N1<Lh.N1 && Lr.N2<Lh.N2)
    { 
        for(r1=0;r1<LMAX;r1++)
        {
            for(r2=0;r2<CMAX;r2++)
            {
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1+1)][(r2+1)] = 1;
                }
            } 
        }     
    }


    if(Lr.N1>Lh.N1 && Lr.N2<Lh.N2)
    {
        for(r1=0;r1<LMAX;r1--)
        {    
            for(r2=0;r2<CMAX;r2++)
            {
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1-1)][(r2+1)] = 1;
                }
            } 
        }
    }

    if(Lr.N1==Lh.N1 && Lr.N2>Lh.N2)
    { 
            for(r2=0;r2<CMAX;r2--)
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1)][(r2-1)] = 1;
                }

        
    }

    if(Lr.N1==Lh.N1 && Lr.N2<Lh.N2)
    {
       // for(r1=0;r1<LMAX;r1--)
            for(r2=0;r2<CMAX;r2++)
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[r1][(r2-1)] = 1;
                }


        
    }

    if(Lr.N1>Lh.N1 && Lr.N2==Lh.N2)
    {
        for(r1=0;r1<LMAX;r1--)
           // for(r2=0;r2<CMAX;r2--)
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1-1)][r2] = 1;
                }


        
    }

    if(Lr.N1<Lh.N1 && Lr.N2==Lh.N2)
    {
        for(r1=0;r1<LMAX;r1++)
           // for(r2=0;r2<CMAX;r2--)
                if(A.posicao[r1][r2] == 1)
                {
                    A.posicao[r1][r2] = 0;
                    A.posicao[(r1+1)][r2] = 1;
                }
        
    }*/

    return;
}
