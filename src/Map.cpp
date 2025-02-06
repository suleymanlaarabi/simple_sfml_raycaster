
#include "wolf.hpp"
#include <Map.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <fstream>
#include <string>

Map::Map(sf::RenderWindow& window, const char *path) : window(window)
{
    std::ifstream file(path);

    int y = 0;
    int x = 0;
    if (file.is_open()) {
        for (std::string line; std::getline(file, line);) {
            vec_map.push_back(line);
            for (char c : line) {
                if (c == '1') {
                    sf::RectangleShape wall(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    wall.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                    wall.setFillColor(sf::Color::White);
                    vec_wall.push_back(wall);
                }
                x++;
            }
            y++;
            x = 0;
        }
    }
}

bool Map::check_ray_intersect(sf::Vector2i pos)
{
    if (vec_map[pos.y / BLOCK_SIZE][pos.x / BLOCK_SIZE] == '1') {
        return true;
    }
    return false;
}

void Map::draw()
{
    for (auto& wall: vec_wall) {
        window.draw(wall);
    }
}
