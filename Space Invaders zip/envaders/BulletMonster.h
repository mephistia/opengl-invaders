#pragma once
#include "Bullet.h"
class BulletMonster: public Bullet
{
public:
	BulletMonster();
	~BulletMonster();

	glm::vec2 MoveMonster(GLfloat dt, GLfloat invaderX, GLfloat invaderY);

};

