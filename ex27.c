/* Exercicio 27 - Desenvolver jogo Robots em  linguagem C.
 * Autores: Flavio Henrique Duarte Santos Filho
 *          Vinicius Lins de Sa
 * Orientador: Ruben C. Benante
 * Disciplina: Informatica para Controle e Automacao. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB 10 /*Criacao da matriz 10x10*/
#define MAXTAB 100 /* Sao as 99 posicoes existentes no mapa para o robo iniciar a partida*/
#define POS MAXTAB /*valor que as coordenadas vao assumir no mapa*/
typedef struct
{
    int matriz[TAB][TAB];
}dados d;

int main(void)
{
    int a, b; /*contadores*/
    int vez;  /*opção que vai selecionar de quem sera a vez de jogar, do computador ou do jogador.*/
    srand(time(NULL)); /* Vai gerar uma nova posicao para o robo a cada inicio de uma nova partida*/
    vez*= -1
        while
        {
            if(vez= -1)
                homemjoga();
            else
                computadorjoga():
        }
}         

dados inicializa(void)
{
    int x, y, z;
    for(x=0; x<MAXTAB; x++)
        for(y=0; y<MAXTAB; y++)
            d.tab[x][y]=0 /*posição livre*/

    
    x=randomPos();
    d.tab[Pos][x%Pos]=1 /*pedra*/
    
        
    x=randomPos();
    d.tab[Pos][x%Pos]=2 /*humano*/
   
   /* x=randomPos(); -- a função rand()%Pos justamente para que a pedra/humano/robo possa a cada nova partida iniciar numa das 99 posicoes distintas existentes.
    d.tab[Pos][x%Pos]=3 - robo*/

void imprimemapa(void)
{
    int x, y;

    system("clear || cls"); /*limpar a tela tanto em linux quanto no windows*/
    printf("\n -");
    for(x=0; x<MAXTAB; x++) /*borda superior*/
    printf(" -");
printf(" -");
    
    for(x=0; x<MAXTAB; x++)
    {
        printf("\n|"); /*fazer a borda da equerda*/
        for(y=0; y<MAXTAB; y++) /* desenhar o mapa*/
        {
            switch(d.tab[x][y]) /*iniciar mapa já com os elementos dentro*/
            {
                case 1:
                    printf(". "); /*espaco livre*/
                    break;
                case 2:
                    printf("*"); /*pedra*/
                    break;
                case 3:
                    printf("@"); /*robo*/
                    break;
                case 4:
                    printf("I"); /*homem*/
                    break;
                default:
                    printf("\nErro na construcao do mapa.");
            }
        }

        printf("|"); /* forma borda direita*/
    }

    printf("\n-"); /*forma borda inferior*/
    for(x=0; x<MAXTAB; x++)
        printf(" -");
    printf(" -\n");
    imprimemenu();
    return;
}


/*void humanojoga(void) / void computadorjoga(void) - prototipos para vez de quem vai jogar */

void menu(void)
{ 
    printf("\n(c) - cima\n(b) - baixo\n(t) - teletransporte\n(x) - sair\n(e) - esquerda\n(d) - direita\n(s) - salvar\n");
    return;
}

/*Sequencia de raciocinio para montar o programa:
 * 1- Funçao para imprimir as opçoes do robo ( acho que a função menu de cima como comentario resolve isso, ou parte), e imprimir a matriz com o jogador, robo e as pedras.
 * 2- Função para o movimento do robo quando for a vez do computador jogar.
 * 3- Criterio de parada para caso o jogador morra ou chegue ao nivel 5.
 * 4- Estabalecer a pontução do jogador a cada nova conquista ou perda (score).
 * 5- Regras do score:
 *  5.1 - A cada teletransporte que o jogador usar ele perderá 5 pontos e ele so tera direito a 2 por partida.
 *  5.2 - Caso de game over o jogador perde toda a pontuacao.
 *  5.3 - Destruiu um robo, ganha 10 pontos.
 *  5.4 - Passou de nivel , ganha 50 pontos. */

