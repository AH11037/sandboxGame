#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "atari-800.hpp"
#include <Windows.h>
#include "resource.h"
#include "physics.h"
#define SFML_NO_CONSOLE
#include "globals.h"

void update(std::vector<std::vector<std::vector<int>>>& grid, std::vector<std::vector<bool>> moved) {
    for (int j = gridSize - 1; j >= 0; j--) {
        for (int i = 0; i < gridSize; i++) {
            if (grid[i][j][0] == 0) continue;
            int type = grid[i][j][0];

            if (grid[i][j][2] > 0) grid[i][j][2]--;
            if (grid[i][j][2] == 0) {
                grid[i][j][0] = 0;
                grid[i][j][1] = 0;
                grid[i][j][2] = -1;
                continue;
            }

            if (type == 5) {
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x == 0 && y == 0) continue;
                        int checkX = i + x;
                        int checkY = j + y;
                        if (checkX < 0 || checkX >= gridSize || checkY < 0 || checkY >= gridSize) continue;
                        if (grid[checkX][checkY][3] > 0) {
                            grid[checkX][checkY][0] = 5;
                            grid[checkX][checkY][1] = 1;
                            grid[checkX][checkY][2] = 4;
                            grid[checkX][checkY][3] = -1;
                        }
                    }
            }
            }
            int fluid = (type == 2 || type == 3) ? 1 : 0;
            int grav = (type == 3) ? -1 : 1;
            if (type != 5) gravityClass::gravity(grid, sf::Vector2i(i, j), grav, fluid, moved);
        }
    }
}

void placeParticle(std::vector<std::vector<std::vector<int>>>& grid, int xIndex, int yIndex, int type,int density) {
    if (grid[xIndex][yIndex][0] == 0) {
        grid[xIndex][yIndex][0] = type;
        grid[xIndex][yIndex][1] = density;
        grid[xIndex][yIndex][2] = (type == 5) ? 4 : -1;
        grid[xIndex][yIndex][3] = (type == 4) ? 1 : -1;
        grid[xIndex][yIndex][4] = rand() % 4;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::Font font;
    if (!font.openFromMemory(atari_800, atari_800_len)) return -1;

    sf::Vector2f positions = sf::Vector2f(10.f, 10.f);
    int x = 1;

    std::vector<std::vector<bool>> moved(gridSize, std::vector<bool>(gridSize, false));
    std::vector<std::vector<std::vector<int>>> grid(gridSize, std::vector<std::vector<int>>(gridSize, std::vector<int>{0, 0, -1, 0, 0}));

    std::vector<std::array<sf::Color, 4>> colours = {
        {sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black},
        {sf::Color(102, 51, 0), sf::Color(139, 69, 19), sf::Color(120, 60, 10), sf::Color(90, 45, 5)}, // Dirt
        {sf::Color(0, 102, 255), sf::Color(51, 153, 255), sf::Color(0, 128, 200), sf::Color(30, 144, 255)}, //Water
        {sf::Color(128, 128, 128, 180), sf::Color(169, 169, 169, 180), sf::Color(105, 105, 105, 180), sf::Color(192, 192, 192, 180)}, //Smoke
        {sf::Color(0, 200, 0), sf::Color(0, 255, 0), sf::Color(0, 180, 0), sf::Color(50, 255, 50)}, //Gunpowder
        {sf::Color(255, 140, 0), sf::Color(255, 69, 0), sf::Color(255, 255, 0), sf::Color(255, 255, 200)} //Fire
    };

    std::string names[] = { "Dirt", "Water", "Smoke", "Gunpowder", "Fire" };
    int densities[] = { 4, 3, 2, 5, 1 };
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(width, height)), "Sandbox", sf::Style::Titlebar | sf::Style::Close);


    sf::VertexArray bigGrid(sf::PrimitiveType::Triangles, 75 * 75 * 6);
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int index = (i + j * gridSize) * 6;
            int type = grid[i][j][0];
            float x = i * squareSize;
            float y = j * squareSize;
            //Triangle uno
            bigGrid[index + 0].position = { x, y };
            bigGrid[index + 1].position = { x + squareSize, y };
            bigGrid[index + 2].position = { x + squareSize, y + squareSize };
            //Triangle 2
            bigGrid[index + 3].position = { x, y };
            bigGrid[index + 4].position = { x + squareSize, y + squareSize };
            bigGrid[index + 5].position = { x, y + squareSize };

            for (int k = 0; k < 6; k++) bigGrid[index + k].color = sf::Color::Black;
        }
    }

    while (window.isOpen()) {
        window.setFramerateLimit(60);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::Space) x = (x < 5) ? x + 1 : 1;

                switch (key->code) {
                case sf::Keyboard::Key::Num1: x = 1; break;
                case sf::Keyboard::Key::Num2: x = 2; break;
                case sf::Keyboard::Key::Num3: x = 3; break;
                case sf::Keyboard::Key::Num4: x = 4; break;
                case sf::Keyboard::Key::Num5: x = 5; break;
                default: break;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            positions = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            int xIndex = std::clamp(static_cast<int>(positions.x / squareSize), 0, gridSize - 1);
            int yIndex = std::clamp(static_cast<int>(positions.y / squareSize), 0, gridSize - 1);
            int bound = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) bound = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ? 2 : 1;
            for (int i = -bound; i <= bound; ++i) for (int j = -bound; j <= bound; ++j) placeParticle(grid, std::clamp(xIndex + i, 0, gridSize - 1), std::clamp(yIndex + j, 0, gridSize - 1), x, densities[x - 1]);
    }

        window.clear();
        update(grid, moved);

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                int type = grid[i][j][0];
                int index = (i + j * gridSize) * 6;
                const auto& palette = colours[type];
                sf::Color chosenColour = palette[grid[i][j][4] % 4];
                for (int k = 0; k < 6; k++) bigGrid[index + k].color = chosenColour;
            }
        }
        window.draw(bigGrid);
        sf::Text text(font, names[x - 1], 30);
        text.setPosition({ 50.f, 50.f });
        text.setFillColor(colours[x][0]);
        window.draw(text);
        window.display();
    }
}
