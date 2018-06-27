/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game_Level.h"
#include "Game_Object.h"
#include "Bullet.h"


// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_OVER,
	GAME_CREDITS
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width, Height;

	GameLevel			   Level1;
	GLuint                 Level;
	glm::vec2              playerPos;


	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

	void Active(GLfloat dt);
	void Menu();
	void Credits();
	void GameOver();
	void GameWin();

	// Collisions
	GLboolean CheckCollision(Bullet & one, GameObject & two);
	void DoCollisions();

	// reset
	void ResetLevel();
	void ResetPlayer();

};

#endif