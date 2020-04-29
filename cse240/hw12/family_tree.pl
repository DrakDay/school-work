/* Database for family tree. It consists of facts and rules. */
/* A portion of the family tree has been implemented for you */

/* Facts */
male(kam).
male(rob).
female(ana).
female(syd).
father_of(kam, rob). 		/* kam is the father of rob */
father_of(kam, syd).		/* kam is the father of syd */
mother_of(ana, rob). 	/* ana is the mother of rob */
mother_of(ana, syd). 	/* ana is the mother of syd */

/* Rules */
is_male(X) :- male(X);father_of(X,_).  	

is_female(X) :- female(X);mother_of(X,_).

parent_of(X,Y):- father_of(X,Y);mother_of(X,Y).

sibling_of(X,Y):- parent_of(Z,X),parent_of(Z,Y).

grandmother_of(X,Z):- female(X),mother_of(X,Y),parent_of(Y,Z).

grandfather_of(X,Z):- male(X),father_of(X,Y),parent_of(Y,Z).

descendent_of(X, Y):- grandfather_of(Y,X);grandmother_of(Y,X).
