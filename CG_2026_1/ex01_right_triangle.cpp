//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//// GLSL source code for the vertex shader
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//// GLSL source code for the fragment shader
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
//// Window dimensions
//const unsigned int WIDTH = 800;
//const unsigned int HEIGHT = 600;
//
//int main() {
//	// Initializing GLFW
//	glfwInit();
//
//	// Setting GLFW window hints for OpenGL major and minor versions and profile
//	// We basically tell GLFW what version of OpenGL we want to use (3.3) and what profile we want to use (core)
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Vertex data array containing the three vertices for our triangle (x, y, z).
//	// We keep the z coordinate at 0 since we are working in 2D space.
//	GLfloat vertices[] = {
//		-0.5f, -0.5f, 0.0f, // First vertex (bottom left) (-0.5, -0.5, 0.0)
//		 0.5f, -0.5f, 0.0f, // Second vertex (bottom right) (0.5, -0.5, 0.0)
//		 -0.5f,  -1.0f, 0.0f // Third vertex (top), aligned with the first vertex to create a right triangle
//	};
//
//	// Creating the window object
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TriangleRemake", nullptr, nullptr);
//
//	// Checking if the window was created successfully. If not, we print an error message and terminate GLFW.
//	if (window == nullptr) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	// Making the context of the window current on the main thread. This is necessary before we can call any OpenGL functions.
//	glfwMakeContextCurrent(window);
//
//	// Loading all OpenGL function pointers using GLAD. This is necessary to use OpenGL functions.
//	gladLoadGL();
//
//	// Adjusting the OpenGL viewport to match the window dimensions. This tells OpenGL how to convert from NDCs to window coordinates.
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);			// Creating a vertex shader object and storing its ID in vertexShader
//	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);	// Attaching the vertex shader source code to the vertex shader object
//	glCompileShader(vertexShader);									// Compiling the vertex shader
//
//	// Doing the same for the fragment shader
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//	glCompileShader(fragmentShader);
//
//	GLuint shaderProgram = glCreateProgram();		// Creating the shader program and storing its ID in shaderProgram
//	glAttachShader(shaderProgram, vertexShader);	// Attaching the vertex shader to the shader program
//	glAttachShader(shaderProgram, fragmentShader);	// Attaching the fragment shader to the shader program
//	glLinkProgram(shaderProgram);					// Linking the shader program. This creates an executable that will run on the GPU and uses the attached shaders.
//
//	glDeleteShader(vertexShader);		// Deleting the vertex shader object since it's no longer needed after linking
//	glDeleteShader(fragmentShader);		// Deleting the fragment shader object for the same reason
//
//	GLuint VAO, VBO;	// Declaring variables for the Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
//
//	glGenVertexArrays(1, &VAO);	// Generating one VAO and storing its ID in VAO
//	glGenBuffers(1, &VBO);		// Generating one VBO and storing its ID in VBO
//
//	glBindVertexArray(VAO);		// Binding the VAO. This means that subsequent vertex attribute calls will be stored in this VAO.
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Binding the VBO to the GL_ARRAY_BUFFER target. This means that subsequent buffer data calls will affect this VBO.
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Uploading the vertex data to the GPU. We specify the target (GL_ARRAY_BUFFER), the size of the data, a pointer to the data, and a usage hint (GL_STATIC_DRAW means the data will not change).
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Defining how the vertex data is structured. This tells OpenGL how to interpret the vertex data in the VBO.
//	glEnableVertexAttribArray(0); // Enabling the vertex attribute at location 0. This means that the vertex shader will be able to access this vertex data.
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding the VBO. This is not strictly necessary, but it's a good practice to prevent accidental modifications to the VBO.
//	glBindVertexArray(0);			  // Unbinding the VAO for the same reason.
//
//	// Render loop
//	while (!glfwWindowShouldClose(window)) {
//		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glUseProgram(shaderProgram);		// Using the shader program. This tells OpenGL to use the shaders we linked earlier for rendering.
//		glBindVertexArray(VAO);				// Binding the VAO. This tells OpenGL to use the vertex data and attribute configuration stored in this VAO for rendering.
//		glDrawArrays(GL_TRIANGLES, 0, 3);	// Drawing the triangle. This tells OpenGL to draw triangles using the currently bound VAO, starting from the first vertex (0) and drawing 3 vertices (which form one triangle).
//		glfwSwapBuffers(window);
//
//		glfwPollEvents();
//	}
//
//	// Cleaning up resources (VAO, VBO, shader program) before exiting
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}