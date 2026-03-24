//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//// Function to match the viewport with window size whenever window dimensions are changed by the user or the OS
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//// Function to process input, takes window object
//void processInput(GLFWwindow* window);
//
//// Window dimensions
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main() {
//	// Initialize glfw
//	glfwInit();
//
//	// Configure glfw with OpenGL specs
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Create the window object
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLBaby", NULL, NULL);
//
//	// for safety
//	if (window == NULL) {
//		std::cout << "Failed to create window\n";
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// load al OpenGL function pointers
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// Render loop
//	while (!glfwWindowShouldClose(window))
//	{
//		processInput(window);
//
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window) {
//	// if escape key is pressed, set WindowShouldClose property of window to true so that render loop does not execute
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}