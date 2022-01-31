#ifndef ROOM_H
#define ROOM_H
typedef struct Room {
      char* name;
      struct Room * North;
      struct Room * South;
      struct Room * East;
      struct Room * West;
      //struct Item * itemList;
     //char *character[MAX_CHARACTER];
} Room;

Room ** constructBoard();







#endif
