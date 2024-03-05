#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

int rollDice(void);
void placeCompToken(char[][6] , int, int, int);
void placeUserToken(char[][6] , int, int, int);
void checkMatch(char[][6] , int, int, int, int[]);
void displayBoard(char[][6] , int, int);

int main()
{
    srand(time(NULL));
    printf("Welcome to the PopThree :)");
    printf("\nLet's get started!");
    char yes_no;


    do
    {
        int score[2]={0,0};
        int computer, player; // for determining who starts first
        int x, i, R=7, C=6, round=7, roundcounter=1;
        char board[7][6]= {{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' '}};

        do //deciding for who's starting first
        {
            player=rollDice();
            computer=rollDice();
            if(player==computer)
            {
                printf("Dices are the same! Re-rolling...\n");
            }

        }
        while(player==computer);
        printf("\n\n-----------------------------------------------\n\n");
        printf("\nI have rolled the dice and got %d!\n", computer);
        printf("I have rolled the dice for you and you got %d!\n", player);

        do
        {
            int play=0;
            printf("\n------------------Round %d----------------------", roundcounter);
            if(player>computer)
            {
                while(play<3)
                {
                    placeUserToken(board, R, C, roundcounter);
                    placeCompToken(board, R, C, roundcounter);
                    play++;
                    displayBoard(board, R, C);
                    checkMatch(board, R, C, round, score);
                }

            }
            else if(computer>player)
            {
                while(play<3)
                {
                    placeCompToken(board, R, C, roundcounter);
                    placeUserToken(board, R, C, roundcounter);
                    play++;
                    displayBoard(board, R, C);
                    checkMatch(board, R, C, round, score);
                }


            }
            roundcounter++;

        }
        while(roundcounter<=7);

        //win-lose check

        if(score[0]>score[1])
        {
            printf("\nI WON!");
        }
        else if(score[0]<score[1])
        {
            printf("\nYOU WON!");
        }
        else
        {
            printf("\nTIE!");
        }

        printf("\nWould you like to play again?:");
        scanf("%c", &yes_no);
        fflush(stdin);
        roundcounter=1;
        if(yes_no=='n' || yes_no=='N')
            printf("\nBye!");
        else if(yes_no!='y' && yes_no!='Y')
        {
            printf("\nInvalid input!");
        }
    } while(yes_no!='n' && yes_no!='N');

    return 0;
}

int rollDice(void)
{
    int a;
    a = (1 + (int) rand() % 6);

    return a;
}

void displayBoard(char board[][6], int r, int c)
{
    printf("\nBoard:\n");
    printf(" \n  1 2 3 4 5 6\n");
    printf("1 %c %c %c %c %c %c\n2 %c %c %c %c %c %c\n3 %c %c %c %c %c %c\n4 %c %c %c %c %c %c\n5 %c %c %c %c %c %c\n6 %c %c %c %c %c %c\n7 %c %c %c %c %c %c",board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5],
           board[1][0], board[1][1], board[1][2], board[1][3], board[1][4],board[1][5],
           board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5],
           board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5],
           board[4][0], board[4][1] ,board[4][2], board[4][3], board[4][4], board[4][5],
           board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5],
           board[6][0], board[6][1], board[6][2], board[6][3], board[6][4], board[6][5],
           board[6][0], board[6][1], board[6][2], board[6][3], board[6][4], board[6][5]);
    printf("\n\n");

    //printing board, value by value.



}

void placeCompToken(char board[][6], int R, int C, int roundcounter)
{
    int checker=0, x=0, row_decider;
    row_decider=R-roundcounter; //depending on the round, computer will pick the right row to add a symbol.

    do
    {
        while(x<C && checker==0)
        {
            if(board[row_decider][x]==' ')
            {
                board[row_decider][x]='+';
                checker=1;
            }

            x++;
        }



    }
    while(checker==0);
    printf("\nMy turn -> I placed token to location (%d,%d)", row_decider+1, x);
    checker=0;
    x=0;

}

void placeUserToken(char board[][6], int R, int C, int roundcounter)
{
    int user_row, user_column, check, row_decider;
    row_decider=R-roundcounter;

    //input checks and assignment below
    do
    {
        printf("\nYour turn -> Enter location to place your token: ");
        scanf("%d %d", &user_row, &user_column);
        if(user_row>7)
        {
            printf("\nYou cannot place a token outside the board!");
            check=0;
        }
        else if(user_row!=row_decider+1)
        {
            printf("\nAt this turn you can only place token to row %d!", row_decider+1);
            check=0;
        }
        else if(board[user_row-1][user_column-1]=='+' || board[user_row-1][user_column-1]=='*')
        {
            printf("\nA token is already placed there!");
            check=0;
        }
        else
            check=1;

        fflush(stdin);

    }
    while(check==0);

    board[user_row-1][user_column-1]='*';

}

void checkMatch(char board[][6] , int R, int C, int round, int score[])
{
    int x, y;
    for(x=0; x<7; x++) //checking array for every possible 3 match and updating scorea array accordingly
    {
        for(y=0; y<4;y++)
        {
            if(board[x][y]=='+' && board[x][y+1]=='+' && board[x][y+2]=='+')
            {
                score[0]++;
            }
            else if(board[x][y]=='*' && board[x][y+1]=='*' && board[x][y+2]=='*')
            {
                score[1]++;
            }
        }
    }
}
