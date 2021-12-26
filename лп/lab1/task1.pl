% task 1
% реализация стандартных предикатов обработки списков

    % длина списка
    % (список, длина)

    lengthList([],0).
    lengthList([_|T],N) :- 
    lengthList(T,N1), N is N1+1.

    % принадлежность элемента списку
    % (элемент, список)

    memberList(X,[X|L]).
    memberList(X,[L|T]) :-
    memberList(X,T).

    % конкатенация списков
    % (список1, список2, список1+2)

    appendList([],L,L).
    appendList([H|T], L, [H|R]) :-
    appendList(T,L,R).

    % удаление элементов из списка
    %(элемент, список, список без элемента)

    deleteList(E,[E|S],S).
    deleteList(E,[E1|S],[E1|X]) :-
    deleteList(E,S,X).

    % перестановка элементов списка
    % (список, перестановка)

    permutList([],[]).
    permutList(S,[L|Y]) :-
    deleteList(L,S,X),
    permutList(X,Y).

    % подсписки списка
    % (подсписок, список)

    subList(X,Y) :-
    appendList(S,L,M),
    appendList(X,S,L).

% 1.1
% предикат 19) циклический сдвиг списка вправо    

    % с использованием встроенных предикатов
    % (список, число сдвигов, сдвинутый список)

    rSlide(L,N,S) :-
    append(Left,Right,L),
    length(Right,N),
    append(Right,Left,S), !.
    

    % без использования встроенных предикатов
    % (список, число сдвигов, сдвинутый список)

    rSlider(N, L0, L3) :-
    appendList(L1, L2, N),
    lengthList(L2, L0),
    appendList(L2, L1, L3), !.


   
% 1.2
% предикат 4) вычисление минимального элемента

    % с использованием встроенных придикатов
    % (список, минимальный элемент)
     
    min_list([MinElem], MinElem):-!.
    min_list([Head|Tail], MinElem):-
    min_list(Tail, TailMinElem),
    TailMinElem < Head, !, MinElem = TailMinElem;
    MinElem = Head.  

    % без использования встроенных предикатов
    % (список, минимальный элемент)
    
    minList([Head|Tail],Result):-
    minList(Tail,Result),Result<Head,!.
    minList([Head|_],Head).

    % пример совместного использования предикатов
    % (список, число сдвигов, результат сдвига, минимальный элемент списка)

    pred1(X,S,Res,M):-
    rSlider(X,S,M),
    minList(M,Res).

