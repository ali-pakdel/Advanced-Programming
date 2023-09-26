CC := g++ -std=c++11

obj_files = main.o Messenger.o Channel.o Functions.o Echo.o Fred.o Librarian.o Logger.o

all = 2.out

2.out: ${obj_files}
	${CC} ${obj_files} -o 2.out

main.o: Messenger.hpp Functions.hpp Channel.hpp Observer.hpp Defines.hpp
	${CC} -c main.cpp -o main.o

Messenger.o: Messenger.hpp Messenger.cpp Channel.hpp Observer.hpp Echo.hpp Logger.hpp Fred.hpp Librarian.hpp AlreadyExist.hpp DoesNotExist.hpp Invalid.hpp Defines.hpp
	${CC} -c Messenger.cpp -o Messenger.o

Channel.o: Channel.hpp Channel.cpp Observer.hpp Defines.hpp
	${CC} -c Channel.cpp -o Channel.o

Functions.o: Functions.hpp Functions.cpp Messenger.hpp Channel.hpp Observer.hpp Defines.hpp
	${CC} -c Functions.cpp -o Functions.o

Echo.o: Echo.hpp Echo.cpp Observer.hpp Defines.hpp Channel.hpp
	${CC} -c Echo.cpp -o Echo.o

Fred.o: Fred.hpp Fred.cpp Observer.hpp Defines.hpp Channel.hpp
	${CC} -c Fred.cpp -o Fred.o

Librarian.o: Librarian.hpp Librarian.cpp Observer.hpp Defines.hpp Channel.hpp
	${CC} -c Librarian.cpp -o Librarian.o

Logger.o: Logger.hpp Logger.cpp Observer.hpp Channel.hpp Defines.hpp
	${CC} -c Logger.cpp -o Logger.o