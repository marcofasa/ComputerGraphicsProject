CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A01 run clean
A01: Assignment01.cpp
	if [ -a A01 ]; then rm A01; fi;
	g++ $(CFLAGS) $(INC) -o A01 Assignment01.cpp $(LDFLAGS)


run: A01
	./A01

clean:
	rm -f A01