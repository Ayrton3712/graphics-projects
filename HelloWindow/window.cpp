#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



// Window dimensions
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, WIDTH, HEIGHT);

	glClearColor(0.07f, 0.12f, 0.17f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}