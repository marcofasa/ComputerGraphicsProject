CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A07 run clean
A07: Assignment07.cpp
	if [ -a A07 ]; then rm A07; fi;
	g++ $(CFLAGS) $(INC) -o A07 Assignment07.cpp $(LDFLAGS)


run: A07
	./A07

clean:
	rm -f A07