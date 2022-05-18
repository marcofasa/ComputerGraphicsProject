CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A19 run clean
A19: Assignment19.cpp
	if [ -a A19 ]; then rm A19; fi;
	g++ $(CFLAGS) $(INC) -o A19 Assignment19.cpp $(LDFLAGS)

run: A19
	./A19

clean:
	rm -f A19

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.vert -o $(SHADER_FOLDER)/BRDFVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/BRDFShader.frag -o $(SHADER_FOLDER)/BRDFFrag.spv
