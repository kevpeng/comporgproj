default: 
	g++ main.cpp -o processor

o: 
	vim -p RegisterFile.cpp Control.cpp Simulate.cpp main.cpp

clean:
	rm processor
	rm a.out
