
#include <string>
using namespace std;

class Student {
private:
	string name;		// data members
	float gpa;
	int enrollYear, rollNumber;


public:
	Student();			 // constructor

	// member functions. Function definition in student.cpp
	void setName(string name_input);
	void setGpa(float gpa_input);
	void setEnrollYear(int enrollYear_input);
	void setRollNumber(int rollNumber_input);
	void displayStudent();
	string getName();
	float getGpa();
	int getEnrollYear();
	int getRollNumber();
};

