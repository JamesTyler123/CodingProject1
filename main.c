// -----------------------------------------------------
//
// Enter to word to modify into the "WordInput.txt" file
//
// -----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char dict[10000][30]; //declaring the variable to store the dictionary into memory
char delim[] = " ,.:;-"; //declaring parts of the strings to split at

// -----------------------------------------------------
//
//    Large calling of functions used in the program
// 
// -----------------------------------------------------

void DecodeRotation();
void DecodeRotationKey();
void EncodeRotationKey();
void DecodeSubstitutionKey();
void EncodeSubstitutionKey();
void DecodeSubstitutionFreqAnal();

char *DecodeRotate(char input[], int y);
char *EncodeRotate(char input[], int y);
char *encodestringkey(char* string, char* key);
char *decodestringkey(char* string, char* key);

void LoadDictionary(char * filename);
int CheckDictionary(char * word);

int ScoreString(char * string);
char *guesskey(char *key);
char *Shuffle(char *key);
char *freqkey(char *code);
char *reorderedkey(char *key);
int CharacterDistribution(char* hidden);

int main(){
    srand(time(0)); //create random numbers for this program launch  
    LoadDictionary("Dictionary10k.txt"); //load the dictionary file used to decode words
    int select; // users input as an integer
    printf("\n------------------------------------------------\n");
    printf("Please select which function you wish to perform\n");
    printf("------------------------------------------------\n\n");
    printf("1) Decode Rotation Cipher brute force\n");
    printf("2) Decode Rotation Cipher with key\n");
    printf("3) Encode Rotation Cipher with key\n");
    printf("4) Decode Substitution Cipher with key\n");
    printf("5) Encode Substitution Cipher with key\n");
    printf("6) Decode Substitution Cipher with Frequency Analysis\n\n");
    scanf("%d", &select); //user input stored into the integer
    switch (select){
        case 1:
            printf("\nRotation Cipher with Brute Force Selected\n\n");
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
        case 6:
            printf("\nSubstitution Cipher with Frequency Analysis Selected\n\n");
            DecodeSubstitutionFreqAnal();
            break;
        default:
            printf("\nInvalid input, please enter a number from 1-5\n");
            main();        
    }  
}

// -----------------------------------------------------
//
//    Function bodies listed below
// 
// -----------------------------------------------------

void LoadDictionary(char * filename){
    int i; //a variable used as a counter
    FILE *input = fopen(filename, "r"); //opens the text file
    for(i = 0; (i < 10000); i++){ //scans all words in the file
        fscanf(input, "%s", dict[i]); //stores the words in the dictionary file into memory
    }
    fclose(input); // closes file after use
}

int CheckDictionary(char * word){
    int i; //a variable used as a counter
    for(i = 0; (i < 10000); i++){ //tests all words in the file
        if (strlen(dict[i]) > strlen(word)){//if the word in the dictionary is longer than current word to be analysed, ignore it and break the loop
            break;
        }
        if (strcmp(dict[i], word) == 0){ //if the string is in the file and matches the cipher
           if (strlen(word) < 5){ //if the word is 4 or less characters long
               return 5;//give it a base score of 5
           }
           else{
               return strlen(word) * strlen(word); //otherwise give it a score based on the square of its length
           }
           break; //once comparison is done break the scan for the word
        }
    }
    return 0; // only returns 0 if the word is not the same length
}

int ScoreString(char * string){
    char tmpstring[1000]; //variable to store the string so the original does not get modified
    int totalscore = 0; //variable used to store the total score value
    strcpy(tmpstring, string); //copies the original string so it does not get modified
    char *hidden = strtok(tmpstring, delim); //split the string into its seperate words
    while(hidden != '\0'){ //while it is not the end of the string
        totalscore += (CheckDictionary(hidden)*10 + CharacterDistribution(hidden)); //adds 10x the value for words, 1x for ideal character distribution
        hidden = strtok(NULL, delim); // move to next word in the string
	}
	return totalscore; //returns the value of the string based on the scoring formula
}

char newkey[26]; //declaring a local variable outside functions because c doesnt like to return a variable created inside the function
char *guesskey(char *key){
    char tempchar; //a placeholder variable to modify the key
    strcpy(newkey, key); //copy the current key to a local variable to not modify to original value
    int index1 = rand()%26; // random number between 1-26
    int index2 = rand()%25; // random number between 1-25
    if (index1 == index2){ // if those two random numbers are the same
        index2 = 25; 
    }
    tempchar = newkey[index1]; // the next 3 lines shuffle those two characters, moving character at first index to second index and vice versa
    newkey[index1] = newkey[index2];
    newkey[index2] = tempchar;
    return newkey; // returns the modified, randomly shuffled key
}



char encodedstring[10000]; //declaring a local variable outside functions because c doesnt like to return a variable created inside the function
char *encodestringkey(char* string, char* key){
    int i; // counter variable for loop
    int n; // counter variable for loop
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}; //hard coded alphabet variable to start with a baseline key
    strcpy(encodedstring, string); // copy string as to avoid modifing the original
    for(i = 0; encodedstring[i] != '\0'; i++){ //a for loop stopping upon the end of string
        if((encodedstring[i] > 96) && (encodedstring[i] < 123)){ //if lowercase
            encodedstring[i] -= 32; //shift to uppercase
        }
        
        if((encodedstring[i] >= 32) && (encodedstring[i] <= 64)){ //keeps the space in characters if two words
        }
        
        else{
            for(n = 0; n < 26; n++){ //test all letters of the alphabet
                if(alphabet[n] == encodedstring[i]){ //if a letter of the alphabet is equal to a letter of the string
                    encodedstring[i] = key[n]; //a letter of the string is now a letter of the key
                    break;
                }
                
            }        
        }
    }
    return encodedstring; //return the modified, substituted string
}

char decodedstring[10000]; //declaring a local variable outside functions because c doesnt like to return a variable created inside the function
char *decodestringkey(char* string, char* key){
    int i;// counter variable for loop
    int n;// counter variable for loop
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}; //hard coded alphabet variable to start with a baseline key
    strcpy(decodedstring, string); // copy string as to avoid modifing the original
    for(i = 0; decodedstring[i] != '\0'; i++){ //a for loop stopping upon the end of string
        if((decodedstring[i] > 96) && (decodedstring[i] < 123)){ //if lowercase
            decodedstring[i] -= 32; //shift to uppercase
        }
    
        if((decodedstring[i] >= 32) && (decodedstring[i] <= 64)){ //keeps the space in characters if two words
        }
        
        else{
            for(n = 0; n < 26; n++){ //test all letters of the alphabet
                if(key[n] == decodedstring[i]){ //if a letter of the alphabet is equal to a letter of the string
                    decodedstring[i] = alphabet[n]; //a letter of the string is now a letter of the key
                    break;
                }
                
            }        
        }
    }
    return decodedstring; //return the modified, substituted string   
}

int CharacterDistribution(char* hidden){
    int i; // counter variable for loop
    int charscoretally = 0; //a variable used to keep total count of score from a word
    for(i = 0; hidden[i] != '\0'; i++){ //while not end of word
        //massive switch case giving score based on ideal distribution of words in the english language
        switch(hidden[i]){
            case 'E':
                charscoretally += 12;
                break;
            case 'T':
                charscoretally += 9;
                break;
            case 'A':
                charscoretally += 8;
                break;
            case 'O':
                charscoretally += 7;
                break;
            case 'I':
                charscoretally += 7;
                break;
            case 'N':
                charscoretally += 7;
                break;
            case 'S':
                charscoretally += 6;
                break;
            case 'R':
                charscoretally += 6;
                break;
            case 'H':
                charscoretally += 5;
                break;
            case 'L':
                charscoretally += 4;
                break;
            case 'D':
                charscoretally += 3;
                break;
            case 'C':
                charscoretally += 3;
                break;
            case 'U':
                charscoretally += 2;
                break;
            case 'M':
                charscoretally += 2;
                break;
            case 'F':
                charscoretally += 2;
                break;
            case 'P':
                charscoretally += 2;
                break;
            case 'G':
                charscoretally += 1;
                break;
            case 'W':
                charscoretally += 1;
                break;
            case 'Y':
                charscoretally += 1;
                break;
            case 'B':
                charscoretally += 1;
                break;
            case 'V':
                charscoretally += 1;
                break;
        }
    }
    return charscoretally; // returns the final value of the distribution
}

char newkey[26]; //declaring a local variable outside functions because c doesnt like to return a variable created inside the function
char *Shuffle(char *key) { //implementation of Fisher
    int i, j, tmp; // create local variables to hold values for shuffle
    int n = strlen(key);
    strcpy(newkey, key);
    for (i = n - 1; i > 0; i--) { // for loop to shuffle
        j = rand() % (i + 1); //randomise j for shuffle with Fisher Yates
        tmp = key[j];
        key[j] = key[i];
        key[i] = tmp;
    }
    return newkey;
}

char approxkey[26]; //declaring a local variable outside functions because c doesnt like to return a variable created inside the function
char *freqkey(char *code){
    int i; //loop counter variable
    int maxcount = 0; // a counter for the most common letter
    int charcount[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int c; //loop counter variable
    for(i = 0; code[i] != '\0'; i++){ //while not the end of the key
        if ((code[i] >= 'A') && (code[i] <= 'Z')){ //if between a-z
            charcount[code[i]-'A'] += 1; //increment the index of the character counter
            if (charcount[code[i]-'A'] > maxcount){ //if it is the largest occurance so far
                maxcount = charcount[code[i]-'A']; //set maxcount to remember that
            }
        }
    }

    int j = 0; //a variable to store the reshuffled index value
    for (i = maxcount; i >= 0 ; i--){ //loop that occurs based on the largest frequency
        for (c = 0; c < 26; c++){ //loop for all values of the key
            if (charcount[c] == i){ 
                approxkey[j] = 'A' + c;
                j += 1;
            }
        }
    }
    return approxkey;
}

char rokey[26]; //declaring a local variable outside functions because c doesnt like to return a variable created inside the function
char *reorderedkey(char *key){
    int i; //counter variable for loop
    int c; //counter variable
    char freq[] = {"ETAOINSRHLDCUMFPGWYBVKXJQZ"};
    for (i = 0; i < 26; i++){ //loop 26 times as there are 26 letters in a key
        c = freq[i]-'A'; //to generate an index number for the reorder
        rokey[c] = key[i]; //create a reordered key
    }
    return rokey; //return the reordered key
}

char *DecodeRotate(char input[], int y){
    int counter, i;
    static char x[1000];
    strcpy(x, input);
    for(counter = 0; counter < y; counter++){ //a counter for how many rotations have occured
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

char *EncodeRotate(char input[], int y){
    int counter, i;
    static char x[1000];
    strcpy(x, input);
    for(counter = 0; counter < y; counter++){ //a counter for how many rotations have occured
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

// -----------------------------------------------------
//
//      Main functions accessed by the main menu
// 
// -----------------------------------------------------

void DecodeRotationKey(){
    char hidden[1024]; // initilise the unknown word
    int key; // declare the key variable
    printf("Enter a key: ");
    scanf("%d", &key); //stores the users input into the variable key
    FILE *userinput = fopen("WordInput.txt", "r"); //open input text file; //initialise file for opening
    fgets(hidden, 10000, userinput); //read file for inpuit
    
    printf("The decoded word is %s\n", DecodeRotate(hidden, key));
}

void EncodeRotationKey(){
    char hidden[1024]; // initilise the unknown word
    int key; // declare the key variable
    printf("Enter a key: ");
    scanf("%d", &key); //stores the users input into the variable key
    FILE *userinput = fopen("WordInput.txt", "r"); //open input text file; //initialise file for opening
    fgets(hidden, 10000, userinput); //read file for inpuit
    
    printf("The encoded word is %s\n", EncodeRotate(hidden, key));
}

void DecodeRotation(){
    char start[1024]; // initalise original word before asigning it to opened file
    FILE *userinput = fopen("WordInput.txt", "r"); //open input text file; //initialise file for opening
    fgets(start, 10000, userinput); //read file for inpuit
    char string[1000]; // initilise a copy of the string to modify and test
    strcpy(string, start); // copy the string
	char *hidden = strtok(string, delim); // split the word on the boundaries
    int counter; // a counter to make the function loop the total possible amount of times
    int key = 26; //the maximum rotation number
    int cntr; // another counter used for determining the best rotation
    int bigger = 0; // used to store the largest amount of rotations
    int bestmatch; // used to store the best key
    
    int scorearray[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    while(hidden != '\0'){ //a loop that continues until the end of a word
		for(counter = 0; counter < key; counter++){ //a counter for how many rotations have occured
		    if ((CheckDictionary(DecodeRotate(hidden, counter))) > 0){
                scorearray[counter] += 1; // add a score point to the key tally
		    }
        }	
        hidden = strtok(NULL, delim); // move to next word in the string
	}
	
	for(cntr = 0; cntr < 26; cntr++){ // check through all keys and how many times they were used
	    if(scorearray[cntr] > bigger){
	        bigger = scorearray[cntr]; // stores the amount of times the key was used
	        bestmatch = cntr; // stores the key
	    }
	}
	
	printf("The decoded phrase is %s\n", DecodeRotate(start, bestmatch));
}

void DecodeSubstitutionKey(){
    char hidden[1024]; // initilise the unknown word
    char key[26]; // declare the key variable
    printf("Enter a key: ");
    scanf("%s", key); //stores the users input into the variable key
    FILE *userinput = fopen("WordInput.txt", "r"); //open input text file; //initialise file for opening
    fgets(hidden, 10000, userinput); //read file for inpuit

    printf("The decoded word is %s\n", encodestringkey(hidden, key));
}

void EncodeSubstitutionKey(){
    char hidden[1024]; // initilise the unknown word
    char key[26]; // declare the key variable
    printf("Enter a key: ");
    scanf("%s", key); //stores the users input into the variable key
    FILE *userinput = fopen("WordInput.txt", "r"); //open input text file; //initialise file for opening
    fgets(hidden, 10000, userinput); //read file for inpuit

    printf("The encoded word is %s\n", decodestringkey(hidden, key));
}

void DecodeSubstitutionFreqAnal(){
    int i; //counter variable for loop
    int improvcounter = 0; //counter that increment if not better key is found
    int tolerance = 0; //variable store how much the score can go down to potentially get out of the hole
    int bestscore; //scores the current best decoding score 
    int testscore; //scores the current score being tested to see if it is bigger than bestscore
    char testkey[26]; //a variable for the current key being tested
    char temp[26]; //used to quad shuffled a key
    char bestGuessKey[26]; // a variable to store the current best key
    char code[10000];// = {"vevibylwb rh z tvmrfh. yfg ru blf qfwtv z urhs yb rgh zyrorgb gl xorny z givv, rg droo orev rgh dslov oruv yvorvermt gszg rg rh hgfkrw. - zoyvig vrmhgvrm"};
    FILE *userinput = fopen("WordInput.txt", "r"); //open input text file
    fgets(code, 10000, userinput); //read file for inpuit
    strcpy(bestGuessKey, reorderedkey(freqkey(code))); //
    bestscore = ScoreString(decodestringkey(code, bestGuessKey));

    for(i = 0; i < 5000; i++){
        if (improvcounter > 500){ //if has not improved for 500 tries, do a quad shuffle
            strcpy(temp, guesskey(bestGuessKey));
            strcpy(testkey, guesskey(temp));
        }
        else{
            strcpy(testkey, guesskey(bestGuessKey)); //if improvment counter less than 100, do a double shuffle
        }

        testscore = ScoreString(decodestringkey(code, testkey)); //saves the current score value
        if (testscore > (bestscore - tolerance)){ //if current score is better than best overall score with tolerance
            strcpy(bestGuessKey, testkey); //saves current key as best key since improvment occured
            bestscore = testscore; //save current score as the best overall score if an increase occured
            improvcounter = 0; //reset improvement counter since the score increased
            tolerance = 0; //reset tolerance to lowering counter since the score increased
        }
        else{
            improvcounter += 1; //if not match increase this counter
        }
        
        if((i < 4500) && (improvcounter > 50)){ //if the counter has not seen improvement for 50 tries, will allow it to go down 5 more each increment
            tolerance += 5;
        }
       
    }
    printf("Based on analysis, the phrase was determined to be:\n\n%s\n\nWith a key of:\n%s\n", decodestringkey(code, bestGuessKey), bestGuessKey);
}
