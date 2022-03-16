CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A05 run clean
A05: Assignment05.cpp
	if [ -a A05 ]; then rm A05; fi;
	g++ $(CFLAGS) $(INC) -o A05 Assignment05.cpp $(LDFLAGS)


run: A05
	./A05

clean:
	rm -f A05