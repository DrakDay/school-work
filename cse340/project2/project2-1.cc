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
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
LexicalAnalyzer lexer;

set<string> universe;
vector<string> task1;

struct rule {
	string LHS;
	vector<string> RHS;
};
vector<rule * > rules;

struct sets {
	string name;
	vector<string> frist;
	vector<string> follow;
};
vector<sets *> first_follow_set;

void Syntax_error() {
	cout << "SYNTAX ERROR !!!" << endl;
	exit(1);
}

vector<string> symbol;
vector<string> parse_id_list() {
	
	Token t = lexer.GetToken();
	if (t.token_type != ID)
		Syntax_error();

	symbol.push_back(t.lexeme);
	universe.insert(t.lexeme);

	t = lexer.GetToken();
	lexer.UngetToken(t);
	if (t.token_type == ID)
		parse_id_list();

	return symbol;
}

vector<string> parse_RHS() 
{
	vector<string> RHS;
	Token t = lexer.GetToken();
	lexer.UngetToken(t);

	if (t.token_type == ID) {
		RHS = parse_id_list();
		for (int i = 0; i<symbol.size(); i++) {
			task1.push_back(symbol[i]);
		}
		symbol.clear();
		return RHS;
	}

	else if (t.token_type == HASH)
	{
		universe.insert("#");
		RHS.push_back("#");
		return RHS;
	}
	else
		Syntax_error();
}

void parse_rule(){

	struct rule * temp_rule = new rule;

	Token t = lexer.GetToken();
	if (t.token_type != ID)
		Syntax_error();

	temp_rule->LHS = t.lexeme;
	
	universe.insert(t.lexeme);

	t = lexer.GetToken();
	if (t.token_type != ARROW)
		Syntax_error();

	universe.insert(t.lexeme);

	temp_rule->RHS = parse_RHS();

	t = lexer.GetToken();
	if (t.token_type != HASH)
		Syntax_error();

	rules.push_back(temp_rule);
}

void parse_ruleList() {
	// rulelist -> rule rulelist | rule

	Token t = lexer.GetToken();
	lexer.UngetToken(t);

	if (t.token_type == ID) {
		task1.push_back(t.lexeme);
		parse_rule();

		t = lexer.GetToken();
		lexer.UngetToken(t);
		if (t.token_type == ID)
			parse_ruleList();
	}else
		Syntax_error();
}

// read grammar
void ReadGrammar()
{
	parse_ruleList();
	Token t = lexer.GetToken();

	if (t.token_type != DOUBLEHASH)
		Syntax_error();

	t = lexer.GetToken();

	if (t.token_type != END_OF_FILE)
		Syntax_error();
	universe.insert("$");
}

vector<string> findterminal() {
	vector<string>Terminal;;
	vector<string>NT;
	for (int i = 0; i < rules.size(); i++) {
		NT.push_back(rules[i]->LHS);
	}

	for (int i = 0; i < task1.size();i++) {
		if (find(NT.begin(), NT.end(), task1[i]) == NT.end()) {
			if (find(Terminal.begin(), Terminal.end(), task1[i]) == Terminal.end())
				Terminal.push_back(task1[i]);
		}
	}
	return Terminal;
}

// Task 1

vector<string> TNNT() {
	vector<string> result2;
	vector<string>NT;
	vector<string>Terminal = findterminal();

	for (int i = 0; i < rules.size(); i++) {
		NT.push_back(rules[i]->LHS);
	}

	for (int i = 0; i < task1.size();i++) {
		if (find(NT.begin(), NT.end(), task1[i]) != NT.end()) {
			if (find(result2.begin(), result2.end(), task1[i]) == result2.end())
				result2.push_back(task1[i]);
		}
	}
	vector<string> xx;
	for (string t : Terminal) {
		xx.push_back(t);
	}
	for (string t : result2) {
		xx.push_back(t);
	}
	return xx;
}
void printTerminalsAndNoneTerminals()
{
	vector<string> ans = TNNT();

	for (string t : ans) {
		cout << t << " ";
	}
}

// Task 2
void RemoveUselessSymbols()
{
	// GET generate set
	set<string> generate;
	vector<string> terminal = findterminal();

	for (string t : terminal) {
		generate.insert(t);
	}
	if(universe.find("#") != universe.end())
		generate.insert("#");

	bool change = true;
	while (change) {
		change = false;
		for (rule * r : rules) {
			string lhs = r->LHS;
			if (generate.find(lhs) == generate.end()) {
				bool g = true;
				for (int i = 0; i < r->RHS.size();i++) {
					string rhs = r->RHS[i];
					bool isgenerating = false;
					if (generate.find(rhs) != generate.end())
						isgenerating = true;
					g = g && isgenerating;
				}
				if (g) {
					generate.insert(lhs);
					change = true;
				}
			}
		}
	}

	// genrule
	vector<rule *> genrule;

	for (rule * r : rules) {
		string lhs = r->LHS;
		if (generate.find(lhs) != generate.end()) {
			bool g = true;
			for (int i = 0; i < r->RHS.size();i++) {
				string rhs = r->RHS[i];
				bool isreachble = false;
				if (generate.find(rhs) != generate.end())
					isreachble = true;
				g = g && isreachble;
			}
			if (g) {
				struct rule * temp_rule = new rule;
				temp_rule->LHS = r->LHS;
				temp_rule->RHS = r->RHS;
				genrule.push_back(temp_rule);

			}
		}
	}
	//cal reachableset
	set<string> reachable;
	reachable.insert(rules[0]->LHS);
	change = true;

	while(change)
	{
		change = false;
		for (rule * r : genrule) {
			string lhs = r->LHS;
			if (reachable.find(lhs) != reachable.end()) {
				bool g = true;
				for (int i = 0; i < r->RHS.size();i++) {
					string rhs = r->RHS[i];
					if (reachable.find(rhs) == reachable.end())
						g = false;
				}
				if (g == false) {
					for (int i = 0; i < r->RHS.size();i++) {
						reachable.insert(r->RHS[i]);
					}

					change = true;
				}
			}
		}
	}

	//cal usefull rule
	vector<rule *> usefullrule;
	for (rule * r : genrule) {
		string lhs = r->LHS;

		if (reachable.find(lhs) != reachable.end()) {
			bool g = true;
			for (int i = 0; i < r->RHS.size();i++) {
				string rhs = r->RHS[i];
				bool isreachble = false;
				if (reachable.find(rhs) != reachable.end())
					isreachble = true;
				g = g && isreachble;
			}
			if (g) {
				struct rule * temp_rule = new rule;
				temp_rule->LHS = r->LHS;
				temp_rule->RHS = r->RHS;
				usefullrule.push_back(temp_rule);

			}
		}
	}

	for (rule * r : usefullrule) {
		cout << r->LHS << " -> ";
		for (int j = 0; j < r->RHS.size();j++) {
			cout << r->RHS[j] << " ";
		}
		cout << endl;
	}
	for (rule * r : genrule)
		delete r;
}

//set opr
bool addwithoutepsilon(int x, int y) {
	vector<string>::iterator it;
	int presize = first_follow_set[x]->frist.size();

	for (string t : first_follow_set[y]->frist) {
		it = find(first_follow_set[x]->frist.begin(), first_follow_set[x]->frist.end(), t);
		if (it == first_follow_set[x]->frist.end() && t != "#")
			first_follow_set[x]->frist.push_back(t);
	}

	int cursize = first_follow_set[x] -> frist.size();
	return  presize != cursize;
}

void addepsilon(int x) {
	vector<string>::iterator it;
	it = it = find(first_follow_set[x]->frist.begin(), first_follow_set[x]->frist.end(), "#");
	if ( it == first_follow_set[x]->frist.end())
		first_follow_set[x]->frist.push_back("#");
}

bool containeplislon(vector<string> x) {
	for (string t : x) {
		if (t == "#")
			return true;
	}
	return false;
}

// Task 3
int firstandfollowindex(string str) {
	for (int i = 0; i < first_follow_set.size(); i++) {
		if (first_follow_set[i]->name == str)
			return i;
	}
}
void CalculateFirstSets()
{
	// rule 1,2
	
		
	vector<string> termianl = findterminal();
	if (universe.find("#") != universe.end())
		termianl.insert(termianl.begin(), "#");
	vector<string> TandNT = TNNT();
	vector<string>::iterator it;
	vector<string>NT;
	for (int i = 0; i < rules.size(); i++) {
		it = find(NT.begin(), NT.end(), rules[i]->LHS);
		if (it == NT.end())
			NT.push_back(rules[i]->LHS);
	}
	
	for (int i = 0; i < NT.size(); i++) {
		struct sets * s = new sets;
		s->name = NT[i];
		first_follow_set.push_back(s);
	}
	
	// rule 3 4 5
	bool change = true;
	int count = 0;
	while (change) {
		change = false;
		for (rule * r : rules) {
			string lhs = r->LHS;
			for (int i = 0; i < r->RHS.size(); i++) 
			{
				string rhs = r->RHS[i];
				it = find(termianl.begin(), termianl.end(), rhs);
				// terminal
				if (it != termianl.end()) {
					int index = firstandfollowindex(lhs);
					it = find(first_follow_set[index]->frist.begin(), first_follow_set[index]->frist.end(), rhs);
					if (it == first_follow_set[index]->frist.end())
					{
						first_follow_set[index]->frist.push_back(rhs);
						change = true;
						
					}
					break;
				}
				//non terminal
				else {
					// add first of rhs to first of lhs
					int lindex = firstandfollowindex(lhs);
					int rindex = firstandfollowindex(rhs);
					bool g = addwithoutepsilon(lindex, rindex);
					if (g == true)
						change = true;

					// if rhs is empty
					if (containeplislon(first_follow_set[rindex]->frist) && i == r->RHS.size() - 1) {
						addepsilon(lindex);
						change = true;
					}
					else if (containeplislon(first_follow_set[rindex]->frist))
						continue;
					else
						break;
				}
			}

		}

	}
	for (int i = 0; i < first_follow_set.size();i++) {
		cout << "FIRST("<< first_follow_set[i]->name << ") = { ";
		for (int j = 0; j < first_follow_set[i]->frist.size();j++) {
			
			if (j == first_follow_set[i]->frist.size() - 1)
				cout << first_follow_set[i]->frist[j] <<" ";
			else
				cout << first_follow_set[i]->frist[j] << ", ";
		}
		cout << "}" << endl;
	}
  //  cout << "3\n";
}

// Task 4
void CalculateFollowSets()
{
   // cout << "4\n";
}

// Task 5
void CheckIfGrammarHasPredictiveParser()
{
   // cout << "5\n";
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

    
    ReadGrammar();  // Reads the input grammar from standard input
                    // and represent it internally in data structures
                    // ad described in project 2 presentation file

    switch (task) {
        case 1: printTerminalsAndNoneTerminals();
            break;

        case 2: RemoveUselessSymbols();
            break;

        case 3: CalculateFirstSets();
            break;

        case 4: CalculateFollowSets();
            break;

        case 5: CheckIfGrammarHasPredictiveParser();
            break;

        default:
      //      cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}


