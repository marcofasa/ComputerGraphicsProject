CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A17 run clean
A17: Assignment17.cpp
	if [ -a A17 ]; then rm A17; fi;
	g++ $(CFLAGS) $(INC) -o A17 Assignment17.cpp $(LDFLAGS)

run: A17
	./A17

clean:
	rm -f A17

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.vert -o $(SHADER_FOLDER)/BRDFVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.frag -o $(SHADER_FOLDER)/BRDFFrag.spv
