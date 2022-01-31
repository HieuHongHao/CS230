#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include "character.h"


void distributeItems(Room ** board)
{
    srand(time(0));
    int i = rand() % 3;
    int j = rand() % 3;
    int numEquippedRooms = 0;
    while(numEquippedRooms < 6){
        if(board[i][j].itemList == NULL){
            char * itemName = malloc(100);    
            numEquippedRooms ++;
            char name[] = "Item";
            snprintf(itemName,38,"%s %d",name,numEquippedRooms);
            (board[i][j].itemList) = (Item *)malloc(sizeof(Item));
            *(board[i][j].itemList) = (Item){itemName,NULL};
        }
        i = rand() % 3;
        j = rand() % 3;
    }
}
/*
void distributeCharacter(Room **board, Character *characters)
*/
    int main(int argc, char *argv[])
{
    /*int opt;*/
    Room **board = constructBoard();
    distributeItems(board);
    /* Create a linkedlist of 6 items */
    srand(time(0));
    int i = rand() % 3;
    int j = rand() % 3;
    Room startingRoom = board[i][j];
    return 0;
}