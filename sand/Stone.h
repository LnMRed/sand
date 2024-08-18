#pragma once
#include "Material.h"
class Stone : public Material
{
public:
    Stone(float density, SDL_Color color);
	~Stone() {};

	void update();
	void interact(Particle* particle, Particle* other, Grid* grid);
	void render(SDL_Renderer* renderer, int x, int y, int size);
	void fall(Particle* particle, Grid* grid);

private:
    Particle* particle;
    Grid* grid;
};

