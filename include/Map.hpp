
#ifndef MAP
    #define MAP
    #include <SFML/Graphics.hpp>
    #include <SFML/Graphics/RectangleShape.hpp>
    #include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
    #include <string>
    #include <vector>
    #include <wolf.hpp>

class Map {
    protected:
        sf::RenderWindow& window;
        std::vector<std::string> vec_map;
        std::vector<sf::RectangleShape> vec_wall;

    public:
        Map(sf::RenderWindow& window, const char *path);
        void draw();
        bool check_ray_intersect(sf::Vector2i pos);
};

#endif
