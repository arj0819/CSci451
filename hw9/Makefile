all: producer1 producer2 producer3 sampler semaphoreResetter
producer1:
	g++ -std=c++11 producer1.cpp -l pthread -o producer1
producer2:
	g++ -std=c++11 producer2.cpp -l pthread -o producer2
producer3:
	g++ -std=c++11 producer3.cpp -l pthread -o producer3
sampler:
	g++ -std=c++11 sampler.cpp -l pthread -o sampler
semaphoreResetter:
	g++ -std=c++11 resetSemaphores.cpp -l pthread -o resetSemaphores

run: runProducer1 runProducer2 runProducer3 runSampler
runProducer1:
	./producer1
runProducer2:
	./producer2
runProducer3:
	./producer3
runSampler:
	./sampler

clean: resetSemaphores cleanAll
resetSemaphores:
	./resetSemaphores
cleanAll:
	rm producer1 producer2 producer3 sampler resetSemaphores
