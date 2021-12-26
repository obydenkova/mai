:- discontiguous female/1. % Информирует систему о том, что предложения указанного предиката (ов) 
			% может не быть вместе в исходном файле
:- discontiguous male/1.

male('Юрий Обыденков').
female('Наталья Харина').
female('Юлия Обыденкова').
male('Александр Харин').
female('Любовь Онищенко').
male('Виктор Обыденков').
female('Раиса Новикова').
female('Мария Волкова').
male('Владимир Онищенко').
female('Виктория Обыденкова').
female('Лариса Харина').
female('Акулина Новикова').
male('Федор Харин').
male('Игорь Никифоров').
male('Евгений Никифоров').
male('Александр Никифоров').
male('Артем Обыденков').
male('Алексей Обыденков').
female('Раиса Артемова').
male('Петр Новиков').
female('Галина Ямпольская').
parents('Юлия Обыденкова', 'Юрий Обыденков', 'Наталья Харина').
parents('Виктория Обыденкова', 'Юрий Обыденков', 'Наталья Харина'). ￼
parents('Лариса Харина', 'Александр Харин', 'Любовь Онищенко').
parents('Наталья Харина', 'Александр Харин', 'Любовь Онищенко').
parents('Юрий Обыденков', 'Виктор Обыденков', 'Раиса Новикова').
parents('Артем Обыденков', 'Виктор Обыденков', 'Раиса Новикова').
parents('Любовь Онищенко', 'Владимир Онищенко', 'Мария Волкова').
parents('Александр Харин', 'Федор Харин', 'Акулина Новикова').
parents('Евгений Никифоров', 'Игорь Никифоров', 'Лариса Харина').
parents('Александр Никифоров', 'Игорь Никифоров', 'Лариса Харина').
parents('Виктор Обыденков', 'Алексей Обыденков', 'Раиса Артемова').
parents('Раиса Новикова', 'Петр Новиков', 'Галина Ямпольская').

father(X, Y) :-
    parents(X, Y, _).

mother(X, Y) :-
    parents(X, _, Y).

child(X, Y) :- 
    parents(X, Z, Y);
    parents(X, Y, Z).

brother(X, Y) :- % брат
    parents(X, F, M),
    parents(Y, F, M),
    X\=Y, male(Y).

sister(X, Y) :- % сестра
    parents(X, F, M),
    parents(Y, F, M),
    X\=Y, female(Y).

bro_or_sist(X, Y) :- % брат или сестра
    parents(X, F, M),
    parents(Y, F, M),
    X\=Y.

double(X, Y) :- % двоюродные брат или сестра
    parents(X, F1, M1),
    parents(Y, F2, M2),
    X\=Y,
    
    (bro_or_sist(F1, F2);
    bro_or_sist(F1, M2);
    bro_or_sist(M1, F2);
    bro_or_sist(M1, M2)).
    
cousin(Person,X) :- % двоюродный брат
    child(Person,P), child(P,PP), 
    child(Y,PP), child(X,Y),
    Y\=P, male(X).

% степень родства

relative(child, Child, Parent) :-
    parents(Child, _, Parent);
    parents(Child, Parent, _).

relative(sister, Sister, Brother) :-
    sister(Sister, Brother).

relative(brother, Brother, Sister) :-
    brother(Brother, Sister).

relative(double, X, Y) :-
	double(X, Y).

relative(father, Father, Child) :-
    parents(Child, Father, _).

relative(mother, Mother, Child) :-
    parents(Child, _, Mother).

relative(husband, Husband, Wife) :-
    parents(_, Husband, Wife), !.

relative(wife, Wife, Husband) :-
    parents(_, Husband, Wife), !.

relative(Way, First, Last) :- 
    dpath(First, Last, Way), !.

chain_of_relation(X):-
      member(X, [child, father, mother, sister, 
      brother, husband, wife]).

print_ans([]).
print_ans([H|Tail]):-
    print_ans(Tail),
    write(H),  write(' - ').

next(Curr, HasBeen, Y, Rel) :-
   (relative(Rel, Curr, Y);
   relative(Rel, Y, Curr)),
   not(member(Y, HasBeen)).

dFS(X, X, _, _).

dFS(Curr, Last, T, [Rev|Tl]) :- 
    next(Curr, T, Next, Rev),
    dFS(Next, Last, [Curr|T], Tl),
    !.

dpath(First, Last, Way) :- 
    dFS(First, Last, [], RevWay),
    reverse(RevWay, Way),
	print_ans(Way),
	!.


% естественно-языковой интерфейс

start_of_question(X):-
    member(X, [who, "Who"]).

is(X):-
    member(X,[is, "Is"]).

suffix(X):-
    member(X, ["'s"]).

mark_of_question(X):-
    member(X, ['?']).


% Пример запроса: [who, is, *name*, "'s", mother, ?]
ask_the_question(List):-
      List = [Word, Is, Name, Suff, Relation, Qstn],
      start_of_question(Word),
      is(Is),
      (male(Name);
      female(Name)),
      nb_setval(lastName, N),
      suffix(Suff),
      chain_of_relation(Relation),
      mark_of_question(Qstn), !,
      relative(Relation, Res, Name),
      write(Res), write(" is "), write(Name), write("'s "), write(Relation).


% Пример запроса: [is, *name*, *name*, "`s", father, ?]
ask_the_question(List):-
      List = [Is, Name1, Name2, Suff, Relation, Qstn],
      nb_setval(lastName, Name2),
      is(Is),
      (male(Name1);female(Name1)),
      (male(Name2);female(Name2)),
      suffix(Suff),
      chain_of_relation(Relation),
      mark_of_question(Qstn),
      relative(Relation, Name1, Name2), !.

   
