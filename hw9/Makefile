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

run:
	./producer1 & ./producer2 & ./producer3 & ./sampler

stop: resetSemaphores killProducers

clean: resetSemaphores killProducers cleanAll
resetSemaphores:
	./resetSemaphores
cleanAll:
	rm producer1 producer2 producer3 sampler resetSemaphores output*.txt
	
killProducers: killP1 killP2 killP3
killP1:
	pkill producer1 || true
killP2:
	pkill producer2 || true
killP3:
	pkill producer3 || true
