
#include "Map.hpp"
#include "wolf.hpp"
#include <Player.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include <sys/types.h>

using namespace sf;

Player::Player(Map& map) : sf::CircleShape(10, 10), map(map) {

    setOrigin(10, 10);
    setFillColor(sf::Color::White);
    setPosition(100, 100);

    for (int i = 0; i < WIDTH_SCREEN; i++) {
        sf::VertexArray ray(sf::Lines, 2);
        ray[0].color = sf::Color::Red;
        ray[1].color = sf::Color::Red;
        vec_ray.push_back(ray);
    }
}

void Player::update(float delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotation += SENSIVITY * delta_time;
        rad_rotation = TO_RAD(rotation);
        direction = {
            cosf(rad_rotation) * SPEED,
            sinf(rad_rotation) * SPEED
        };
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotation -= SENSIVITY * delta_time;
        rad_rotation = TO_RAD(rotation);
        direction = {
            cosf(rad_rotation) * SPEED,
            sinf(rad_rotation) * SPEED
        };
    }
    // TODO: handle colision to block move
    sf::Vector2f new_pos = sf::Vector2f {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        new_pos = direction * delta_time;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        new_pos = direction * -delta_time;
    }
    move(new_pos);
    position = getPosition();
    if (rotation < 0) {
        rotation = 360;
    } else if (rotation > 360) {
        rotation = 0;
    }
}


void Player::draw(sf::RenderWindow& window, float delta_time)
{
    update(delta_time);
    float step_rad = 0;
    float used_rot = rotation - FOV / 2;
    sf::Vector2f side = { 0, 0 };
    sf::Vector2i step_dir = { 0, 0 };
    sf::Vector2i map_pos = {
        int(position.x),
        int(position.y)
    };
    sf::Vector2f direction = {0, 0};

    /// UPDATE AND DRAW RAY
    for (int i = 0; i < WIDTH_SCREEN; i++) {
        vec_ray[i][0].position = position;
        step_rad = TO_RAD(used_rot + i * step);
        direction = {
            cosf(step_rad),
            sinf(step_rad)
        };
        map_pos = {(int) position.x, (int)position.y};
        sf::Vector2f delta_dist {
           (direction.x == 0) ? 1e30f : std::abs(1 / direction.x),
           (direction.y == 0) ? 1e30f : std::abs(1 / direction.y)
        };
        // more info about this code ??? -> https://lodev.org/cgtutor/raycasting.html <- its amazing !
        if (direction.x < 0) {
            step_dir.x = -1;
            side.x = (position.x - map_pos.x) * delta_dist.x;
        } else {
            step_dir.x = 1;
            side.x = (map_pos.x + 1.0 - position.x) * delta_dist.x;
        } if (direction.y < 0) {
            step_dir.y = -1;
            side.y = (position.y - map_pos.y) * delta_dist.y;
        } else {
            step_dir.y = 1;
            side.y = (map_pos.y + 1.0 - position.y) * delta_dist.y;
        }
        while (!map.check_ray_intersect(map_pos)) {
            if (side.x < side.y) {
                side.x += delta_dist.x;
                map_pos.x += step_dir.x;
            } else {
                side.y += delta_dist.y;
                map_pos.y += step_dir.y;
            }
        }
        vec_ray[i][1].position = {
            (float) map_pos.x,
            (float) map_pos.y
        };
        window.draw(vec_ray[i]);
    }
    window.draw(*static_cast<sf::CircleShape*>(this));
}
