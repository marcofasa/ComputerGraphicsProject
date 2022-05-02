CFLAGS = -std=c++17 -O2
INC=-I./headers
GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
SHADER_FOLDER = ./shaders
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: shader A10 run clean
A10: Assignment10.cpp
	if [ -a A10 ]; then rm A10; fi;
	g++ $(CFLAGS) $(INC) -o A10 Assignment10.cpp $(LDFLAGS)


run: A10
	./A10

clean:
	rm -f A10

shader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/PBRShader.frag -o $(SHADER_FOLDER)/PBRFrag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/PBRShader.vert -o $(SHADER_FOLDER)/PBRVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/SkyBoxShader.frag -o $(SHADER_FOLDER)/SkyBoxFrag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/SkyBoxShader.vert -o $(SHADER_FOLDER)/SkyBoxVert.spv


alternativeShader:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Assignment10altVersions/PBRShader.vert -o $(SHADER_FOLDER)/Assignment10altVersions/PBRVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Assignment10altVersions/PBRShader.frag -o $(SHADER_FOLDER)/Assignment10altVersions/PBRFrag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Assignment10altVersions/SkyBoxShader.vert -o $(SHADER_FOLDER)/Assignment10altVersions/SkyBoxVert.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Assignment10altVersions/SkyBoxShader.frag -o $(SHADER_FOLDER)/Assignment10altVersions/SkyBoxFrag.spv