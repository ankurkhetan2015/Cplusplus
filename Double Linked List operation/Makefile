all: Main Minmain

Main: DoublyLinkedList.o Main.o
	g++ -std=c++11 DoublyLinkedList.o Main.o -o Main
	
Minmain: main2.cpp part2.h
	g++ -std=c++11 DoublyLinkedList.o main2.cpp -o Minmain

DoublyLinkedList.o: DoublyLinkedList.cpp DoublyLinkedList.h
	g++ -std=c++11 -c DoublyLinkedList.cpp

Main.o: Main.cpp DoublyLinkedList.h
	g++ -std=c++11 -c Main.cpp

clean:
	rm *.o Main