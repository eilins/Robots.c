/*Ex27.c: Desenvolver o jogo Robots em linguagem C.
 * Autores: 
 * Flavio Henrique Duarte Santos Filhos
 * Vinicius Lins de Sa
 * Orientador: Ruben C. Benante
 * Disciplina: Informatica para Automacao e Controle*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#define LMAX 15
#define CMAX 15
#define TABMAX 20
#define NPEDRA 5
#define NIVELMAX 5
#define PTELE 5
#define PNIVEL 100
#define PROBO 10

/* Bordas UTF 8 */

#define WUL L'\u2518' /* ^VU2518 ┘ */
#define WDL L'\u2510' /* ^VU2510 ┐ */
#define WDR L'\u250c' /* ^VU250c ┌ */
#define WUR L'\u2514' /* ^VU2514 └ */
#define WVH L'\u253c' /* ^VU253c ┼ */
#define WHH L'\u2500' /* ^VU2500 ─ */
#define WVR L'\u251c' /* ^VU251c ├ */
#define WVL L'\u2524' /* ^VU2524 ┤ */
#define WUH L'\u2534' /* ^VU2534 ┴ */
#define WDF L'\u252c' /* ^VU252c ┬ */
#define WVV L'\u2502' /* ^VU2502 │ */
#define WGL L'\u2571' /* ^VU2571 ╱ */
#define WGR L'\u2572' /* ^VU2572 ╲ */
#define WGX L'\u2573' /* ^VU2573 ╳ */

struct lista
{
    int Ppedra[LMAX][CMAX];
    int Probos[LMAX][CMAX];
    float posicao[LMAX][CMAX];
    float score;
}A={};

struct lugar
{
    int N1;
    int N2;
}Lr,Lh,Lp; /* R ==robo , H == humano, P==pedra, L ==lugar */

void valinit(int nivel);
void tabuleiro(int nivel);
char mover(char tecla);
void teleport(char tecla);
int moverrobo(int n, int antigo);

int main(void)
{
    int NIVEL=1, sair=0, morto=0, NIVELUP=0, ANTIGO, i, n1, n2;
    char TECLA;
    int retorno;
    valinit(NIVEL);

    while(morto != 1 && retorno!='x')/*|| sair ==0 ) || (NIVELUP == 0)) */
    {   
        ANTIGO = -1;
        if(morto==2)
        {
            printf("\nVoce passou de nivel\n");
            NIVEL++;
            A.score = A.score+PNIVEL;
            valinit(NIVEL);
        }
        tabuleiro(NIVEL);
        printf("\nDigite Uma tecla\nDigite 'x' pra sair\nDigite 'w' para mover para cima\nDigite 'a' para mover para esquerda\nDigite 's' para mover para baixo\nDigite 'd' para mover para direita\nDigite 't' para teletransportar\n"); /* menu aqui */
        TECLA = getchar();
        if(TECLA == 'x')
            return 0;
        getchar();
        printf("\e[H\e[2J");
        mover(TECLA);
        for(i=0; i<NIVEL; i++)
        {
            morto = moverrobo(i, ANTIGO);
            ANTIGO++;
        }
    }
        printf("SCORE : %g", A.score);
        return 0;
    }

void valinit(int nivel)
{ 
        int i,j;

        for(i=0;i<LMAX;i++)
            for(j=0;j<CMAX;j++)
                A.Ppedra[i][j]=0;

        for(i=0;i<LMAX;i++)
            for(j=0;j<CMAX;j++)
                A.Probos[i][j]=0;

        for(i=0;i<LMAX;i++)
            for(j=0;j<CMAX;j++)
                A.posicao[i][j]=0;

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

        setlocale(LC_ALL, ""); /* para caracteres UTF-8*/

        printf("\nJOGO ROBOTS!\n");
        printf("\n%lc", WDR);
        for(n1=0;n1<CMAX;n1++) /*  borda de cima */
        {
            printf("%lc", WHH);
            if(n1<CMAX-1)
                printf("%lc", WDF);
        }
        printf("%lc", WDL);

        for(n1=0;n1<CMAX;n1++)
        {
            printf("\n%lc", WVV);      /*  borda esquerda */
            for(n2=0;n2<CMAX;n2++)/* mapa */
            {
                if(A.posicao[n1][n2] == 1)
                    printf("I%lc", WVV);
                else if(A.Ppedra[n1][n2] == 1)
                    printf("@%lc", WVV);
                else if(A.Probos[n1][n2] == 1)
                    printf("+%lc", WVV);
                else if(A.Probos[n1][n2] == 2)
                    printf("$%lc", WVV);
                else
                    printf(" %lc", WVV);
            }

            if(n1<CMAX-1)
            {
                printf("\n%lc", WVR);
                for(n2=0;n2<CMAX;n2++)
                {
                    printf("%lc", WHH);
                    if(n2<CMAX-1)
                        printf("%lc", WVH);
                }
                printf("%lc", WVL);
            }
        }

        printf("\n%lc", WUR);
        for(n1=0;n1<CMAX;n1++)
        {
            printf("%lc", WHH);
            if(n1<CMAX-1)
                printf("%lc", WUH);
        }
        printf("%lc\n", WUL);
        printf("\n Nivel: %d \n Score: %g \n",nivel, A.score);

    }

    char mover(char tecla)
    {
        int n1, n2;

        printf(" ----------- %c ------------- \n",tecla);

        if((tecla == 'd')) //&& (Lh.N2<CMAX))
        {
            for(n1=0;n1<LMAX;n1++)
            {
                for(n2=0;n2<CMAX;n2++)
                {
                    if((A.posicao[n1][n2] == 1 && (n2+1 != LMAX)) && A.Ppedra[n1][n2+1] == 0)
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
                    if((A.posicao[n1][n2] == 1 && n1 != 0) && A.Ppedra[n1-1][n2] == 0)
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
                    if((A.posicao[n1][n2] == 1 && n2 != 0) && A.Ppedra[n1][n2-1] == 0)
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
                    if((((A.posicao[n1][n2] == 1 && enable == 0) && n1+1 != LMAX) && A.Ppedra[n1+1][n2] == 0))
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
            int tn1, tn2, n3=1;
            A.score = A.score - PTELE;
            for(n1=0;n1<LMAX;n1++)
            {
                for(n2=0;n2<CMAX;n2++)
                {
                    if(A.posicao[tn1][tn2]=0)  
                    { 
                        do{
                            tn1=rand()%LMAX;
                            tn2=rand()%CMAX;
                            if(A.Ppedra[tn1][tn2] == 0)
                            {
                                A.posicao[tn1][tn2]=1;
                                A.posicao[n1][n2]=0;
                                break;
                            }
                        }while(n3 != 0);

                    }
                }
            }
        }


        return tecla;
    }

int moverrobo(int n, int antigo)
{

        int  h1, h2, r1, r2, posh1, posh2, posr1[NIVELMAX], posr2[NIVELMAX], pospedra[5][2];

        /*    printf("\nPOSICAO HUMANO %d %d\n", posh1, posh2);*/
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


        //    printf("\n POSICAO ROBO %d %d\n", posr1, posr2);
        for(r1=0;r1<LMAX;r1++)
        {
            for(r2=0;r2<LMAX;r2++)
            {
                if(A.Probos[r1][r2] == 1 && n!=antigo)
                {
                    posr1[n]=r1;
                    posr2[n]=r2;
                }

            }
        }
        /* printf("\n POSICAO ROBO %d %d\n", posr1, posr2);*/

        if(((posr1[n] < posh1 && posr2[n]==posh2) && A.Probos[posr1[n]][posr2[n]] ==1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]+1][posr2[n]] = 1;
        }
        // else
        if(((posr1[n] > posh1 && posr2[n]==posh2) && A.Probos[posr1[n]][posr2[n]] == 1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]-1][posr2[n]] = 1;
        }   
        //  else
        if(((posr1[n] < posh1 && posr2[n] < posh2) && A.Probos[posr1[n]][posr2[n]] == 1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]+1][posr2[n]+1] = 1;
        }
        //    else
        if(((posr1[n] < posh1 && posr2[n] > posh2) && A.Probos[posr1[n]][posr2[n]] == 1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]+1][posr2[n]-1] = 1;
        }
        //      else
        if(((posr1[n] > posh1 && posr2[n] > posh2) && A.Probos[posr1[n]][posr2[n]] == 1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]-1][posr2[n]-1] = 1;
        }
        //        else

        if(((posr1[n] > posh1 && posr2[n] < posh2) && A.Probos[posr1[n]][posr2[n]] == 1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]-1][posr2[n]+1] = 1;
        }
        //          else
        if(((posr1[n]== posh1 && posr2[n] > posh2) && A.Probos[posr1[n]][posr2[n]] == 1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]][posr2[n]-1] = 1;
        }
        //            else
        if(((posr1[n] == posh1 && posr2[n] < posh2) && A.Probos[posr1[n]][posr2[n]]==1))
        {
            A.Probos[posr1[n]][posr2[n]] = 0;
            A.Probos[posr1[n]][posr2[n]+1] = 1;
        }


        for(r1=0;r1<LMAX;r1++)
        {
            for(r2=0;r2<LMAX;r2++)
            {
                if(A.Probos[r1][r2] == 1)
                {
                    posr1[n]=r1;
                    posr2[n]=r2;
                }
            }
        }
        printf("\n\nNOVA POSICAO ROBO E HUMANO: %d %d    %d %d\n", posr1[n], posr2[n], posh1, posh2);

        int c=0;

        for(r1=0; r1<LMAX; r1++)
        {
            for(r2=0; r2<LMAX; r2++)
            {
                if(A.Ppedra[r1][r2] == 1)
                {
                    pospedra[c][0]=r1;
                    pospedra[c][1]=r2;
                    c=c+1;
                }
            }
        }

        for(c=0;c<5;c++)
        {
            if(posr1[n]==pospedra[c][0] && posr2[n]==pospedra[c][1])
            {
                printf("\nRobo Destruido!\n");
                A.Probos[posr1[n]][posr2[n]] = 0;
                A.score = A.score+PROBO;

            }
        }
        int n1, n2, n3=0;

        /* if(posr1[n] == posr1[n-1] && posr1[n] == posr1[n-1])
         * {
         *      A.Probos[n1][n2] = 2;
         *      printf("\n Oi,os robos se chocaram\n");
         *      return 2;
         *      }
         */
        for(n1=0; n1<LMAX; n1++)
        {
            for(n2=0; n2<CMAX; n2++)
            {
                if(A.Probos[n1][n2] == 1)
                {
                    n3 = 1;
                }
            }
        }
        if(n3 == 0)
        {
            printf("todos morreram \n");
            return 2;
        }

        if(posr1[n] == posh1 && posr2[n] == posh2)
        {
            printf("\n O robo lhe pegou! \n");
            A.score = 0;
            return 1;
        }


        return 0;
    }
