/*Rule*/

get_last([E],E).
get_last([_|T],E) :- get_last(T,E).

q1 :- get_last([1,2,3,4,5],E),write('E='),write(E).


remove_last([_],[]).
remove_last([H|T],[H|T2]) :- remove_last(T,T2).

q2 :- remove_last([1,2,3,4,5,6],X),write('X='),write(X).


qsort([],[]) :- !.

qsort(X,Sorted):-
	get_last(X,Pivot),
	remove_last(X,Tail),
	split(Pivot, Tail, L1, L2),
	qsort(L1,Sorted1), 
	qsort(L2,Sorted2),
	append(Sorted1,[Pivot|Sorted2], Sorted).

split(_,[],[],[]).
split(Pivot,[X|T],[X|Le],Gt):- X=<Pivot, split(Pivot,T,Le,Gt).
split(Pivot,[X|T],Le,[X|Gt]):- X > Pivot, split(Pivot,T,Le,Gt).


q3 :- qsort([8,3,4,12,25,4,6,1,9,22,6],Sorted),write('soted='),write(Sorted).

