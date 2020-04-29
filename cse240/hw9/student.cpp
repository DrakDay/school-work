
#include "student.h"
#include <iostream>
#include <string>

using namespace std;

// Q1 Student (2 points)
// Student() constructor assigns the following default values to class data members
// name: abc
// gpa: 1.0
// enrollYear: 2019
// rollNumber: 0
Student::Student()
{
	name = "abc";
	gpa = 1.0;
	enrollYear = 2019;
	rollNumber = 0;
}

// Q2 (18 points)
// 2 points for each function

// Define all the class member functions.
// While defining member functions, note that these functions will be called using 
// a 'Student' object which will represent one student.
// Eg-  Student s[10]; creates 10 Student objects
//		s[2].setGpa(3.5); will set 3rd student's GPA to 3.5

// setName assigns 'name_input' to class data member 'name'
void Student::setName(string name_input)
{
	name = name_input;
}

// setGpa assigns gpa_input to class data member 'gpa'
void Student::setGpa(float gpa_input)
{
	gpa = gpa_input;
}

// setEnrollYear assigns 'enrollYear_input' to class data member 'enrollYear'
void Student::setEnrollYear(int enrollYear_input)
{
	enrollYear = enrollYear_input;
}

// setRollNumber assigns 'rollNumber_input' to class data member 'rollNumber'
void Student::setRollNumber(int rollNumber_input)
{
	rollNumber = rollNumber_input;
}

// displayStudents displays the name, GPA, enrollment year and roll number of the student
// See expected output in question file.
void Student::displayStudent()
{
	cout << "Name : " << name << endl;
	cout << "GPA : " << gpa << endl;
	cout << "Enrollment year : " << enrollYear << endl;
	cout << "Roll Number : " << rollNumber << endl;
}

// getName returns the class data member 'name'.
string Student::getName()
{
	// enter code here

	return name;	// remove line if needed
}

// getGpa returns the class data member 'gpa'.
float Student::getGpa()
{
	// enter code here

	return gpa;		// remove line if needed
}

// getEnrollYear returns the class data member 'enrollYear'.
int Student::getEnrollYear()
{
	// enter code here
	return enrollYear;		// remove line if needed
}

// getRollNumber returns the class data member 'rollNumber'.
int Student::getRollNumber()
{	// enter code here

	return rollNumber;		// remove line if needed
}
