#include "Noise.h"
#include "Handler.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Particle.h"
#include "Sand.h"
#include "Water.h"
#include "Stone.h"

float noise::lerp(float a, float b, float t) // linear interpolation
{
    return a + t * (b - a);
}

float noise::fade(float t) // makes a pseudo-random vector
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float noise::grad(int hash, float x, float y)
{
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

float noise::perlin(float x, float y, std::vector<int>& perm)
{
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;

    x -= floor(x);
    y -= floor(y);

    float u = fade(x);
    float v = fade(y);

    int A = perm[X] + Y;
    int B = perm[X + 1] + Y;

    return lerp(v, lerp(u, grad(perm[A], x, y), grad(perm[B], x - 1, y)),
        lerp(u, grad(perm[A + 1], x, y - 1), grad(perm[B + 1], x - 1, y - 1)));
}

std::vector<int> noise::generatePermutation()
{
    std::vector<int> perm(256);
    int seed = rand();
    for (int i = 0; i < 256; i++) perm[i] = i;
    std::shuffle(perm.begin(), perm.end(), std::default_random_engine(seed));
    perm.insert(perm.end(), perm.begin(), perm.end()); // Duplicate permutation vector
    return perm;
}

void noise::generateMap(Grid& grid, Handler& handler) {
    std::vector<int> perm = generatePermutation();

    int MAP_HEIGHT = grid.getRows();
    int MAP_WIDTH = grid.getCols();

    float frequencyX = 0.0102f;
    float frequencyY = 0.0105f;
    int width = 5;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            float noiseValue = perlin(x * frequencyX, y * frequencyY, perm);  // Adjust frequency if needed
            Particle* newParticle = nullptr;

            if (noiseValue < 0.3) {
                
                std::cout << "sand generated" << std::endl;
                handler.setSelectedMaterial(CurrentMaterial::SAND);
                handler.createParticles(x, y);
            }
            else if (noiseValue < 0.5) {              
                std::cout << "water generated" << std::endl;
                handler.setSelectedMaterial(CurrentMaterial::WATER);
                handler.createParticles(x, y);
            }
            else if (noiseValue < 0.7) {
                
                std::cout << "stone generated" << std::endl;
                handler.setSelectedMaterial(CurrentMaterial::STONE);
                handler.createParticles(x, y);
            }
        }
    }
}
