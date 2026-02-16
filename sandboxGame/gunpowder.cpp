#include "gunpowder.h"

gunpowder::gunpowder(sf::Vector2f positions)
    : pixel(positions, 4)
{
    shape.setFillColor(colours[randomColour]);
}

void gunpowder::gravity(int grid[75][75]) {
    solid::gravity(grid, shape, type, coordinates);
}

void gunpowder::flameCheck(int grid[75][75]) {
    int x = coordinates.x;
    int y = coordinates.y;
    bool nearFire =
        (x > 0 && grid[x - 1][y] == 5) ||
        (x < 74 && grid[x + 1][y] == 5) ||
        (y < 74 && grid[x][y + 1] == 5) ||
        (y > 0 && grid[x][y - 1] == 5);

    if (nearFire && !burning) {
        burning = true;
        lifetime = 3;
        shape.setFillColor(burningColors[randomColour]);

    }
};
void gunpowder::update(int grid[75][75]) {
    gravity(grid);
    flameCheck(grid);
    if (burning && lifetime > 0) {
        lifetime--;
    }
}
int gunpowder::transformTo() {
    if (burning && lifetime<= 0) {
        return 5;
    }
    return -1;
}