#include "Bullet.h"



Bullet::Bullet()
	: GameObject(), Radius(12.5f), CanShoot(true){}

Bullet::Bullet(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), CanShoot(true) {}


glm::vec2 Bullet::Move(GLfloat dt, GLfloat playerX)
{
	// If not stuck to player board
	if (!this->CanShoot)
	{
		this->Position += this->Velocity * dt;
		// Then check if outside window bounds and if so, reverse velocity and restore at correct position
		
		 
		if (this->Position.y <= 0.0f)
		{
			
			CanShoot = true;

			Position.y = 600;
			Position.x = playerX;
		}
	}
	return this->Position;
}

void Bullet::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->CanShoot = true;
}

Bullet::~Bullet()
{
}


