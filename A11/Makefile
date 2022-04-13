CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A11 run
A11: Assignment11.cpp
	if [ -a A11 ]; then rm A11; fi;
	g++ $(CFLAGS) $(INC) -o A11 Assignment11.cpp $(LDFLAGS)


run: A11
	./A11

clean:
	rm -f A11

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.frag -o $(SHADER_FOLDER)/Frag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.vert -o $(SHADER_FOLDER)/Vert.spv

