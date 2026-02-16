#include "smoke.h"

smoke::smoke(sf::Vector2f positions)
    : pixel(positions, 1),
    colours({
        { 0,{10,9,11} },
        {1,{19,19,21}},
        {2, {29,28,32}},
        {3,{38,37,43}}
        })
{
    shape.setFillColor(colours[randomColour]);
}

void smoke::gravity(int grid[75][75]) {
    gas::gravity(grid, shape, type, coordinates);
}
