
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdlib>
#include <wolf.hpp>
#include <Camera.hpp>
#include <Map.hpp>

int main(void)
{
    sf::RenderWindow window(
        sf::VideoMode(1280, HEIGHT_SCREEN),
        "game",
        sf::Style::Default
    );
    Map map(window, "map");
    Player player(map);
    sf::Event event;
    sf::Clock clock;
    float delta_time = 0;

    window.setFramerateLimit(120);
    while (window.isOpen()) {
        handle_event(window, event);
        delta_time = clock.restart().asSeconds();
        window.clear();
        player.draw(window, delta_time);
        map.draw();
        window.display();
    }
}
