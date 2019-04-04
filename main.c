#include <stdio.h>
#include <string.h>

void DecryptRotation();
void EncodeRotationKey();

int main(){
    int select; // = 1; // hard coded for testing
    printf("Please select which function you wish to perform\n");
    printf("1) Decode Rotation Cipher\n");
    printf("2) Decode Rotation Cipher with key\n");
    printf("3) Encode Rotation Cipher with key\n");
    printf("4) Decode Substitution Cipher\n");
    printf("5) Encode Substitution Cipher\n");
    scanf("%d", &select); //user input for later
    switch (select){
        case 1:
            printf("Rotation Cipher Decoder Selected\n");
            DecryptRotation();
            break;
        case 2:
            break;
        case 3:
            printf("Rotation Cipher with Key Encoder Selected\n");
            EncodeRotationKey();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            printf("Invalid input, please enter a number from 1-5");
        
    }
    
}

void DecryptRotation(){
    
    char hidden[1024]; // "shfvba"; //this text is "fusion" it has two outputs
    printf("Please enter a word to decode: ");
    scanf("%s", hidden);
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
                printf("The word decoded is: %s\n", hidden);
            }

        }
    }
}

void EncodeRotationKey(){
    char hidden[1024]; // "shfvba"; //this text is "fusion" it has two outputs
    int key = 0;
    printf("Please enter a word to encode: ");
    scanf("%s", hidden);
    printf("Enter a key: ");
    scanf("%d", &key);
    int counter;
    int i = 0;
    
    for(counter = 0; counter < key; counter++){ //a counter for how many rotations have occured
        for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if(hidden[i] != 32){ //keeps the space in characters if two words
                hidden[i]+= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (hidden[i] > 'z'){ //if character is above z, moves it back to a
                hidden[i] = 'a';
            }
        }
    }
    printf("The encoded word is %s\n", hidden);
}
