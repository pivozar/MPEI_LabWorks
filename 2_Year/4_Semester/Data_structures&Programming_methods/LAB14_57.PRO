domains
    file=data; dataPos; dataNeg
predicates
    PrepareFile(file)
    Prepare;
    Sort(file, file, file)
    ReadItem(integer, file)
    WriteNum(integer, file, file)
clauses
    PrepareFile(Data):- writedevice(Data),
                             writedevice(screen).
    ReadItem(F, In):- readdevice(In),
                      not(eof(In)),
                      readint(F),
                      readdevice(keyboard),!.
    Sort(In, DataPos, DataNeg):- ReadItem(F,In),
                                 WriteNum(F,dataPos,dataNeg),
                                 Sort(In, dataPos, dataNeg).
    WriteNum(F, DataPos, DataNeg):- F>0, writedevice(dataPos),
                                   write(F), nl,
                                   writedevice(screen),!.
    WriteNum(F, DataPos, DataNeg):- F<0, writedevice(dataNeg),
                                   write(F), nl,
                                   writedevice(screen),!.
    Prepare():- openread(data,"integers.dat"),
                readdevice(data),
                readdevice(keyboard),
                openwrite(dataPos,"DataPos.dat"),
                openwrite(dataNeg,"DataNeg.dat"),
                PrepareFile(dataPos),
                PrepareFile(dataNeg).
goal
    Prepare(),
    Sort(data,dataPos,dataNeg),
    closefile(data),
    closefile(dataPos),
    closefile(dataNeg)