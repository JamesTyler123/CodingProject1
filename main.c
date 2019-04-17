#include <stdio.h>
#include <string.h>

void DecodeRotation();
void DecodeRotationKey();
void EncodeRotationKey();
void DecodeSubstitutionKey();
void EncodeSubstitutionKey();
void Testing();
char *DecodeRotate(char input[], int y);
char *EncodeRotate(char x[], int y);

int main(){
    int select; // users input as an integer
    printf("\n------------------------------------------------\n");
    printf("Please select which function you wish to perform\n");
    printf("------------------------------------------------\n\n");
    printf("1) Decode Rotation Cipher brute force\n");
    printf("2) Decode Rotation Cipher with key\n");
    printf("3) Encode Rotation Cipher with key\n");
    printf("4) Decode Substitution Cipher with key\n");
    printf("5) Encode Substitution Cipher with key\n\n");
    scanf("%d", &select); //user input stored into the integer
    switch (select){
        case 1:
            //printf("\nRotation Cipher Decoder Selected\n\n");
            //Testing();       
            DecodeRotation();
            break;
        case 2:
            printf("\nRotation Cipher with Key Decoder Selected\n\n");
            DecodeRotationKey();
            break;
        case 3:
            printf("\nRotation Cipher with Key Encoder Selected\n\n");
            EncodeRotationKey();
            break;
        case 4:
            printf("\nSubstitution Cipher with Key Decoder Selected\n\n");
            DecodeSubstitutionKey();
            break;
        case 5:
            printf("\nSubstitution Cipher with Key Encoder Selected\n\n");
            EncodeSubstitutionKey();
            break;
        default:
            printf("\nInvalid input, please enter a number from 1-5\n\n");
            main();        
    }  
}

char *DecodeRotate(char input[], int y){
    int counter, i;
    static char x[1000];
    strcpy(x, input);
    for(counter = 1; counter < y; counter++){ //a counter for how many rotations have occured
        for(i = 0; x[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if((x[i] > 96) && (x[i] < 123)){
                x[i] -= 32;
            }
            
            if((x[i] >= 32) && (x[i] <= 64)){ //keeps the space in characters if two words
            }
            
            else{
                x[i]-= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (x[i] == 64){ //if character is above z, moves it back to a
                x[i] = 'Z';
            }
        }
    }
    return x;
}

char *EncodeRotate(char x[], int y){
    int counter, i;
    for(counter = 1; counter < y; counter++){ //a counter for how many rotations have occured
        for(i = 0; x[i] != '\0'; i++){ //a for loop stopping upon the end of string
            if((x[i] > 96) && (x[i] < 123)){
                x[i] -= 32;
            }
            
            if((x[i] >= 32) && (x[i] <= 64)){ //keeps the space in characters if two words
            }
            
            else{
                 x[i]+= 1; //increases the current letter to next, i.e. moves a to b
            }
            
            if (x[i] == 91){ //if character is above z, moves it back to a
                x[i] = 'A';
            }
        }
    }
    return x;
}

void Testing(){
    char string[] = "testing sentence for breaking words";
    char delim[] = " ";
    char *split = strtok(string, delim);
    while(split != '\0'){
        printf("%s \n", split);
        split = strtok('\0', delim);
    }
}
void DecodeRotation(){
    char string[] = "lejlsslua qvi kljvkpun pm aopz dvyrz";
	char delim[] = " ,.:;-";
	char *hidden = strtok(string, delim);
    char word[100];
    int counter; // a counter to make the function loop the total possible amount of times
    int i = 0; // a counter to determine each character of the string
    int key = 26; //the maximum rotation number
    
    int temp = 0;
    while(hidden != '\0'){
		for(counter = 1; counter < key; counter++){ //a counter for how many rotations have occured
            FILE *input = fopen("Dictionary.txt", "r"); //opens the text file
            for(i = 0; (i < 120000) && (temp == 0); i++){ //tests all words in the file
                fscanf(input, "%s", word);
                if(strcmp(DecodeRotate(string, counter), word) == 0){ //if the string is in the file and matches the cipher, print it
                    temp = counter;
                }
            }
        }	
		printf("The decoded word is %s\n", DecodeRotate(hidden, temp));
        hidden = strtok(NULL, delim);
	}
}

void DecodeRotationKey(){
    char hidden[1024]; // initilise the unknown word
    int key; // declare the key variable
    printf("Enter a key: ");
    scanf("%d", &key);
    getchar();
    printf("Please enter a word to decode: ");
    fgets(hidden, 100, stdin);
    
    printf("The decoded word is %s\n", DecodeRotate(hidden, key));
}

void EncodeRotationKey(){
    char hidden[1024]; // "shfvba"; //this text is "fusion" it has two outputs
    int key;
    printf("Enter a key: ");
    scanf("%d", &key);
    getchar(); //blank new line to clear console and allows double inputs
    printf("Please enter a word to encode: ");
    fgets(hidden, 100, stdin);
    
    printf("The encoded word is %s\n", EncodeRotate(hidden, key));
}


void DecodeSubstitutionKey(){
    char hidden[1024]; 
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char key[] = {"BCDEFGHIJKLMNOPQRSTUVWXYZA"};
    //printf("Enter a key: ");
    //scanf("%s", key);
    getchar();
    printf("Please enter a word to decode: ");
    fgets(hidden, 100, stdin);
    int i = 0; // a counter to determine each character of the string
    int n; //a variable to store the substituted cipher key
    int k; // a variable used to make the key all uppercase
    
    for(k = 0; alphabet[k] != '\0'; k++){
        if((alphabet[k] > 96) && (alphabet[k] < 123)){
            alphabet[k] -= 32;
        }
    }
    
    for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
        if((hidden[i] > 96) && (hidden[i] < 123)){
            hidden[i] -= 32;
        }
        
        if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
        }
        
        else{
            for(n = 0; n < 26; n++){ //test all letters of the alphabet
                if(key[n] == hidden[i]){ //if a letter of the alphabet is equal to a letter of the string
                    hidden[i] = alphabet[n]; //a letter of the string is now a letter of the key
                    break;
                }
            }        
        }
    }
    printf("The decoded word is %s\n", hidden);
}

void EncodeSubstitutionKey(){
    char hidden[1024]; 
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char key[] = {"BCDEFGHIJKLMNOPQRSTUVWXYZA"};
    //printf("Enter a key: ");
    //scanf("%s", key);
    getchar();
    printf("Please enter a word to encode: ");
    fgets(hidden, 100, stdin);
    int i = 0; // a counter to determine each character of the string
    int n; // a variable to store the substituted cipher key
    int k; // a variable used to make the key all uppercase
    
    for(k = 0; alphabet[k] != '\0'; k++){
        if((alphabet[k] > 96) && (alphabet[k] < 123)){
            alphabet[k] -= 32;
        }
    }

    for(i = 0; hidden[i] != '\0'; i++){ //a for loop stopping upon the end of string
        if((hidden[i] > 96) && (hidden[i] < 123)){ //if lowercase
            hidden[i] -= 32; //shift to uppercase
        }
        
        if((hidden[i] >= 32) && (hidden[i] <= 64)){ //keeps the space in characters if two words
        }
        
        else{
            for(n = 0; n < 26; n++){ //test all letters of the alphabet
                if(alphabet[n] == hidden[i]){ //if a letter of the alphabet is equal to a letter of the string
                    hidden[i] = key[n]; //a letter of the string is now a letter of the key
                    break;
                }
                
            }        
        }
    }
    printf("The encoded word is %s\n", hidden);
}