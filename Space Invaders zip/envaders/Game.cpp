/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"


// Game-related State data
SpriteRenderer  *Renderer;


Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(50, 50);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(400.0f);

GameObject      *Player;

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("test_vs.glsl", "test_fs.glsl", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("textures/invader1.png", GL_TRUE, "invader1");
	ResourceManager::LoadTexture("textures/invader2.png", GL_TRUE, "invader2");
	ResourceManager::LoadTexture("textures/bg.png", GL_FALSE, "bg");
	ResourceManager::LoadTexture("textures/invader3.png", GL_TRUE, "invader3");
	ResourceManager::LoadTexture("textures/player.png", true, "player");
	// Load levels
	Level1.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	this->Level = 1;

	glm::vec2 playerPos = glm::vec2(
		this->Width / 2 - PLAYER_SIZE.x / 2,
		this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
	
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt; // delta time

		// Move playerboard
		if (this->Keys[GLFW_KEY_LEFT])
		{
			if (Player->Position.x >= 64) // 64
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_RIGHT])
		{
			if (Player->Position.x <= this->Width - Player->Size.x -64)
				Player->Position.x += velocity;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("bg"),
			glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
		);

		// Draw level
		Level1.Draw(*Renderer);

		// Draw player
		Player->Draw(*Renderer);

	}
}