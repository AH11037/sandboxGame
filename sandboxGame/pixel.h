#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics.hpp>

class pixel {
public:
    float length = 10.f;
    sf::RectangleShape shape;
    int randomColour = rand() % 4;
    int type;
    sf::Vector2i coordinates;

    pixel(sf::Vector2f positions, int type);
    virtual ~pixel() = default;

    void addGrid(int grid[75][75]);
    virtual void gravity(int grid[75][75]) = 0;
    virtual void drawPixel(sf::RenderWindow& window);
    virtual int transformTo() { return -1; };
    virtual void update(int grid[75][75]) {gravity(grid); }
};
class empty : public pixel {
public:
    empty(sf::Vector2f pos) : pixel(pos, 0) {}

    void update(int grid[75][75]) override {}
    int transformTo() override { return -1; }
    void gravity(int grid[75][75]) override {}
    void drawPixel(sf::RenderWindow& window) override {}
};

#endif
