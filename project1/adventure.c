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
void distributeItemsAndCharacters(Room **board, Item* item, Character * characters)
{
    int i = rand() % 3;
    int j = rand() % 3;
    int numEquippedRooms = 0;
    while (numEquippedRooms < 6)
    {
        if (board[i][j].itemList == NULL)
        {
            Item anItem  = item[numEquippedRooms];
            Character character = characters[numEquippedRooms];
            numEquippedRooms++;
            board[i][j].itemList = (Item *)malloc(sizeof(Item));
            board[i][j].charList = (Character *)malloc(sizeof(Character));
            *(board[i][j].itemList) = anItem;
            *(board[i][j].charList) = character;
        }
        i = rand() % 3;
        j = rand() % 3;
    }
}

void distributeRoom(Room **board)
{
    int m = rand() % 3;
    int k = rand() % 3;
    char room[9][30] = {"Kitchen", "Lounge", "Study Room", "Library", "Ball Room", "Hall", "Conservatory", "Billiard Room", "Dining Room"};
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

void move(Room ** current, Room * direction, char * currentRoom , char * currChar ){
    if(direction == NULL){
        printf("direction is not valid, please renter go and choose a new direction \n");
        return;
    }
   Character* removed = remove_character(&((*current)->charList),currChar);
    if(removed != NULL){
      Character removedChar = *removed;
      add_character(&(direction->charList),removedChar);
    }
    *current = direction;
    if(removed == NULL){
        printf("None was removed \n");
    }else{
        printf("Move %s to : %s\n",currChar,currentRoom);
    }
}
void moveCharacter(Room ** current, char * character, Room ** board){
    Character * temp;
    for(int i = 0 ;  i < 3 ; i++){
        for(int j = 0 ; j < 3; j++){
            temp = remove_character(&(board[i][j].charList),character);
            if(temp!= NULL){
               add_character(&((*current)->charList),*temp);
               printf("%s moved to %s \n",character,(*current)->name);
               return;
            }
        }
    }
    printf("No charcter was moved \n");
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
    Character characters[6]={
        (Character){"Shrek",NULL},
        (Character){"Betas Shrek",NULL},
        (Character){"Sigma Shrek",NULL},
        (Character){"Giga Shrek",NULL},
        (Character){"Shrek The Ogre",NULL},
        (Character){"Shrek Fanboy",NULL}
    };
    distributeRoom(board);
    distributeItemsAndCharacters(board,items,characters);
    int i = rand() % 3;
    int j = rand() % 3;
    int m = rand() % 3;
    
    Room* current ;
    int flag = 0;
    while (!flag)
    {
        if(board[i][j].charList != NULL){
            current = &board[i][j];    
            flag = 1;
        }
        else{
            i = rand() % 3 ;
            j = rand() % 3 ;
        }
    }
    
    struct Avatar user = {current->charList->name,NULL};
    Room answer = board[i][j];    
    int cludeMade = 0;
    
    size_t bufferSize = 32;
    char * buffer = (char *)malloc(bufferSize);
    char commandTable[9][100] = {"help: See list of commands", "list: See list of items,rooms,or characters",
    "look: See current room information", "go: Travel to a direction", "take: Pick up an item",
    "drop: Drop an item", "inventory: check current items","clue: make a guess","exit: quit "
    };
    
    while(getline(&buffer,&bufferSize,stdin)!= -1){
        char * token = strtok(buffer,"\n");
        if(!strcmp(token,"help")){
            for(int i = 0 ;i < 9 ; i++){
                printf("%s\n",commandTable[i]);
                printf("\n");
            }
        }
        else if(!strcmp(token,"look")){
            char * North = current->North == NULL ? "End" : current->North->name; 
            char * South = current->South == NULL ? "End" : current->South->name;
            char * East = current->East == NULL ? "End" : current->East->name;
            char * West = current->West == NULL ? "End" : current->West->name;
            printf("%s, North: %s, South: %s, East: %s, West: %s \n",current->name,North,South,East,West);
            printf("\n");
            printf("Current items in the room:\n");
            Item * temp =  current->itemList;
            if(temp == NULL){
                printf("None \n");
                printf("\n");
            }
            while(temp != NULL){
                printf("%s \n",temp->name);
               temp = temp->nextItem;
            }
            printf("\n");
            printf("Current characters in the room: \n");
           Character * currChar = current->charList;
            if(currChar == NULL){printf("None \n");}
            while(currChar != NULL){
                printf("%s \n",currChar->name);
               currChar = currChar->nextCharacter;
            }
        }
        else if(!strcmp(token,"inventory")){
            printf("User avatar: %s \n", user.name);
            printf("\n");
            Item * temp = user.inventory;
            printf("Avatar inventory: \n");
            printf("\n");
            if(temp == NULL){printf("None \n");}
            while(temp != NULL){
                printf("%s \n", temp->name);
                temp = temp->nextItem;
            }
        }
        else if(!strcmp(token,"go")){
            printf("Pick a direction: north,south,east,or west\n");
            getline(&buffer,&bufferSize,stdin);
            char * tk = strtok(buffer,"\n");
            if(!strcmp(tk,"north")){
                move(&current,current->North,"north",user.name);
            }
            else if(!strcmp(tk,"south")){
                move(&current,current->South,"south",user.name);
            }
            else if(!strcmp(tk,"east")){
                move(&current,current->East,"east",user.name);
            }
            else if(!strcmp(tk,"west")){
                move(&current,current->West,"west",user.name);
            }
            else{
                printf("direction is not valid, please renter go and choose a new direction \n");
            }
        }
        else if(!strcmp(token,"clue")){
            printf("Guess a character \n");
            getline(&buffer,&bufferSize,stdin);
            char * tk = strtok(buffer,"\n");
            moveCharacter(&current,tk,board);
        }
        else if(!strcmp(token,"take")){
            printf("Choose an item to take(no space after the last words) \n");
            printf("\n");
            getline(&buffer,&bufferSize,stdin);
            char * tk = strtok(buffer,"\n");
            Item * removed = remove_item(&(current->itemList),tk);
            if(removed == NULL){
                printf("No item with given name found, please re-enter take and choose again \n");
            }
            else{
                add_item(&(user.inventory),*removed);
                printf("User took %s out of %s \n",removed->name,current->name);
                printf("\n");
            }
        }
        else if(!strcmp(token,"drop")){
            printf("Choose an item to drop \n");
            printf("\n");
            getline(&buffer,&bufferSize,stdin);
            char * tk = strtok(buffer,"\n");
            Item * removed = remove_item(&(user.inventory),tk);
            if(removed == NULL){
                printf("No item with given name found, please re-enter drop and choose again \n");
                printf("\n");
            }
            else{
                add_item(&(current->itemList),*removed);
                printf("User drop item %s at %s",removed->name,current->name);
                printf("\n");
            }
        }
        else if(!strcmp(token,"exit")){
            printf("exited \n");
            printf("\n");
            break;
        }
        else{
            printf("Command has space after or command is not in the list of regconized commands \n");
            printf("Type help(no space, no uppercase) for commands look up \n");
        }
    }
    return 0;
}