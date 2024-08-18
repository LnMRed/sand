#pragma once
#include <SDL.h>
#include "Material.h"

class Grid;

class Particle
{
public:
    Particle(Material* material, int x, int y, int size, float velocityX, float velocityY, Grid* grid); // Constructor accepting a raw pointer for Material

    ~Particle();

    void update();
    void render(SDL_Renderer* renderer); // Update to use SDL renderer

    Material* getMaterial() const; // Returns a raw pointer to Material
    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    int getSize() const;
    float getXVelocity() const;
    float getYVelocity() const;
    void setXVelocity(float x);
    void setYVelocity(float y);

    SDL_Color getColor() const;

    void setActive(bool active) { isActive = active; }
    bool getActive() const { return isActive; }
    
    bool hasParticleMoved() const;

private:

    bool isActive = true;

    bool hasMoved = false;
    int x, y, size;
    float velocityX, velocityY;

    Material* material; // Raw pointer to Material
    Grid* grid;         // Raw pointer to Grid
};
