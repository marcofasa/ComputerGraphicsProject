CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A09 run clean
A09: Assignment09.cpp
	if [ -a A09 ]; then rm A09; fi;
	g++ $(CFLAGS) $(INC) -o A09 Assignment09.cpp $(LDFLAGS)


run: A09
	./A09

clean:
	rm -f A09