#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int turnsLeft = 9;
int check = 0;
void initTable(char (*mat)[3][3]);
void printTable(char (*mat)[3][3]);
int CPURandNumber();
void CPUTurn(char (*mat)[3][3]);
void playerTurn(char (*mat)[3][3]);
void checkWinner(char (*mat)[3][3], int *check);
int main()
{
    char mat[3][3];
    srand(time(NULL));
    initTable(&mat);
    while (turnsLeft > 0)
    {
        if (turnsLeft % 2 != 0)
        {
            playerTurn(&mat);
            printTable(&mat);
            checkWinner(&mat, &check);
            printf("\n");
            if (check != 0)
            {
                break;
            }
        }
        else
        {
            CPUTurn(&mat);
            printTable(&mat);
            checkWinner(&mat, &check);
            printf("\n");
            if (check != 0)
            {
                break;
            }
        }
    }
    return 0;
}

void initTable(char (*mat)[3][3])
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            *mat[i][j] = ' ';
        }
    }
}

void printTable(char (*mat)[3][3])
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            printf("%c ", *mat[i][j]);
            if (j < 2)
            {
                printf("|");
            }
            
        }
        printf("\n");
        if (i < 2)
        {
            printf("--------\n");
        }   
    }
}

int CPURandNumber()
{
    int rd_number = rand() % 3;
    return rd_number;
}

void CPUTurn(char (*mat)[3][3])
{
    int firstNumber = CPURandNumber();
    int secondNumber = CPURandNumber();
    while (*mat[firstNumber][secondNumber] != ' ' && turnsLeft > 0)
    {
        firstNumber = CPURandNumber();
        secondNumber = CPURandNumber();
    }
    if(turnsLeft > 0)
    {
        *mat[firstNumber][secondNumber] = 'O';
        turnsLeft--;
    }
}

void playerTurn(char (*mat)[3][3])
{
    int field1, field2;
    printf("Enter which field you want to play (must enter X and Y axes): ");
    scanf("%d %d", &field1, &field2);
    if (*mat[field1 - 1][field2 - 1] == ' ' && turnsLeft > 0)
    {
        *mat[field1 - 1][field2 - 1] = 'X';
        turnsLeft--;
    }
    else
    {
        printf("Invalid place.\n");
    }
}

void checkWinner(char (*mat)[3][3], int *check)
{
    int winner = -1;
    for (size_t i = 0; i < 3; i++)
    {
        if (*mat[i][0] != ' ' && *mat[i][0] == *mat[i][1] && *mat[i][0] == *mat[i][2])
        {
            winner = (*mat[i][0] == 'X') ? 1 : 0;
            break;
        }
    }
    if (winner == -1)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (*mat[0][i] != ' ' && *mat[0][i] == *mat[1][i] && *mat[0][i] == *mat[2][i])
            {
                winner = (*mat[0][i] == 'X') ? 1 : 0;
                break;
            }
        }
    }
    if (winner == -1)
    {
        if (*mat[0][0] != ' ' && *mat[0][0] == *mat[1][1] && *mat[0][0] == *mat[2][2])
        {
            winner = (*mat[0][0] == 'X') ? 1 : 0;
        }
        else if (*mat[0][2] != ' ' && *mat[0][2] == *mat[1][1] && *mat[0][2] == *mat[2][0])
        {
            winner = (*mat[0][2] == 'X') ? 1 : 0;
        }
    }
    if (winner == 1)
    {
        printf("YOU WON!\n");
        *check = 1;
    }
    else if (winner == 0)
    {
        printf("YOU LOST!\n");
        *check = 1;
    }
    else if (turnsLeft == 0)
    {
        printf("IT'S A DRAW!\n");
        *check = 1;
    }
}