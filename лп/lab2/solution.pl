% вариант 18
:- discontiguous close1/2.
:- discontiguous open/2.

open('обувной','вторник').
open('обувной','среда').
open('обувной','четверг').
open('обувной','пятница').
open('обувной','суббота').
close1('обувной','понедельник').

open('хозяйственный','понедельник').
open('хозяйственный','среда').
open('хозяйственный','четверг').
open('хозяйственный','пятница').
open('хозяйственный','суббота').
close1('хозяйственный','вторник').

open('продуктовый','понедельник').
open('продуктовый','вторник').
open('продуктовый','среда').
open('продуктовый','пятница').
open('продуктовый','суббота').
close1('продуктовый','четверг').

open('парфюмерный', 'понедельник').
open('парфюмерный', 'среда').
open('парфюмерный', 'пятница').
close1('парфюмерный', 'вторник').
close1('парфюмерный', 'четверг').
close1('парфюмерный', 'суббота').


getLenList([],0).
getLenList([_|L],N):- getLenList(L,N1), N is N1+1.



findmax([L|Ls], Max) :-
    findmax(Ls, L, Max).

findmax([], Max, Max).
findmax([L|Ls], Max0, Max) :-
    Max1 is max(L, Max0),
    findmax(Ls, Max1, Max).

% номер дня недели, когда они пошли в магазин, а вообще это первое
% вхождение аргумента в список.
num([],N,_):- N is 0.
num([L|_],N,Max) :-N is 1, L = Max.
num([_|Ls],N,Max):- num(Ls,N1,Max), N is N1+1.

day([],_,_,_):-!.
day([L|_],N,L,Num):-N=Num.
day([_|Ls],N,S,Num):-Num1 is Num + 1, day(Ls,N,S,Num1).

poisk(NextDay,PrevDay, S, Name,_,_,_,_,_,_, Name):-
member(NextDay,S), member(PrevDay,S).

poisk(NextDay,PrevDay, _, _,S,Name,_,_,_,_, Name):-
member(NextDay,S), member(PrevDay,S).

poisk(NextDay,PrevDay, _, _,_,_,S,Name,_,_, Name):-
member(NextDay,S), member(PrevDay,S).

poisk(NextDay,PrevDay, _, _,_,_,_,_,S,Name, Name):- 
member(NextDay,S), member(PrevDay,S).

poisk(_,_, _, _,_,_,_,_,_,_, 'No'):-!.

ira(NextDay, PrevDay,S, Name,_,_,_,_,_,_, Name):-
member(PrevDay, S),not(member(NextDay,S)). 

ira(NextDay, PrevDay,_, _,S,Name,_,_,_,_, Name):-
member(PrevDay, S),not(member(NextDay,S)).

ira(NextDay, PrevDay,_, _,_,_,S,Name,_,_, Name):-
member(PrevDay, S),not(member(NextDay,S)).

ira(NextDay, PrevDay,_, _,_,_,_,_,S,Name, Name):-
member(PrevDay, S),not(member(NextDay,S)).

ira(_,_, _, _,_,_,_,_,_,_, 'No'):-!.

elem([L|_],L):-!.

work :-
     L = ['понедельник','вторник','среда','четверг', 'пятница', 'суббота', 'воскресенье'],
     F = [F0,F1,F2,F3,F4,F5,F6],
     findall(X,open(X,'понедельник') ,Pn),
     findall(X,open(X,'вторник') ,Vt),
     findall(X,open(X, 'среда') ,Sr),
     findall(X,open(X,'четверг') ,Ch),
     findall(X,open(X,'пятница') ,Pt),
     findall(X,open(X,'суббота') ,Sb),
     findall(X,open(X,'воскресенье') ,Vs),
     getLenList(Pn,F0),
     getLenList(Vt,F1),
     getLenList(Sr,F2),
     getLenList(Ch,F3),
     getLenList(Pt,F4),
     getLenList(Sb,F5),
     getLenList(Vs,F6),

     findmax(F,Max),
     num(F,N,Max),
    % здесь становится понятно, что искомый день - среда.
     day(L,N,NowDay,1),
    % дни с которыми я работаю
     N1 is N + 1, N2 is N - 1, N3 is N2 - 1,
     day(L,N1,NextDay,1),
     day(L,N2,PrevDay,1),
     day(L,N3,PrevprevDay,1),

     findall(X,open('обувной',X) ,Ob),
     findall(X,open('хозяйственный',X) ,Hz),
     findall(X,open('продуктовый', X) ,Prd),
     findall(X,open('парфюмерный',X) ,Prf),

     poisk(NextDay,PrevDay, Ob,'обувной',Hz,'хозяйственный', Prd,
     'продуктовый', Prf, 'парфюмерный', Zhenya),
     
     poisk(PrevprevDay,PrevDay, Ob,'обувной',Hz,'хозяйственный', Prd,
     'продуктовый', Prf, 'парфюмерный', Klava),
     
     findall(X,close1(X,NextDay) ,List1),
     delete(List1,Zhenya,List2),
     delete(List2, Klava, List),
     elem(List,Ira),
     findall(X,open(X,NowDay) ,Result1),
     delete(Result1,Zhenya,Result2),
     delete(Result2, Klava, Result3),
     delete(Result3,Ira,Result),
     elem(Result,Asya),
     write('Ася : '), write(Asya), nl,
     write('Женя : '), write(Zhenya), nl,
     write('Клава : '), write(Klava), nl,
     write('Ира : '), write(Ira), nl,
     !.
