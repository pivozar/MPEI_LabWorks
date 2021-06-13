domains
    list = integer*

predicates
    palin(list)
    _palin(list, list)
    last(list, integer)
    sum_and_len(list, integer, integer)
    max(list, integer)

clauses
    palin(List):-_palin(List, []).
    _palin(List, List).
    _palin([_ | Tail], Tail).
    _palin([Head | Tail], Other):-_palin(Tail, [Head | Other]).
    
    last([X], X).
    last([Head | Tail], Res):- last(Tail, Res).
    
    sum_and_len([], Sum, Len):- Sum=0,
    				Len=0, !.
    sum_and_len([Head | Tail], Sum, Len):- sum_and_len(Tail, Sum2, Len2),
    					   Sum = Sum2 + Head,
    					   Len = Len2 + 1, !.
    max([X], X).
    max([Head | Tail], Head) :- max(Tail, Max2),
    			        Head > Max2, !.
    max([_ | Tail], Max) :- max(Tail, Max).
    