CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A10 run clean
A10: Assignment10.cpp
	if [ -a A10 ]; then rm A10; fi;
	g++ $(CFLAGS) $(INC) -o A10 Assignment10.cpp $(LDFLAGS)


run: A10
	./A10

clean:
	rm -f A10