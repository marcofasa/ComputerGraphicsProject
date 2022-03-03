CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A02 run clean
A02: Assignment02.cpp
	if [ -a A01 ]; then rm A02; fi;
	g++ $(CFLAGS) $(INC) -o A02 Assignment02.cpp $(LDFLAGS)


run: A02
	./A02

clean:
	rm -f A02