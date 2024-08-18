#pragma once

#include "Grid.h"
#include "Particle.h"
#include "Noise.h"

#include <iostream>
#include <vector>
#include <utility>
#include "SDL.h"

enum class CurrentMaterial
{
	EMPTY,
	SAND,
	WATER,
	STONE
};

class Handler
{
public:
	Handler();
	~Handler();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);

	void handleEvents();
	void calc_fps();

	void update();
	void render();
	void clean();

	void createParticles(int x, int y);

	bool running();

	int getScreenDimensions();

	SDL_Renderer* getRenderer();

	void generateNoiseMap(Grid* grid);
	void addParticle(Particle* particle);

	void setSelectedMaterial(CurrentMaterial material);

private:
	int	count = 0;

	int fps = 0;
	Uint32 frameStart = 0;
	Uint32 frameEnd = 0;
	Uint32 frameDelay = 0;

	int brush_size = 1;
	bool isRunning;
	bool mouseDown;

	int width;
	int height;

	CurrentMaterial selectedMaterial = CurrentMaterial::SAND;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Grid* grid; // raw pointer for grid
	std::vector<Particle*> particles; // raw pointers for particles

	noise sound;
};