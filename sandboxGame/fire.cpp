#include "fire.h"

fire::fire(sf::Vector2f positions)
    : pixel(positions, 5), lifetime(3),
    colours({
        {0,{255,77,0}},
        {1,{255,116,0}},
        {2,{255,154,0}},
        {3,{255,193,0}}
        })
{
    shape.setFillColor(colours[randomColour]);
}
void fire::gravity(int grid[75][75]) {
    return;
}
void fire::update(int grid[75][75]) {
    if (lifetime > 0) {
        lifetime--;
    }
}
int fire::transformTo() {
    if (lifetime <= 0) return 0;
    return -1;
}