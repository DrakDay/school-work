#pragma once
#include <string>
using namespace std;

struct symboal {
	string name;
	int pos;
	int value;
};

struct stmt {
	int stmt_type; // 1 for input 2 for eval
	struct poly_eval * eval;
	int varaibale;
	struct stmt* next;
};

struct poly_decl {
	string name;
	struct id_list * parameter;
	struct poly_body * body;

};

struct monomial {
	int pos;
	int exponent = 1;
};

struct monomial_list {
	struct monomial * monomial;
	struct monomial_list * next;
};

struct term {
	int cofficient = 1;
	int oper; // 1 for plus 2 for minuns
	struct monomial_list * mono_list;
	struct term * next;
};

struct poly_body {
	struct term* poly;
};

struct id_list {
	string id;
	struct id_list * next;
};

struct poly_eval {
	int pos;
	struct argunment * argu;
};

struct argunment {
	int type; //1 for num 2 for eval 3 for id
	int value;
	int index;
	struct poly_eval* eval;
	struct argunment* next;
};

struct namewithlineno {
	string name;
	int line_no;
};