#include <stdio.h>
#include <stdlib.h>

int getAnswer(){
    int ans = 41;
    return ans;
}

int main(int argc,char * agrv[]){
    if(getAnswer() == 42){
        printf("Correct answer");
    }
    exit(0);
}