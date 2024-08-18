#include "Sand.h"
#include <SDL.h>

#include "Particle.h"
#include "Grid.h"
#include "Water.h"
#include <iostream>

Sand::Sand(float density, SDL_Color color) : grid(new Grid(0, 0, 5)), Material(density, color), particle(nullptr)
{

}

void Sand::update()
{
	fall(particle, grid);
}

void Sand::interact(Particle* particle, Particle* other, Grid* grid)
{

}

void Sand::render(SDL_Renderer* renderer, int x, int y, int size)
{
	// hoeft niet
}

void Sand::fall(Particle* particle, Grid* grid) // moet een fall template worden
{
    int x = particle->getX();
    int y = particle->getY();
    int size = particle->getSize();
    float velocityX = particle->getXVelocity();
    float velocityY = particle->getYVelocity();
    setMoved(true);
    particle->setX(x + velocityX);
    particle->setY(y + velocityY);

    particle->setYVelocity(velocityY - 0.01f);

    int newY = y + size; // Check if cell is occupied, maybe +1 due to coordinate

    if (newY < grid->getRows() * grid->getWidth() && !grid->isOccupied(x, newY))
    {
        particle->setY(newY);
    }
    else
    {
        int direction = size; // Random for left or right
        // If directly below is occupied, check diagonal down-left and down-right
        int newXLeft = x - direction;
        int newXRight = x + direction;
        // Check down-left
        if (newY < grid->getRows() && !grid->isOccupied(newXLeft, newY))
        {
            particle->setX(newXLeft);
            particle->setY(newY);
        }
        // Check down-right
        else if (newXRight < grid->getCols() && newY < grid->getRows() && !grid->isOccupied(newXRight, newY))
        {
            particle->setX(newXRight);
            particle->setY(newY);
        }
        // If vertical and diagonal movements are blocked, attempt horizontal movement
        else
        {
            int direction = rand() % 2 == 0 ? -1 : 1; // Randomize initial direction
            // Try to move left first
            if (x + direction >= 0 && x + direction < grid->getCols() && !grid->isOccupied(x + direction, y))
            {
                particle->setX(x + direction);
            }
            // If left is blocked, try right
            else if (x - direction >= 0 && x - direction < grid->getCols() && !grid->isOccupied(x - direction, y))
            {
                particle->setX(x - direction);
            }
        }
        /*
        if (newY < grid->getRows() && grid->isOccupied(x, newY))
        {
            Particle* belowParticle = grid->getParticle(x, newY);
            if (belowParticle && dynamic_cast<Water*>(belowParticle->getMaterial()))
            {
                grid->swapParticles(x, y, x, newY);
            }
        }
        */
    }
    if (getMoved() == true)
    {
        if (particle->getX() < 0) particle->setX(0);
        if (particle->getX() >= grid->getCols()) particle->setX(grid->getCols() - 1);
        if (particle->getY() < 0) particle->setY(0);
        if (particle->getY() >= grid->getRows()) particle->setY(grid->getRows() - 1);
        particle->setYVelocity(1.0f);
        setMoved(true);
    }
}