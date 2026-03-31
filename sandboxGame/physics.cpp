#include <SFML/Graphics.hpp>
#include "physics.h"
#include "globals.h"

void gravityClass::gravity(std::vector<std::vector<std::vector<int>>>& grid, sf::Vector2i coordinates, int grav, int state, std::vector<std::vector<bool>>& moved) {
    int x = coordinates.x;
    int y = coordinates.y;

    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) return;
    if (state == 2) return;
    if (moved[x][y]) return;
    if (grid[x][y][0] == 0) return;

    // Down or up
    if (y + grav >= 0 && y + grav < gridSize) {
        if (grid[x][y + grav][0] == 0 || grid[x][y][1] > grid[x][y + grav][1]) {
            std::swap(grid[x][y], grid[x][y + grav]);
            moved[x][y + grav] = true;
            return;
        }
    }

    // Down-left or up-left
    if (x - 1 >= 0 && y + grav >= 0 && y + grav < gridSize) {
        if (grid[x - 1][y + grav][0] == 0 || grid[x][y][1] > grid[x - 1][y + grav][1]) {
            std::swap(grid[x][y], grid[x - 1][y + grav]);
            moved[x - 1][y + grav] = true;
            return;
        }
    }

    // Down-right or up-right
    if (x + 1 < gridSize && y + grav >= 0 && y + grav < gridSize) {
        if (grid[x + 1][y + grav][0] == 0 || grid[x][y][1] > grid[x + 1][y + grav][1]) {
            std::swap(grid[x][y], grid[x + 1][y + grav]);
            moved[x + 1][y + grav] = true;
            return;
        }
    }

    if (state) {
        int randNum = rand() % 2;

        // Left
        if (randNum == 0 && x - 1 >= 0) {
            if (grid[x - 1][y][0] == 0 || grid[x][y][1] > grid[x - 1][y][1]) {
                std::swap(grid[x][y], grid[x - 1][y]);
                moved[x - 1][y] = true;
                return;
            }
        }

        // Right
        else if (randNum == 1 && x + 1 < gridSize) {
            if (grid[x + 1][y][0] == 0 || grid[x][y][1] > grid[x + 1][y][1]) {
                std::swap(grid[x][y], grid[x + 1][y]);
                moved[x + 1][y] = true;
                return;
            }
        }
    }
    moved[x][y] = true;
}