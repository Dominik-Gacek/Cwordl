#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <time.h> 

int loadWord(char dict[][6], char word[]){ //randomly selects the word from the dictionary
    int rndm= (rand()%5757);
    for(int i=0;i<6;i++){
        word[i] = dict[rndm][i];
    }
    return *word;
    
}
int guessIn(char guess[]){ //takes in the guess
    int check = 0;
    while(check!=1){ // keeps going until a valid 5 letter word is entered
        printf("enter a 5 letter word (lowercase): ");
        check=1;
        for(int i=0; i<5;i++){
            guess[i] = getchar();
            if (guess[i]=='\n'){ //check for enter seperately so that you dont need double enter between short answers
                i=5;
                check = 2;
                printf("enter 5 letters! ");
            }else if ((guess[i]>'z') | (guess[i]<'A') | (guess[i]<'a' && guess[i]>'Z')){
                i=5;
                check = 0;
                printf("enter letters only! ");
				
            }else if (guess[i]<='Z') { //changes capital to lowercase
				guess[i]+=32;
            }
        }
        if (check!=2){
        while ( getchar() != '\n' );
        }
    }
return 0;
}
int getIncorrect(char alphabet[], char letters[], char incorrect[]){ //gets the list of incorrect guessed letters
    for(int i=0; i<26; i++){
        int check = 0;
        if(alphabet[i]==0){
                i=26;
        }else{
            for(int j=0; j<5; j++){
                if(alphabet[i]!=letters[j]){
                    check+=1;
                }
                if(check==5){
                    for(int k=0; k<26; k++){
                        if(incorrect[k]==alphabet[i]){
                            k=26;
                        }else if(incorrect[k]==0){
                            incorrect[k]=alphabet[i];
                            k=26;
                        }
                    }
                }
                
            }  
        }
    }
}

int checkValid(char guess[], char dict[][6]){ // checks if the answer is a real word
    for(int i=0; i<5757; i++){
        int test=0;
        for(int j=0; j<5; j++){
            if(dict[i][j]==guess[j]){
                test=1;
            }else{
                test=0;
                j=6;
            }
        }
        if(test==1){
            return 1;
        }
        
    }
    return 0;   /// 
}

int checkHard(char guess[], char display[], char incorrect[], char letters[]){ // checks the requirements for hard mode
    int counter =0;
    char templetters[5];
    for(int i=0; i<5; i++){
        for(int j=0; j<26; j++){
            if(guess[i]==incorrect[j]){
                return 0;
            }
        }if(display[i]!='-'){
            if(display[i]!=guess[i]){
                return 0;
            }
        }
        templetters[i]=0;
        if(letters[i]!=0){
            templetters[i]=letters[i];
        }
        
    }
    for(int k=0; k<5;k++){
        for(int i=0; i<5;i++){
            if(guess[k]==templetters[i]){
                templetters[i]=0;
            }
        }
    }
    for(int k=0; k<5;k++){
        if(templetters[k]!=0){
            return 0;
        }
    }
return 1;    
}

int checkAns(char answer[], char guess[], char display[]){ // checks if the guess is correct. returns 5 if true
    int correctLetters;
    correctLetters = 0;
    for(int i=0; i<5; i++){
        if(guess[i]==answer[i]){
            display[i]=guess[i];
            correctLetters+=1;
        }
    }
return correctLetters;
}

int checkLetters(char answer[], char guess[], char* letters, char* alphabet){ // checks all letters guessed
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(guess[i]==answer[j]){
                for(int k=0; k<5; k++){
                    if((letters[k]==0) | (answer[j]==letters[k])){
                        letters[k]=answer[j];
                        k=5;
                    } 
                }
            }
        }
        for(int m=0; m<26; m++){ // for every letter in the guess checks if the letter has been guessed before and if not it is added to 
            if((alphabet[m]==0) | (guess[i]==alphabet[m])){ // the alphabet array(used for statistics)
                alphabet[m]=guess[i];
                m=26;
            }
        }
    }
return 0;
}
int countAlphabet(char alphabet[]){ // checks how many different letters were used in this game
    int alphabetcount =0;
    for(int m=0; m<26; m++){ 
        if(alphabet[m]==0){
            m=26;
        }else{
            alphabetcount +=1;
        }
    }
    return alphabetcount;
}
int printInfo(char display[], char guess[], char letters[], char alphabet[], char incorrect[]){ // prints out all the information to help with next guess
    printf("Your guess: ");
    for(int i = 0; i<5;i++){
        printf("%c", guess[i]);
    }
    printf("\nRequired Word:    ");
    for(int i = 0; i<5;i++){
        printf("%c", display[i]);
    }
    printf("\nCorrect letters: ");
    for(int i=0; i<5; i++){
        if((letters[i]!=0)){
            printf("%c ", letters[i]);
        }
    }
    printf("\nIncorrect letters: ");
    for(int i=0; i<26; i++){
        if(incorrect[i]==0){
            i=26;
        }else{
            printf("%c ", incorrect[i]);
        }
    }
    printf("\n");
    return 0;
}

int winner(int chances){	// tells the user they won !!!!!
    printf("Congrats!!!  You guessed the correct word on guess no.%d\n  ", 6-chances);
    return 0;
}

int gameLoop(int* chances, double* alphabetrate, char dict[][6], int mode){ // controller for a single game. 
    *chances = 6;
    char guess[6];
    
    char* alphabet = (char*) malloc(26 * sizeof(char)); // array of 26 for all guessed letters
    for (int i=0; i <26; i++){ alphabet[i] = 0;}
    
    char* incorrect = (char*) malloc(26 * sizeof(char)); // array of 26 for incorrect quesses
    for (int i=0; i <26; i++){ incorrect[i] = 0;}
    
    char* letters = (char*) malloc(5 * sizeof(char)); // array of 5 zeros for correct quesses
    for (int i=0; i <5; i++){ letters[i] = 0;}
    
    char answer[6]; // required word
    loadWord(dict, answer); 
    
    char display[] = "-----";               // guessed letters in correct position
    
    int correct = 0;
    
    while (*chances >=0 && correct <5){
    guessIn(guess);
     
    if ((checkValid(guess, dict)==1)){                 // updates the letter array and display word
        
        if((mode==1)){
            if(checkHard(guess, display, incorrect, letters)==1){
                checkLetters(answer, guess, letters, alphabet);
                getIncorrect(alphabet, letters, incorrect);
                correct = checkAns(answer, guess, display);
                printInfo(display, guess, letters, alphabet, incorrect);
                *chances -=1;
            }else{
                printf("Must use all correctly guessed letters, all correctly placed letters in the right space,\n and all incorrect letters cannot be used!!!\n");
            }
        }else{
            checkLetters(answer, guess, letters, alphabet);
            getIncorrect(alphabet, letters, incorrect);
            correct = checkAns(answer, guess, display);
            printInfo(display, guess, letters, alphabet, incorrect);
            *chances -=1;
        }
    }else{
        printf("Enter a real word!\n");
    }
    
    
    }
    
    int alphabetcount = countAlphabet(alphabet);
    *alphabetrate = (alphabetcount/26.0);
    if(correct==5){
        winner(*chances);
    }
    
return 0;    
}

int statistics(int played, double* wr, int hist[], int chances) { // used to calculate the winrate and the histogram
    if (chances>=0){
        *wr = ((*wr*played)+1)/(played+1);
    }else{
        *wr = (*wr*played)/(played+1);
    }
    printf("Winrate is %.2f\nGuesses used in last 5 games:\n", *wr);
    for(int i=1; i<5; i++){
        hist[5-i] = hist[4-i];
    } 
    hist[0] = (6-chances);
    for(int k=0; k<=played&& k<5; k++){
        if(hist[k]==7){
            printf("%d Lost\n", k+1);
        }else{
            printf("%d ",k+1);
        for(int j=0; j<hist[k]; j++){
            printf("*");
        }
        printf("\n");
        }
    }
    return 0;
}
int calcRates(int played, double* ar, double currentrate){ // used to calculate the alphabet use rate
    printf("Alphabet usage last round: %.2f\n", currentrate);
    *ar = ((*ar*played)/(played+1))+(currentrate/(played+1));
    printf("Average alphabet usage: %.2f\n", *ar);
    return 0;
}


int main() {		// allocating memory for variables and arrays/pointers
    srand(time(0)); // generates random number 
    char dict[5757][6];
    int played=0;
    double winrate=0;
    double alphabetrate=0;
    int* hist;
    hist = (int*) malloc(6 * sizeof(int));
    double currentrate = 0;
    int chances;
    int mode = 0;
    load_word_list(dict);
    
		printf("Enter 0 for normal mode, 1 for hardmode, 2 for exit: "); // ask for mode selection first time in case user wants to quit.
	    mode = getchar()-48;
	    while ( getchar() != '\n' );
		
	while(mode!=2){	// checks if user didn't exit
	    
        gameLoop(&chances, &currentrate, dict, mode);
        statistics(played, &winrate, hist, chances); 
        calcRates(played, &alphabetrate, currentrate);
        played +=1;
		
		printf("Enter 0 for normal mode, 1 for hardmode, 2 for exit: "); // asks for mode selection again after every run.
	    mode = getchar()-48;
	    while ( getchar() != '\n' );
	    
	}
    return 0;
}
