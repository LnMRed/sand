#include "Handler.h"
#include <iostream>
#include "Sand.h"
#include "Water.h"
#include "Stone.h"

Handler::Handler()
    : isRunning(true), window(nullptr), renderer(nullptr), grid(new Grid(0, 0, 5)), mouseDown(false)
{
}

Handler::~Handler()
{
    // Clean up grid
    delete grid;

    // Clean up particles
    for (Particle* particle : particles)
    {
        delete particle;
    }
    particles.clear();
}

void Handler::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
    int flags = 0;
    if (fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "subsystem initialized" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "window made successfully" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            std::cout << "renderer initialized" << std::endl;
        }

        int cols = width;
        int rows = height;
        delete grid; // Delete the old grid
        grid = new Grid(cols, rows, 5);
    }
}

void Handler::handleEvents()
{
    int x, y;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                std::cout << "chosen material is sand " << std::endl;
                selectedMaterial = CurrentMaterial::SAND;
                break;
            case SDLK_2:
                std::cout << "chosen material is water " << std::endl;
                selectedMaterial = CurrentMaterial::WATER;
                break;
            case SDLK_3:
                std::cout << "chosen material is stone " << std::endl;
                selectedMaterial = CurrentMaterial::STONE;
                break;
            case SDLK_4:
                generateNoiseMap(grid);
            default:
                break;
            }
        }
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.button.x;
            y = event.button.y;
            createParticles(x, y);
            mouseDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDown = false;
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0)
            {
                brush_size = std::min(brush_size + 1, 50);
                std::cout << brush_size << std::endl;
            }
            else if (event.wheel.y < 0)
            {
                brush_size = std::max(brush_size - 1, 1);
                std::cout << brush_size << std::endl;
            }
            break;
        case SDL_MOUSEMOTION:
            if (mouseDown)
            {
                x = event.motion.x;
                y = event.motion.y;

                createParticles(x, y);     
            }
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }
}

void Handler::generateNoiseMap(Grid* grid)
{
    sound.generateMap(*grid, *this);
}

void Handler::calc_fps()
{
    static int frameCount = 0;
    static Uint32 lastTime = 0;

    frameCount++;
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime > 1000)
    {
        fps = frameCount / ((currentTime - lastTime) / 1000.0f);
        frameCount = 0;
        std::cout << fps << std::endl;
        lastTime = currentTime;
    }
}

void Handler::update()
{
    std::vector<Particle*> activeParticles;
    for (Particle* particle : particles)
    {
        if(particle->getActive())
        particle->update();
        if (particle->getActive()) {
            activeParticles.push_back(particle);
        }
    }
    particles.swap(activeParticles);
    grid->updateGrid(particles);
}

void Handler::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (Particle* particle : particles)
    {
        SDL_Color color = particle->getColor();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect{ particle->getX(), particle->getY(), 5, 5};
        SDL_RenderFillRects(renderer, &rect, 1);
    }

    SDL_RenderPresent(renderer);

    frameEnd = SDL_GetTicks();
    frameDelay = frameEnd - frameStart;

    calc_fps();
}

void Handler::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "game quit/cleaned" << std::endl;
}

void Handler::createParticles(int x, int y)
{
    for (int i = -brush_size; i <= brush_size; i++)
    {
        for (int j = -brush_size; j <= brush_size; j++)
        {
            if (i * i + j * j <= brush_size * brush_size)
            {
                Particle* newParticle = nullptr;
                int width = 5;

                switch (selectedMaterial)
                {
                case CurrentMaterial::SAND:
                    newParticle = new Particle(new Sand(1, SDL_Color{ 255, 165, 0, 255 }), x + i, y + j, width, 0, 0, grid);
                    break;
                case CurrentMaterial::WATER:
                    newParticle = new Particle(new Water(1, SDL_Color{ 0, 0, 255, 255 }), x + i, y + j, width, 0, 0, grid);
                    break;
                case CurrentMaterial::STONE:
                    newParticle = new Particle(new Stone(1, SDL_Color{ 125, 125, 125, 255 }), x + i, y + j, width,0,0,  grid);
                    break;
                }
                if (newParticle) {
                    addParticle(newParticle);
                }
            }
        }
    }
}

SDL_Renderer* Handler::getRenderer()
{
    return renderer;
}

void Handler::addParticle(Particle* particle)
{
    if (particle) {
        particles.push_back(particle);
    }
}

void Handler::setSelectedMaterial(CurrentMaterial material)
{
    selectedMaterial = material;
}

bool Handler::running()
{
    return isRunning;
}

int Handler::getScreenDimensions()
{
    return width, height;
}
