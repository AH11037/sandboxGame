#ifndef FIRE_H
#define FIRE_H

#include "pixel.h"
#include <map>

class fire : public pixel {
public:
    fire(sf::Vector2f positions);
    void gravity(int grid[75][75]);
    void update(int grid[75][75]);
    int transformTo() override;
private:
    std::map<int, sf::Color> colours;
    int lifetime;
};

#endif