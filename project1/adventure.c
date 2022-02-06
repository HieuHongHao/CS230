#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include "character.h"
struct Avatar{
    char * name;
    Item * inventory;
};
void distributeItems(Room **board, Item* item)
{
    int i = rand() % 3;
    int j = rand() % 3;
    int numEquippedRooms = 0;
    while (numEquippedRooms < 6)
    {
        if (board[i][j].itemList == NULL)
        {
            Item anItem  = item[numEquippedRooms];
            numEquippedRooms++;
            (board[i][j].itemList) = (Item *)malloc(sizeof(Item));
            *(board[i][j].itemList) = anItem;
        }
        i = rand() % 3;
        j = rand() % 3;
    }
}

void distributeRoom(Room **board)
{
    int m = rand() % 3;
    int k = rand() % 3;
    char room[9][30] = {"Kitchen", "Lounge", "Study Room", "Library", "BallRoom", "Hall", "Conservatory", "Billiard Room", "Dining Room"};
    int assignedNameRooms = 0;
    while (assignedNameRooms < 9)
    {
        if (board[m][k].name == NULL)
        {
            // probably have to malloc here. C be like pointers and malloc go brah brah
            board[m][k].name = (char *)malloc(sizeof(room[assignedNameRooms]));
            strcpy(board[m][k].name, room[assignedNameRooms]);
            assignedNameRooms++;
        }
        m = rand() % 3;
        k = rand() % 3;
    }
}
// void distributeCharacter(Room ** board)
void move(Room * current, Room * direction, char * currentRoom ){
    if(direction == NULL){
        printf("direction is not valid, please renter direction \n");
        return;
    }
    *current = *direction;
    printf("Move to : %s\n",currentRoom);
}

int main()
{
    srand(time(NULL));
    Room **board = constructBoard();
    Item items[6] = {
        (Item){"Shrek Toy",NULL},
        (Item){"Shrek Spoon",NULL},
        (Item){"Shrek Towel",NULL},
        (Item) {"Shrek Love Chair",NULL},
        (Item){"Shrek Knife",NULL},
        (Item){"Shrek Pencil",NULL}
    };
    distributeRoom(board);
    distributeItems(board,items);
    int i = rand() % 3;
    int j = rand() % 3;
    int m = rand() % 3;
    Room current = board[i][j];
    size_t bufferSize = 32;
    char * buffer = (char *)malloc(bufferSize);
    char commandTable[8][100] = {"help: See list of commands", "list: See list of items,rooms,or characters",
    "look: See current room information", "go: Travel to a direction", "take: Pick up an item",
    "drop: Drop an item", "inventory: check current items","clue: make a guess"
    };
    char characters[6][100] ={
        "Shrek",
        "Betas Shrek",
        "Sigma Shrek",
        "Giga Shrek",
        "Shrek The Ogre",
        "Shrek Fanboy"
    };
    
    struct Avatar user = {characters[m],NULL};
    while(getline(&buffer,&bufferSize,stdin)!= -1){
        char * token = strtok(buffer,"\n");
        if(!strcmp(token,"help")){
            for(int i = 0 ;i < 8 ; i++){
                printf("%s\n",commandTable[i]);
            }
        }
        else if(!strcmp(token,"look")){
            char * North = current.North == NULL ? "End" : current.North->name; 
            char * South = current.South == NULL ? "End" : current.South->name;
            char * East = current.East == NULL ? "End" : current.East->name;
            char * West = current.West == NULL ? "End" : current.West->name;
            printf("%s, North: %s , South: %s, East: %s, West: %s \n",current.name,North,South,East,West);
            printf("Current items:\n");
            Item * temp =  current.itemList;
            if(temp == NULL){printf("None \n");}
            while(temp != NULL){
                printf("%s \n",temp->name);
                temp = temp->nextItem;
            }
        }
        else if(!strcmp(token,"exit")){
            printf("exited \n");
            break;
        }
        else if(!strcmp(token,"go")){
            printf("Pick a direction: north,south,east,or west\n");
            getline(&buffer,&bufferSize,stdin);
            token = strtok(buffer,"\n");
            if(!strcmp(token,"north")){
                move(&current,current.North,"north");
            }
            else if(!strcmp(token,"south")){
                move(&current,current.South,"south");
            }
            else if(!strcmp(token,"east")){
                move(&current,current.East,"east");
            }
            else{
                move(&current,current.West,"west");
            }
        }
    }
    return 0;
}