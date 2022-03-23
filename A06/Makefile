CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A06 run clean
A06: Assignment06.cpp
	if [ -a A06 ]; then rm A06; fi;
	g++ $(CFLAGS) $(INC) -o A06 Assignment06.cpp $(LDFLAGS)


run: A06
	./A06

clean:
	rm -f A06