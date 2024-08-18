#include "Stone.h"
#include <SDL.h>

#include "Particle.h"
#include "Grid.h"
#include <iostream>

Stone::Stone(float density, SDL_Color color) : grid(new Grid(0, 0, 5)), Material(density, color), particle(nullptr)
{
}

void Stone::update()
{
	
}

void Stone::interact(Particle* particle, Particle* other, Grid* grid)
{

}

void Stone::render(SDL_Renderer* renderer, int x, int y, int size)
{
	// hoeft niet
}

void Stone::fall(Particle* particle, Grid* grid) // moet een fall template worden
{
	int x = particle->getX();
	int y = particle->getY();
	int size = particle->getSize();
	
	int newX = x;
	int newY = y; // check if cell is occupied

	if (newY < grid->getRows() * grid->getWidth())
	{
		if (!grid->isOccupied(x, newY))
		{
			particle->setY(newY);
		}
		else
		{
			if (x > 0 && newY < grid->getRows() * grid->getWidth() && !grid->isOccupied(x - 1, newY))
			{
				particle->setX(newX - 1);
				particle->setY(newY);
				setMoved(false);
			}
			if (x < grid->getCols() - 1 && newY < grid->getRows() * grid->getWidth() && !grid->isOccupied(x + 1, newY))
			{
				particle->setX(newX - 1);
				particle->setY(newY);
				setMoved(false);
			}
		}
	}
	if (getMoved()==false)
	{
		particle->setYVelocity(0.1f); //rook particles moeten -1 hebben
	}
	if (particle->getX() < 0) particle->setX(0);
	if (particle->getX() >= grid->getCols()) particle->setX(grid->getCols() - 1);
	if (particle->getY() < 0) particle->setY(0);
	if (particle->getY() >= grid->getRows()) particle->setY(grid->getRows() - 1);
}
