#include <stdio.h>
#include <string.h>

int main(){
    char hidden[] = "shfvba"; //this text is "fusion" it has two outputs
    char final[100];
    int counter;
    int i = 0;
    
    for(counter = 1; counter < 26; counter++){ //a counter for how many rotations have occured
        for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if(hidden[i] != 32){ //keeps the space in characters if two words
                hidden[i]+= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (hidden[i] > 'z'){ //if character is above z, moves it back to a
                hidden[i] = 'a';
            }
        }
    
        FILE *input;
        input = fopen("text.txt", "r"); //opens the text file
        for(i = 0; i < 10000; i++){ //tests all words in the file
            fscanf(input, "%s", final);
            if(strcmp(hidden, final) == 0){ //if the string is in the file and matches the cipher, print it
                printf("%s\n", hidden);
            }
        }
    }
}
