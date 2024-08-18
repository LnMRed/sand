#pragma once

#include <vector>
#include "Material.h"
#include "Particle.h"

class Grid
{
public:
    Grid(int cols, int rows, int width); // width of cells
    ~Grid();

    bool isOccupied(int x, int y) const;
    void updateGrid(const std::vector<Particle*>& particles);  // Changed to use raw pointers
    void swapParticles(int x1, int y1, int x2, int y2);

    Material* getMaterial(int x, int y);
    Particle* getParticle(int x, int y) const;

    float checkCellDensity(int x, int y);

    int getCols();
    int getRows();
    int getWidth();

    std::vector<std::vector<Particle*>>& getCells();  // Changed to use raw pointers
    Particle* getCell(int x, int y) const;
    void setCell(int x, int y, Particle* particle);  // Changed to use raw pointers

private:
    int cols;
    int rows;
    int width;
    std::vector<std::vector<Particle*>> cells;  // Changed to use raw pointers
};
