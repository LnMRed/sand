#pragma once
#include <SDL.h>
#include <memory>

class Grid;
class Particle;

class Material
{
public:
    Material(float density, SDL_Color color);
    virtual ~Material() = default; // Use default for virtual destructor

    virtual void update() = 0;
    virtual void interact(Particle* particle, Particle* other, Grid* grid) = 0;
    virtual void render(SDL_Renderer* renderer, int x, int y, int size) = 0;
    virtual void fall(Particle* particle, Grid* grid) = 0;

    float getDensity() const;
    SDL_Color getColor() const;
    void setMoved(bool state);
    bool getMoved() const; // Make this const to match usage in Particle

protected:
    float density;
    SDL_Color color;
    bool hasMoved = false;
};
