CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A13 run clean
A13: Assignment13.cpp
	if [ -a A13 ]; then rm A13; fi;
	g++ $(CFLAGS) $(INC) -o A13 Assignment13.cpp $(LDFLAGS)


run: A13
	./A13

clean:
	rm -f A13