#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *hidden = "uvqqra zrffntr"; //text reads hidden message
    int counter;
    int i;
    int letternum = 0;
    for(counter = 1; counter < 26; counter++){
        if (hidden[letternum] > 122){
            hidden[letternum];
        }
        
        while (hidden[letternum] != 0){
            printf("%c", hidden[letternum]);
            letternum++;
        }
        
        for(i = 0; i < 20; i++){
            hidden[i]++; 
        }

    }
}
