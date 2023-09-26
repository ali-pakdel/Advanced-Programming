all: Goodreads.out

Goodreads.out: main.o GoodReads.o User.o Author.o Book.o Functions.o Review.o 
	g++ -std=c++11 main.o GoodReads.o User.o Author.o Book.o Functions.o Review.o   -o Goodreads.out

main.o: main.cpp GoodReads.hpp Functions.hpp
	g++ -std=c++11 -c main.cpp

GoodReads.o: GoodReads.cpp GoodReads.hpp Author.hpp Book.hpp User.hpp Review.hpp
	g++ -std=c++11 -c GoodReads.cpp

User.o: User.cpp User.hpp Book.hpp Review.hpp
	g++ -std=c++11 -c User.cpp

Author.o: Author.cpp Author.hpp Book.hpp Review.hpp
	g++ -std=c++11 -c Author.cpp

Book.o: Book.cpp Book.hpp Review.hpp 
	g++ -std=c++11 -c Book.cpp

Functions.o: Functions.cpp Functions.hpp 
	g++ -std=c++11 -c Functions.cpp

Review.o: Review.cpp Review.hpp
	g++ -std=c++11 -c Review.cpp



