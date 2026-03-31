#ifndef PHYSICS_H
#define PHYSICS_H
#include <SFML/Graphics.hpp>

class gravityClass {
public:
    static void gravity(std::vector<std::vector<std::vector<int>>>& grid, sf::Vector2i coordinates, int gravity, int state, std::vector<std::vector<bool>>& moved);
};

#endif
