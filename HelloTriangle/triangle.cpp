#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex shader GLSL code
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// Function to match the viewport with window size whenever window dimensions are changed by the user or the OS
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Function to process input, takes window object
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	// Initialize glfw
	glfwInit();

	// Configure glfw with OpenGL specs
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLBaby", NULL, NULL);

	// for safety
	if (window == NULL) {
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Array with triangle vertices in NDCs
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // (0.5, 0.5, 0)
		0.5f, -0.5f, 0.0f,  // (0.5, 0.5, 0)
		0.0f, 0.5f, 0.0f   // (0, 0.5, 0)
	};

	// ******* VERTEX SHADER *******
	// Creating vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attaching shader source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// Compiling vertex shader
	glCompileShader(vertexShader);

	// Checking for compile-time errors for vertex shader
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ******* FRAGMENT SHADER *******
	// Creating fragment shader, very similar to vertex shader creation
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Checking for compile-time errors for fragment shader
	int successFragShader;
	char infoLogFragShader[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragShader);

	if (!successFragShader) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragShader);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogFragShader << std::endl;
	}

	// Creating shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Tell OpenGL how to interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Optional (good practice)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	// if escape key is pressed, set WindowShouldClose property of window to true so that render loop does not execute
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}