#include "rooms.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int isInvalid(int x, int y)
{
    return x > 2 || x < 0 || y > 2 || y < 0 ;
}

Room **constructBoard()
{
    Room **board = (Room **)calloc(3, sizeof(Room *));
    for (int i = 0; i < 3; i++)
    {
        board[i] = (Room *)calloc(3, sizeof(Room));
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
           board[i][j] = (Room){NULL, (isInvalid(i - 1, j)) ? NULL : &board[i - 1][j], (isInvalid(i + 1, j)) ? NULL : &board[i + 1][j],(isInvalid(i, j + 1)) ? NULL : &board[i][j + 1], (isInvalid(i, j - 1)) ? NULL : &board[i][j - 1], NULL, NULL};
        }
    }
    
    return board;
}