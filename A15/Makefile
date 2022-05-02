CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A15 run clean
A15: Assignment15.cpp
	if [ -a A15 ]; then rm A15; fi;
	g++ $(CFLAGS) $(INC) -o A15 Assignment15.cpp $(LDFLAGS)

run: A15
	./A15

clean:
	rm -f A15

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/PhongShader.frag -o $(SHADER_FOLDER)/PhongFrag.spv
