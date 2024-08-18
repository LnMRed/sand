#include "Particle.h"
#include "Grid.h"
#include <iostream>

Particle::Particle(Material *material, int x, int y, int size, float velocityX, float velocityY, Grid* grid)
	: material(material),  // Initialize raw pointer to the material
	x(x),                // Initialize x coordinate
	y(y),                // Initialize y coordinate
	size(size),          // Initialize size of the particle
	velocityX(velocityX),// Initialize X velocity
	velocityY(velocityY),// Initialize Y velocity
	grid(grid)
{
}

Particle::~Particle()
{
	
}

// update with gravity and velocity 
// implement gravity later now itss const
void Particle::update()
{
	material->fall(this, grid);
	velocityY -= 0.1f;
	x += velocityX;
	y += velocityY;

	if (x < 0 || x >= grid->getCols() * grid->getWidth()) {
		velocityX = 0; // bounce off the wall
	}
	if (y < 0 || y >= grid->getRows() * grid->getWidth()) {
		velocityY = 0; // bounce off the floor/ceiling
	}
}

void Particle::render(SDL_Renderer* renderer)
{
	material->render(renderer, x, y, size);
}

Material* Particle::getMaterial() const
{
	return material;
}

int Particle::getX() const
{
	return x;
}

int Particle::getY() const
{
	return y;
}

void Particle::setX(int x)
{
	this->x = x;
}

void Particle::setY(int y)
{
	this->y = y;
}

int Particle::getSize() const
{
	return size;
}

float Particle::getXVelocity() const
{
	return velocityX;
}

float Particle::getYVelocity() const
{
	return velocityY;
}

void Particle::setXVelocity(float velocityX)
{
	this->velocityX = velocityX;
}

void Particle::setYVelocity(float velocityY)
{
	this->velocityY = velocityY;
}

SDL_Color Particle::getColor() const
{
	SDL_Color sdlColor = material->getColor();
	return sdlColor;
}

bool Particle::hasParticleMoved() const
{
	return material->getMoved();
}



