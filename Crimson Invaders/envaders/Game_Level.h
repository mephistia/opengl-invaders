/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "BulletMonster.h"


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
	// Level state
	std::vector<GameObject> Invaders;
	GLboolean gameover;

	// Constructor
	GameLevel() { }
	// Loads level from file
	void      Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	// Render level
	void      Draw(SpriteRenderer &renderer);
	// Check if the level is completed (all invaders are destroyed)
	GLboolean IsCompleted();
	// Movement pattern
	void	  Move(GLfloat dt);
private:
	// Initialize level from tile data
	void      init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
	GLfloat   time, direction, vel;
};

#endif