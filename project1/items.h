#ifndef ITEM_H
#define ITEM_H

typedef struct Item{
    char * name;
    struct Item * nextItem;
} Item;
 

void add_item(Item ** headPointer ,Item item);

Item * remove_item(Item ** headPointer, char * name);






#endif
