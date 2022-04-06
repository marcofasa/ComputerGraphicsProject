CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread
.PHONY: A10 run clean
A10: Assignment10.cpp
	if [ -a A10 ]; then rm A10; fi;
	g++ $(CFLAGS) $(INC) -o A10 Assignment10.cpp $(LDFLAGS)


run: A10
	./A10

clean:
	rm -f A10

shader:
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/PBRShader.vert -o shaders/PBRVert.spv
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/PBRShader.frag -o shaders/PBRFrag.spv
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/SkyBoxShader.vert -o shaders/SkyBoxVert.spv
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/SkyBoxShader.frag -o shaders/SkyBoxFrag.spv

alternativeShader:
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/Assignment10altVersions/PBRShader.vert -o shaders/Assignment10altVersions/PBRVert.spv
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/Assignment10altVersions/PBRShader.frag -o shaders/Assignment10altVersions/PBRFrag.spv
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/Assignment10altVersions/SkyBoxShader.vert -o shaders/Assignment10altVersions/SkyBoxVert.spv
	/Users/fasa/VulkanSDK/1.3.204.0/macOS/bin/glslc shaders/Assignment10altVersions/SkyBoxShader.frag -o shaders/Assignment10altVersions/SkyBoxFrag.spv