#include "dirt.h"

dirt::dirt(sf::Vector2f positions)
    : pixel(positions, 1),
    colours({
        {0,{90,79,62}},
        {1,{114,93,76}},
        {2,{79,58,43}},
        {3,{43,24,12}}
        })
{
    shape.setFillColor(colours[randomColour]);
}

void dirt::gravity(int grid[75][75]) {
    solid::gravity(grid, shape, type, coordinates);
}
