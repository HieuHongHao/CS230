#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rooms.h"
#include "items.h"



int main(int argc, char *argv[]){
    /*int opt;
    Room ** board = constructBoard();
    srand(time(0));
    int i = rand() % 3;
    int j = rand() % 3;
    Room startingRoom = board[i][j];
    free(board);*/
    Item * head = (Item*)malloc(sizeof(Item));
    Item firstItem = {"item 1", NULL};
    head = &firstItem;
    Item secondItem = {"item 2", NULL};
    add_item(head,&secondItem);
    remove_item(head,"item 2");
    
    return 0 ;
}