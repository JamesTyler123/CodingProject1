#include <stdio.h>
#include <string.h>

void DecryptRotation();
void DecodeRotationKey();
void EncodeRotationKey();

int main(){
    int select; // = 1; // hard coded for testing
    printf("Please select which function you wish to perform\n");
    printf("1) Decode Rotation Cipher brute force\n");
    printf("2) Decode Rotation Cipher with key\n");
    printf("3) Encode Rotation Cipher with key\n");
    printf("4) Decode Substitution Cipher with key\n");
    printf("5) Encode Substitution Cipher with key\n");
    scanf("%d", &select); //user input for later
    switch (select){
        case 1:
            printf("Rotation Cipher Decoder Selected\n");
            DecryptRotation();
            break;
        case 2:
            printf("Rotation Cipher with Key Decoder Selected\n");
            DecodeRotationKey();
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
    FILE *input; //initialise file for opening
    input = fopen("input.txt", "r"); //open input text file
    fgets(hidden, 10000, input); //read file for inpuit
    char final[100];
    int counter;
    int i = 0;
    
    for(counter = 1; counter < 26; counter++){ //a counter for how many rotations have occured
        for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
            }
            
            else{
                 hidden[i]+= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (hidden[i] == 123 ){ //if character is above z, moves it back to a
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
    printf("Enter a key: ");
    scanf("%d", &key);
    getchar();
    printf("Please enter a word to encode: ");
    fgets(hidden, 100, stdin);
    int counter;
    int i = 0;
    
    for(counter = 0; counter < key; counter++){ //a counter for how many rotations have occured
        for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
            }
            
            else{
                 hidden[i]+= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (hidden[i] == 123){ //if character is above z, moves it back to a
                hidden[i] = 'a';
            }
        }
    }
    printf("The encoded word is %s\n", hidden);
}

void DecodeRotationKey(){
    char hidden[1024]; // "shfvba"; //this text is "fusion" it has two outputs
    int key = 0;
    printf("Enter a key: ");
    scanf("%d", &key);
    getchar();
    printf("Please enter a word to decode: ");
    fgets(hidden, 100, stdin);
    int counter;
    int i = 0;
    
    for(counter = 0; counter < key; counter++){ //a counter for how many rotations have occured
        for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
            }
            
            else{
                 hidden[i]-= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (hidden[i] == 96){ //if character is below a, moves it back to z
                hidden[i] = 'z';
            }
        }
    }
    printf("The decoded word is %s\n", hidden);
}