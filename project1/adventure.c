#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include "rooms.h"

#include "items.h"

#include "character.h"

struct Avatar {
    char * name;
    Item * inventory;
};
void distributeItemsAndCharacters(Room ** board, Item * item, Character * characters) {
    int i = rand() % 3;
    int j = rand() % 3;
    int numEquippedRooms = 0;
    while (numEquippedRooms < 6) {
        if (board[i][j].itemList == NULL) {
            Item anItem = item[numEquippedRooms];
            Character character = characters[numEquippedRooms];
            numEquippedRooms++;
            board[i][j].itemList = (Item * ) malloc(sizeof(Item));
            board[i][j].charList = (Character * ) malloc(sizeof(Character));
            *(board[i][j].itemList) = anItem;
            *(board[i][j].charList) = character;
        }
        i = rand() % 3;
        j = rand() % 3;
    }
}

void distributeRoom(Room ** board) {
    int m = rand() % 3;
    int k = rand() % 3;
    char room[9][30] = {
        "Kitchen",
        "Lounge",
        "Study Room",
        "Library",
        "Ball Room",
        "Hall",
        "Conservatory",
        "Billiard Room",
        "Dining Room"
    };
    int assignedNameRooms = 0;
    while (assignedNameRooms < 9) {
        if (board[m][k].name == NULL) {
            // probably have to malloc here. C be like pointers and malloc go brah brah
            board[m][k].name = (char * ) malloc(sizeof(room[assignedNameRooms]));
            strcpy(board[m][k].name, room[assignedNameRooms]);
            assignedNameRooms++;
        }
        m = rand() % 3;
        k = rand() % 3;
    }
}

void move(Room ** current, Room * direction, char * currentRoom, char * currChar) {
    if (direction == NULL) {
        printf("direction is not valid, please renter go and choose a new direction \n");
        return;
    }
    Character * removed = remove_character( & (( * current) -> charList), currChar);
    if (removed != NULL) {
        Character removedChar = * removed;
        add_character( & (direction -> charList), removedChar);
    }
    * current = direction;
    if (removed == NULL) {
        printf("None was removed \n");
    } else {
        printf("Move %s to : %s\n", currChar, currentRoom);
    }
}
void moveCharacter(Room ** current, char * character, Room ** board) {
    Character * temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp = remove_character( & (board[i][j].charList), character);
            if (temp != NULL) {
                add_character( & (( * current) -> charList), * temp);
                printf("%s moved to %s \n", character, ( * current) -> name);
                printf("\n");
                return;
            }
        }
    }
    printf("No charcter was moved, please re-enter clue and select another character(no space) \n");
}

int main() {
    srand(time(NULL));
    Room ** board = constructBoard();
    Item items[6] = {
        (Item) {
            "Shrek Toy",
            NULL
        },
        (Item) {
            "Shrek Spoon",
            NULL
        },
        (Item) {
            "Shrek Towel",
            NULL
        },
        (Item) {
            "Shrek Love Chair",
            NULL
        },
        (Item) {
            "Shrek Knife",
            NULL
        },
        (Item) {
            "Shrek Pencil",
            NULL
        }
    };
    Character characters[6] = {
        (Character) {
            "Shrek",
            NULL
        },
        (Character) {
            "Betas Shrek",
            NULL
        },
        (Character) {
            "Sigma Shrek",
            NULL
        },
        (Character) {
            "Giga Shrek",
            NULL
        },
        (Character) {
            "Shrek The Ogre",
            NULL
        },
        (Character) {
            "Shrek Fanboy",
            NULL
        }
    };
    distributeRoom(board);
    distributeItemsAndCharacters(board, items, characters);
    int i = rand() % 3;
    int j = rand() % 3;
    int m = rand() % 3;

    Room * current;
    int flag = 0;
    while (!flag) {
        if (board[i][j].charList != NULL) {
            current = & board[i][j];
            flag = 1;
        } else {
            i = rand() % 3;
            j = rand() % 3;
        }
    }

    struct Avatar user = {
        current -> charList -> name,
        NULL
    };
    i = rand() % 3;
    j = rand() % 3;
    Room answerRoom = board[i][j];
    i = rand() % 3;
    j = rand() % 3;
    Character answerChar = characters[i];
    Item answerItem = items[j];
    int clueMade = 0;
    int matches = 0;
    char ** matched = (char ** ) calloc(3, 100);
    matched[0] = NULL;
    matched[1] = NULL;
    matched[2] = NULL;

    size_t bufferSize = 32;
    char * buffer = (char * ) malloc(bufferSize);
    char commandTable[9][100] = {
        "help: See list of commands",
        "list: See list of items,rooms,or characters",
        "look: See current room information",
        "go: Travel to a direction",
        "take: Pick up an item",
        "drop: Drop an item",
        "inventory: check current items",
        "clue: make a guess",
        "exit: quit "
    };

    while (getline( & buffer, & bufferSize, stdin) != -1) {
        char * token = strtok(buffer, "\n");
        if (!strcmp(token, "help")) {
            for (int i = 0; i < 9; i++) {
                printf("%s\n", commandTable[i]);
                printf("\n");
            }
        } else if (!strcmp(token, "look")) {
            char * North = current -> North == NULL ? "End" : current -> North -> name;
            char * South = current -> South == NULL ? "End" : current -> South -> name;
            char * East = current -> East == NULL ? "End" : current -> East -> name;
            char * West = current -> West == NULL ? "End" : current -> West -> name;
            printf("Current room: %s, North: %s, South: %s, East: %s, West: %s \n", current -> name, North, South, East, West);
            printf("\n");
            printf("Current items in the room:\n");
            Item * temp = current -> itemList;
            if (temp == NULL) {
                printf("None \n");
                printf("\n");
            }
            while (temp != NULL) {
                printf("%s \n", temp -> name);
                temp = temp -> nextItem;
            }
            printf("\n");
            printf("Current characters in the room: \n");
            Character * currChar = current -> charList;
            if (currChar == NULL) {
                printf("None \n");
            }
            while (currChar != NULL) {
                printf("%s \n", currChar -> name);
                currChar = currChar -> nextCharacter;
            }
        } else if (!strcmp(token, "list")) {
            printf("All rooms: \n");
            printf("%s, %s, %s \n", board[0][0].name, board[0][1].name, board[0][2].name);
            printf("%s, %s, %s \n", board[1][0].name, board[1][1].name, board[1][2].name);
            printf("%s, %s, %s \n", board[2][0].name, board[2][1].name, board[2][2].name);
            printf("\n");
            printf("All items: \n");
            for (int i = 0; i < 6; i++) {
                printf("%s \n", items[i].name);
            }
            printf("\n");
            printf("All characters: \n");
            for (int i = 0; i < 6; i++) {
                printf("%s \n", characters[i].name);
            }
        } else if (!strcmp(token, "inventory")) {
            printf("User avatar: %s \n", user.name);
            printf("\n");
            Item * temp = user.inventory;
            printf("Avatar inventory: \n");
            printf("\n");
            if (temp == NULL) {
                printf("None \n");
            }
            while (temp != NULL) {
                printf("%s \n", temp -> name);
                temp = temp -> nextItem;
            }
        } else if (!strcmp(token, "go")) {
            printf("Pick a direction: north,south,east,or west\n");
            char * North = current -> North == NULL ? "End" : current -> North -> name;
            char * South = current -> South == NULL ? "End" : current -> South -> name;
            char * East = current -> East == NULL ? "End" : current -> East -> name;
            char * West = current -> West == NULL ? "End" : current -> West -> name;
            printf("Current room: %s, North: %s, South: %s, East: %s, West: %s \n", current -> name, North, South, East, West);
            getline( & buffer, & bufferSize, stdin);
            char * tk = strtok(buffer, "\n");
            if (!strcmp(tk, "north")) {
                move( & current, current -> North, "north", user.name);
            } else if (!strcmp(tk, "south")) {
                move( & current, current -> South, "south", user.name);
            } else if (!strcmp(tk, "east")) {
                move( & current, current -> East, "east", user.name);
            } else if (!strcmp(tk, "west")) {
                move( & current, current -> West, "west", user.name);
            } else {
                printf("direction is not valid, please renter go and choose a new direction \n");
            }
            printf("\n");
        } else if (!strcmp(token, "take")) {
            printf("Choose an item to take(no space after the last words) \n");
            printf("\n");
            getline( & buffer, & bufferSize, stdin);
            char * tk = strtok(buffer, "\n");
            Item * removed = remove_item( & (current -> itemList), tk);
            if (removed == NULL) {
                printf("No item with given name found, please re-enter take and choose again \n");
            } else {
                add_item( & (user.inventory), * removed);
                printf("User took %s out of %s \n", removed -> name, current -> name);
                printf("\n");
            }
        } else if (!strcmp(token, "drop")) {
            printf("Choose an item to drop \n");
            printf("\n");
            getline( & buffer, & bufferSize, stdin);
            char * tk = strtok(buffer, "\n");
            Item * removed = remove_item( & (user.inventory), tk);
            if (removed == NULL) {
                printf("No item with given name found, please re-enter drop and choose again \n");
                printf("\n");
            } else {
                add_item( & (current -> itemList), * removed);
                printf("User drop item %s at %s", removed -> name, current -> name);
                printf("\n");
            }
        } else if (!strcmp(token, "clue")) {
            printf("Guess a character \n");
            getline( & buffer, & bufferSize, stdin);
            char * tk = strtok(buffer, "\n");
            moveCharacter( & current, tk, board);
            if (!strcmp(current -> name, answerRoom.name) && matched[0] == NULL) {
                matched[0] = "Room match";
                matches++;
            }
            if (matched[1] == NULL) {
                Character * temp = current -> charList;
                while (temp != NULL) {
                    if (!strcmp(answerChar.name, temp -> name)) {
                        matched[1] = "Character match";
                        matches++;
                        break;
                    }
                    temp = temp -> nextCharacter;
                }
            }
            if (matched[2] == NULL) {
                Item * tempItem = current -> itemList;
                while (tempItem != NULL) {
                    if (!strcmp(answerItem.name, tempItem -> name)) {
                        matched[2] = "Item match";
                        matches++;
                        break;
                    }
                    tempItem = tempItem -> nextItem;
                }
            }
            for (int i = 0; i < 3; i++) {
                if (matched[i] != NULL) {
                    printf("%s \n", matched[i]);
                }
            }
            if (matches == 3) {
                printf("You win \n");
                break;
            }
            clueMade++;
            if (clueMade > 10) {
                printf("Oof out of guess.You lost \n");
                break;
            }
        } else if (!strcmp(token, "exit")) {
            printf("exited \n");
            printf("\n");
            break;
        } else if(!strcmp(token,"key")){
            printf("%s uses %s to kill someone in %s \n",answerChar.name,answerItem.name,answerRoom.name);
        }
        else {
            printf("Command has space after or command is not in the list of regconized commands \n");
            printf("Type help(no space, no uppercase) for commands look up \n");
        }
    }
    return 0;
}