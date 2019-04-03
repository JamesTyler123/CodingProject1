#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char hidden[] = "uvqqra"; //this text is "hidden"
    char final[100];
    int counter;
    int i = 0;
    for(counter = 1; counter < 26; counter++){
        for(i = 0; hidden[i] != '\0'; i++){
            if(hidden[i] != 32){
                hidden[i]+= 1;
            }
            
            if (hidden[i] > 'z'){
                hidden[i] = 'a';
            }
        }
    
        FILE *input;
        input = fopen("text.txt", "r");
        for(i = 0; i < 10000; i++){
            fscanf(input, "%s", final);
            if(strcmp(hidden, final) == 0){
                printf("%s\n", hidden);
                break;
            }
        }
    }
}
