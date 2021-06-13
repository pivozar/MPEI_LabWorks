domains
    list = integer*
    stringlist = string*
predicates
    pred(integer)
    findlist(integer, list, list)
    findlist_if(list, list)

    noun(string)
    adj(string)
    verb(string)
    rule(string, string)
    analysis(stringlist)

clauses
    noun("avtomobil").
    noun("stol").
    noun("victor").
    noun("on").

    adj("bystriy").
    adj("kholodniy").
    adj("priyatniy").
    adj("zeleniy").

    verb("bejit").
    verb("gorit").
    verb("molchit").
    verb("smotrit").

    pred(X) :- X < 0.

    findlist(_, [], []).
    findlist(Obj, [Head | Tail], [Head | Res]) :- Obj < Head, findlist(Obj, Tail, Res).
    findlist(Obj, [Head | Tail], Res) :- findlist(Obj, Tail, Res), !.

    findlist_if([], []).
    findlist_if([Head | Tail], [Head | Res]) :- pred(Head), findlist_if(Tail, Res).
    findlist_if([Head | Tail], Res) :- findlist_if(Tail, Res), !.

    rule(W1, W2) :- adj(W1), adj(W2).
    rule(W1, W2) :- adj(W1), noun(W2).
    rule(W1, W2) :- noun(W1), verb(W2).

    analysis([]).
    analysis([Word]) :- verb(Word).
    analysis([W1, W2 | Sent]) :- rule(W1, W2), analysis([W2 | Sent]). 