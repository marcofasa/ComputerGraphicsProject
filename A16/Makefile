CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A16 run clean
A16: Assignment16.cpp
	if [ -a A16 ]; then rm A16; fi;
	g++ $(CFLAGS) $(INC) -o A16 Assignment16.cpp $(LDFLAGS)

run: A16
	./A16

clean:
	rm -f A16

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.frag -o $(SHADER_FOLDER)/BRDFFrag.spv
