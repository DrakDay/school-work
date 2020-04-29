/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "util.h"
#include "lexer.h"

class Parser {
private:
	LexicalAnalyzer lexer;

	void syntax_error();
	Token expect(TokenType expected_type);
	Token peek();
public:
	void parse_input();
	void parse_program();
	void parse_poly_decl_section();
	void parse_start();
	void parse_poly_decl();
	struct poly_decl * parse_polynomial_header();
	struct poly_body * parse_polynomial_body(id_list * parameter);
	string parse_polynomial_name();
	struct id_list * parse_id_list();
	struct term* parse_term_list(id_list * parameter);
	struct term* parse_term(id_list * parameter);
	int parse_add_operator();
	int parse_cofficient();
	struct monomial_list * parse_monomial_list(id_list * parameter);
	struct monomial *  parse_monomial(id_list * parameter);
	int parse_exponent();
	struct stmt * parse_statement_list();
	struct stmt * parse_statement();
	struct stmt * parse_polynomial_evaluation_statement();
	struct stmt * parse_input_statement();
	struct poly_eval * parse_polynomial_evaluation();
	struct argunment * parse_argument_list();
	struct argunment * parse_argument();
	void parse_inputs();
};

#endif

