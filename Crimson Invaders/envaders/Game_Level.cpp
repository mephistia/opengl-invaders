/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_level.h"

#include <fstream>
#include <sstream>
#include <iostream>



void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
	time = 8;
	vel = 12;
	direction = 1;
	gameover = false;
	// Clear old data
	this->Invaders.clear();
	// Load from file
	GLuint tileCode; // code for each invader sprite
	GameLevel level; // code for loading new invader pattern
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
	for (GameObject &invader : this->Invaders) 
		if (!invader.Destroyed) // if the invader exists
			invader.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
	for (GameObject &invader : this->Invaders)
		if (!invader.IsSolid && !invader.Destroyed)
			return GL_FALSE;
	return GL_TRUE;
}

void GameLevel::Move(GLfloat dt)
{
	for (GameObject &invader : this->Invaders) {
		if (!invader.IsSolid) {
			if (!invader.Destroyed) // if the invader exists
			{
				if (direction == 1)
					invader.Position.x += vel * dt; // move right
				else
					invader.Position.x -= vel * dt; // move left
			}
		}
		
	}

	// calculate time
	time -= dt;

	if (time <= 0) {
		for (GameObject &invader : this->Invaders) {
			if (!invader.IsSolid) {
				invader.Position.y += 32;
				if (invader.Position.y == 586) {
					gameover = true;
				}
			}
			
		
		}
		direction = -direction;
		time = 14;
	}
	
}

void GameLevel::init(std::vector<std::vector<GLuint>> invaderData, GLuint levelWidth, GLuint levelHeight)
{
	// Calculate dimensions
	GLuint height = invaderData.size();
	GLuint width = invaderData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;
	// create different GLchar for each sprite
	GLchar *sprite;
	GLuint addpoints;
	GLboolean solid;
	// Initialize level tiles based on invaderData		
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			
			/// Check block type from level data (2D level array)
			///if (invaderData[y][x] == 1) // Solid
			///{
			///	glm::vec2 pos(unit_width * x, unit_height * y);
			///	glm::vec2 size(unit_width, unit_height);
			///	GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
			///	obj.IsSolid = GL_TRUE;
			///	this->Invaders.push_back(obj);
			///}
			///else 

			if (invaderData[y][x] > 0)	// Non-solid
			{
				
				if (invaderData[y][x] == 2) {
					sprite = "invader2";
					solid = false;
					addpoints = 20;
				}
				
				else if (invaderData[y][x] == 1) {
					sprite = "invader1"; 
					solid = false;
					addpoints = 10;
				}
				else if (invaderData[y][x] == 3)
				{
					sprite = "invader3";	
					solid = false;
					addpoints = 30;
				}

				else if (invaderData[y][x] == 4)
				{
					sprite = "block";
					solid = true;
					
				}
			

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				this->Invaders.push_back(GameObject(solid,pos, size, ResourceManager::GetTexture(sprite)));
				
			}
		}
	}
}