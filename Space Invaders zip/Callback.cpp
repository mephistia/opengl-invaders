/*                 
 "Hello World GLFW3". Just the basics.   
 Dependencies:
    GLFW3 
*/

#include <GLFW/glfw3.h>
#include <iostream>
#include <locale>



// if a key is pressed / released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		std::cout << "Tecla W pressionada" << std::endl;

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		std::cout << "Tecla A pressionada" << std::endl;

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		std::cout << "Tecla S pressionada" << std::endl;

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		std::cout << "Tecla D pressionada" << std::endl;

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
		std::cout << "Tecla X pressionada" << std::endl;
}


// posição do cursor
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "Mouse X: " << xpos << "  Mouse Y: " << ypos << std::endl;
}

// botões do mouse
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	setlocale(LC_ALL, "Portuguese");

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "Botão Direito do Mouse pressionado" << std::endl;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		std::cout << "Botão Direito do Mouse solto" << std::endl;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "Botão Esquerdo do Mouse pressionado" << std::endl;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		std::cout << "Botão Esquerdo do Mouse solto" << std::endl;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* background color */
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here - first clear color buffer with glClearColor */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}