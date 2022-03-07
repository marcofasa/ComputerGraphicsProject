CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A03 run clean
A03: Assignment03.cpp
	if [ -a A03 ]; then rm A03; fi;
	g++ $(CFLAGS) $(INC) -o A03 Assignment03.cpp $(LDFLAGS)


run: A03
	./A03

clean:
	rm -f A03