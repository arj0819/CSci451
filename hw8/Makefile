all: program1 program2 program3
program1:
	g++ -std=c++11 program1.cpp -o program1
program2:
	g++ -std=c++11 program2.cpp -o program2
program3:
	g++ -std=c++11 program3.cpp -o program3

run: runProgram1 runProgram2 runProgram3
runProgram1:
	./program1
runProgram2:
	./program2
runProgram3:
	./program3

clean:
	rm program1 program2 program3 temp*.data shared*.dat