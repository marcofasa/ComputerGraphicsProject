CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A20 run clean
A20: Assignment20.cpp
	if [ -a A20 ]; then rm A20; fi;
	g++ $(CFLAGS) $(INC) -o A20 Assignment20.cpp $(LDFLAGS)

run: A20
	./A20

clean:
	rm -f A20

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.vert -o $(SHADER_FOLDER)/BRDFVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.frag -o $(SHADER_FOLDER)/BRDFFrag.spv
