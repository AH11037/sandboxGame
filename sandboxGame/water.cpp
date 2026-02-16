#include "water.h"

water::water(sf::Vector2f positions)
    : pixel(positions, 1),
    colours({
        { 0,{15,94,156} },
        {1,{35,137,218}},
        {2, {28,163,236}},
        {3,{90,188,216}}
        })
{
    shape.setFillColor(colours[randomColour]);
}

void water::gravity(int grid[75][75]) {
    liquid::gravity(grid, shape, type, coordinates);
}
