

#ifndef __PLAYER_H__
    #define __PLAYER_H__
    #include "Map.hpp"
    #include "wolf.hpp"
    #include <SFML/Graphics/CircleShape.hpp>
    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Graphics/VertexArray.hpp>
    #include <SFML/System/Vector2.hpp>
    #include <SFML/Window/Event.hpp>
    #include <vector>
    #define SPEED 300
    #define SENSIVITY 200

class Player : public sf::CircleShape {
    protected:
        Map& map;
        std::vector<sf::VertexArray> vec_ray;
        float rotation = 360;
        float rad_rotation = TO_RAD(rotation);
        sf::Vector2f position;
        sf::Vector2f direction = {
            cosf(rad_rotation) * SPEED,
            sinf(rad_rotation) * SPEED
        };
        float step = FOV / WIDTH_SCREEN;
        void update_ray_pos(sf::VertexArray& ray, int index, int len);

    public:
        void update(float delta_time);
        void draw(sf::RenderWindow& window, float delta_time);
        Player(Map& map);
};

#endif
