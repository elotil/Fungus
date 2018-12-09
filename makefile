CC = g++
CFLAGS = -g -c -Wall -std=c++11
OBJ = main.o Spore.o Hypha.o Controller.o
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

Fungus: $(OBJ)
	$(CC) $(OBJ) -o Fungus

run:
	make Fungus
	./Fungus

main.o: Controller.h Spore.h Hypha.h

Spore.o: Controller.h

Hypha.o: Controller.h

Controller.o: Controller.h

clean:
	rm $(OBJ) Fungus
