#include "pixel.h"

pixel::pixel(sf::Vector2f positions, int type)
{
    shape.setSize({ length, length });
    shape.setFillColor(sf::Color::Red);
    this->coordinates = sf::Vector2i(positions.x / 10.f, positions.y / 10.f);
    shape.setPosition(positions);
    this->type = type;
}

void pixel::addGrid(int grid[75][75]) {
    if (coordinates.x >= 0 && coordinates.x < 75 && coordinates.y >= 0 && coordinates.y < 75) {
        if (!grid[coordinates.x][coordinates.y]) grid[coordinates.x][coordinates.y] = type;
    }
}

void pixel::drawPixel(sf::RenderWindow& window) {
    if (type == 0) return;
    window.draw(shape);
}
