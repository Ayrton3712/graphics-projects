// Exercise 1. Change the color of the window to a shade of Orange

//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//int main() {
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
//
//	if (window == nullptr) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	gladLoadGL();
//
//	glViewport(0, 0, 800, 600);
//
//	glClearColor(0.5f, 0.2f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glfwSwapBuffers(window);
//
//	while (!glfwWindowShouldClose(window)) {
//		glfwPollEvents();
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}

// Exercise 2. Change the size of the window to width = 400, height = 225

//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//int main() {
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(400, 225, "LearnOpenGL", nullptr, nullptr);
//
//	if (window == nullptr) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	gladLoadGL();
//
//	glViewport(0, 0, 400, 225);
//
//	glClearColor(0.5f, 0.2f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glfwSwapBuffers(window);
//
//	while (!glfwWindowShouldClose(window)) {
//		glfwPollEvents();
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}

// Exercise 3. Change the name of the window to ”I made this!”
//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//int main() {
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(400, 225, "I made this!", nullptr, nullptr);
//
//	if (window == nullptr) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	gladLoadGL();
//
//	glViewport(0, 0, 400, 225);
//
//	glClearColor(0.5f, 0.2f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glfwSwapBuffers(window);
//
//	while (!glfwWindowShouldClose(window)) {
//		glfwPollEvents();
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}

// MEDIUM

// Exercise 1. !!!EPILEPSY WARNING!!!
// Make the window flicker between two colors
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(400, 225, "I made this!", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 400, 225);

	while (!glfwWindowShouldClose(window)) {
		// Clearing color
		glClearColor(0.37f, 0.73f, 0.95f, 1.0f);
		// Applying the clear color to the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		// Doing the same thing but with a different color
		glClearColor(0.95f, 0.37f, 0.73f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}