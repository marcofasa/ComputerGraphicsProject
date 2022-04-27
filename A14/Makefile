CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A14 run clean
A14: Assignment14.cpp
	if [ -a A14 ]; then rm A14; fi;
	g++ $(CFLAGS) $(INC) -o A14 Assignment14.cpp $(LDFLAGS)


run: A14
	./A14

clean:
	rm -f A14