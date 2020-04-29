/*
 * Copyright (C) Rida Bazzi, 2020
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
#include <iostream>
#include <cstdlib>
#include "parser.h"
#include <vector>
#include <algorithm> 
#include <math.h>

using namespace std;

//for eval
vector<symboal *> symboal_table;
vector<int> inputs;
vector<poly_decl*> poly_decl_table;
vector<stmt * > poly_eval_table;

//for errors
vector<namewithlineno * > error1;
vector<int> error2;
vector<int> error3;
vector<int> error4;
vector<int> error5;

void Parser::syntax_error()
{
	cout << "SYNTAX ERROR !!!\n";
	exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
	Token t = lexer.GetToken();
	if (t.token_type != expected_type)
		syntax_error();
	return t;
}

// this function simply checks the next token without
// consuming the input
// Written by Mohsen Zohrevandi
Token Parser::peek()
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}


// Parsing
void Parser::parse_input() {
	// input -> program inputs
	parse_program();
	parse_inputs();
	Token t = lexer.GetToken();
	if (t.token_type != END_OF_FILE)
		syntax_error();
}

void Parser::parse_program() {
	// program -> poly_dec_section start
	parse_poly_decl_section();
	parse_start();
}

void Parser::parse_poly_decl_section() {
	// poly_dec_section -> poly_decl| poly_decl poly_decl_section
	parse_poly_decl();
	if (peek().token_type == POLY)
		parse_poly_decl_section();
}

void Parser::parse_poly_decl() {
	// parse_poly_decl -> POLY polynomial_header EQUAL polynomial_body SEMICOLON 

	Token t = lexer.GetToken();
	if (t.token_type != POLY)
		syntax_error();

	struct poly_decl * po_decl = parse_polynomial_header();
	t = lexer.GetToken();

	if (t.token_type != EQUAL)
		syntax_error();


	po_decl->body = parse_polynomial_body(po_decl->parameter);

	t = lexer.GetToken();
	if (t.token_type != SEMICOLON)
		syntax_error();

	poly_decl_table.push_back(po_decl);
}

struct poly_decl * Parser::parse_polynomial_header() {
	//polynomial_header -> polynomial_name | polynomial_name LPAREN id_list RPAREN
	struct poly_decl * po_decl = new poly_decl();

	//get the poly name and line no, later check if any repeat for error 1
	struct namewithlineno * error = new namewithlineno();
	Token t = lexer.GetToken();
	error->name = t.lexeme;
	error->line_no = t.line_no;
	error1.push_back(error);
	lexer.UngetToken(t);

	string name = parse_polynomial_name();
	po_decl->name = name;

	peek().t
	if (peek().token_type == LPAREN)
	{
		Token t = lexer.GetToken();
		po_decl->parameter = parse_id_list();
		t = lexer.GetToken();

		if (t.token_type != RPAREN)
			syntax_error();
	}
	return po_decl;
}

string Parser::parse_polynomial_name() {
	//polynomial name -> id

	Token t = lexer.GetToken();

	if (t.token_type != ID)
		syntax_error();
	else
		return t.lexeme;
}

struct id_list * Parser::parse_id_list() {
	// id list -> id | id comma id list
	struct id_list * lh = new id_list();
	struct id_list * lt = new id_list();

	Token t = lexer.GetToken();
	if (t.token_type == ID) {

		lh->id = t.lexeme;
		lh->next = NULL;
		if (peek().token_type == COMMA) {
			t = lexer.GetToken();
			lt = parse_id_list();
			lh->next = lt;
		}
	}
	else {
		syntax_error();
	}
	return lh;
}

struct poly_body * Parser::parse_polynomial_body(struct id_list * parameter) {
	// polynomial_body -> term_list

	struct term * terma = new term();
	struct poly_body * body = new poly_body();
	body->poly = parse_term_list(parameter);
	delete terma;
	return body;
}

struct term * Parser::parse_term_list(id_list * parameter) {
	//term list -> term | term add_operator(plus minus) term_list

	struct term * terma = new term();
	terma = parse_term(parameter);

	if (peek().token_type == PLUS || peek().token_type == MINUS)
	{
		terma->oper = parse_add_operator();
		struct term * rest = new term;
		rest = parse_term_list(parameter);
		terma->next = rest;
	}
	return terma;
}

int Parser::parse_add_operator() {
	// add operator -> plus | minus
	Token t = lexer.GetToken();
	if (t.token_type == PLUS)
		return 1;
	else if (t.token_type == MINUS)
		return 2;
	else
		syntax_error();

}

struct term * Parser::parse_term(id_list * parameter) {
	//term -> monomial_list  | coefficient(NUM) | coeefficient monomial_list
	struct term * terma = new term;

	if (peek().token_type == NUM)
	{
		terma->cofficient = parse_cofficient();
		if (peek().token_type == ID)
			terma->mono_list = parse_monomial_list(parameter);
	}
	else {
		terma->mono_list = parse_monomial_list(parameter);
	}
	return terma;
}

int Parser::parse_cofficient() {
	// coeff => num
	Token t = lexer.GetToken();
	if (t.token_type != NUM)
		syntax_error();
	else
		return stoi(t.lexeme);
}

struct monomial_list * Parser::parse_monomial_list(id_list * parameter) {
	// monomial_list -> monomial | monomial monomial_list 
	struct monomial_list* m1 = new monomial_list();
	m1->monomial = parse_monomial(parameter);

	if (peek().token_type == ID) {
		struct monomial_list* m2 = new monomial_list();
		m2 = parse_monomial_list(parameter);
		m1->next = m2;
	}
	return m1;
}

struct monomial * Parser::parse_monomial(id_list * parameter) {
	// monoial -> ID | ID exponent
	struct monomial * mono = new monomial();
	Token t = lexer.GetToken();

	//check error if parameter is none then "x" does not count 
	if (parameter == NULL) {
		if (t.lexeme != "x")
			error2.push_back(t.line_no);
	}
	else
	{
		// if parameter is not none, check current ID in the parameter list or not
		bool flag = false;
		struct id_list * copy = parameter;
		while (copy != NULL) {
			if (copy->id == t.lexeme)
				flag = true;
			copy = copy->next;
		}
		if (flag == false)
			error2.push_back(t.line_no);
	}
	if (t.token_type != ID)
		syntax_error();

	int count = 0;

	while (parameter != NULL) {
		if (parameter->id == t.lexeme)
			mono->pos = count;
		count++;
		parameter = parameter->next;
	}

	if (peek().token_type == POWER) {
		mono->exponent = parse_exponent();
	}

	return mono;
}

int Parser::parse_exponent() {
	// exponent -> power num
	Token t = lexer.GetToken();
	if (t.token_type != POWER)
		syntax_error();

	t = lexer.GetToken();
	if (t.token_type != NUM)
		syntax_error();

	return stoi(t.lexeme);
}

void Parser::parse_start() {
	//start -> START statement_list
	Token t = lexer.GetToken();
	if (t.token_type != START)
		syntax_error();
	struct stmt * st = new stmt();
	st = parse_statement_list();
	poly_eval_table.push_back(st);
}

struct stmt*  Parser::parse_statement_list() {
	//statement_list -> statement | statement statement_list
	struct stmt* st = new stmt();
	struct stmt* stl = new stmt();
	st = parse_statement();

	// statement start with input or ID
	if (peek().token_type == INPUT || peek().token_type == ID)
	{
		stl = parse_statement_list();
		st->next = stl;
	}
	return st;
}

struct stmt * Parser::parse_statement() {
	// statement -> input_statement | polynomial_evaluation_statement
	if (peek().token_type == INPUT)
	{
		struct stmt* st = parse_input_statement();
		return st;
	}
	else {
		struct stmt* st = parse_polynomial_evaluation_statement();
		
		return st;
	}
}

struct stmt * Parser::parse_polynomial_evaluation_statement() {
	// poly_evalution_statment -> poly_evaluation Semicolon

	struct stmt* st = new stmt();
	st->eval = parse_polynomial_evaluation();
	st->stmt_type = 2;

	Token t = lexer.GetToken();
	if (t.token_type != SEMICOLON)
		syntax_error();

	return st;
}

int next_available = 0;

struct stmt* Parser::parse_input_statement() {
	//input statement -> input id semicolon
	Token t = lexer.GetToken();
	struct stmt * st = new stmt();
	string name = "";
	bool find = false;

	//alocating memory for varible
	if (t.token_type == INPUT) {

		t = lexer.GetToken();

		symboal * sym = new symboal();
		sym->name = t.lexeme;
		sym->pos = next_available;

		st->stmt_type = 1; // 1 for input
		st->eval = NULL;
		name = t.lexeme;

		if (t.token_type == ID)
		{
			// see if id is in the table or not
			for (int i = 0; i < symboal_table.size(); i++) {

				if (symboal_table[i]->name.compare(t.lexeme) == 0)
				{
					find = true;
					break;
				}
			}
			if (find == true) {
				delete sym;
			}
			else {
				symboal_table.push_back(move(sym));
				next_available++;
			}

			t = lexer.GetToken();
			if (t.token_type != SEMICOLON)
				syntax_error();
		}
		else
			syntax_error();
	}
	else
		syntax_error();

	for (int i = 0; i < symboal_table.size();i++) {
		if (name == symboal_table[i]->name)
			st->varaibale = i;
	}

	return st;
}

struct poly_eval* Parser::parse_polynomial_evaluation() {
	//polynomial_evaluation -> polynomial_name LPAREN argument_list RPAREN 

	Token tt = peek();
	Token t = peek();
	string poly_name = parse_polynomial_name();

	//check error 3
	bool flag = false;
	for (int i = 0; i < error1.size(); i++) {
		if (poly_name == error1[i]->name)
			flag = true;
	}
	if (flag == false)
		error3.push_back(t.line_no);
	//

	struct id_list * idd = new id_list();
	struct poly_eval* po_eval = new poly_eval();

	for (int i = 0; i < poly_decl_table.size(); i++) {
		if (poly_name == poly_decl_table[i]->name)
		{
			po_eval->pos = i;
			idd = poly_decl_table[i]->parameter;
		}
	}


	t = lexer.GetToken();
	if (t.token_type != LPAREN)
		syntax_error();

	po_eval->argu = parse_argument_list();

	struct argunment * arg = po_eval->argu;
	//error 4
	int count = 0;
	int count2 = 0;

	while (arg->next != NULL) {
		count++;

		arg = arg->next;
	}

	if (idd == NULL && count < 2) {

	}
	else {
		if (idd == NULL) {

		}
		else {
			while (idd->next != NULL) {
				count2++;
				idd = idd->next;
			}
		}
		
	}
	if (count != count2)
		error4.push_back(tt.line_no);

	t = lexer.GetToken();

	if (t.token_type != RPAREN)
		syntax_error();

	return po_eval;
}

struct argunment * Parser::parse_argument_list() {
	// pargument_list = argument | argument comma argunment_list
	struct argunment* argu;
	struct argunment* rest;
	argu = parse_argument();

	Token t = lexer.GetToken();
	if (t.token_type == COMMA)
	{
		rest = parse_argument_list();
		argu->next = rest;

	}
	else
		lexer.UngetToken(t);

	return argu;
}

struct argunment * Parser::parse_argument() {
	// argument -> id| num |polymial_evaluation
	struct argunment * argu = new argunment();

	Token t = lexer.GetToken();
	if (t.token_type == ID && peek().token_type == LPAREN) {
		lexer.UngetToken(t);

		struct poly_eval* po_eval = new poly_eval();
		argu->type = 2;
		po_eval = parse_polynomial_evaluation();
		argu->eval = po_eval;
	}
	else if (t.token_type == NUM)
	{
		argu->type = 1;
		argu->value = stoi(t.lexeme);
		argu->eval = NULL;

	}
	else if (t.token_type == ID) {
		argu->type = 3;
		argu->eval = NULL;
		for (int i = 0; i < symboal_table.size(); i++) {
			if (t.lexeme == symboal_table[i]->name)
				argu->index = i;
		}

		bool flag = false;
		for (int i = 0; i < symboal_table.size(); i++) {
			if (t.lexeme == symboal_table[i]->name)
				flag = true;
		}
		if (flag == false)
			error5.push_back(t.line_no);
	}
	else
		syntax_error();

	return argu;

}

void Parser::parse_inputs() {
	//inputs -> num | num inputs
	Token t = lexer.GetToken();
	if (t.token_type != NUM)
		syntax_error();

	inputs.push_back(stoi(t.lexeme));

	if (peek().token_type == NUM)
		parse_inputs();
}



int evalue_monomial_list(struct monomial_list * list, vector<int> parameters) {

	struct monomial_list * mo_list = list;
	int result = 1;

	while (mo_list != NULL) {
		int pos = mo_list->monomial->pos;
		result = result * pow(parameters[pos], mo_list->monomial->exponent);
		mo_list = mo_list->next;
	}
	return result;
}

int evalue_poly(struct poly_decl * decl, vector<int> parameters) {
	vector<int> res;
	struct term * terma = decl->body->poly;
	int sum = 0;
	int coff = 1;
	while (terma->oper != 0) {
		coff = terma->cofficient;

		sum = coff * evalue_monomial_list(terma->mono_list, parameters);

		res.push_back(sum);
		if (terma->oper == 1)
			res.push_back(1);
		else {
			res.push_back(2);
		}

		terma = terma->next;
	}

	coff = terma->cofficient;
	sum = coff * evalue_monomial_list(terma->mono_list, parameters);
	res.push_back(sum);

	int pos = 0;
	int len = res.size();
	while (pos < len - 1) {
		if (res[pos + 1] == 1) {
			res[pos + 2] = res[pos] + res[pos + 2];
		}
		else {
			res[pos + 2] = res[pos] - res[pos + 2];
		}
		pos = pos + 2;
	}
	return res[len - 1];
}

int evaluate_polynomial(struct poly_eval * po_eval) {
	vector<int> parameters;
	struct poly_eval * po = po_eval;

	while (po->argu != NULL) {
		if (po->argu->type == 1)
			parameters.push_back(po->argu->value);
		else if (po->argu->type == 3)
			parameters.push_back(symboal_table[po->argu->index]->value);
		else if (po->argu->type == 2) {
			struct  poly_eval * z = po_eval->argu->eval;
			int x = evaluate_polynomial(z);
			parameters.push_back(x);
		}

		po->argu = po->argu->next;
	}

	struct poly_decl* dec = poly_decl_table[po->pos];
	int ans = evalue_poly(dec, parameters);
	return ans;
}



void excute_program(struct stmt * start) {
	struct stmt* pc;
	int v;
	pc = start;
	int next_input = 0;
	while (pc != NULL) {
		switch (pc->stmt_type)
		{
		case 2:  //eval
			v = evaluate_polynomial(pc->eval);
			cout << v << endl;
			break;
		case 1: // input
			symboal_table[pc->varaibale]->value = inputs[next_input];
			next_input++;
			break;
		}
		pc = pc->next;
	}

}


int main() {
	Parser parse;
	LexicalAnalyzer lexer;
	Token token;
	parse.parse_input();



	//error 1 done
	vector<int> xd;
	for (int i = 0; i < error1.size(); i++) {

		for (int j = i + 1; j < error1.size(); j++) {
			if (error1[i]->name == error1[j]->name) {
				xd.push_back(error1[i]->line_no);
				xd.push_back(error1[j]->line_no);
			}
		}
	}
	sort(xd.begin(), xd.end());
	xd.erase(unique(xd.begin(), xd.end()), xd.end());

	if (xd.size() > 0) {
		cout << "Error Code 1 :";
		for (int i = 0; i < xd.size(); i++) {
			cout << " " << xd[i];
		}
		exit(1);
	}

	//error2 done
	if (error2.size() > 0) {
		cout << "Error Code 2 :";
		for (int i = 0; i < error2.size(); i++) {
			cout << " " << error2[i];
		}
		exit(1);
	}

	//error3 done
	if (error3.size() > 0) {
		cout << "Error Code 3 :";
		for (int i = 0; i < error3.size(); i++) {
			cout << " " << error3[i];
		}
		exit(1);
	}
	//errpr4
	if (error4.size() > 0) {
		sort(error4.begin(), error4.end());
		cout << "Error Code 4 :";
		for (int i = 0; i < error4.size(); i++) {
			cout << " " << error4[i];
		}
		exit(1);
	}

	//error 5
	if (error5.size() > 0) {

		cout << "Error Code 5 :";
		for (int i = 0; i < error5.size(); i++) {
			cout << " " << error5[i];
		}
		exit(1);
	}



	struct stmt * st = poly_eval_table[0];
	excute_program(st);
	//error5

//	for (int i = 0; i < symboal_table.size(); i++) {
		//cout << symboal_table[i]->name << " " << symboal_table[i]->pos << endl;
	//}


	/*

	cout << endl;

	cout << endl;
	for (int i = 0; i < inputs.size(); i++) {
		cout << inputs[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < poly_decl_table.size(); i++) {
		cout <<"name "<< i << " " <<poly_decl_table[i]->name << endl;

		if (poly_decl_table[i]->parameter == NULL)
		{
			struct id_list * defalut = new id_list;
			defalut->id = "X"; defalut->next = NULL;
			poly_decl_table[i]->parameter = defalut;
		}
		while (poly_decl_table[i]->parameter != NULL) {
			cout <<"id " <<poly_decl_table[i]->parameter->id << endl;
			poly_decl_table[i]->parameter = poly_decl_table[i]->parameter->next;
		}
	}

	for (int i = 0; i < poly_decl_table.size(); i++) {
		while (poly_decl_table[i]->body->poly != NULL) {
			cout << endl;
			cout << "cofficient " << poly_decl_table[i]->body->poly->cofficient << endl;

			while (poly_decl_table[i]->body->poly->mono_list != NULL) {

				cout << " pos " << poly_decl_table[i]->body->poly->mono_list->monomial->pos << endl;
				cout << " exp " << poly_decl_table[i]->body->poly->mono_list->monomial->exponent << endl;

				poly_decl_table[i]->body->poly->mono_list = poly_decl_table[i]->body->poly->mono_list->next;
			}
			cout << "oper " << poly_decl_table[i]->body->poly->oper << endl;
			poly_decl_table[i]->body->poly = poly_decl_table[i]->body->poly->next;
		}

	}



	/*


	struct stmt * st = poly_eval_table[0];

	while (st != NULL) {

		if (st->stmt_type == 1) {
			cout << "type " << st->stmt_type << " pos" << st->varaibale << endl;
		}
		else {

			struct poly_eval * pol_eval = st->eval;
			cout << "type " << st->stmt_type << " poly " << pol_eval->pos << endl;
			if (pol_eval->argu->eval != NULL)
			{
				struct poly_eval * xt = pol_eval->argu->eval;
				while (xt->argu != NULL) {
					if (xt->argu->type == 1)
						cout << " NUM " << xt->argu->value << endl;
					else {
						cout << " ID " << xt->argu->index << endl;

						xt->argu = xt->argu->next;
					}
				}
			}else{
				while (pol_eval->argu != NULL) {
					if (pol_eval->argu->type == 1)
						cout << " NUM " << pol_eval->argu->value << endl;
					else {
						cout << " ID " << pol_eval->argu->index << endl;

						pol_eval->argu = pol_eval->argu->next;
					}
				}
			}
		}

		st = st->next;
	}

	*/

}
