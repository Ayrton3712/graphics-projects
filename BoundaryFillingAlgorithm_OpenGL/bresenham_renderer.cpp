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

// GLSL source code for the vertex shader. Modified to include color attribute and point size uniform
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"uniform float pointSize;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	gl_PointSize = pointSize;\n"
"	ourColor = aColor;\n"
"}\0";

// GLSL source code for the fragment shader. Modified to include color attribute
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor, 1.0);\n"
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

	GLfloat radius = 5.0f;

	// Generating point vertices
	std::vector<Point> points;
	BresenhamCircle(0, radius, points);

	//std::cout << "Reached\n";

	GLfloat fillColor[4] = { 1.0f, 0.5f, 0.2f, 1.0f }; // RGBA color for filling

	std::vector<Point> fill;
	boundary_filling_algorithm(Point(0, 0), points, fill, radius);

	//std::cout << "Reached\n";

	// Storing normalization factors as constants for clarity and maintainability
	const GLfloat normalizationX = 10.0f;
	const GLfloat normalizationY = 7.5f;
	// Normalizing points to fit within the NDC range of [-1, 1]
	for (size_t i = 0; i < points.size(); i++) {
		points[i].normalizePoint(normalizationX, normalizationY);
	}
	for (size_t i = 0; i < fill.size(); i++) {
		fill[i].normalizePoint(normalizationX, normalizationY);
	}

	// Allocate combined vertex buffer for boundary + fill points
	size_t totalPoints = points.size() + fill.size();
	GLfloat* vertices = new GLfloat[totalPoints * 6];

	// Boundary points: WHITE
	for (size_t i = 0; i < points.size(); i++) {
		size_t base = i * 6;
		vertices[base] = points[i].getX();
		vertices[base + 1] = points[i].getY();
		vertices[base + 2] = 0.0f;

		vertices[base + 3] = 1.0f; // R
		vertices[base + 4] = 1.0f; // G
		vertices[base + 5] = 1.0f; // B

		std::cout << "Added boundary point: ";
		points[i].displayPoint();
	}

	//std::cout << "Reached\n";

	// Fill points: ORANGE
	for (size_t i = 0; i < fill.size(); i++) {
		size_t base = (points.size() + i) * 6;
		vertices[base] = fill[i].getX();
		vertices[base + 1] = fill[i].getY();
		vertices[base + 2] = 0.0f;

		vertices[base + 3] = fillColor[0];	// R
		vertices[base + 4] = fillColor[1];	// G
		vertices[base + 5] = fillColor[2];	// B
		vertices[base + 6] = fillColor[3];	// A

		std::cout << "Added fill point: ";
		fill[i].displayPoint();
	}

	//std::cout << "Reached\n";

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
	glBufferData(GL_ARRAY_BUFFER, totalPoints * 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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