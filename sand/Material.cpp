#include "Material.h"

Material::Material(float density, SDL_Color color)
    : density(density), color(color)
{
}

float Material::getDensity() const
{
    return density;
}

SDL_Color Material::getColor() const
{
    return color;
}

void Material::setMoved(bool state)
{
    hasMoved = state;
}

bool Material::getMoved() const // This method should be const
{
    return hasMoved;
}
