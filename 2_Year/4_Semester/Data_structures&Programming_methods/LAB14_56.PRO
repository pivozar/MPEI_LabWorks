domains
    file=data
predicates
    ReadItem(integer)
    ReadList(file)
clauses
    ReadItem(F):- write("Enter Num:"), nl,
                  readint(F).
    ReadList(data):- ReadItem(F), writedevice(data),
                     write(F), nl, writedevice(screen),
                     write("Another one?(y/n)"), nl,
                     readchar(Ans), Ans='y',
                     ReadList(data).
    ReadList(data):- write("________"), nl,
                     write("Output over. File: integers.dat").
goal
    openwrite(data, "integers.dat"),
    writedevice(data),
    writedevice(screen),
    ReadList(data),
    closefile(data)