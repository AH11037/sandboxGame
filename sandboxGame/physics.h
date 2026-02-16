#ifndef PHYSICS_H
#define PHYSICS_H
#include <SFML/Graphics.hpp>

class solid {
public:
    void gravity(int grid[75][75], sf::RectangleShape& shape, int type, sf::Vector2i& coordinates);
};

class liquid {
public:
    void gravity(int grid[75][75], sf::RectangleShape& shape, int type, sf::Vector2i& coordinates);
};

class gas {
public:
    void gravity(int grid[75][75], sf::RectangleShape& shape, int type, sf::Vector2i& coordinates);
};

#endif
