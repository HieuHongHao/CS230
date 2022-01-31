#include "rooms.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int isInvalid(int x, int y ){
    return abs(x) > 2 || abs(y) > 2;   
}

Room ** constructBoard(){
    Room ** board = (Room **)calloc(3,sizeof(Room * ));
    for(int i = 0 ; i < 3; i++){
        board[i] = (Room *)calloc(3,sizeof(Room));
    }
    int room = 1;
    for(int i = 0 ; i < 3 ; i++ ){
        for(int j = 0 ; j < 3 ; j++){
            int length = snprintf(NULL,0,"%d",room);
            char * roomNumber = malloc(length + 1);
            snprintf(roomNumber,length + 1,"%d",room);
            board[i][j] = (Room){roomNumber,(isInvalid(i-1,j)) ? NULL : &board[i-1][j],(isInvalid(i+1,j)) ? NULL : &board[i+1][j],
            (isInvalid(i,j+1)) ? NULL : &board[i][j+1],(isInvalid(i,j-1)) ? NULL : &board[i][j-1],NULL,NULL};
            room++;
        }
    } 
    return board;
}