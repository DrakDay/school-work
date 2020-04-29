/* Facts */

edge(ca,or).	
edge(ca,nv).	
edge(ca,az).	
edge(az,nv).	
edge(az,ut).	
edge(az,co).	
edge(az,nm).	
edge(nm,co).	
edge(nv,or).	
edge(nv,id).	
edge(nv,ut).	
edge(ut,id).	
edge(ut,wy).	
edge(ut,co).	
edge(co,wy).	
edge(co,ks).	
edge(co,ne).	
edge(ks,ne).		
edge(ne,sd).		
edge(or,wa).		
edge(or,id).	
edge(id,mt).	
edge(id,wy).	
edge(wy,ne).	
edge(wy,sd).	
edge(wa,id).	
edge(mt,nd).	
edge(mt,sd).		
color(ca,pink).
color(az,orange).
color(nm,red).
color(nv,yellow).
color(ut,red).
color(co,blue).
color(ks,red).
color(or,yellow).
color(id,blue).
color(wy,pink).
color(ne,orange).
color(sd,blue).
color(nd,yellow).
color(mt,pink).
color(wa,orange).
population(ca,40).
population(az,7).
population(nd,1).
population(nm,2).
population(sd,1).
population(nv,3).
population(ne,2).
population(ut,3).
population(co,6).
population(ks,3).
population(wa,8).
population(or,4).
population(id,2).
population(mt,1).
population(wy,1).

/* Rule */

adjacent(X,Y) :- edge(X,Y); edge(Y,X).   % see if X and Y are neighbor

miscolor(S1,S2,Color1) :- adjacent(S1,S2), color(S1,Color1), color(S2,Color1).  %if they are beighbor then check if they have sample color

%totalpopulation
total(L,Total):- total(L,0,Total). 	/*expand total/2 to total/3 with an accumulator.*/
total([],Total,Total). 			/*if the list is empty then pass the value of the accumulator to Total*/
total([[_|HT]|T],Temp,Total) :- 	/*take the tial of the first list*/
		Temp1 is Temp + HT, 	/*add HT to Temp and store it to Temp*/
		total(T,Temp1,Total). 	/*recursive call it self with a update accumulator*/

q1 :- miscolor(S1, S2, Color1),
	write(S1), write(' and '), write(S2),
	write(' have conflict color: '), write(Color1),nl,
	total([[az,7],[ca,40],[nd,1],[nm,2],[sd,1],[nv,3],[ne,2],[ut,3],[co,6],[ks,3],[wa,8],[or,4],[id,2],[mt,1],[wy,1]],Total),
	write('Total = '),write(Total),nl.


pizza(P,M,B,O,C):-

    member(P, [0,1,2,3,4,5,6,7,8,9]), 	/* 45/5 =9 */
    member(M, [0,1,2,3,4]),		/*45 / 10 = 4*/
    member(B, [0,1,2,3,4,5,6]),		/*45 / 7 = 6*/
    member(O, [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]),	/*45 / 3 = 15*/
    member(C, [0,1,2,3,4,5]),	/*45 / 8 = 5*/
    
    A is P*5 + M*10 + B*7 + O*3 + C*8,
    A =:= 45.

q2:-	 pizza(2, 1, 2, 1, 1),
	 pizza(1, M2, 1, O2, C2),
	 pizza(P3, M3, 1, O3, 1),
	 nl,
	 write('M2='),write(M2),write(' O2='),write(O2),write(' C2='),write(C2),nl,
	 write('P3='),write(P3),write(' M3='),write(M3),write(' O3='),write(O3).
