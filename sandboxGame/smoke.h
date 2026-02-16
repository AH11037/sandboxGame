#ifndef SMOKE_H
#define SMOKE_H

#include "Pixel.h"
#include "Physics.h"
#include <map>

class smoke : public pixel, public gas {
public:
    smoke(sf::Vector2f positions);
    void gravity(int grid[75][75]) override;

private:
    std::map<int, sf::Color> colours;
};

#endif
