CC := g++ -std=c++11

obj_files = main.o UTrip.o Hotel.o Functions.o User.o Room.o Rating.o CityFilter.o StarPeriodFilter.o AvgPriceFilter.o RoomFilter.o DefaultPriceFilter.o

all = utrip.out

utrip.out: ${obj_files}
	${CC} ${obj_files} -o utrip.out

main.o: Functions.hpp UTrip.hpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp User.hpp NotFound.hpp NotEnoughCredit.hpp NoRating.hpp Filter.hpp Defines.hpp
	${CC} -c main.cpp -o main.o

UTrip.o: UTrip.hpp UTrip.cpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp User.hpp NotEnoughCredit.hpp CityFilter.hpp RoomFilter.hpp AvgPriceFilter.hpp StarPeriodFilter.hpp DefaultPriceFilter.hpp BadRequest.hpp NotFound.hpp PermissionDenied.hpp NotEnoughRoom.hpp InsufficientRatings.hpp Filter.hpp Defines.hpp
	${CC} -c UTrip.cpp -o UTrip.o

Hotel.o: Hotel.hpp Hotel.cpp NoRating.hpp Room.hpp Comment.hpp Rating.hpp Defines.hpp
	${CC} -c Hotel.cpp -o Hotel.o

User.o: User.hpp User.cpp Room.hpp NotEnoughCredit.hpp NotFound.hpp Defines.hpp
	${CC} -c User.cpp -o User.o

Room.o: Room.hpp Room.cpp Defines.hpp
	${CC} -c Room.cpp -o Room.o

Rating.o: Rating.hpp Rating.cpp Defines.hpp
	${CC} -c Rating.cpp -o Rating.o

CityFilter.o: CityFilter.hpp CityFilter.cpp Filter.hpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp Defines.hpp
	${CC} -c CityFilter.cpp -o CityFilter.o

StarPeriodFilter.o: StarPeriodFilter.hpp StarPeriodFilter.cpp Filter.hpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp Defines.hpp 
	${CC} -c StarPeriodFilter.cpp -o StarPeriodFilter.o

AvgPriceFilter.o: AvgPriceFilter.hpp AvgPriceFilter.cpp Filter.hpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp Defines.hpp
	${CC} -c AvgPriceFilter.cpp -o AvgPriceFilter.o

DefaultPriceFilter.o: DefaultPriceFilter.hpp DefaultPriceFilter.cpp Filter.hpp Hotel.hpp Room.hpp Comment.hpp Room.hpp Defines.hpp
	${CC} -c DefaultPriceFilter.cpp -o DefaultPriceFilter.o

RoomFilter.o: RoomFilter.hpp RoomFilter.cpp Filter.hpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp Defines.hpp
	${CC} -c RoomFilter.cpp -o RoomFilter.o

Functions.o: Functions.hpp Functions.cpp UTrip.hpp Hotel.hpp Room.hpp Comment.hpp Rating.hpp User.hpp NotEnoughCredit.hpp Filter.hpp BadRequest.hpp NotFound.hpp PermissionDenied.hpp Defines.hpp
	${CC} -c Functions.cpp -o Functions.o
