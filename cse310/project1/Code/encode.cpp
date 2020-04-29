#include <iostream>
#include <vector>
#include <string>
//#include <algorithm>
using namespace std;

vector<string> strings;
void encode(vector<string> encodestring, string cho);
void merge(vector<string> &array, vector<string> &L, vector<string> &R);
void mergeSort(vector<string> &array);

int main(int argc, char* argv[])
{
	// rad key word merge of insertion
	string sort = argv[1];

	// read every line from the file and put it into a vector<string>  and encode it
	for (string line; getline(cin, line); ) {
		if (line.empty()) {
			cout << "0" << endl << endl;
		}
		else {
			strings.push_back(line);
			encode(strings, sort);
			strings.pop_back();
			
		}
	}
	
}
//

void encode(vector<string> encodestring, string sort) {
	// encoding start
	// 1: doing left cirual shift 

	// declare a vector<vector<string>> to store shift string 
	vector <vector<string> > shiftstring;
	string current;
	// start shif string
	for (int i = 0; i < encodestring.size(); i++)
	{
		current = encodestring[i];
		vector <string> temp;
		temp.push_back(current);
		for (int j = 1; j < encodestring[i].size(); j++) {
			string x = current.substr(j, encodestring[i].size() - 1) + current.substr(0, j);
			temp.push_back(x);
		}
		shiftstring.push_back(temp);
	}


	// 2: sort the sorting with sorting pointer
	vector< vector< string* > > ptr;
	for (int i = 0; i < shiftstring.size(); i++)
	{
		ptr.push_back({});
		for(int j =0; j < shiftstring[i].size();j++)
		{
			ptr.back().push_back(&shiftstring[i][j]);
		}	
	}
	
	// insertion sor

	if (sort == "insertion") {
		for (int i = 0; i < ptr.size(); i++) 
		{
			for (int j = 1; j < ptr[i].size(); j++) 
			{
				string key = *ptr[i][j];
				int k = j - 1;
				while (k >= 0 && *ptr[i][k] > key) {
					ptr[i][k + 1] = ptr[i][k];
					k = k - 1;
				}
				ptr[i][k + 1] = &shiftstring[i][j];
			}
		}
	}else {
		for (int i = 0; i < shiftstring.size(); i++) {
			mergeSort(shiftstring[i]);
		}
	}


	// 3: encode the string
	// find the index oringal string in shift strings
	vector<int> index;
	for (int i = 0; i < ptr.size();i++) {
		for (int j = 0; j < ptr[i].size(); j++)
		{
			if (encodestring[i] == *ptr[i][j])
			{
				index.push_back(j);
			}
		}
	}

	//find the last chars
	vector<vector<int> > lastnum;
	vector<vector<char> > lastcha;

	for (int i = 0; i < ptr.size(); i++)
	{	
		int count = 1;
		int n = ptr[i].size();
		vector<int> x1;
		vector<char> x2;
		char lastchar = (*ptr[i][0])[n - 1];
		for (int j = 1; j < ptr[i].size(); j++)
		{
			char newlast = (*ptr[i][j])[n - 1];
			if (lastchar != newlast)
			{
				x1.push_back(count);
				x2.push_back(lastchar);
				lastchar = newlast;
				count = 1;
			}
			else {
				count++;
			}
		}
		x1.push_back(count);
		x2.push_back(lastchar);
		lastnum.push_back(x1);
		lastcha.push_back(x2);
	}

	//stdout the finish encode string
	for (int i = 0; i < lastcha.size(); i++) {
		cout << index[i] << endl;
		for (int j = 0; j < lastcha[i].size(); j++) {
			if (j == lastcha[i].size() - 1) {
				cout << lastnum[i][j] << " " << lastcha[i][j];
			}
			else {
				cout << lastnum[i][j] << " " << lastcha[i][j] << " ";
			}

		}
		cout << endl;
	}
}


void merge(vector<string> &array, vector<string> &L, vector<string> &R) {
	vector<string>::iterator a = array.begin();
	vector<string>::iterator l = L.begin();
	vector<string>::iterator r = R.begin();

	while (l != L.end() && r != R.end()) {
		if (*l <= *r) {
			*a = *l;
			l++;
		}
		else {
			*a = *r;
			r++;
		}
		a++;
	}
	while (l != L.end()) {
		*a = *l;
		a++;
		l++;
	}
	while (r != R.end()) {
		*a = *r;
		a++;
		r++;
	}
	return;
}

void mergeSort(vector<string> &array) {
	if (array.size() == 1) { 
		return;
	}
	else {
		 int len = array.size();
		 int lo = len / 2;
		

		vector<string> L(&array[0], &array[lo]);
		vector<string> R(&array[lo], &array[len]);

		mergeSort(L);
		mergeSort(R);
		merge(array, L, R);
	}
	return;
}
