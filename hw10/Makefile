all: master program1 program2 program3 reset
master:
	g++ -std=c++11 master.cpp -o master -l pthread
program1:
	g++ -std=c++11 program1.cpp -o program1 -l pthread
program2:
	g++ -std=c++11 program2.cpp -o program2 -l pthread
program3:
	g++ -std=c++11 program3.cpp -o program3 -l pthread
reset:
	g++ -std=c++11 resetSemaphores.cpp -o reset -l pthread 

run: runMaster runReset
runMaster:
	./master input.data temp3.data
runProgram1:
	./program1
runProgram2:
	./program2
runProgram3:
	./program3
runReset:
	./reset

clean:
	rm master program1 program2 program3