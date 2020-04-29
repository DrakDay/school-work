
/* RUle */
%foo is size n problem
foo(X,Y,Z) :- 
	Y =< 0, Z is X. %stop condition and its return value
foo(X,Y,Z) :- 
	X =< 0, Z is Y. %stop condition and its return value
foo(X,Y,Z) :- 
	X >= Y,                     %condtion check
	X1 is X - 1 , Y1 is Y - 2,  %size m problem
	foo(X1,Y1,Z1) , 	    %size m soulution
	Z = X + Z1.                 %output value
foo(X,Y,Z) :- 
	X < Y,  		    %condtion check
	X1 is X - 2 , Y1 is Y - 3,  %size m problem
	foo(X1,Y1,Z1) , 	    %size m soulution
	Z = Y + Z1.		    %output value

