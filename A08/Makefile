CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A08 run clean
A08: Assignment08.cpp
	if [ -a A08 ]; then rm A08; fi;
	g++ $(CFLAGS) $(INC) -o A08 Assignment08.cpp $(LDFLAGS)


run: A08
	./A08

clean:
	rm -f A08