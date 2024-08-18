#pragma once

#include <cmath>
#include <vector>
#include <SDL.h>
#include "Grid.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Particle.h"
#include "Sand.h"

#include "Water.h"
#include "Stone.h"

class Grid; 
class Handler;

class noise
{
public:

	float lerp(float a, float b, float t); //linear interpolation
	float fade(float t);
	float grad(int hash, float x, float y); // maakt een pseudo random vector aan 
	float perlin(float x, float y, std::vector<int>& perm);
	std::vector<int> generatePermutation();

	void generateMap(Grid& grid, Handler& handler); // moet wss een grid nodig hebben of screen width en height
};

