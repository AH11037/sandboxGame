#ifndef DIRT_H
#define DIRT_H

#include "Pixel.h"
#include "Physics.h"
#include <map>

class dirt : public pixel, public solid {
public:
    dirt(sf::Vector2f positions);
    void gravity(int grid[75][75]) override;

private:
    std::map<int, sf::Color> colours;
};

#endif
