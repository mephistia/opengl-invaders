#include "BulletMonster.h"



BulletMonster::BulletMonster()
{
}


BulletMonster::~BulletMonster()
{

}

glm::vec2 BulletMonster::MoveMonster(GLfloat dt, GLfloat invaderX, GLfloat invaderY)
{
	if (CanShoot) {
		this->Position += this->Velocity * dt;

	}
	return glm::vec2();
}
