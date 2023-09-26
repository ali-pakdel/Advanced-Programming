CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/UTrip.o: codes/UTrip.cpp codes/UTrip.hpp codes/Hotel.hpp codes/User.hpp codes/Room.hpp codes/Rating.hpp codes/Comment.hpp codes/User.hpp codes/Filter.hpp codes/CityFilter.hpp codes/RoomFilter.hpp codes/AvgPriceFilter.hpp codes/StarPeriodFilter.hpp codes/DefaultPriceFilter.hpp codes/NotFound.hpp codes/NotEnoughCredit.hpp codes/BadRequest.hpp codes/NotFound.hpp codes/PermissionDenied.hpp codes/NotEnoughRoom.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/UTrip.cpp -o $(BUILD_DIR)/UTrip.o

$(BUILD_DIR)/Hotel.o: codes/Hotel.cpp codes/Hotel.hpp codes/Room.hpp codes/Rating.hpp codes/Comment.hpp codes/NoRating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/User.o: codes/User.cpp codes/User.hpp codes/Room.hpp codes/NotFound.hpp codes/NotEnoughCredit.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Room.o: codes/Room.cpp codes/Room.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/Rating.o: codes/Rating.cpp codes/Rating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/Rating.cpp -o $(BUILD_DIR)/Rating.o

$(BUILD_DIR)/Functions.o: codes/Functions.cpp codes/Functions.hpp codes/UTrip.hpp codes/Hotel.hpp codes/Rating.hpp codes/Comment.hpp codes/User.hpp codes/Room.hpp codes/NotEnoughCredit.hpp codes/NotFound.hpp codes/Filter.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/Functions.cpp -o $(BUILD_DIR)/Functions.o

$(BUILD_DIR)/CityFilter.o: codes/CityFilter.cpp codes/CityFilter.hpp codes/Filter.hpp codes/Hotel.hpp codes/Room.hpp codes/Comment.hpp codes/Rating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/CityFilter.cpp -o $(BUILD_DIR)/CityFilter.o

$(BUILD_DIR)/StarPeriodFilter.o: codes/StarPeriodFilter.cpp codes/StarPeriodFilter.hpp codes/Filter.hpp codes/Hotel.hpp codes/Room.hpp codes/Comment.hpp codes/Rating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/StarPeriodFilter.cpp -o $(BUILD_DIR)/StarPeriodFilter.o

$(BUILD_DIR)/AvgPriceFilter.o: codes/AvgPriceFilter.cpp codes/AvgPriceFilter.hpp codes/Filter.hpp codes/Hotel.hpp codes/Room.hpp codes/Comment.hpp codes/Rating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/AvgPriceFilter.cpp -o $(BUILD_DIR)/AvgPriceFilter.o

$(BUILD_DIR)/RoomFilter.o: codes/RoomFilter.cpp codes/RoomFilter.hpp codes/Filter.hpp codes/Hotel.hpp codes/Room.hpp codes/Comment.hpp codes/Rating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/RoomFilter.cpp -o $(BUILD_DIR)/RoomFilter.o

$(BUILD_DIR)/DefaultPriceFilter.o: codes/DefaultPriceFilter.cpp codes/DefaultPriceFilter.hpp codes/Filter.hpp codes/Hotel.hpp codes/Room.hpp codes/Comment.hpp codes/Rating.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/DefaultPriceFilter.cpp -o $(BUILD_DIR)/DefaultPriceFilter.o

$(BUILD_DIR)/main.o: codes/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp server/server.hpp codes/Functions.hpp codes/UTrip.hpp codes/Hotel.hpp codes/Room.hpp codes/Comment.hpp codes/Rating.hpp codes/User.hpp codes/NotEnoughCredit.hpp codes/NotFound.hpp codes/Filter.hpp codes/Defines.hpp
	$(CC) $(CF) -c codes/main.cpp -o $(BUILD_DIR)/main.o
	
$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o
	
$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/LoginAndLogoutHandler.o: codes/LoginAndLogoutHandler.hpp codes/LoginAndLogoutHandler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp codes/UTrip.hpp
	$(CC) $(CF) -c codes/LoginAndLogoutHandler.cpp -o $(BUILD_DIR)/LoginAndLogoutHandler.o

$(BUILD_DIR)/SignupHandler.o: codes/SignupHandler.hpp codes/LoginAndLogoutHandler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp codes/UTrip.hpp
	$(CC) $(CF) -c codes/SignupHandler.cpp -o $(BUILD_DIR)/SignupHandler.o

$(BUILD_DIR)/HomePageHandler.o: codes/HomePageHandler.hpp codes/HomePageHandler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp codes/UTrip.hpp
	$(CC) $(CF) -c codes/HomePageHandler.cpp -o $(BUILD_DIR)/HomePageHandler.o

$(BUILD_DIR)/HotelDetailsHandler.o: codes/HotelDetailsHandler.hpp codes/HotelDetailsHandler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp codes/UTrip.hpp
	$(CC) $(CF) -c codes/HotelDetailsHandler.cpp -o $(BUILD_DIR)/HotelDetailsHandler.o

$(BUILD_DIR)/FinancialHandler.o: codes/FinancialHandler.hpp codes/FinancialHandler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp codes/UTrip.hpp
	$(CC) $(CF) -c codes/FinancialHandler.cpp -o $(BUILD_DIR)/FinancialHandler.o

myserver.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/LoginAndLogoutHandler.o $(BUILD_DIR)/SignupHandler.o $(BUILD_DIR)/HomePageHandler.o $(BUILD_DIR)/HotelDetailsHandler.o $(BUILD_DIR)/FinancialHandler.o $(BUILD_DIR)/UTrip.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Functions.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Rating.o $(BUILD_DIR)/CityFilter.o $(BUILD_DIR)/StarPeriodFilter.o $(BUILD_DIR)/AvgPriceFilter.o $(BUILD_DIR)/RoomFilter.o $(BUILD_DIR)/DefaultPriceFilter.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/LoginAndLogoutHandler.o $(BUILD_DIR)/SignupHandler.o $(BUILD_DIR)/HomePageHandler.o $(BUILD_DIR)/HotelDetailsHandler.o $(BUILD_DIR)/FinancialHandler.o $(BUILD_DIR)/UTrip.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Functions.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Rating.o $(BUILD_DIR)/CityFilter.o $(BUILD_DIR)/StarPeriodFilter.o $(BUILD_DIR)/AvgPriceFilter.o $(BUILD_DIR)/RoomFilter.o $(BUILD_DIR)/DefaultPriceFilter.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
