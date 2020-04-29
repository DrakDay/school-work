#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <sstream>
#include "defn.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "BST.h"

using namespace std;

struct annual_storms annualstorm[69]; // 2019-1950

void findevent(int id, int index);
void findmax(int number, string years, string str);
void findmaxfatality(int number, string year);
void range(string year, string filed_name, string low, string high);

int strtoint(string str) {

	bool decimal = false; // see if there is any decimal in the string
	int sum = 0;
	int count = 0; // count how many digit after the decimal
	for (int i = 0;i < str.length();i++) {
		if (str[i] == ' ') {

		}
		if (str[i] == 'K') {
			sum = sum * 1000;
		}
		else if (str[i] == 'M') {
			sum = sum * 1000000;
		}
		else if (str[i] == '.') {
			decimal = true;
		}
		else {
			sum = sum * 10 + int(str[i] - 48);
			if (decimal == true) {
				count++;
			}
		}
	}
	// figuer out sign. if ther is 2 digit after decimal then it sign should be 10 power 2 
	int sign = 1;
	for (int j = 0; j < count; j++) {
		sign = sign * 10;
	}
	return sum / sign;
}

bool isprime(int n) {
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

int main(int argc, char* argv[]) {

	annualstorm->length =atoi(argv[1]);

	int sum = 0;
	
	// read detalis file from 1950 - 1952
	for (int i = 0; i < annualstorm->length; i++) {

		int size = -1;
		int count = 0;

		ifstream myfile;

		int y = atoi(argv[2 + i]);
		annualstorm[i].year = y;
		string z = "details-" + to_string(y) + ".csv";

		// getting the total lines of the file
		myfile.open(z);
		while (myfile.good()) {
			string line;
			getline(myfile, line, '\n');
			size++;
		}
		myfile.close();

		struct storm_event * stormevent = new struct storm_event[size];

		//reading csv file
		myfile.open(z);

		// skip first line
		string firstline;
		getline(myfile, firstline, '\n');

		while (myfile.good()) {
			string line;

			// read event id
			getline(myfile, line, ',');
			if (strtoint(line) == 0) { continue; }
			stormevent[count].event_id = strtoint(line);

			// read state name
			getline(myfile, line, ',');
			strcpy(stormevent[count].state, line.c_str());

			// read year
			getline(myfile, line, ',');
			stormevent[count].year = strtoint(line);

			// read month_name
			getline(myfile, line, ',');
			strcpy(stormevent[count].month_name, line.c_str());

			// read event_type
			getline(myfile, line, ',');
			strcpy(stormevent[count].event_type, line.c_str());

			//read cz type
			getline(myfile, line, ',');
			stormevent[count].cz_type = line[0];

			//read cz_name
			getline(myfile, line, ',');
			strcpy(stormevent[count].cz_name, line.c_str());

			// read injuires_direct
			getline(myfile, line, ',');
			stormevent[count].injuries_direct = strtoint(line);

			// read injuries_indirect
			getline(myfile, line, ',');
			stormevent[count].injuries_indirect = strtoint(line);

			// read deaths_direct
			getline(myfile, line, ',');
			stormevent[count].deaths_direct = strtoint(line);

			// read deaths_indirect
			getline(myfile, line, ',');
			stormevent[count].deaths_indirect = strtoint(line);

			// read damage_property
			getline(myfile, line, ',');
			stormevent[count].damage_property = strtoint(line);

			//read damage crops
			getline(myfile, line, ',');
			stormevent[count].damage_crops = strtoint(line);

			// tor f scale
			getline(myfile, line, '\n');
			strcpy(stormevent[count].tor_f_scale, line.c_str());

			stormevent[count].numoffatality = 0;

			count++;
		}
		
		myfile.close();

		sum = sum + count;
		annualstorm[i].events = stormevent;
		annualstorm[i].events->length = count;
	}

	
	//find prime
	int prime = 0;
	for (int i = 2 * sum; i > 0; i++) {
		if (isprime(i) == true)
		{
			prime = i;
			break;
		}
	}

	HashTable h(prime);

	//inserting data into hashtable

	for (int i = 0; i < annualstorm->length; i++) {
		for (int j = 0;j < annualstorm[i].events->length;j++) {
			annualstorm[i].events[j].f = NULL;
			h.insert(annualstorm[i].events[j].event_id, annualstorm[i].events[j].year, j);
		}
	}


	//reading fatalities file
	for (int i = 0; i < annualstorm->length; i++) {
		int count = 0;
		int y = atoi(argv[2 + i]);
		string z = "fatalities-" + to_string(y) + ".csv";

		//reading second csv file
		ifstream myfile2;
		myfile2.open(z);

		//skip first line
		string firstline;
		getline(myfile2, firstline, '\n');
	
		while (myfile2.good()) {
			
			fatality_event * newnode = new fatality_event();
			string line;

			//fatality id
			getline(myfile2, line, ',');
			newnode->fatality_id = strtoint(line);

			//event id
			getline(myfile2, line, ',');
			newnode->event_id = strtoint(line);

			//fatality type
			getline(myfile2, line, ',');
			newnode->fatality_type = line[0];

			//fatality date
			getline(myfile2, line, ',');
			strcpy(newnode->fatality_date, line.c_str());

			//datatlity age
			getline(myfile2, line, ',');
			newnode->fatality_age = strtoint(line);

			//fatality sex
			getline(myfile2, line, ',');
			newnode->fatality_sex = line[0];

			//fatality location
			getline(myfile2, line, '\n');
			strcpy(newnode->fatality_location, line.c_str());


			int index = h.index(newnode->event_id);

			for (int i = 0;i < annualstorm->length; i++) {
				if(index == -1){}
				else if (index < annualstorm[i].events->length) {

					if (newnode->event_id == annualstorm[i].events[index].event_id) {

						fatality_event * head = annualstorm[i].events[index].f;
						fatality_event * temp = head;

						if (index != -1) {
							if (head == NULL)
							{
								head = newnode;
							}
							else {
								temp = newnode;
								temp->next = head;
								head = temp;
							}
						}
						annualstorm[i].events[index].f = head;
						annualstorm[i].events[index].numoffatality++;
						count++;
					}
				}
			}
		}

		myfile2.close();
		annualstorm[i].fatalitylength = count;
	}


	int number = 0;
	cin >> number;
	while (number > 0) {
		string  x;
		getline(cin, x);
		if (x.find("find event") != string::npos) {
			int id = strtoint(x.substr(11, 30));
			int index = h.index(id);
			findevent(id, index);
			number--;
		}
		else if (x.find("find max fatality") != string::npos) {
			if (x.find("all") != string::npos) {
				int number = stoi(x.substr(17, 19));
				string year = "all";
				findmaxfatality(number, year);

			}
			else {
				int number = stoi(x.substr(17, 19));
				string year = x.substr(20, 30);
				findmaxfatality(number, year);
			}
			number--;
		}
		else if (x.find("find max") != string::npos) {
			if (x.find("all") != string::npos) {
				int number = stoi(x.substr(8, 10));
				string year = "all";
				string type = x.substr(15, 20);
				findmax(number, year, type);
			}
			else {
				int number = stoi(x.substr(8, 10));
				int year = stoi(x.substr(11,15));
				string type = x.substr(16, 30);
				findmax(number, to_string(year), type);
			}
			number--;
		}
		else if (x.find("range") != string::npos) {
			string line = x.substr(6, 100);
			string year; string filed_name; string low; string high;
			int count = 0;
			istringstream ss(line);
			do {
				if (count == 0) { ss >> year; }
				else if (count == 1) { ss >> filed_name; }
				else if (count == 2) { ss >> low; }
				else if (count == 3) { ss >> high; }
				else if (count == 4) { break; }
				count++;
			} while (ss);
			range(year, filed_name, low, high);
			number--;
		}
		
	}
	cout << endl;
	cout << "characteristics of hash table" << endl;
	h.displayHash();
	system("Pause");
}


void findevent(int id, int index)
{
	cout << endl;
	if (index == -1) {
		cout << "storm event " << id << " not found " << endl;
	}
	else {
		for (int i = 0; i < annualstorm->length;i++) {
			if (index < annualstorm[i].events->length) {
				if (annualstorm[i].events[index].event_id == id) {
					cout << "event id: " << annualstorm[i].events[index].event_id << endl
						<< "state: " << annualstorm[i].events[index].state << endl
						<< "year: " << annualstorm[i].events[index].year << endl
						<< "month : " << annualstorm[i].events[index].month_name << endl
						<< "event type: " << annualstorm[i].events[index].event_type << endl
						<< "cz type: " << annualstorm[i].events[index].cz_type << endl
						<< "cz name: " << annualstorm[i].events[index].cz_name << endl
						<< "injuries direct: " << annualstorm[i].events[index].injuries_direct << endl
						<< "injuries indirect: " << annualstorm[i].events[index].injuries_indirect << endl
						<< "death direct: " << annualstorm[i].events[index].deaths_direct << endl
						<< "death indirect: " << annualstorm[i].events[index].deaths_indirect << endl
						<< "damage property: " << annualstorm[i].events[index].damage_property << endl
						<< "damage crops: " << annualstorm[i].events[index].damage_crops << endl
						<< "tor f scale: " << annualstorm[i].events[index].tor_f_scale << endl
						<< endl;

					if (annualstorm[i].events[index].f != NULL) {
						fatality_event * n = annualstorm[i].events[index].f;
						while (n != NULL) {
							cout << "fataility id: " << n->fatality_id << endl
								<< "event id : " << n->event_id << endl
								<< "fataility type: " << n->fatality_type << endl
								<< "fataility date: " << n->fatality_date << endl
								<< "fataility age: " << n->fatality_age << endl
								<< "fataility sex: " << n->fatality_sex << endl
								<< "fataility location: " << n->fatality_location << endl
								<< endl;

							n = n->next;
						}
					}
					else {
						cout << "no fatality event find" << endl << endl;
					}
				}
			}
		}
		
	}

}

void findmax(int number, string years, string str) {
	if (years == "all") {

		//find out total number of event in all year;
		int sum = 0;
		for (int i = 0; i < annualstorm->length;i++) {
			sum = sum + annualstorm[i].events->length;
		}

		// make a copy
		int count = 0;
		storm_event * events = new storm_event[sum];

		for (int i = 0;i < annualstorm->length;i++) {
			for (int j = 0; j < annualstorm[i].events->length;j++) {

				events[count] = annualstorm[i].events[j];
				count++;
			}
		}

		MaxHeap heap;

		if (str == "damage_property" || str == " damage_property" ) {

			heap.buildMaxHeap(events, sum, "damage_property");

			for (int i = 0; i < number; i++) {
				cout << endl << "event id: " << events[sum -i -1].event_id << "		"
					<< "event type: " << events[sum - i -1].event_type << "		"	
					<< "damage property: $" << events[sum -i - 1].damage_property  << endl;
			}
		}
		else {
			heap.buildMaxHeap(events, sum, "damage_crops");

			for (int i = 0; i < number; i++) {
				cout << endl << "event id: " << events[sum - i - 1].event_id << "	"
					<< "event type: " << events[sum - i - 1].event_type << "	"
					<< "damage crops: $" << events[sum - i - 1].damage_crops << endl;
			}

		}
		cout << endl;
		cout << "the total numbers of node in max heap is : " << sum << endl;
		cout << "the height of the max heap is : " << floor(log2(sum)) << endl;
		delete[] events;
	}
	else {
		int year = stoi(years);

		for (int i = 0; i < annualstorm->length; i++) {
			int index = i;
			if (year == annualstorm[i].year) {

				storm_event * events = new storm_event[annualstorm[i].events->length];

				for (int j = 0; j < annualstorm[i].events->length; j++) {
					events[j] = annualstorm[i].events[j];
				}

				MaxHeap heap;

				if (str == "damage_property" || str == " damage_property") {

					heap.buildMaxHeap(events, annualstorm[index].events->length, "damage_property");

					for (int i = 0; i < number; i++) {

						cout << endl << "event id: "<<events[annualstorm[index].events->length-i-1].event_id << "		"
							<< "event type: "	<<events[annualstorm[index].events->length - i - 1].event_type << "		"
							<< "damage property: $" <<events[annualstorm[index].events->length - i - 1].damage_property << endl;
					}
				}
				else {
					heap.buildMaxHeap(events, annualstorm[i].events->length, "damage_crops");

					for (int i = 0; i < number; i++) {
						cout << endl << "event id: " << events[annualstorm[index].events->length - i - 1].event_id << "	"
							<< "event type: "	<< events[annualstorm[index].events->length - i - 1].event_type << "	"
							<< "damage crops: $" << events[annualstorm[index].events->length - i - 1].damage_crops  << endl;
					}

				}
				cout<<endl;
				cout << "the total numbers of node in max heap is : " << annualstorm[i].events->length << endl;
				cout << "the height of the max heap is : " << floor(log2(annualstorm[i].events->length)) << endl;
				delete[] events;
			}
		}
		
	}
}

void findmaxfatality(int number, string year) {
	if (year == "all") {
		int sum = 0;
		for (int i = 0; i < annualstorm->length; i++) {
			sum = sum + annualstorm[i].fatalitylength;
		}
		int count = 0;
		storm_event * events = new storm_event[sum];
		
		for (int i = 0; i < annualstorm->length; i++) {
			for (int j = 0; j < annualstorm[i].events->length; j++) {
				if (annualstorm[i].events[j].numoffatality != 0) {
					events[count] = annualstorm[i].events[j];
					count++;
				}
			}
		}

		MaxHeap heap;
		heap.buildMaxHeap_fatality(events, sum);

		for (int i = 0; i < number; i++) {
			fatality_event * n = events[sum - i - 1].f;
			cout << endl;
			cout << "event id:  " << events[sum - i - 1].event_id << "  have  " << events[sum - i - 1].numoffatality << "  fataility event " << endl;
			while (n != NULL) {
				cout << endl
					<< "fatality id:" << n->fatality_id << endl
					<< "fatality type:" << n->fatality_type << endl
					<< "fatality date:" << n->fatality_date << endl
					<< "fatality age:" << n->fatality_age << endl
					<< "fatality sex:" << n->fatality_sex << endl
					<< "fatality location:" << n->fatality_location << endl << endl;
				n = n->next;
			}
		}

		cout << "the total numbers of node in max heap is : " << sum << endl;
		cout << "the height of the max heap is : " << floor(log2(sum)) << endl;

	}
	else {
		int years = stoi(year);
		for (int i = 0; i < annualstorm->length; i++) {
			int index = i;
			if (years == annualstorm[i].year) {

				int sum = annualstorm[i].fatalitylength;

				storm_event * events = new storm_event[sum];

				int count = 0;
				for (int i = 0; i < annualstorm[index].events->length; i++) {
					if (annualstorm[index].events[i].numoffatality != 0) {
						events[count] = annualstorm[index].events[i];
						count++;
					}
				}

				MaxHeap heap;
				heap.buildMaxHeap_fatality(events, sum);

				for (int i = 0; i < number; i++) {
					fatality_event * n = events[sum - i - 1].f;
					cout << endl;
					cout << "event id:  " << events[sum - i - 1].event_id << "  have " << events[sum - i - 1].numoffatality << "  fataility event " << endl;
					while (n != NULL) {
						cout << endl
							<< "fatality id:" << n->fatality_id << endl
							<< "fatality type:" << n->fatality_type << endl
							<< "fatality date:" << n->fatality_date << endl
							<< "fatality age:" << n->fatality_age << endl
							<< "fatality sex:" << n->fatality_sex << endl
							<< "fatality location:" << n->fatality_location << endl << endl;
						n = n->next;
					}
				}
				cout << "the total numbers of node in max heap is : " << sum << endl;
				cout << "the height of the max heap is : " << floor(log2(sum)) << endl;
			}
		}
	}
}

void range(string year, string filed_name, string low, string high) {
	BST tree;
	if (year == "all") {
		if (filed_name == "month_name") {
			for (int i = 0; i < annualstorm->length; i++) {
				for (int j = 0; j < annualstorm[i].events->length; j++) {
					tree.insert(annualstorm[i].events[j].month_name,
						annualstorm[i].events[j].event_id,
						annualstorm[i].events[j].year,
						annualstorm[i].events[j].event_type,
						annualstorm[i].events[j].cz_type,
						annualstorm[i].events[j].cz_name);
				}
			}
			tree.inorder(low, high,filed_name);
			cout << "the number of node in BST is : " << tree.countnode() << endl;
			cout << "the height of the tree is : " << tree.getheight() << endl;
			cout << "the height of the left sub tree is : " << tree.lefttreeheight() << endl;
			cout << "the height of the right sub tree is : " << tree.righttreeheight() << endl;
			cout << endl;
		}
		else {
			for (int i = 0; i < annualstorm->length; i++) {
				for (int j = 0; j < annualstorm[i].events->length; j++) {
					tree.insert(annualstorm[i].events[j].state,
						annualstorm[i].events[j].event_id,
						annualstorm[i].events[j].year, 
						annualstorm[i].events[j].event_type,
						annualstorm[i].events[j].cz_type,
						annualstorm[i].events[j].cz_name);
				}
			}
			tree.inorder(low, high,filed_name);
			
			cout << "the number of node in BST is : " << tree.countnode() << endl;
			cout << "the height of the tree is : " << tree.getheight() << endl;
			cout << "the height of the left sub tree is : " << tree.lefttreeheight() << endl;
			cout << "the height of the right sub tree is : " << tree.righttreeheight() << endl;
			cout << endl;
		}
	
	}
	else {
		int years = strtoint(year);
		for (int i = 0; i < annualstorm->length; i++) {
			int index = i;
			if (years == annualstorm[i].year) {
				if (filed_name == "month_name")
				{
					for (int i = 0; i < annualstorm[index].events->length; i++) {
						tree.insert(annualstorm[index].events[i].month_name,
							annualstorm[index].events[i].event_id,
							annualstorm[index].events[i].year,
							annualstorm[index].events[i].event_type,
							annualstorm[index].events[i].cz_type,
							annualstorm[index].events[i].cz_name);
					}
					tree.inorder(low, high,filed_name);
					cout << "the number of node in BST is : " << tree.countnode() << endl;
					cout << "the height of the tree is : " << tree.getheight() << endl;
					cout << "the height of the left sub tree is : " << tree.lefttreeheight() << endl;
					cout << "the height of the right sub tree is : " << tree.righttreeheight() << endl;
					cout << endl;
				}
				else {
					for (int i = 0; i < annualstorm[index].events->length; i++) {
						tree.insert(annualstorm[index].events[i].state,
							annualstorm[index].events[i].event_id,
							annualstorm[index].events[i].year,
							annualstorm[index].events[i].event_type,
							annualstorm[index].events[i].cz_type,
							annualstorm[index].events[i].cz_name);
					}
					tree.inorder(low, high,filed_name);
					cout << "the number of node in BST is : " << tree.countnode() << endl;
					cout << "the height of the tree is : " << tree.getheight() << endl;
					cout << "the height of the left sub tree is : " << tree.lefttreeheight() << endl;
					cout << "the height of the right sub tree is : " << tree.righttreeheight() << endl;
					cout << endl;
				}
			}
		}
	}

}
