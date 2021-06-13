Predicates
    gcd(integer, integer, integer)
    lcm(integer, integer, integer)
    fib(integer, integer)
    sumsquares(integer, integer, integer)
Clauses
    gcd(X, Y, Res) :- X = Y, Res = X, !.
    gcd(X, Y, Res) :- X = 0 ; Y = 0, Res = X + Y, !.
    gcd(X, Y, Res) :- X > Y,
    		      X1 = X mod Y,
    		      gcd(Y, X1, Res1),
    		      Res = Res1, !.
    gcd(X, Y, Res) :- X < Y,
    		      Y1 = Y mod X,
    		      gcd(X, Y1, Res1),
    		      Res = Res1, !.
    lcm(X, Y, Res) :- gcd(X, Y, Gcd),
    		      Res = X * Y / Gcd, !.

    fib(1, 1) :- !.
    fib(2, 2) :- !.
    fib(N, Res) :- N1 = N - 1,
                   N2 = N - 2,
                   fib(N1, R1),
                   fib(N2, R2),
                   Res = R1 + R2.

    sumsquares(M, N, Sum):- M = N, Sum = M*M, !.
    sumsquares(M, N, Sum):- M < N,
    			    M1 = M + 1,
    			    sumsquares(M1, N, Sum1),
    			    Sum = Sum1 + M*M, !.
