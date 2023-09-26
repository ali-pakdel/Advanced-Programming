CC := g++ -std=c++11

obj_files = main.o JsonBuilder.o Data.o Container.o Object.o Array.o IntegerVariable.o StringVariable.o IntegerValue.o StringValue.o

all = 1.out

Json.out: ${obj_files}
	${CC} ${obj_files} -o 1.out

main.o: JsonBuilder.hpp Data.hpp Defines.hpp
	${CC} -c main.cpp -o main.o

JsonBuilder.o: JsonBuilder.cpp JsonBuilder.hpp Data.hpp Container.hpp Variable.hpp Array.hpp Object.hpp IntegerVariable.hpp StringVariable.hpp Defines.hpp
	${CC} -c JsonBuilder.cpp -o JsonBuilder.o

Data.o: Data.hpp Data.cpp Defines.hpp
	${CC} -c Data.cpp -o Data.o

Container.o: Container.hpp Container.cpp Data.hpp Defines.hpp
	${CC} -c Container.cpp -o Container.o

Array.o: Array.hpp Array.cpp Container.hpp Data.hpp Defines.hpp
	${CC} -c Array.cpp -o Array.o

Object.o: Object.hpp Object.cpp Container.hpp Data.hpp Defines.hpp
	${CC} -c Object.cpp -o Object.o

IntegerVariable.o: IntegerVariable.hpp IntegerVariable.cpp Variable.hpp Data.hpp Defines.hpp
	${CC} -c IntegerVariable.cpp -o IntegerVariable.o

StringVariable.o: StringVariable.hpp StringVariable.cpp Variable.hpp Data.hpp Defines.hpp
	${CC} -c StringVariable.cpp -o StringVariable.o

IntegerValue.o: IntegerValue.hpp IntegerValue.cpp Value.hpp Data.hpp Defines.hpp
	${CC} -c IntegerValue.cpp -o IntegerValue.o

StringValue.o: StringValue.hpp StringValue.cpp Value.hpp Data.hpp Defines.hpp
	${CC} -c StringValue.cpp -o StringValue.o