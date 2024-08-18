#include "Grid.h"
#include <algorithm>
#include <iostream>

Grid::Grid(int cols, int rows, int width)
    : cols(cols), rows(rows), width(width), cells(rows, std::vector<Particle*>(cols, nullptr))
{
}

Grid::~Grid()
{
    // Since we're using raw pointers, we need to manually delete each particle.
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            delete cells[y][x];
        }
    }
}

bool Grid::isOccupied(int x, int y) const
{
    int gridX = std::abs(x / width);
    int gridY = std::abs(y / width);
    return gridX >= 0 && gridX < cols && gridY >= 0 && gridY < rows && cells[gridY][gridX] != nullptr;
}

void Grid::updateGrid(const std::vector<Particle*>& particles)
{
    for (auto& row : cells) {
        std::fill(row.begin(), row.end(), nullptr);
    }

    for (const auto& particle : particles) {
        int x = particle->getX() / width;
        int y = particle->getY() / width;

        if (x >= 0 && x < cols && y >= 0 && y < rows) {
            cells[y][x] = particle;
        }
    }
}

void Grid::swapParticles(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || x1 >= cols || y1 < 0 || y1 >= rows ||
        x2 < 0 || x2 >= cols || y2 < 0 || y2 >= rows) {
        return; // Mouse is out of bounds, do nothing
    }

    std::swap(cells[y1][x1], cells[y2][x2]);
    if (cells[y1][x1]) {
        cells[y1][x1]->setX(x1);
        cells[y1][x1]->setY(y1);
        std::cout << "swapped " << x1 << " " << y1 << std::endl;
    }
    if (cells[y2][x2]) {
        cells[y2][x2]->setX(x2);
        cells[y2][x2]->setY(y2);
        std::cout << "swapped " << x2 << " " << y2 << std::endl;
    }
}

Material* Grid::getMaterial(int x, int y)
{
    if (x >= 0 && x < cols && y >= 0 && y < rows) {
        Particle* particle = cells[y][x];
        return particle ? particle->getMaterial() : nullptr;
    }
    return nullptr;
}

Particle* Grid::getParticle(int x, int y) const
{
    if (x >= 0 && x < cols && y >= 0 && y < rows) {
        return cells[y][x]; // Return raw pointer for access
    }
    return nullptr;
}

float Grid::checkCellDensity(int x, int y)
{
    int newY = y + 1;
    if (newY >= getRows()) {
        return -1;  // Indicate out of bounds
    }

    if (isOccupied(x, newY)) {
        Material* materialBelow = getMaterial(x, newY);
        return materialBelow ? materialBelow->getDensity() : -1;
    }
    else {
        return -1;  // Indicate that the cell is empty
    }
}

int Grid::getCols()
{
    return cols;
}

int Grid::getRows()
{
    return rows;
}

int Grid::getWidth()
{
    return width;
}

std::vector<std::vector<Particle*>>& Grid::getCells()
{
    return cells;
}

Particle* Grid::getCell(int x, int y) const
{
    if (x >= 0 && x < cols && y >= 0 && y < rows) {
        return cells[y][x]; // Return raw pointer directly
    }
    return nullptr;
}

void Grid::setCell(int x, int y, Particle* particle)
{
    if (x >= 0 && x < cols && y >= 0 && y < rows) {
        delete cells[y][x];  // Clean up the existing particle to avoid memory leaks
        cells[y][x] = particle;
    }
}
