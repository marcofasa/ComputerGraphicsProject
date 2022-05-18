CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A18 run clean
A18: Assignment18.cpp
	if [ -a A18 ]; then rm A18; fi;
	g++ $(CFLAGS) $(INC) -o A18 Assignment18.cpp $(LDFLAGS)

run: A18
	./A18

clean:
	rm -f A18

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.vert -o $(SHADER_FOLDER)/BRDFVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.frag -o $(SHADER_FOLDER)/BRDFFrag.spv
