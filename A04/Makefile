CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A04 run clean
A04: Assignment04.cpp
	if [ -a A04 ]; then rm A04; fi;
	g++ $(CFLAGS) $(INC) -o A04 Assignment04.cpp $(LDFLAGS)


run: A04
	./A04

clean:
	rm -f A04