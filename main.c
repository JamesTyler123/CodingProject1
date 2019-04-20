#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char dict[9000][30];
char delim[] = " ,.:;-";

void DecodeRotation();
void DecodeRotationKey();
void EncodeRotationKey();
void DecodeSubstitutionKey();
void EncodeSubstitutionKey();

char *DecodeRotate(char input[], int y);
char *EncodeRotate(char input[], int y);

void LoadDictionary(char * filename);
int CheckDictionary(char * word);
int ScoreString(char * string);

char *guesskey(char *key);
char *encodestringkey(char* string, char* key);
char *decodestringkey(char* string, char* key);

void TestFunc();

char *Shuffle(char *key);
char *freqkey(char *code);
char *reorderedkey(char *key);

int CharacterDistribution(char* hidden);

int main(){
    srand(time(0));   
    LoadDictionary("Dictionary10k.txt");
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
            //DecodeRotation();
            //printf("%d \n", ScoreString("EVERY IS A FGLJKHSDAFHJDJSHF"));
            //printf("%s", guesskey("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"));
            //printf("%s", decodestringkey("UFTU TUSJOH", "BCDEFGHIJKLMNOPQRSTUVWXYZA"));
            TestFunc();
            //printf("%s\n", firstkey("AAAAAAAAHHLMMMMMOO"));
            //printf("%s\n", reorderedkey("FPOBJSUTEDMGIQNLXVHWZCAKRY"));
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

void LoadDictionary(char * filename){
    int i;
    FILE *input = fopen(filename, "r"); //opens the text file
    for(i = 0; (i < 9000); i++){ //tests all words in the file
        fscanf(input, "%s", dict[i]); 
    }
    fclose(input); // closes file after use
}

int CheckDictionary(char * word){
    int i;
    for(i = 0; (i < 9000); i++){ //tests all words in the file
        if (strlen(dict[i]) > strlen(word)){
            break;
        }
        if (strcmp(dict[i], word) == 0){ //if the string is in the file and matches the cipher
           if (strlen(word) < 4){
               return 0;
           }
           else{
               return strlen(word) * strlen(word);
           }
           break;
        }
    }
    return 0;
}

int ScoreString(char * string){
    char tmpstring[1000];
    int totalscore = 0;
    strcpy(tmpstring, string);
    char *hidden = strtok(tmpstring, delim);
    while(hidden != '\0'){
        totalscore += CheckDictionary(hidden)*20 + CharacterDistribution(hidden); // add a score point to the key tally
        //printf("Score - %d, Word %s\n", totalscore, hidden);
        hidden = strtok(NULL, delim); // move to next word in the string
	}
	return totalscore;
}

char newkey[26];
char *guesskey(char *key){
    char tempchar;
    strcpy(newkey, key);
    int index1 = rand()%26;
    int index2 = rand()%25;
    if (index1 == index2){
        index2 = 25; 
    }
    tempchar = newkey[index1];
    newkey[index1] = newkey[index2];
    newkey[index2] = tempchar;
    return newkey;
}



char encodedstring[10000];
char *encodestringkey(char* string, char* key){
    int i;
    int n;
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    strcpy(encodedstring, string);
    for(i = 0; encodedstring[i] != '\0'; i++){ //a for loop stopping upon the end of string
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
    return encodedstring;
}

char decodedstring[10000];
char *decodestringkey(char* string, char* key){
    int i;
    int n;
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    strcpy(decodedstring, string);
    for(i = 0; decodedstring[i] != '\0'; i++){ //a for loop stopping upon the end of string
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
    return decodedstring;    
}

void TestFunc(){
    int i;
    int improvcounter = 0;
    int tolerance = 0;
    int bestscore;
    int testscore;
    char testkey[26];
    char bestGuessKey[26];// = {"ETAOINSRHLDCUMFPGWYBVKXJQZ"};
    char secretPhrase[] = {"NEVER IS THIS PRINCIPLE MORE PERTINENT THAN WHEN DEALING WITH TYPE, THE BREAD AND BUTTER OF WEB-BORNE COMMUNICATION. A WELL-SET PARAGRAPH OF TEXT IS NOT SUPPOSED TO WOW THE READER; THE WOWING SHOULD BE LEFT TO THE IDEA OR OBSERVATION FOR WHICH THE PARAGRAPH IS A VEHICLE. IN FACT, THE PERFECT PARAGRAPH IS UNASSUMING TO THE POINT OF NEAR INVISIBILITY. THAT IS NOT TO SAY THAT THE APPEARANCE OF YOUR TEXT SHOULD HAVE NO APPEAL AT ALL. ON THE CONTRARY: WELL-BALANCED, COMFORTABLY READ TYPOGRAPHY IS A THING OF BEAUTY; IT’S JUST NOT THE ARRESTING SORT OF BEAUTY THAT MIGHT DISTRACT YOU FROM READING."};
    char secretKey[] = {"KEIJUTVHPSNCFAMWGDQZXYBROL"};
    char code[100000]; 
    strcpy(code, encodestringkey(secretPhrase, secretKey));
    
    strcpy(bestGuessKey, reorderedkey(freqkey(code)));
    //printf("%s %s\n", freqkey(code), bestGuessKey);
    bestscore = ScoreString(decodestringkey(code, bestGuessKey));
    printf("%d was the initial score \n%s - was the initial encoded text\n", bestscore, code);
    
    for(i = 0; i < 5000; i++){
        strcpy(testkey, guesskey(bestGuessKey));
        testscore = ScoreString(decodestringkey(code, testkey));
        if (testscore > (bestscore - tolerance)){
            strcpy(bestGuessKey, testkey);
            bestscore = testscore;
            improvcounter = 0;
            tolerance = 0;
        }
        else{
            improvcounter += 1;
        }
        
        if((i < 4500) && (improvcounter > 50)){
            tolerance += 5;
        }
       
        
        if (i%100 == 0){
            printf("%d - %d %d %d %d\n", i,  bestscore, CharacterDistribution(decodestringkey(code, bestGuessKey)), improvcounter, tolerance);
        }
    }
    printf("%s - was the best key \n%s - was the decoded text \n%d - was the best score\n", bestGuessKey, decodestringkey(code, bestGuessKey), bestscore);
}

int CharacterDistribution(char* hidden){
    int i;
    int charscoretally = 0;
    for(i = 0; hidden[i] != '\0'; i++){
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
    return charscoretally;
}

char newkey[26];
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

char approxkey[26];
char *freqkey(char *code){
    int i;
    int maxcount = 0;
    int charcount[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int c;
    for(i = 0; code[i] != '\0'; i++){
        if ((code[i] >= 'A') && (code[i] <= 'Z')){
            charcount[code[i]-'A'] += 1;
            if (charcount[code[i]-'A'] > maxcount){
                maxcount = charcount[code[i]-'A'];
            }
        }
    }

    int j = 0;
    for (i = maxcount; i >= 0 ; i--){
        for (c = 0; c < 26; c++){
            if (charcount[c] == i){
                approxkey[j] = 'A' + c;
                j += 1;
            }
        }
    }
    return approxkey;
}

//printf("%s\n", keyguess("RRRRRRRSSTTTB"));

char rokey[26];
char *reorderedkey(char *key){
    int i;
    int c;
    char freq[] = {"ETAOINSRHLDCUMFPGWYBVKXJQZ"};
    for (i = 0; i < 26; i++){
        c = freq[i]-'A';
        rokey[c] = key[i];
    }
    return rokey;
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
    
    while(hidden != '\0'){
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
    char key[] = {"ETAOINSRHLDCUMFPGWYBVKXJQZ"};
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
    char key[] = {"ETAOINSRHLDCUMFPGWYBVKXJQZ"};
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