
// CSE240 Spring 2019 HW6
// zhi li hu
// Write the compiler used:gcc

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of patient records.
// Each record(struct) has this information: patient's name, doctor's name, critical level of patient, room number.
// The struct 'patientRecord' holds information of one patient. Critical level is enum type.
// A linked list called 'list' is made to hold the list of patients.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.
// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. 10% deduction for not using comments *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_NAME_LENGTH 25

typedef enum { very_critical = 0, critical, not_critical } criticalType; // enum type 

struct patientRecord {
	char patientName[MAX_NAME_LENGTH];
	char doctorName[MAX_NAME_LENGTH];
	criticalType criticalLevel;
	unsigned int roomNumber;
	struct patientRecord* next;	// pointer to next node
} *list = NULL;					// Declare linked list 'list'

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
int add(char* patientName_input, char* doctorName_input, char* criticalLevel_input, unsigned int roomNumber_input); // 10 points
void displayList();						// 10 points
int countNodes();						// 5 points
int deleteNode(char* patientName_input);	// 10 points
void swapNodes(struct patientRecord* node1, struct patientRecord* node2);	// 5 points
void sortList();						// 10 points


int main()
{	
	char selection = 'i';		// initialized to a dummy value
	printf("\nCSE240 HW6\n");
	do
	{
		printf("\nCurrently %d patient(s) on the list.", countNodes());	// NOTE: countNodes() called here
		printf("\nEnter your selection:\n");
		printf("\t a: add a new patient\n");
		printf("\t d: display patient list\n");
		printf("\t r: remove a patient from the list\n");
		printf("\t s: sort patient list by name\n");
		printf("\t q: quit\n");
		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar(); 
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the code in the function, case by case
void executeAction(char c)
{
	char patientName_input[MAX_NAME_LENGTH], doctorName_input[MAX_NAME_LENGTH];
	unsigned int roomNumber_input, result = 0;
	char criticalLevel_input[20];
	switch (c)
	{
	case 'a':	// add patient
		// input patient details from user
		printf("\nEnter patient name: ");
		fgets(patientName_input, sizeof(patientName_input), stdin);
		patientName_input[strlen(patientName_input) - 1] = '\0';	// discard the trailing '\n' char

		printf("Enter doctor name: ");
		fgets(doctorName_input, sizeof(doctorName_input), stdin);
		doctorName_input[strlen(doctorName_input) - 1] = '\0';	// discard the trailing '\n' char

		printf("Enter whether patient is 'very critical' or 'critical' or 'not critical': ");
		fgets(criticalLevel_input, sizeof(criticalLevel_input), stdin);
		criticalLevel_input[strlen(criticalLevel_input) - 1] = '\0';	// discard the trailing '\n' char

		printf("Please enter room number: ");
		scanf("%d", &roomNumber_input);
		flushStdIn();

		// add the patient to the list
		result = add(patientName_input, doctorName_input, criticalLevel_input, roomNumber_input);
		if (result == 0)
			printf("\nPatient is already on the list! \n\n");
		else if (result == 1)
			printf("\nPatient successfully added to the list! \n\n");
		else
			printf("x");
		break;

	case 'd':		// display the list
		displayList();
		break;

	case 'r':		// remove a patient
		printf("\nPlease enter patient name: ");
		fgets(patientName_input, sizeof(patientName_input), stdin);
		patientName_input[strlen(patientName_input) - 1] = '\0';	// discard the trailing '\n' char

		// delete the node
		result = deleteNode(patientName_input);
		if (result == 0)
			printf("\nPatient does not exist! \n\n");
		else if (result == 1)
			printf("\nPatient successfully removed from the list. \n\n");
		else
			printf("\nList is empty! \n\n");
		break;

	case 's':		// sort the list
		sortList();
		break;

	case 'q':		// quit
		break;
	default: printf("%c is invalid input!\n",c);
	}
}

// Q1 : add (10 points)
// This function is used to insert a new patient into the list. You can insert the new patient to the end of the linked list.
// Do not allow the patient to be added to the list if that patient already exists in the list. You can do that by checking the names of the patients already in the list.
// If the patient already exists then return 0 without adding patient to the list. If the patient does not exist in the list then go on to add the patient at the end of the list and return 1.
// NOTE: You must convert the string 'criticalLevel_input' to an enum type and store it in the list because the struct has enum type for critical level.

int add(char* patientName_input, char* doctorName_input, char* criticalLevel_input, unsigned int roomNumber_input) // 20 points
{
	struct patientRecord* tempList = list;	// work on a copy of 'list'
	// enter code here
	while (tempList)
	{
		if (strcmp(tempList->patientName, patientName_input) == 0)
		{
			return 0;
		}
		if (tempList->next != NULL)
			tempList = tempList->next;
		else
			break;
	}

	struct patientRecord* newpatient = (struct patientRecord*) malloc(sizeof(struct patientRecord));
	strcpy(newpatient->patientName, patientName_input);
	strcpy(newpatient->doctorName, doctorName_input);
	if (strcmp(criticalLevel_input, "very critical") == 0) {
		newpatient->criticalLevel = very_critical;
	}
	else if (strcmp(criticalLevel_input, "critical") == 0) {
		newpatient->criticalLevel = critical;
	}
	else {
		newpatient->criticalLevel = not_critical;
	}
	newpatient->roomNumber = roomNumber_input;
	newpatient->next = NULL;
	if (tempList != NULL)
		tempList->next = newpatient;
	else {
		tempList = newpatient;
		list = tempList;
	}
	return 1;	// edit this line as needed
}

// Q2 : displayList (10 points)
// This function displays the linked list of patients, with all details (struct elements). 
// Parse through the linked list and print the patient details one after the other. See expected output screenshots in homework question file.
// NOTE: Critical level is stored in the struct as enum type. You need to display a string for critical level.
void displayList()
{
	struct patientRecord* tempList = list;				// work on a copy of 'list'
	// enter code here
	while (tempList != NULL)
	{
		printf("Patient Name: %s \n", tempList->patientName);
		printf("Doctor Name:  %s \n", tempList->doctorName);
		if (tempList->criticalLevel == very_critical)
		{
			printf("Critical Level: very critical\n");
		}
		else if (tempList->criticalLevel == critical) 
		{
			printf("Critical Level: critical\n");
		}
		else {
			printf("Critical Level: not critical\n");
		}
		printf("Room Number: %d\n\n", tempList->roomNumber);

		tempList = tempList->next;
	}
}

// Q3: countNodes (5 points)
// This function counts the number of patients on the linked list and returns the number.
// You may use this function in other functions like deleteNode(), sortList(), addNode(), if needed. 
// It can helpful to call this function in other functions, but not necessary.
// This function is called in main() to display number of patients along with the user menu.
int countNodes()
{
	int count = 0;
	struct patientRecord* tempList = list;	
	while (tempList != NULL)
	{
		tempList = tempList->next;
		count ++;
	}
	return count; // edit this line as needed
}

// Q4 : deleteNode (10 points)
// This function deletes the node specified by the patient name.
// Parse through the linked list and remove the node containing this patient name.
// NOTE: After you remove the node, make sure that your linked list is not broken.
// (Hint: Visualize the list as: list......-> node1 -> node_to_remove -> node2 -> ...end. 
//        After removing "node_to_remove", the list is broken into "list ....node1" and "node2.... end". Stitch these lists.)

int deleteNode(char* patientName_input)
{	
	struct patientRecord* templist = list;
	struct patientRecord* templistprve = list;
	
	if (templist == NULL)
		return 2;

	if (strcmp(templist->patientName, patientName_input) == 0)
	{
		list = templist->next;
		free(templist);
		return 1;
	}
	while (templist != NULL)
	{
		if (strcmp(templist->patientName, patientName_input) == 0)
		{
			break;
		}
		templistprve = templist;
		templist = templist->next;
	}
	if (templist != NULL)
	{
		templistprve->next = templist->next;
		free(templist);
		return 1;
	}
}


// Q5 : swapNodes (5 points)
// This function swaps the elements of parameters 'node1' and 'node2' (Here node1 does NOT mean 1st node of the list. 'node1' is just the name of the node)
// This function should not alter the 'next' element of the nodes. Only then will the nodes be swapped.
// Hint: The swap logic is similar to swapping two simple integer/string variables.
// NOTE: This function can be used in the sorting logic in sortList()

void swapNodes(struct patientRecord* node1, struct patientRecord* node2)
{
	char tempPatientName[MAX_NAME_LENGTH];
	char tempDoctorName[MAX_NAME_LENGTH];
	criticalType tempCriticalLevel = node1->criticalLevel;
	unsigned int tempRoomNo = node1->roomNumber;

	strcpy(tempPatientName, node1->patientName);
	strcpy(tempDoctorName, node1->doctorName);


	strcpy(node1->patientName, node2->patientName);
	strcpy(node1->doctorName, node2->doctorName);
	node1->criticalLevel = node2->criticalLevel;
	node1->roomNumber = node2->roomNumber;

	strcpy(node2->patientName, tempPatientName);
	strcpy(node2->doctorName, tempDoctorName);
	node2->criticalLevel = tempCriticalLevel;
	node2->roomNumber = tempRoomNo;

}



// Q6 : sortList (10 points)
// This function sorts the linked list by alphabetical order of patient name.
// Parse the list and compare the patient names to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new linked list of patients having sorted patients.
// Hint: One of the string library function can be useful to implement this function because the sorting needs to happen by patient name which is a string.
//       Use swapNodes() to swap the nodes in the sorting logic

void sortList()
{
	struct patientRecord* tempList = list; // work on a copy of 'list'
	struct patientRecord* tempList1 = list->next; // work on a copy of 'list'

	while (tempList) {
		while (tempList1) {
			if (strcmp(tempList->patientName, tempList1->patientName) > 0) {
				swapNodes(tempList, tempList1);
			}
			if (tempList1->next == NULL)
				break;
			tempList1 = tempList1->next;
		}
		if (tempList->next == NULL)
			break;
		tempList = tempList->next;
	}
	printf("\nPatient list sorted! Use display option 'd' to view sorted list.\n");
}
