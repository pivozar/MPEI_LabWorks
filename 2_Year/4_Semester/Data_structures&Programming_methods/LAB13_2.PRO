constants
	library = [book("book1", "Author1", 40), book("book2", "Author2", 60), book("book3", "Author1", 50), book("book4", "Author2", 30)]

domains
	Name, Author = string
	Pages, Book_size = integer
	lib_record = book(Name, Author, Pages)
	lib = lib_record*
	author_ = author(Author, Book_size)
	alist = author_*

predicates
	findt(integer, alist)
	find(lib, integer, alist)

clauses
	search(Set_pages, Res):- find(library, Set_pages, Res2), Res = Res2, !.
	
	find([], Set_pages, Author_list):- Author_list = [], !.
	find([book(NAme, AUthor, PAges) | Lib_left], Set_pages, [author(AUthor, 1) | AUthor_list]) :- PAges >= Set_pages,
																									find(Lib_left, Set_pages, AUthor_list).
	find([book(NAme, AUthor, PAges) | Lib_left], Set_pages, AUthor_list) :- PAges < Set_pages, find(Lib_left, Set_pages, AUthor_list).