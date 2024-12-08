//Georgia Guillebeau
//Elijah Biddle
//Brooke Bobards
//11.28.2024
//Purpose: Functions for final project

#include <stdio.h>
#define ROW 50 //An arbitrary number to use until we figure out how big the file is
#define COLUMN 100 //Each line only has a MAX of 50 characters
#define STR_CAP 100
#define FILENAME "madlib1.txt"
#define FILENAME2 "madlib2.txt"

//Function Prototypes

//Georgia's Function that read and store the Madlib
int stringLength(const char string[]);
void chopString(char string[]);
void copy(int row, int col, char source[], char dest[][col]);
void readSort(FILE* fptr, int row, int col, int *lineCounter, char sortedArray[], char fileStrings[][col]);
//elijah's function that asks user for adjective/verb/noun
void prompt(char typeArray[], char words[ROW][COLUMN]);


int main(){
	char testString[STR_CAP]; //Tests to find if it is a string or a single character (blank), and determin string length, temporary storage
	char typeArray [STR_CAP]; //Holds the collection of blanks
	char userWords[ROW][COLUMN]; //The user entered words
	char template[ROW][COLUMN]; //Stores the collection of strings from template
	FILE* madlibptr = fopen(FILENAME, "r");
	int actualRows = 0, rowT = 0, rowU = 0; //Will keep track of the amount of lines in the file
	if(madlibptr == NULL){ //We still only open the file once
		("Unable to open Madlib text file\n");
		return 0;
	}
	else{
		readSort(madlibptr, ROW, COLUMN, &actualRows, typeArray, template); 
		fclose(madlibptr);
	}
	
	//gets users words elijah
	prompt(typeArray, userWords);
	
	for(int i = 0; typeArray[i] != '\0'; i++){ //For testing purposes to show that it stores user words
		printf("%s ", userWords[i]);
	}
	
	for(int i = 0; typeArray[i] != '\0'; i++){ //For testing purposes to show that it stores correctly
		printf("%c ", typeArray[i]);
	}
	printf("\n");
	printf("%d\n", actualRows); //Testing that our pointer updated correctly in the readSort function
	for(int i = 0; i < 11; i++){  //Now we will use the 'actualRows' when referancing our 2D array for the template
		printf("%s ", template[i]); //This is also for testing purposes
	}
	for(int i = 0; i < actualRows; i++){	//Test that it prints every other line for the full template
		if(i % 2 == 0){
			printf("%s ", template[rowT]);
			rowT++;
		}
		else{
			printf("%s ", userWords[rowU]);
			rowU++;
		}
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
	if(string[length - 2] == ' '){   //removes any extra spaces
		string[length - 2] == '\0';
	}
	else if(string[length - 1] == '\n'){
	 string[length - 1] = '\0';
	}
}

void copy(int row, int col, char source[], char dest[][col]){ //Specifically for copying into 2D array
	int i;
	for(i = 0; source[i] != '\0'; i++){
		dest[row][i] = source[i];
	}
	dest[row][i] = '\0';
}

//This function reads teh file, and sorts it into the respective arrays, and also counters how many lines are in the file
void readSort(FILE* fptr, int row, int col, int* lineCounter, char sortedArray[], char fileStrings[][col]){ //This function reads the file, and sorts between sentences and blanks
	int i, currentLength, sortIndex = 0, currentRow = 0, lines = 0;
	char string[col]; //A temporary 1D array to store each lines string, to be able to then sort it
	while(fgets(string, STR_CAP, fptr)){	//Whenever this loop runs, it adds tothe line count
		lines++;
		currentLength = stringLength(string) - 1; //First determine string length
		if(currentLength == 1 && (string[0] == 'A' || string[0] == 'N' || string[0] == 'V')){ // if it is a blank, include in sorted 'fill in blank' array
			sortedArray[sortIndex] = string[0];
			sortIndex++;
		}
		else{  //if it is apart of the madlib template, chop it (add null) and copy it into the madlib 2D array
			chopString(string);
			copy(currentRow, COLUMN, string, fileStrings);
			currentRow++;
			}
		}	
	*lineCounter = lines;
}


void prompt(char typeArray[], char words[ROW][COLUMN]){
	for (int i = 0; i < STR_CAP; i++) {
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
