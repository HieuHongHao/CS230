#ifndef ITEM_H
#define ITEM_H

typedef struct Item{
    char * name;
    struct Item * nextItem;
} Item;
 

void add_item(Item * head ,Item item);

Item * remove_item(Item * head, char * name);






#endif
