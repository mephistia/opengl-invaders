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
#include "Bullet.h"
#include <iostream>



// Game-related State data
SpriteRenderer  *Renderer;


Game::Game(GLuint width, GLuint height)
	: State(GAME_MENU), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(50, 50);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(350.0f);

GameObject      *Player;

// Initial velocity of the bullet
const glm::vec2 INITIAL_B_VELOCITY(0, -750.0f);
// Radius of the bullet object
const GLfloat B_RADIUS = 8.5f;

Bullet     *B;



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
	ResourceManager::LoadTexture("textures/bullet.png", GL_TRUE, "bullet");
	ResourceManager::LoadTexture("textures/player.png", true, "player");
	ResourceManager::LoadTexture("textures/block.png", false, "block");
	//ResourceManager::LoadTexture("textures/credits.png", GL_FALSE, "credits");
	//ResourceManager::LoadTexture("textures/gameover.png", GL_FALSE, "gameover");
	//ResourceManager::LoadTexture("textures/gamewin.png", GL_FALSE, "gamewin");
	//ResourceManager::LoadTexture("textures/menu.png", GL_FALSE, "menu");




	// Load levels
	Level1.Load("levels/one.lvl", this->Width, this->Height * 0.8);
	this->Level = 1;

	playerPos = glm::vec2(
		Width / 2 - PLAYER_SIZE.x / 2,
		Height - 2 * PLAYER_SIZE.y);
	Player = new GameObject(false,playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
	
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	glm::vec2 bPos = glm::vec2(playerPos.x + (PLAYER_SIZE.x/2), Height - 64);
	B = new Bullet(bPos, B_RADIUS, INITIAL_B_VELOCITY,
		ResourceManager::GetTexture("bullet"));
}

void Game::Update(GLfloat dt)
{
	B->Move(dt,playerPos.x);
	this->DoCollisions();

	// Move the invaders
	Level1.Move(dt);

	if (Level1.gameover == true) {
		this->ResetLevel();
		this->ResetPlayer();
	}
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
			{
				Player->Position.x -= velocity;
				playerPos.x = Player->Position.x + 16;

				if (B->CanShoot)
					B->Position.x -= velocity;
			}
				
		}
		if (this->Keys[GLFW_KEY_RIGHT])
		{
			if (Player->Position.x <= this->Width - Player->Size.x - 64)
			{
				Player->Position.x += velocity;
				playerPos.x = Player->Position.x + 16;

				if (B->CanShoot)
					B->Position.x += velocity;
			}
				
		}
		if (this->Keys[GLFW_KEY_SPACE]) {
				
			if (B->Cooldown <= 0 && B->CanShoot) {
				B->Cooldown = 1.2;
				B->CanShoot = false;

			}

		}
	
	}
	//if (this->State == GAME_MENU) {
	//	if (this->Keys[GLFW_KEY_SPACE]) 
	//		this->State == GAME_ACTIVE;
	//	
	//	if (this->Keys[GLFW_KEY_C])
	//		this->State == GAME_CREDITS;
	//}
	//if (this->State == GAME_CREDITS) {
	//	if (this->Keys[GLFW_KEY_SPACE])
	//		this->State == GAME_MENU;
	//}
		
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

		// Draw bullet
		if (!B->CanShoot)
			B->Draw(*Renderer);


	}
	// if (this->State == GAME_MENU) {
	//	Renderer->DrawSprite(ResourceManager::GetTexture("menu"),
	//		glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
	//	);
	//}
	// if (this->State == GAME_CREDITS) {
	//	Renderer->DrawSprite(ResourceManager::GetTexture("credits"),
	//		glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
	//	);
	//}
}


GLboolean Game::CheckCollision(Bullet & one, GameObject & two)
{

	glm::vec2 center(one.Position + one.Radius);
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// Retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < one.Radius;
}

void Game::DoCollisions()
{
	for (GameObject &box : Level1.Invaders)
	{
		if (!box.Destroyed)
		{
			if (CheckCollision(*B, box))
			{
				if (!box.IsSolid) {
					box.Destroyed = GL_TRUE;
					
					B->Position.y = 600 - 74;
					playerPos.x = Player->Position.x + 16;
					B->Position.x = playerPos.x;
					B->CanShoot = true;
				}
				else
				{
					// Don't destroy
					B->Position.y = 600 - 74;
					playerPos.x = Player->Position.x + 16;
					B->Position.x = playerPos.x;
					B->CanShoot = true;

				}
			}
		}
	}
}

void Game::ResetLevel()
{
	Level1.Load("levels/one.lvl", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
	// Reset player/ball stats
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	B->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - B_RADIUS, -(B_RADIUS * 2)), INITIAL_B_VELOCITY);
}
