domains
    list = integer*
predicates
    member(integer, list)
    insert(integer, list, list)
    intersect(list, list, list)
clauses
    member(Elem, [Elem | _ ]) :- !.
    member(Elem, [ _ | List]) :- member(Elem, List).
    
    insert(X, List, Res) :- member(X, List), !, Res = List ; Res = [X | List].

    intersect([X], [], [X]).
    intersect([X | L1_rem], [], Res) :- intersect(L1_rem, [], Res2),
                                        insert(X, Res2, Res).
    intersect([], L2, Res) :- intersect(L2, [], Res).
    
    intersect([X | L1_rem], L2, Res) :- intersect(L1_rem, L2, Res2),
                                        insert(X, Res2, Res).