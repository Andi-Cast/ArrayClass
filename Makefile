Array: Array.o driver.o
	g++ Array.o driver.o -o Array

Array.o: Array.cpp
	g++ -c Array.cpp

driver.o: driver.cpp
	g++ -c driver.cpp

clean:
	rm *.o Array

run: Array
	./Array

	