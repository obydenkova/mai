move([H|T],X,T,[H|X]):-!.

% продление пути без зацикливания
prolong(Zabrat,Zabrat1,[H|T],[Y,H|T]):-
    move(Zabrat,H,Zabrat1,Y),
    \+ member(Y,[H|T]).

work_tupik([H|T],T,K,[H|K]).


inv_print([]).
inv_print([A|T]):-inv_print(T), write(A), nl.

int(1).
int(X):-
    int(Y),
    X is Y + 1.

% поиск в глубину
search_dpth(A,B):-
    write('DFS START'), nl,
    get_time(DFS),
    dpth([[]],B,L,[],A),
    inv_print(L),
    get_time(DFS1),
    write('DFS END'), nl, nl,
    T1 is DFS1 - DFS,
    write('TIME IS '), write(T1), nl, nl.

dpth([X|T],X,[X|T],_,_):-!.

dpth(_,_,_,_,[]):-fail.

dpth(P,F,L,Tupik,Nach):-
    prolong(Nach,Nach1,P,P1),dpth(P1,F,L,Tupik,Nach1).

dpth(P,F,L,Tupik,Nach):-
    work_tupik(Nach,Nach1,Tupik,Tupik1), dpth(P,F,L,Tupik1,Nach1).

dpth(P,F,L,Tupik,Nach):-
   length(Tupik,Num), Num > 0, prolong(Tupik,Tupik1,P,P1), dpth(P1,F,L,Tupik1,Nach).


% поиск в ширину

search_bdth(X,Y):-
    write('BFS START'), nl,
    get_time(BFS),
    bdth([[[]]],X,[],Y,L),
    inv_print(L),
    get_time(BFS1),
    write('BFS END'), nl, nl,
    T1 is BFS1 - BFS,
    write('TIME IS '), write(T1), nl, nl.

bdth([[X|T]|_],_,_,X,[X|T]).

bdth(_,[],_,_,_):-fail.

bdth([P|QI],A,Tupik,X,R):-
    (
    prolong(Tupik,Tupik1,P,P1),append(QI,P1,Q0), bdth([Q0],A,Tupik1,X,R);
    prolong(A,A1,P,P1), append(QI,P1,Q0), bdth([Q0],A1,Tupik,X,R);
    work_tupik(A,A1,Tupik,Tupik1), bdth([P|QI],A1,Tupik1,X,R)
    ).

bdth([_|T],A,Tupik,Y,L):-
    bdth(T,A,Tupik,Y,L).


% поиск с итерационным заглублением
search_id(Start,Finish):-
    write('ITER START'), nl,
    get_time(ITER),
    int(DepthLimit),
    depth_id([[]],Start,[],Finish,Res,DepthLimit),
    inv_print(Res),
    get_time(ITER1),
    write('ITER END'), nl, nl,
    T1 is ITER1 - ITER,
    write('TIME IS '), write(T1), nl, nl.

depth_id([Finish|T],[],_,Finish,[Finish|T],0).

depth_id(P,A,Tupik,Finish,R,N):-
    N > 0,
    (
    prolong(Tupik,Tupik1,P,P1), N1 is N - 1, depth_id(P1,A,Tupik1,Finish,R,N1);
    prolong(A,A1,P,P1),  N1 is N - 1, depth_id(P1,A1,Tupik,Finish,R,N1);
    work_tupik(A,A1,Tupik,Tupik1), depth_id(P,A1,Tupik1,Finish,R,N)
    ).