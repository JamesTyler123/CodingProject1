#include <stdio.h>
#include <string.h>

void DecodeRotation();
void DecodeRotationKey();
void EncodeRotationKey();
void DecodeSubstitutionKey();
void EncodeSubstitutionKey();

int main(){
    int select; // users input as an integer
    printf("Please select which function you wish to perform\n");
    printf("1) Decode Rotation Cipher brute force\n");
    printf("2) Decode Rotation Cipher with key\n");
    printf("3) Encode Rotation Cipher with key\n");
    printf("4) Decode Substitution Cipher with key\n");
    printf("5) Encode Substitution Cipher with key\n");
    scanf("%d", &select); //user input stored into the integer
    switch (select){
        case 1:
            printf("Rotation Cipher Decoder Selected\n");
            DecodeRotation();
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
            printf("Substitution Cipher with Key Decoder Selected\n");
            DecodeSubstitutionKey();
            break;
        case 5:
            printf("Substitution Cipher with Key Encoder Selected\n");
            EncodeSubstitutionKey();
            break;
        default:
            printf("Invalid input, please enter a number from 1-5");
        
    }
    
}

void DecodeRotation(){
    
    char hidden[1024]; // "shfvba"; //this text is "fusion" it has two outputs
    FILE *input; //initialise file for opening
    input = fopen("WordInput.txt", "r"); //open input text file
    fgets(hidden, 10000, input); //read file for inpuit
    char final[100];
    int counter; // a counter to make the function loop the total possible amount of times
    int i = 0; // a counter to determine each character of the string
    int k;
    
    for(counter = 1; counter < 26; counter++){ //a counter for how many rotations have occured
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
    
        FILE *input;
        input = fopen("Dictionary.txt", "r"); //opens the text file
        for(i = 0; i < 500000; i++){ //tests all words in the file
            fscanf(input, "%s", final);
            if(strcmp(hidden, final) == 0){ //if the string is in the file and matches the cipher, print it
                for(k = 0; hidden[k] != '\0'; k++){
                    if((hidden[k] > 96) && (hidden[k] < 123)){
                        hidden[k] -= 32;
                    }  
                }
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
            if((hidden[i] > 96) && (hidden[i] < 123)){
                hidden[i] -= 32;
            }
            
            if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
            }
            
            else{
                 hidden[i]+= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (hidden[i] == 91){ //if character is above z, moves it back to a
                hidden[i] = 'A';
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
            if((hidden[i] > 96) && (hidden[i] < 123)){
                hidden[i] -= 32;
            }
            
            if((hidden[i] >= 32) && (hidden[i] < 64)){ //keeps the space in characters if two words
            }
            
            else{
                 hidden[i]-= 1; //decreases the current letter to previous, i.e. moves b to a
            }
            
            if (hidden[i] == 64){ //if character is below a, moves it back to z
                hidden[i] = 'Z';
            }
        }
    }
    printf("The decoded word is %s\n", hidden);
}

void DecodeSubstitutionKey(){
    char hidden[1024]; 
    char key[] = {"BCDEFGHIJKLMNOPQRSTUVWXYZA"};
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    //printf("Enter a key: ");
    //scanf("%s", key);
    getchar();
    printf("Please enter a word to decode: ");
    fgets(hidden, 100, stdin);
    int i = 0;
    int n;
    
    for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
        if((hidden[i] > 96) && (hidden[i] < 123)){
            hidden[i] -= 32;
        }
        
        if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
        }
        
        else{
            for(n = 0; n < 26; n++){
                if(key[n] == hidden[i]){
                    hidden[i] = alphabet[n];
                    break;
                }
            }        
        }
    }
    printf("The decoded word is %s\n", hidden);
}

void EncodeSubstitutionKey(){
    char hidden[1024]; 
    char key[] = {"BCDEFGHIJKLMNOPQRSTUVWXYZA"};
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    getchar();
    printf("Please enter a word to encode: ");
    fgets(hidden, 100, stdin);
    int i = 0;
    int n;
    
    for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
        if((hidden[i] > 96) && (hidden[i] < 123)){
            hidden[i] -= 32;
        }
        
        if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
        }
        
        else{
            for(n = 0; n < 26; n++){
                if(alphabet[n] == hidden[i]){
                    hidden[i] = key[n];
                    break;
                }
                
            }        
        }
    }
    printf("The encoded word is %s\n", hidden);
}