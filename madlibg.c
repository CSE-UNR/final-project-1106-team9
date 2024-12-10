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
void readSort(FILE* fptr, int row, int col, int *lineCounter, int* blankCounter, char sortedArray[], char fileStrings[][col], int lineArray[]);
//elijah's function that asks user for adjective/verb/noun
void prompt(char typeArray[], char words[ROW][COLUMN]);


int main(){
	char testString[STR_CAP]; //Tests to find if it is a string or a single character (blank), and determin string length, temporary storage
	char typeArray [STR_CAP]; //Holds the collection of blanks
	char userWords[ROW][COLUMN]; //The user entered words
	char template[ROW][COLUMN]; //Stores the collection of strings from template
	FILE* madlibptr = fopen(FILENAME2, "r");
	int actualRows = 0, numBlanks = 0, rowT = 0, rowU = 0, blankIndex = 0;//Will keep track of the amount of lines in the file
	int blankTracker[ROW]; //Keeps track of what lines the blanks are on, the size index will change after we account for the total amount of lines
	if(madlibptr == NULL){ //We still only open the file once
		("Unable to open Madlib text file\n");
		return 0;
	}
	else{
		readSort(madlibptr, ROW, COLUMN, &actualRows, &numBlanks, typeArray, template, blankTracker); 
		fclose(madlibptr);
	}
	printf("%d\n", numBlanks);
	for(int i = 0; i < numBlanks; i++){	///Test that is have blanks at corresponding lines
		printf("%d ", blankTracker[i]);
	}
	printf("%d\n", actualRows);
	
	//gets users words elijah
	prompt(typeArray, userWords);
	
	/*for(int i = 0; typeArray[i] != '\0'; i++){ //For testing purposes to show that it stores user words
		printf("%s ", userWords[i]);
	}
	
	for(int i = 0; typeArray[i] != '\0'; i++){ //For testing purposes to show that it stores correctly
		printf("%c ", typeArray[i]);
	}
	printf("\n");
	printf("%d\n", actualRows); //Testing that our pointer updated correctly in the readSort function
	for(int i = 0; i < 11; i++){  //Now we will use the 'actualRows' when referancing our 2D array for the template
		printf("%s ", template[i]); //This is also for testing purposes
	}*/
	for(int i = 0; i < actualRows; i++){	//Test that it prints every other line for the full template
		if(blankTracker[blankIndex] == i && blankIndex < numBlanks){
			printf("%s ", userWords[rowU]);
			rowU++;
			blankIndex++;
		}
		else{
			printf("%s ", template[rowT]);
			rowT++;
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
		if(dest[row][i] == '\n'){
			printf("1\n");
		}
	}
	dest[row][i] = '\0';
}

//This function reads teh file, and sorts it into the respective arrays, and also counters how many lines are in the file
void readSort(FILE* fptr, int row, int col, int* lineCounter, int* blankCounter, char sortedArray[], char fileStrings[][col], int lineArray[]){ //This function reads the file, and sorts between sentences and blanks
	int i, currentLength, sortIndex = 0, currentRow = 0, lines = 0, lineIndex = 0, blanks = 0;
	char string[col]; //A temporary 1D array to store each lines string, to be able to then sort it
	while(fgets(string, STR_CAP, fptr)){	//Whenever this loop runs, it adds tothe line count
		lines++;
		currentLength = stringLength(string) - 1; //First determine string length
		if(currentLength == 1 && (string[0] == 'A' || string[0] == 'N' || string[0] == 'V')){ // if it is a blank, include in sorted 'fill in blank' array
			sortedArray[sortIndex] = string[0];
			lineArray[lineIndex] = lines;
			sortIndex++;
			lineIndex++;
			blanks++;
			
		}
		else{  //if it is apart of the madlib template, chop it (add null) and copy it into the madlib 2D array
			chopString(string);
			copy(currentRow, COLUMN, string, fileStrings);
			currentRow++;
			}
		}	
	*lineCounter = lines;
	*blankCounter = blanks;
}


void prompt(char typeArray[], char words[ROW][COLUMN]){
for (int i = 0; i < STR_CAP; i++) {
char type = typeArray[i];
switch (type){
	case 'A': 
		printf("Please enter an adjective: ");
		fgets(words[i], COLUMN - 1, stdin);
		break;
	case 'N' :
		printf("Please enter an noun: ");
		fgets(words[i], COLUMN - 1, stdin);
		break;
	case 'V':
		printf("Please enter an verb: ");
		fgets(words[i], COLUMN - 1, stdin);
		break;
	}
		int length = stringLength(words[i]);
        	if (words[i][length-1] == '\n') {
            		words[i][length-1] = '\0';
            }
		
	}



}
