#include "Point.h"
#include "bresenham_circle.h"
#include "normalize.h"

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

// GLSL source code for the fragment shader — now accepts a color uniform
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 uColor;\n"
"void main()\n"
"{\n"
"   FragColor = uColor;\n"
"}\n\0";

// Window dimensions
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {
	// Initializing GLFW
	glfwInit();

	// Setting GLFW window hints for OpenGL major and minor versions and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Generating point vertices
	std::vector<Point> points;
	BresenhamCircle(0, 550, points);

	// Normalizing points to fit within the NDC range of [-1, 1]
	for (size_t i = 0; i < points.size(); i++) {
		points[i].normalizePoint(800.0f, 600.0f);
	}

	// Prepend the circle center so GL_TRIANGLE_FAN renders a proper filled disk.
	// The center must be the first vertex for the fan to work correctly.
	Point center(0, 550);
	center.normalizePoint(800.0f, 600.0f);

	// Sort perimeter points by angle so GL_TRIANGLE_FAN connects them continuously
	std::sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
		float angleA = std::atan2(a.getY() - center.getY(), a.getX() - center.getX());
		float angleB = std::atan2(b.getY() - center.getY(), b.getX() - center.getX());
		return angleA < angleB;
		});

	points.insert(points.begin(), center);

	// Build the vertex buffer (x, y, z) for each point
	GLfloat* vertices = new GLfloat[points.size() * 3];
	for (size_t i = 0; i < points.size(); i++) {
		vertices[i * 3] = points[i].getX(); // x
		vertices[i * 3 + 1] = points[i].getY(); // y
		vertices[i * 3 + 2] = 0.0f;             // z
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
	glBufferData(GL_ARRAY_BUFFER, points.size() * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Enable shader-based point sizing and set default point size uniform
	glEnable(GL_PROGRAM_POINT_SIZE);
	glUseProgram(shaderProgram);
	GLint pointSizeLoc = glGetUniformLocation(shaderProgram, "pointSize");
	if (pointSizeLoc >= 0) glUniform1f(pointSizeLoc, 5.0f);

	// Get the color uniform location for use in the render loop
	GLint colorLoc = glGetUniformLocation(shaderProgram, "uColor");

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glLineWidth(5.0f);

		// Pass 1: yellow fill using GL_TRIANGLE_FAN (center vertex is first)
		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());

		// Pass 2: orange boundary using GL_LINE_LOOP (skip center vertex at index 0)
		glUniform4f(colorLoc, 0.0f, 0.0f, 0.8f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 1, (GLsizei)points.size() - 1);

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