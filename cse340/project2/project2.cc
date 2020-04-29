/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *               Rida Bazzi 2019
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lexer.h"
#include <set>
#include <algorithm>
using namespace std;

LexicalAnalyzer lexer;

vector<string> TNNT;
vector<string> universe;
vector<string> terminal;
vector<string> non_terminal;
bool have_esplison;

struct rule {
	string LHS;
	vector<string> RHS;
};
vector<rule*> rules;

struct int_rule {
	int LHS;
	vector<int> RHS;
};
vector<int_rule *> int_rules;
vector<int_rule*> usefull_rule;

struct sets {
	int lhs;
	set<int> first;
	set<int> follow;
};
vector<sets*> first_follow_set;


// read grammar
vector<string> symbol;
void Syntax_error() {
	cout << "SYNTAX ERROR !!!" << endl;
	exit(1);
}

vector<string> temp_idlist;
vector<string> parse_idList() {

	Token t = lexer.GetToken();
	if (t.token_type != ID)
		Syntax_error();

	temp_idlist.push_back(t.lexeme);
	TNNT.push_back(t.lexeme);

	t = lexer.GetToken();
	lexer.UngetToken(t);
	if (t.token_type == ID)
		parse_idList();

	return temp_idlist;
}

vector<string> parse_RHS() {

	vector<string> rhs;

	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	if (t.token_type == ID) {
		
		rhs = parse_idList();
		for (string t : temp_idlist)
			TNNT.push_back(t);
		temp_idlist.clear();
		return rhs;

	}
	else if (t.token_type == HASH) {
		have_esplison = true;
		rhs.push_back("#");
		return rhs;
	}
	else
		Syntax_error();
}

void parse_rule() {

	struct rule * temp_rule = new rule;

	Token t = lexer.GetToken();
	if (t.token_type != ID)
		Syntax_error();

	temp_rule->LHS = t.lexeme;
	TNNT.push_back(t.lexeme);


	t = lexer.GetToken();
	if (t.token_type != ARROW)
		Syntax_error();

	temp_rule->RHS = parse_RHS();

	t = lexer.GetToken();
	if (t.token_type != HASH)
		Syntax_error();

	rules.push_back(temp_rule);
}

void parse_ruleList() {
	Token t = lexer.GetToken();
	lexer.UngetToken(t);

	if (t.token_type == ID) {
		parse_rule();

		t = lexer.GetToken();
		lexer.UngetToken(t);

		if (t.token_type == ID)
			parse_ruleList();
	}
	else
		Syntax_error();
}

void ReadGrammar()
{
	parse_ruleList();
	Token t = lexer.GetToken();

	if (t.token_type != DOUBLEHASH)
		Syntax_error();

	t = lexer.GetToken();

	if (t.token_type != END_OF_FILE)
		Syntax_error();

}


void find_non_terminal() {
	vector<string> res;
	for (rule * r: rules) {
		res.push_back(r->LHS);
	}
	for (string t : TNNT) {
		if (find(res.begin(), res.end(), t) != res.end()) {
			if (find(non_terminal.begin(), non_terminal.end(), t) == non_terminal.end()) {
				non_terminal.push_back(t);
			}
		}
	}
}

void find_terminal() {
	for (string t : TNNT) {
		if (find(non_terminal.begin(), non_terminal.end(),t) == non_terminal.end()) {
			if (find(terminal.begin(), terminal.end(), t) == terminal.end()) {
				terminal.push_back(t);
			}
		}
	}
}

int index(string str) {
	for (int i = 0; i < universe.size(); i++) {
		if (universe[i] == str)
			return i;
	}
}
// Task 1
void printTerminalsAndNoneTerminals()
{
	for (string t : terminal) {
		cout << t << " ";
	}
	for (string t : non_terminal) {
		cout << t << " ";
	}
}

// Task 2
void RemoveUselessSymbols(bool print)
{
    // calculat generat set
	vector<bool> generate_set(universe.size(), false);

	for (string t : terminal)
		generate_set[index(t)] = true;
	if (have_esplison == true);
		generate_set[0] = true;

	bool change = true;
	while (change) {
		change = false;

		for (int_rule * r : int_rules) {
			if (generate_set[r->LHS] == false) {
				bool g = true;
				for (int t : r->RHS) {
					bool isgenerating = (generate_set[t] == true);
					g = g && isgenerating;
				}
				if (g) {
					generate_set[r->LHS] = true;
					change = true;
				}
			}
		}
	}

	//caculate generate rule
	vector<int_rule* > generate_rule;
	for (int_rule * r : int_rules) {
		if (generate_set[r->LHS] ==true) {
			bool g = true;
			for (int t : r->RHS) {
				bool isgenerating = (generate_set[t] == true);
				g = g && isgenerating;
			}
			if (g) {
				struct int_rule * temp_rule = new int_rule;
				temp_rule->LHS = r->LHS;
				temp_rule->RHS = r->RHS;
				generate_rule.push_back(temp_rule);
			}
		}			
	}

	
	//calculate reachable set
	vector<bool>reachable_set(generate_set.size(), false);
	reachable_set[index(non_terminal[0])] = true;
	
	change = true;
	while (change) {
		change = false;
		for (int_rule * r : generate_rule) {
			if (reachable_set[r->LHS] == true) {
				bool g = true;
				for (int t : r->RHS) {
					if (reachable_set[t] == false)
						g = false;
				}
				if (g==false) {
					for (int t : r->RHS) {
						reachable_set[t] = true;
					}
					change = true;
				}
			}
		}
	}

	// calculate userfull grammar
	
	for (int_rule * r : generate_rule) {
		if (reachable_set[r->LHS] == true) {
			bool g = true;
			for (int t : r->RHS) {
				bool isreachable = (reachable_set[t] == true);
				g = g && isreachable;
			}
			if (g) {
				struct int_rule * temp_rule = new int_rule;
				temp_rule->LHS = r->LHS;
				temp_rule->RHS = r->RHS;
				usefull_rule.push_back(temp_rule);
			}
		}
	}
	//print
	if (print == true) {
		for (int_rule * r : usefull_rule) {
			cout << universe[r->LHS] << " -> ";
			for (int t : r->RHS)
				cout << universe[t] << " ";
			cout << endl;
		}
	}
}

int non_terminal_index(string str) {
	for (int i = 0; i < non_terminal.size(); i++) {
		if (non_terminal[i] == str)
			return i;
	}
}
//set operation
bool add_first_set_without_elpison(int x, int y) {
	int size1 = first_follow_set[x]->first.size();
	for (int t : first_follow_set[y]->first) {
		if (universe[t] != "#")
			first_follow_set[x]->first.insert(t);
	}
	int size2 = first_follow_set[x]->first.size();
	return size1 != size2;
}

bool contain_epsilon(int x) {
	for (int i : first_follow_set[x]->first)
	{
		if (i == 0)
			return true;
	}
	return false;
}

bool add_epsilon(int x) {
	int size1 = first_follow_set[x]->first.size();
	first_follow_set[x]->first.insert(0);
	int size2 = first_follow_set[x]->first.size();
	return size1 != size2;
}

// Task 3
void CalculateFirstSets(bool print)
{
	terminal.push_back("#");
	
	bool change = true;
	int i = 100;
	while (i-- > 0) {
		change = false;
		for (int_rule * r : int_rules) {

			for (int i = 0; i < r->RHS.size(); i++) {
				int t = r->RHS[i];
				if ((find(terminal.begin(), terminal.end(), universe[t]) != terminal.end()))
				{
				// add a to first(X)
				int index = non_terminal_index(universe[r->LHS]);
				// see if make change or not 
				int prelength = first_follow_set[index]->first.size();
				first_follow_set[index]->first.insert(t);
				int curlength = first_follow_set[index]->first.size();
				if (prelength != curlength)
					change = true;
				break;
				}
				// it is a non terminal
				else {
					int index1 = non_terminal_index(universe[r->LHS]);
					int index2 = non_terminal_index(universe[t]);
					change = add_first_set_without_elpison(index1, index2);

					if (contain_epsilon(index2) == true && i == r->RHS.size() - 1) {
						change = add_epsilon(index1);
						
					}
					else if (contain_epsilon(index2) == true)
						continue;
					else
						break;
				}

			}
		}

	}
	if (print == true) {


		for (sets * s : first_follow_set) {
			cout << "FIRST(" << universe[s->lhs] << ") = { ";
			set<int>::iterator it = s->first.begin();
			for (int i = 0; i < s->first.size();i++) {

				if (i == s->first.size() - 1)
				{
					cout << universe[*it] << " ";
				}

				else
					cout << universe[*it] << ", ";
				it++;
			}
			cout << "} " << endl;
		}
	}
	terminal.pop_back();
}


void add_first_to_follow(int x, int y) {
	
	for (int i : first_follow_set[y]->first) {
		if (i != 0)
			first_follow_set[x]->follow.insert(i);
	}
}

bool add_follow(int x, int y) {

	int size1 = first_follow_set[y]->follow.size();

	for (int i : first_follow_set[x]->follow) {
		if (i != 0)
			first_follow_set[y]->follow.insert(i);
	}

	int size2 = first_follow_set[y]->follow.size();
	return size1 != size2;
}

// Task 4
void CalculateFollowSets(bool print)
{
	CalculateFirstSets(false);
	terminal.push_back("$");
	terminal.push_back("#");
	first_follow_set[0]->follow.insert(1);


	// one pass for rule 4 5

	for (int_rule * r : int_rules) {
		for (int i = 0; i < r->RHS.size(); i++) {

			if (find(terminal.begin(), terminal.end(), universe[r->RHS[i]]) == terminal.end())
			{
				for (int j = i + 1; j < r->RHS.size(); j++)
				{
					if (find(terminal.begin(), terminal.end(), universe[r->RHS[j]]) == terminal.end())
					{
						int index1 = non_terminal_index(universe[r->RHS[i]]);
						int index2 = non_terminal_index(universe[r->RHS[j]]);
						add_first_to_follow(index1, index2);
						if (contain_epsilon(index2) == true)
							continue;
						else
							break;
					}
					else {
						int index1 = non_terminal_index(universe[r->RHS[i]]);
						first_follow_set[index1]->follow.insert(r->RHS[j]);
						break;
					}


				}
			}
		}
	}

	// rule 2 3
	bool change = true;
	int i = 10;
	while (i-- >0) {
		change = false;
		for (int_rule * r : int_rules) {

			for (int i = r->RHS.size() - 1; i >= 0; i--) {
				if (find(terminal.begin(), terminal.end(), universe[r->RHS[i]]) == terminal.end())
				{
					int index1 = non_terminal_index(universe[r->LHS]);
					int index2 = non_terminal_index(universe[r->RHS[i]]);
					change = add_follow(index1, index2);
				}
				if (contain_epsilon(non_terminal_index(universe[r->RHS[i]])) == false ||
					find(terminal.begin(), terminal.end(), universe[r->RHS[i]]) != terminal.end())
					break;

			}
		}
	}

	if (print == true) {
		for (sets * s : first_follow_set) {
			cout << "FOLLOW(" << universe[s->lhs] << ") = { ";
			set<int>::iterator it = s->follow.begin();
			for (int i = 0; i < s->follow.size();i++) {

				if (i == s->follow.size() - 1)
				{
					cout << universe[*it] << " ";
				}
				else
					cout << universe[*it] << ", ";
				it++;
			}
			cout << "} " << endl;
		}
	}
	terminal.pop_back();
	terminal.pop_back();
}

// Task 5
void CheckIfGrammarHasPredictiveParser()
{	//check useless
	RemoveUselessSymbols(false);
	if (usefull_rule.size() != rules.size())
	{
		cout << "NO";
		exit(1);
	}

	CalculateFirstSets(false);
	CalculateFollowSets(false);
	//check condition 1

	//check condition 2
	for (sets * s : first_follow_set) {
		for (int i : s->first) {
			if (s->follow.find(i) != s->follow.end())
			{
				cout << "NO";
				exit(1);
			}
		}
	}
	cout << "YES";

}
    
int main (int argc, char* argv[])
{
    int task;

    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
	universe.push_back("#");
	universe.push_back("$");
	

    
    ReadGrammar();  // Reads the input grammar from standard input
                    // and represent it internally in data structures
                    // ad described in project 2 presentation file

	find_non_terminal();
	find_terminal();
	for (string t : terminal) {
		universe.push_back(t);
	}
	for (string t : non_terminal) {
		universe.push_back(t);
	}

	//grammar mapping
	for (rule * r : rules) {
		struct int_rule * ir = new int_rule;
		ir->LHS = index(r->LHS);

		for (string t : r->RHS) {
			ir->RHS.push_back(index(t));
		}
		int_rules.push_back(ir);
	}
	// init first_and_follow set lhs
	for (string t : non_terminal) {
		struct sets * s = new sets;
		s->lhs = index(t);
		first_follow_set.push_back(s);
	}


    switch (task) {
        case 1: printTerminalsAndNoneTerminals();
            break;

        case 2: RemoveUselessSymbols(true);
            break;

        case 3: CalculateFirstSets(true);
            break;

        case 4: CalculateFollowSets(true);
            break;

        case 5: CheckIfGrammarHasPredictiveParser();
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}

