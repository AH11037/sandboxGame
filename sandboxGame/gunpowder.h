#ifndef GUNPOWDER_H
#define GUNPOWDER_H

#include <map>
#include "Physics.h"
#include "pixel.h"

class gunpowder : public pixel, public solid {
public:
    gunpowder(sf::Vector2f positions);
    void gravity(int grid[75][75]) override;
    void flameCheck(int grid[75][75]);
    void update(int grid[75][75]);
    bool burning = false;
    int transformTo() override;

private:
    std::map<int, sf::Color> colours{
        {0,{0,103,26}},
        {1,{4,161,43}},
        {2,{0,204,51}},
        {3,{11,244,70}}
    };
    std::map<int, sf::Color> burningColors{
        {0,{255,77,0}},
        {1,{255,116,0}},
        {2,{255,154,0}},
        {3,{255,193,0}}
    };
    int lifetime;
};

#endif
