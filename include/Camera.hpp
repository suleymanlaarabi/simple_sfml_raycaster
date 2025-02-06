#ifndef MY_CAMERA
    #define MY_CAMERA
    #include <Map.hpp>
    #include <SFML/Graphics/CircleShape.hpp>
    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Graphics/VertexArray.hpp>
    #include <SFML/System/Clock.hpp>
    #include <SFML/System/Time.hpp>
    #include <SFML/System/Vector2.hpp>
    #include <vector>
    #define CAMERA_SHAPE_RADIUS 5

class Camera {
    protected:
        sf::RenderWindow& window;
        sf::CircleShape camera_shape;
        sf::Clock clock;
        sf::Vector2f current_intersect;
        Map& map;

        float angle, fov, ray_length, step, fov_divid_2;
        float speed, speed_angle;

        std::vector<sf::VertexArray> vec_rays;
    public:
        Camera(sf::RenderWindow& window, Map& map);
        void draw();
        void update();
        void project();
        void check_keyboard_hit(sf::Time dt);
        bool intersect(unsigned int it, sf::Vector2f direction);
};

#endif
