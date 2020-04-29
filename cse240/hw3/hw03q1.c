//CSE240 Spring 2019 HW3

// zhi li hu
// State the IDE that you use: GCC

#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)  // compiler directive for Visual Studio only

// Read before you start:
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// You shoud not modify the function return types or parameters.
// You can assume that all inputs are valid. Ex: If prompted for an integer, the user will input an integer.

// Global Macro Values. They are used to define the size of 2D array of characters
#define NUM_STRINGS 4
#define STRING_LENGTH 50

// Forward Declarations
void initializeStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);
void reverseStrings(char strings[NUM_STRINGS][STRING_LENGTH]);
void encryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void decryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
int splitAndPrintSentences(char s[NUM_STRINGS*STRING_LENGTH]);
void inputMatrix(int matrixA[3][3]);
void determinant(int matrixA[3][3]);

// Problem 1: initializeStrings (5 points)
// Traverse the 2D array of characters variable 'strings' (input from user in main() ) and set all characters in each
// array to a null terminator so that there is a 4 row and 35 column 2D array full of null terminators.
// The null terminator is represented by the character value '\0' and is used to denote the end of a string.
// This may come in use later in the program to know the end of string.
void initializeStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i,j;
	for(i=0; i<NUM_STRINGS; i++)
	{
		for(j=0; j<STRING_LENGTH; j++)
		{
			strings [i][j] = '\0';
		}
	}
}

// Problem 2: printStrings (5 points)
// Traverse the 2D character array "strings" and print each of the contained strings.
// See the example outputs provided in the word document. Your output should match the example outputs.
void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i,j;
	for(i =0; i< NUM_STRINGS; i++)
	{
		for(j =0; j<STRING_LENGTH; j++)
		{
			printf("%c",strings[i][j]);
		}
	printf("\n");
	}
}

// Problem 3: reverseString (5 points)
// Reverse each string of strings[][]. 
// Consider one string at a time and reverse the characters. For instance, "hi hello" should reverse to "olleh ih".
void reverseStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	int i,j;
	for(i = NUM_STRINGS; i>=0 ;i--)
	{
		for(j =STRING_LENGTH; j>=0; j--)
		{
			printf("%c",strings[i][j]);
		}
	printf("\n");
	}
}

// Problem 4: encryptStrings (5 points)
// Traverse the 2D character array 'strings' and encrypt each string in 2 steps as follows-
// 1) Reverse the string. 
// Hint: Use 'reverseStrings()' for this step. 
// 2) Then shift those ASCII characters forward by the integer value of 'key'.
// If the string is "hello" and key = 2, reversing will get you "olleh" and adding key to it will result in "qnnfj"
// If the value of 'key' is large, you will extend past the alphabetical characters and reach non-alphabetical characters. Thats ok.

// NOTE: DO NOT encrypt the null terminator character. Use the null terminator '\0' to find the end string.
// *** NOTE: If you were unable to code for reverseStrings(), then skip that step in this function and simply shift the characters ahead by 'key'.
//			While decrypting in the next function, you will again have to skip the reversing part. You will get partial points in that case.	
void encryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	int i,j;
	reverseStrings(strings);
	
	for (i =0; i<NUM_STRINGS; i++)
	{
		for(j =0; j<STRING_LENGTH; j++)
		{
			if(strings[i][j] == '\0')
				break;
			else
				strings[i][j] = strings[i][j]+key;
		}
	}
	
}
// Problem 5: decryptStrings (5 points)
// HINT: This should be very similiar to the encryption function defined above.
// Traverse the 2D character array 'strings' and decrypt each string in 2 steps as follows- 
// 1) Shift those ASCII characters backward by the integer value of 'key'.
// 2) Then reverse the string.
// Hint: Use 'reverseStrings()' for this step.
// *** NOTE: If you were unable to code for reverseStrings(), then skip that step in this function and simply shift the characters backward by 'key'.
//			You will get partial points in that case.
void decryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	int i,j;
	for (i = 0; i < NUM_STRINGS; i++)
	{
		for (j = 0; j < STRING_LENGTH; j++)
		{
			if (strings[i][j] == '\0')
				break;
			else
				strings[i][j] = strings[i][j] - key;
		}
	}
	reverseStrings(strings);
}

// Problem 6: splitAndPrintSentences (10 points)
// Split s[] into individual sentences and store them in str[][].
// Read s[] character by character and copy into str[][], such that sentence 1 is in str[0][], sentence 2 is in str[1][] and so on.
// Print the char array str[][], so that you will print the separated sentences. Finally return the number of sentences in 'count'
// Dont forget to initialize str[][] with nulls.
// Hint: Sentences are separated by full-stop.

int splitAndPrintSentences(char s[NUM_STRINGS*STRING_LENGTH])
{
	char str[NUM_STRINGS][STRING_LENGTH];
	int count = 0;
	int i, j=0;
	// enter code below
	for (i = 0; s[i] != NULL; i++)
	{
		if (s[i] != '.')
		{
			str[count][j] = s[i];
			j++;
		}
		else {
			str[count][j] = ' ';
			count++;
			j = 0;
		}
	}
	for (i = 0;i < count; i++)
	{
		printf("\n%s", str[i]);
	}
	return count;
}

// Problem 7: inputMatrix (10 points)
// Ask the user for each element of the 3X3  matrix and store the elements in "matrixA[][]"
// Display the matrix in the following form:
// matrixA =
// 1 2 3
// 4 5 6
// 7 8 9
// The user may input any inetgers for matrix elements, not necessarily same as example above.
void inputMatrix(int matrixA[3][3])
{	
	int i,j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("plase enter integer element at [%d][%d]= ", i, j);
			scanf("%d", &matrixA[i][j]);
		}
	}
	printf("\nMatrix = \n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d", matrixA[i][j]);
		}
		printf("\n");
	}
}

// Problem 8: determinant (5 points)
// Calculate the determinant of the 3x3 matrix "matrixA[][]" and print it.
// Read about how to caclualte the determinant of 3x3 matrix. Here is a video tutorial: https://www.khanacademy.org/math/algebra-home/alg-matrices/alg-determinants-and-inverses-of-large-matrices/v/finding-the-determinant-of-a-3x3-matrix-method-2
// Since it is strictly a 3x3 matrix, you may use hardcoded indices. For eg- matrixA[0][0] to access 1st element of the matrix
void determinant(int matrixA[3][3])
{
	int  det, part1, part2, part3;
		// enter code below
	
	part1 = matrixA[0][0] * (matrixA[1][1] * matrixA[2][2] - matrixA[1][2] * matrixA[2][1]);
	part2 = matrixA[0][1] * (matrixA[1][0] * matrixA[2][2] - matrixA[2][0] * matrixA[1][2]);
	part3 = matrixA[0][2] * (matrixA[1][0] * matrixA[2][1] - matrixA[2][0] * matrixA[1][1]);
	det = part1- part2 + part3;


	printf("\nDeterminant of matrix = %d\n", det);
}

// You should study and understand how this main() works.
// *** DO NOT modify it in any way ***
int main()
{
	char sentences[NUM_STRINGS*STRING_LENGTH];
	char strings[NUM_STRINGS][STRING_LENGTH]; // will store four strings each with a max length of 34
	int i, key, count;
	char input[STRING_LENGTH];
	int matrixA[3][3];						// 3x3 int array for matrix
	
	printf("CSE240 HW3: 2D Character Arrays\n\n");
	initializeStrings(strings);
	
	for (i = 0; i < NUM_STRINGS; i++)
	{
		printf("Enter string for encryption: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store input string
		input[strlen(input) - 1] = '\0'; // convert trailing '\n' char to '\0' (null terminator)
		strcpy(strings[i], input); // copy input to 2D strings array
	}
	
	printf("\nEnter a key value for encryption: "); // prompt for integer key
	scanf("%d", &key); 
	
	encryptStrings(strings, key);
	printf("\nEncrypted Strings:\n");
	printStrings(strings);
	decryptStrings(strings, key);
	printf("\nDecrypted Strings:\n");
	printStrings(strings);
	
	i = getchar(); // remove the character '\n'
	printf("\nEnter sentences(max 4): ");
	fgets(sentences, sizeof(sentences), stdin); // store string
	input[strlen(sentences) - 1] = '\0';			// convert trailing '\n' char to '\0' (null terminator)
	count = splitAndPrintSentences(sentences);
	printf("\nNumber of sentences= %d \n", count);

	printf("\nCSE240 HW3: 2D Integer Arrays\n\n");
	inputMatrix(matrixA);
	determinant(matrixA);

	i = getchar(); // remove the character '\n'
	i = getchar(); // keep console open in VS
	return 0;
}
