
#ifndef WOLF
    #define WOLF
    #include <math.h>
    #define PI = 3.1415f
    #define BLOCK_SIZE 32
    #define WIDTH_SCREEN 1920
    #define HEIGHT_SCREEN 720
    #define FOV 60.0
    #define TO_RAD(x) (0.017453292f * (x))
    #define TO_DEG(x) ((x) * 57.295779513f)
    #define D_COS(x) cos(TO_RAD(x))
    #define D_SIN(x) sin(TO_RAD(x))
    #include <SFML/Graphics.hpp>

void handle_event(sf::RenderWindow& window, sf::Event& event);

#endif
