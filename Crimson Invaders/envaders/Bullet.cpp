#include "Bullet.h"



Bullet::Bullet()
	: GameObject(), Radius(12.5f), CanShoot(true){}

Bullet::Bullet(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(false,pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), CanShoot(true), Cooldown(1.2) {}


glm::vec2 Bullet::Move(GLfloat dt, GLfloat playerX)
{
	// If bullet is on the screen
	if (!CanShoot)
	{
		this->Position += this->Velocity * dt;
		Cooldown -= dt;


		if (Position.y <= 0) {
			CanShoot = true;
			Position.y = 600 - 74;
			Position.x = playerX + 16;

		}
	}
	if (Cooldown > 0 && CanShoot) {
		Cooldown -= dt;
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


