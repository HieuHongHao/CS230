#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct Character{
    char * name;
    struct Character * nextCharacter;
} Character;
 

void add_character(Character ** headPointer ,Character character);

Character * remove_character(Character ** headPointer, char * name);


#endif
