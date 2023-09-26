CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
Obj_files = main.o Functions.o Fieldrunners.o rsdl.o Tower.o Enemy.o Missile.o Glue.o Gatling.o Tesla.o Bullet.o TheRunner.o StubbornRunner.o SuperTrooper.o Scrambler.o 

all: FieldRunners.out

FieldRunners.out: ${Obj_files}
	$(CC) ${Obj_files} $(CCFLAGS) -o FieldRunners.out

main.o: rsdl.hpp main.cpp Fieldrunners.hpp Functions.hpp Tower.hpp Enemy.hpp Bullet.hpp
	$(CC) -c main.cpp -o main.o

Functions.o: Functions.cpp Functions.hpp TheRunner.hpp Fieldrunners.hpp StubbornRunner.hpp SuperTrooper.hpp Scrambler.hpp Gatling.hpp Missile.hpp Tesla.hpp Glue.hpp Tower.hpp Enemy.hpp Bullet.hpp rsdl.hpp
	$(CC) -c Functions.cpp -o Functions.o

Fieldrunners.o: Fieldrunners.cpp TheRunner.hpp StubbornRunner.hpp SuperTrooper.hpp Scrambler.hpp Gatling.hpp Missile.hpp Tesla.hpp Glue.hpp Fieldrunners.hpp Tower.hpp Enemy.hpp Bullet.hpp rsdl.hpp 
	$(CC) -c Fieldrunners.cpp -o Fieldrunners.o

Gatling.o: Gatling.cpp Gatling.hpp Tower.hpp rsdl.hpp Enemy.hpp Bullet.hpp
	$(CC) -c Gatling.cpp -o Gatling.o

Tesla.o: Tesla.cpp Tesla.hpp Tower.hpp rsdl.hpp Enemy.hpp Bullet.hpp
	$(CC) -c Tesla.cpp -o Tesla.o

Missile.o: Missile.cpp Missile.hpp Tower.hpp rsdl.hpp Enemy.hpp Bullet.hpp
	$(CC) -c Missile.cpp -o Missile.o

Glue.o: Glue.cpp Glue.hpp Tower.hpp rsdl.hpp Enemy.hpp Bullet.hpp
	$(CC) -c Glue.cpp -o Glue.o

Tower.o: Tower.cpp Tower.hpp Bullet.hpp Enemy.hpp rsdl.hpp
	$(CC) -c Tower.cpp -o Tower.o

TheRunner.o: TheRunner.cpp TheRunner.hpp Enemy.hpp rsdl.hpp
	$(CC) -c TheRunner.cpp -o TheRunner.o

StubbornRunner.o: StubbornRunner.cpp StubbornRunner.hpp Enemy.hpp rsdl.hpp
	$(CC) -c StubbornRunner.cpp -o StubbornRunner.o

SuperTrooper.o: SuperTrooper.cpp SuperTrooper.hpp Enemy.hpp rsdl.hpp
	$(CC) -c SuperTrooper.cpp -o SuperTrooper.o

Scrambler.o: Scrambler.cpp Scrambler.hpp Enemy.hpp rsdl.hpp
	$(CC) -c Scrambler.cpp -o Scrambler.o

Enemy.o: Enemy.cpp Enemy.hpp rsdl.hpp
	$(CC) -c Enemy.cpp -o Enemy.o

rsdl.o: rsdl.cpp rsdl.hpp
	$(CC) -c rsdl.cpp -o rsdl.o

Bullet.o: Bullet.cpp Bullet.hpp Enemy.hpp rsdl.hpp
	$(CC) -c Bullet.cpp -o Bullet.o