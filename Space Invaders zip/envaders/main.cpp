//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <assert.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <string.h>
//#include <time.h>
//#define GL_LOG_FILE "gl.log"
//#include <iostream>
//#include "gl_utils.h"
////#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//
//int g_gl_width = 800;
//int g_gl_height = 600;
//GLFWwindow *g_window = NULL;
//
//
//int main() {
//	restart_gl_log();
//	// all the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
//	start_gl("Space Invaders");
//	// tell GL to only draw onto a pixel if the shape is closer to the viewer
//	//glEnable( GL_DEPTH_TEST ); // enable depth-testing
//	//glDepthFunc( GL_LESS );		 // depth-testing interprets a smaller value as "closer"
//
//
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		// positions          // colors           // texture coords
//		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
//	};
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//
//	unsigned int VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	// texture coord attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	char vertex_shader[1024 * 256];
//	char fragment_shader[1024 * 256];
//	parse_file_into_str( "test_vs.glsl", vertex_shader, 1024 * 256 );
//	parse_file_into_str( "test_fs.glsl", fragment_shader, 1024 * 256 );
//
//	GLuint vs = glCreateShader( GL_VERTEX_SHADER );
//	const GLchar *p = (const GLchar *)vertex_shader;
//	glShaderSource( vs, 1, &p, NULL );
//	glCompileShader( vs );
//
//	// check for compile errors
//	int params = -1;
//	glGetShaderiv( vs, GL_COMPILE_STATUS, &params );
//	if ( GL_TRUE != params ) {
//		fprintf( stderr, "ERROR: GL shader index %i did not compile\n", vs );
//		print_shader_info_log( vs );
//		return 1; // or exit or something
//	}
//
//	GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
//	p = (const GLchar *)fragment_shader;
//	glShaderSource( fs, 1, &p, NULL );
//	glCompileShader( fs );
//
//	// check for compile errors
//	glGetShaderiv( fs, GL_COMPILE_STATUS, &params );
//	if ( GL_TRUE != params ) {
//		fprintf( stderr, "ERROR: GL shader index %i did not compile\n", fs );
//		print_shader_info_log( fs );
//		return 1; // or exit or something
//	}
//
//	GLuint shader_programme = glCreateProgram();
//	glAttachShader( shader_programme, fs );
//	glAttachShader( shader_programme, vs );
//	glLinkProgram( shader_programme );
//
//	glGetProgramiv( shader_programme, GL_LINK_STATUS, &params );
//	if ( GL_TRUE != params ) {
//		fprintf( stderr, "ERROR: could not link shader programme GL index %i\n",
//						 shader_programme );
//		print_programme_info_log( shader_programme );
//		return false;
//	}
//
//	// load and create a texture
//	// -------------------------
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//    
//	//stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load("spaceshuttle.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	glEnable( GL_CULL_FACE ); // cull face
//	glCullFace( GL_BACK );		// cull back face
//	glFrontFace( GL_CW );			// GL_CCW for counter clock-wise
//
//
//	while ( !glfwWindowShouldClose( g_window ) ) {
//
//		// wipe the drawing surface clear
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//		glViewport(0, 0, g_gl_width, g_gl_height);
//
//		// bind Texture
//		glBindTexture(GL_TEXTURE_2D, texture);
//
//		//
//		// Note: this call is not necessary, but I like to do it anyway before any
//		// time that I call glDrawArrays() so I never use the wrong shader programme
//		glUseProgram( shader_programme );
//
//		// Note: this call is not necessary, but I like to do it anyway before any
//		// time that I call glDrawArrays() so I never use the wrong vertex data
//		glBindVertexArray( VAO );
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		// update other events like input handling
//		glfwPollEvents();
//		if ( GLFW_PRESS == glfwGetKey( g_window, GLFW_KEY_ESCAPE ) ) {
//			glfwSetWindowShouldClose( g_window, 1 );
//		}
//		// put the stuff we've been drawing onto the display
//		glfwSwapBuffers( g_window );
//	}
//
//	// close GL context and any other GLFW resources
//	glfwTerminate();
//	return 0;
//}


/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game SpaceI(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	SpaceI.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	SpaceI.State = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		SpaceI.ProcessInput(deltaTime);

		// Update Game state
		SpaceI.Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SpaceI.Render();

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}