all: master program1 program2 program3
master:
	g++ -std=c++11 master.cpp -o master -l pthread
program1:
	g++ -std=c++11 program1.cpp -o program1 -l pthread
program2:
	g++ -std=c++11 program2.cpp -o program2 -l pthread
program3:
	g++ -std=c++11 program3.cpp -o program3 -l pthread

run: runMaster #runProgram1 runProgram2 runProgram3
runMaster:
	./master input.data temp3.data
runProgram1:
	./program1
runProgram2:
	./program2
runProgram3:
	./program3

clean:
	rm master program1 program2 program3 shared*.dat