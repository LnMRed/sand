#pragma once
#include "Material.h"
class Sand : public Material
{
public:
    Sand(float density, SDL_Color color);
    void update() override;
    void interact(Particle* particle, Particle* other, Grid* grid) override;
    void render(SDL_Renderer* renderer, int x, int y, int size) override;
    void fall(Particle* particle, Grid* grid) override;




private:
    Particle* particle;
    Grid* grid;
};