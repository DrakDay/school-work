#include <iostream>
#include <string>
#include <vector>

using namespace std;
void decode(vector<int> index, vector<string> decodestring,string sort);
void merge(vector<string> &array, vector<string> &L, vector<string> &R);
void mergeSort(vector<string> &array);

int strtoint(string str){
	int a = 0;
	for (int i = 0; i < str.length();i++){
		a = (int)(str[i] - 48) + a * 10;
	}
	return a;
}

int main(int argc, char* argv[]) {
	vector<int> index;
	vector<string> decodestring;
	// read key word merge or insertion
	string sort = argv[1];

	// read everline and decode the line
	int i = 0;
	for(string s; getline(cin,s);)
	{
		if (i % 2 == 0) {
			int x = strtoint(s);
			index.push_back(x);
		}
		else if (s.empty()) {
			cout << endl;
		}
		else {
			string word = "";
			int j = 0;
			while(j < s.size()){
				if (s[j] == ' ') 
				{
					if((s[j] == ' ') && (s[j + 1] == ' ') ) {
						decodestring.push_back(word);
						word = ' ';
						decodestring.push_back(word);
						word = "";
						j = j + 2;
					}
					else {
						decodestring.push_back(word);
						word = "";
					}
				}
				else {
					word = word + s[j];
				}
				j++;
			}
			if (word == "") {

			}
			else {
				decodestring.push_back(word);
			}
		}
		i++;

		if (s.empty()) {
			index.clear();
			decodestring.clear();
		}
		else if (i % 2 == 0 && i >= 1) {
			decode(index, decodestring,sort);
			index.clear();
			decodestring.clear();
		}
		
	}

}

void decode(vector<int> index, vector<string> decodestring , string sort) {
	vector<string> lastchar;
	vector<string> lastcopy;

	// split cluster string
	for (int i = 0; i < decodestring.size();i++) {
		if (i % 2 == 0) {
			int x = strtoint(decodestring[i]);
			
			while (x > 1) {
				lastchar.push_back(decodestring[i + 1]);
				x--;
			}		
		}
		else {
			lastchar.push_back(decodestring[i]);
		}
	}

	//make a copy of last char and use it later to find the next
	lastcopy = lastchar;

	//sort
	if (sort == "insertion") {
		for (int i = 1;i < lastcopy.size();i++) {
			string key = lastcopy[i];
			int j = i - 1;
			while (j >= 0 && lastcopy[j] > key) {
				lastcopy[j + 1] = lastcopy[j];
				j--;
			}
			lastcopy[j + 1] = key;
		}
	}
	else {
		mergeSort(lastcopy);
	}


	//finding next
	vector<int> next;
	for (int i = 0; i < lastcopy.size();i++) {
		for (int j = 0;j < lastchar.size(); j++) {
			
			//if (lastcopy[i] == lastchar[j] && count(next.begin(),next.end(),j) == 0) {
			//	next.push_back(j);
			//}
			if(lastcopy[i] == lastchar[j]) {
				int count = 0;
				for(int x = 0; x < next.size();x++){
					if ( next[x]  == j ){
						count ++;
					}
				}
				if(count == 0) { next.push_back(j);}
				else {}
					
			}
		}
	}
	
	// decode1
	int y = index[0];
	int x = next[y];
	for (int i = 0;i < lastchar.size();i++) {
		cout << lastchar[x];
		x = next[x];
	}
	cout << endl;

	
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
