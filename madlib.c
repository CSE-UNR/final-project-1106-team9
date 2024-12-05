//Georgia Guillebeau
//Elijah Biddle
//Brooke Bobards
//11.28.2024
//Purpose: Functions for final project

#include <stdio.h>
#define ROW 100  //Rows for 2D Arrays, is the size of lines of the Madlib Template (currently not being used)
#define COLUMN 100 //Columns for 2D Arrays (currently not being used)
#define STR_CAP 100
#define FILENAME "madlib1.txt"
#define FILENAME2 "madlib2.txt"

//Function Prototypes
int stringLength(const char string[]);
void chopString(char string[]);
void copy(int row, char source[], char dest[row][COLUMN]);
void readFile(FILE* fptr, char string[], char sortedArray[]);
void collectTemplate(FILE *fptr, char string[], char fileStrings[ROW][COLUMN]);
//elijah's function that asks user for adjective/verb/noun
void prompt(char typeArray[], char words[ROW][COLUMN]);


#include <stdio.h>
#define ROW 100  //Rows for 2D Arrays, is the size of lines of the Madlib Template (currently not being used)
#define COLUMN 100 //Columns for 2D Arrays (currently not being used)
#define STR_CAP 100
#define FILENAME "madlib1.txt"
#define FILENAME2 "madlib2.txt"

int main(){
	char testString[STR_CAP]; //Tests to find if it is a string or a single character (blank)
	char typeArray [STR_CAP]; //Holds the collection of blanks
	char userWords[ROW][COLUMN]; //The user entered words
	char template[ROW][COLUMN]; //Stores the collection of strings from template
	FILE* madlibptr = fopen(FILENAME2, "r");
	if(madlibptr == NULL){	
		printf("Unable to open Madlib text file\n");
		return 0;
	}
	else{
		readFile(madlibptr, testString, typeArray);
		fclose(madlibptr);
	}
	madlibptr = fopen(FILENAME2, "r");
	if(madlibptr == NULL){
		("Unable to open Madlib text file\n");
		return 0;
	}
	else{
		collectTemplate(madlibptr, testString, template); //Test string is used as a temp string to display the words in file
		fclose(madlibptr);
	}
	//gets users words elijah
	prompt(typeArray, userWords);
	
	for(int i = 0; typeArray[i] != '\0'; i++){ //For testing purposes to show that it stores user words
		printf("%s ", userWords[i]);
	}
	
	for(int i = 0; typeArray[i] != '\0'; i++){ //For testing purposes to show that it stores correction
		printf("%c ", typeArray[i]);
	}
	printf("\n");
	for(int i = 0; i < 18; i++){  //18 lines in second madlib.txt file
		printf("%s ", template[i]); //This is also for testing purposes
	}
	printf("\n");
	return 0;
}

int stringLength(const char string[]){
	int i, length = 0;
	for(i = 0; string[i] != '\0'; i++){
		length++;
	}
	return length;
}

void chopString(char string[]){
	int length;
	length = stringLength(string);
	if(string[length - 2] == ' '){   //removes and extra spaces
		string[length - 2] == '\0';
	}
	else if(string[length - 1] == '\n'){
	 string[length - 1] = '\0';
	}
}

void copy(int row, char source[], char dest[row][COLUMN]){ //Specifically for copying into 2D array
	int i;
	for(i = 0; source[i] != '\0'; i++){
		dest[row][i] = source[i];
	}
	dest[row][i] == '\0';
}

void readFile(FILE* fptr, char string[], char sortedArray[]){
	int currentLength, sortIndex = 0, n = 22, i; //n is the number of lines
	for(i = 0; i < n; i++){
		fgets(string, STR_CAP, fptr);
		currentLength = stringLength(string) - 1;
		if(currentLength == 1){
			sortedArray[sortIndex] = string[0];
			sortIndex++;
		}
	}
	sortedArray[sortIndex + 1] = '\0';
}

void collectTemplate(FILE *fptr, char string[], char fileStrings[ROW][COLUMN]){
	int n = 22, i, j = 0, length, index, row = 0;
	for(i = 0; i < n; i++){
		fgets(string, STR_CAP, fptr);
		chopString(string);
		if(i >= 1 &&  i % 2 == 0){	//Only every other line gets printed
			copy(row, string, fileStrings);
			row++;
		}
		else if(i == 0){
			copy(row, string, fileStrings);
			row++;
		}
	}
}

void prompt(char typeArray[], char words[ROW][COLUMN]){
	for (int i = 0; typeArray[i] != '\0'; i++) {
		if(typeArray[i] == 'A') {
			printf("Please enter an adjective: ");
			fgets(words[i], COLUMN-1, stdin);
		} else if(typeArray[i] == 'N') {
			printf("Please enter an noun: ");
			fgets(words[i], COLUMN-1, stdin);
		} else if(typeArray[i] == 'V') {
			printf("Please enter an verb: ");
			fgets(words[i], COLUMN-1, stdin);
		}
	}



}
