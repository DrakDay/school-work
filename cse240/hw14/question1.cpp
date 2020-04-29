#include <iostream>
using namespace std;
int foo(int x, int y)  //size n problem
{
	if (y <= 0)	      // stoping condtion 1
		return x;     // its return value
	else if (x <= 0)  // stoping condtion 2
		return y;     // its return value
	else if (x >= y)  // condtion check
		return x + foo(x - 1, y - 1);   // size m problem and its soulution
	else
		return y + foo(x - 2, y - 3);   // size m problem and its soultion 
}	
int main()
{
	cout << foo(5, 6);
	system("pause");
	return 0;
}