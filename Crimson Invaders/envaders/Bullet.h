#ifndef BULLET_H
#define BULLET_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "texture.h"
#include "sprite_renderer.h"
#include "game_object.h"

class Bullet: public GameObject
{
public:

	GLfloat   Radius;
	GLboolean CanShoot;
	GLfloat   Cooldown;

	Bullet();
	Bullet(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	glm::vec2 Move(GLfloat dt, GLfloat playerX);
	void      Reset(glm::vec2 position, glm::vec2 velocity);
	~Bullet();
};

#endif