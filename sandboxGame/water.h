#ifndef WATER_H
#define WATER_H

#include "Pixel.h"
#include "Physics.h"
#include <map>

class water : public pixel, public liquid {
public:
    water(sf::Vector2f positions);
    void gravity(int grid[75][75]) override;

private:
    std::map<int, sf::Color> colours;
};

#endif
