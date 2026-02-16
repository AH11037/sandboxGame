#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "dirt.h"
#include "water.h"
#include "smoke.h"
#include "gunpowder.h"
#include "fire.h"
#include "atari-800.hpp"
#include <Windows.h>

std::unique_ptr<pixel> createPixel(int type, sf::Vector2f pos) {
    switch (type) {
    case 0: return std::make_unique<empty>(pos);
    case 1: return std::make_unique<dirt>(pos);
    case 2: return std::make_unique<water>(pos);
    case 3: return std::make_unique<smoke>(pos);
    case 4: return std::make_unique<gunpowder>(pos);
    case 5: return std::make_unique<fire>(pos);
    default: return nullptr;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::Font font;

    if (!font.openFromMemory(atari_800, atari_800_len)) {
        return -1;
    }

    sf::Vector2f positions = sf::Vector2f(10.f, 10.f);
    int grid[75][75] = {};
    std::vector<std::unique_ptr<pixel>> pixels;
    int x = 0;
    std::map<int, sf::Color> colours = { {0, {255,255,255}}, { 1, { 102, 51, 0 } } , {2, { 0, 102, 255 }}, {3, {58,56,64}} ,{4, {0,204,51}}, {5, {255,116,0}} };
    std::string names[6] = { "Blank (^_^;)","Dirt", "Water", "Smoke", "Gunpowder", "Fire" };
    sf::RenderWindow window(sf::VideoMode({ 750, 750 }), "Sandbox", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        window.setFramerateLimit(60);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::Space) {
                    x = (x < 5) ? x + 1 : 0;
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            positions = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            int xIndex = std::clamp(static_cast<int>(std::round(positions.x / 10)), 0, 74);
            int yIndex = std::clamp(static_cast<int>(std::round(positions.y / 10)), 0, 74);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int newX = std::clamp(xIndex + j, 0, 74);
                        int newY = std::clamp(yIndex + i, 0, 74);
                        if (grid[newX][newY] == 0) {
                            positions = sf::Vector2f(newX * 10, newY * 10);
                            auto ptr = createPixel(x, positions);
                            if (ptr) {
                                ptr->addGrid(grid);
                                pixels.push_back(std::move(ptr));
                            }
                        }
                    }
                }
            }
            else {
                if (grid[xIndex][yIndex] == 0) {
                    auto ptr = createPixel(x, positions);
                    if (ptr) {
                        ptr->addGrid(grid);
                        pixels.push_back(std::move(ptr));
                    }
                }
            }
        }
        window.clear();

        for (size_t i = 0; i < pixels.size(); i++) {
            auto& p = pixels[i];
            p->update(grid);
            int newType = p->transformTo();
            if (newType != -1) {
                sf::Vector2f pos = p->shape.getPosition();
                int oldX = p->coordinates.x;
                int oldY = p->coordinates.y;
                grid[oldX][oldY] = 0;
                pixels[i] = createPixel(newType, pos);
                pixels[i]->coordinates = sf::Vector2i(oldX, oldY);
                grid[oldX][oldY] = pixels[i]->type;
            }
            pixels[i]->drawPixel(window);
        }
        sf::Text text(font, names[x], 30);
        text.setPosition({ 50.f, 50.f });
        text.setFillColor(colours[x]);
        window.draw(text);
        window.display();
    }
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main();
}