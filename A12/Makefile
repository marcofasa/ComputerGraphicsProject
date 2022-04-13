CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A12 run clean
A12: Assignment12.cpp
	if [ -a A12 ]; then rm A12; fi;
	g++ $(CFLAGS) $(INC) -o A12 Assignment12.cpp $(LDFLAGS)


run: A12
	./A12

clean:
	rm -f A12