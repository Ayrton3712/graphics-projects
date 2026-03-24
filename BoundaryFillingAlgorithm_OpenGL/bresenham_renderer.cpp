#include "Point.h"
#include "bresenham_circle.h"
#include "normalize.h"
#include "boundary_filling_algorithm.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLSL source code for the vertex shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float pointSize;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   gl_PointSize = pointSize;\n"
"}\0";

// GLSL source code for the fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// Window dimensions
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {
	// Initializing GLFW
	glfwInit();

	// Setting GLFW window hints for OpenGL major and minor versions and profile
	// We basically tell GLFW what version of OpenGL we want to use (3.3) and what profile we want to use (core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Generating point vertices
	std::vector<Point> points;
	BresenhamCircle(0, 5, points);

	GLfloat fillColors[4] = { 1.0f, 0.5f, 0.2f, 1.0f }; // RGBA color for filling

	std::vector<Point> fill = boundary_filling_algorithm(Point(0, 0), fillColors, WIDTH, HEIGHT, points);

	// Normalizing points to fit within the NDC range of [-1, 1]
	for (size_t i = 0; i < points.size(); i++) {
		points[i].normalizePoint(10.0f, 7.5f);
	}
	for (size_t i = 0; i < fill.size(); i++) {
		fill[i].normalizePoint(10.0f, 7.5f);
	}

	// Allocate combined vertex buffer for boundary + fill points
	size_t totalPoints = points.size() + fill.size();
	GLfloat* vertices = new GLfloat[totalPoints * 3];

	// Copy boundary points
	for (size_t i = 0; i < points.size(); i++) {
		vertices[i * 3]     = points[i].getX(); // x
		vertices[i * 3 + 1] = points[i].getY(); // y
		vertices[i * 3 + 2] = 0.0f;             // z
	}
	// Copy filled points after boundary points
	for (size_t i = 0; i < fill.size(); i++) {
		size_t base = (points.size() * 3) + (i * 3);
		vertices[base]     = fill[i].getX(); // x
		vertices[base + 1] = fill[i].getY(); // y
		vertices[base + 2] = 0.0f;           // z
	}

	// Creating the window object
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Boundary Filling Algorithm", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Loading OpenGL functions using GLAD
	if (!gladLoadGL()) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Adjust viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// Compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO / VBO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// IMPORTANT: upload the full vertex buffer (boundary + fill)
	glBufferData(GL_ARRAY_BUFFER, totalPoints * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Enable shader-based point sizing and set default point size uniform
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUseProgram(shaderProgram);
	GLint pointSizeLoc = glGetUniformLocation(shaderProgram, "pointSize");
	if (pointSizeLoc >= 0) glUniform1f(pointSizeLoc, 5.0f); // change 5.0f to preferred pixel size

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// Draw all points (boundary + fill)
		glDrawArrays(GL_POINTS, 0, (GLsizei)totalPoints);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	delete[] vertices;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}