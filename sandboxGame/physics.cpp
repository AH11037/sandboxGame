#include <SFML/Graphics.hpp>
#include "physics.h"

void solid::gravity(int grid[75][75], sf::RectangleShape& shape, int type, sf::Vector2i& coordinates) {

    if (coordinates.x < 0 || coordinates.x >= 75 || coordinates.y < 0 || coordinates.y >= 75) return;

    if (coordinates.y + 1 < 75 && (grid[coordinates.x][coordinates.y + 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y += 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    else if (coordinates.y + 1 < 75 && coordinates.x - 1 >= 0 && (grid[coordinates.x - 1][coordinates.y + 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y += 1;
        coordinates.x -= 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    else if (coordinates.y + 1 < 75 && coordinates.x + 1 < 75 && (grid[coordinates.x + 1][coordinates.y + 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y += 1;
        coordinates.x += 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
}

void liquid::gravity(int grid[75][75], sf::RectangleShape& shape, int type, sf::Vector2i& coordinates) {
    if (coordinates.x < 0 || coordinates.x >= 75 || coordinates.y < 0 || coordinates.y >= 75) return;
    if (coordinates.y + 1 < 75 && (grid[coordinates.x][coordinates.y + 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y += 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    else if (coordinates.y + 1 < 75 && coordinates.x - 1 >= 0 && (grid[coordinates.x - 1][coordinates.y + 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y += 1;
        coordinates.x -= 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    else if (coordinates.y + 1 < 75 && coordinates.x + 1 < 75 && (grid[coordinates.x + 1][coordinates.y + 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y += 1;
        coordinates.x += 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    int randNum = rand() % 2;
    if (randNum == 0) {
        if (coordinates.x - 1 >= 0 && (grid[coordinates.x - 1][coordinates.y] == 0)) {
            grid[coordinates.x][coordinates.y] = 0;
            coordinates.x -= 1;
            shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
            grid[coordinates.x][coordinates.y] = type;
            return;
        }
        return;
    }
    else {
        if (coordinates.x + 1 < 75 && (grid[coordinates.x + 1][coordinates.y] == 0)) {
            grid[coordinates.x][coordinates.y] = 0;
            coordinates.x += 1;
            shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
            grid[coordinates.x][coordinates.y] = type;
            return;
        }
    return;
    }
}
void gas::gravity(int grid[75][75], sf::RectangleShape& shape, int type, sf::Vector2i& coordinates) {
    if (coordinates.x < 0 || coordinates.x >= 75 || coordinates.y < 0 || coordinates.y >= 75) return;
    if (coordinates.y - 1 >= 0 && (grid[coordinates.x][coordinates.y - 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y -= 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    else if (coordinates.y - 1 >= 0 && coordinates.x - 1 >= 0 && (grid[coordinates.x - 1][coordinates.y - 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y -= 1;
        coordinates.x -= 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    else if (coordinates.y - 1 >= 0 && coordinates.x + 1 < 75 && (grid[coordinates.x + 1][coordinates.y - 1] == 0)) {
        grid[coordinates.x][coordinates.y] = 0;
        coordinates.y -= 1;
        coordinates.x += 1;
        shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
        grid[coordinates.x][coordinates.y] = type;
        return;
    }
    int randNum = rand() % 2;
    if (randNum == 0) {
        if (coordinates.x - 1 >= 0 && (grid[coordinates.x - 1][coordinates.y] == 0)) {
            grid[coordinates.x][coordinates.y] = 0;
            coordinates.x -= 1;
            shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
            grid[coordinates.x][coordinates.y] = type;
            return;
        }
        return;
    }
    else {
        if (coordinates.x + 1 < 75 && (grid[coordinates.x + 1][coordinates.y] == 0)) {
            grid[coordinates.x][coordinates.y] = 0;
            coordinates.x += 1;
            shape.setPosition(sf::Vector2f(coordinates.x * 10, coordinates.y * 10.f));
            grid[coordinates.x][coordinates.y] = type;
            return;
        }
        return;
    }
}